#include <GL/glut.h>
#include "Graphics.h"
#include "Game.h"
#include "Util.h"
#include <cmath>
//#include <iostream>

extern "C" {
    #include <unistd.h>
}

GameClass::GameClass()
{
    glutDisplayFunc(renderStatic);
    glutIdleFunc(updateStatic);
    glutMouseFunc(mouseEvent);

    int stripeWidth = 0;
    float scaleFactor = 0.0f;

    gameTime = 0;
    startTimer = 0;

    stopping = false;
    stopped = true;
    stripeHeight = 0;

    startButton = new Button(0, 0, BUTTON_WIDTH, BUTTON_WIDTH / 3, "start.tga");
    stopButton = new Button(0, 0, BUTTON_WIDTH, BUTTON_WIDTH / 3, "stop.tga");

    stopButton->setEnabled(false);

    items.push_back("vim.tga");
    items.push_back("gentoo.tga");
    items.push_back("debian.tga");

    for (int i = 0; i < STRIPES_NUMBER; ++i) {
        for (int j = 0; j < SQUARES_NUMBER + 1; ++j)
            stripes[i][j] = rand() % items.size();
        offsets[i] = 0.0f;
        stripesSpeeds[i] = 0.0f;
    }
}

GameClass::~GameClass()
{
    delete startButton;
    delete stopButton;
}

void GameClass::renderStatic()
{
    Game::getInstance().render();
}

void GameClass::render()
{
    int timeStart = glutGet(GLUT_ELAPSED_TIME);

    Graphics::beginFrame();
    Graphics::drawTexture("background.tga",
                          0, 0,
                          Graphics::screenWidth(), Graphics::screenHeight());
  
    int stripeX = (Graphics::screenWidth() / 3) / 2;
    int stripeY = Graphics::screenHeight() / 5;
    stripeWidth = (Graphics::screenWidth() - Graphics::screenWidth() / 3) / STRIPES_NUMBER;
    int stripeHeight = stripeWidth * SQUARES_NUMBER;

    float scaleFactorX = ((float)Graphics::screenWidth() / (float)(stripeWidth * STRIPES_NUMBER));
    scaleFactorY = ((float)Graphics::screenHeight() / (float)(stripeHeight));
    Graphics::setClip(stripeX, stripeY, stripeWidth * STRIPES_NUMBER, stripeHeight);
    Game::getInstance().renderStripes(stripeWidth, scaleFactorX, scaleFactorY);
    Graphics::resetClip();

    Game::getInstance().renderUi();
    Graphics::endFrame();

    // sync rendering
    while ((glutGet(GLUT_ELAPSED_TIME) - timeStart) < MS_PER_FRAME)
    {
        int pause = (int)(MS_PER_FRAME - (glutGet(GLUT_ELAPSED_TIME) - timeStart));
        if (pause < 0)
            break;
        usleep(pause);
    }
}

void GameClass::renderUi() const
{
    startButton->setCoords(
        Graphics::screenWidth() / 10,
        Graphics::screenHeight() / 10
    );
    stopButton->setCoords(
        Graphics::screenWidth() - Graphics::screenWidth() / 10 - BUTTON_WIDTH,
        Graphics::screenHeight() / 10
    );
    startButton->render();
    stopButton->render();
}

void GameClass::renderStripes(int stripeWidth, float scaleFactorX, float scaleFactorY) const
{
    int stripeHeight = stripeWidth * SQUARES_NUMBER;

    for (int i = 0; i < STRIPES_NUMBER; ++i)
    {
        Graphics::drawTexture("stripe.tga",
                              i * stripeWidth * scaleFactorX,
                              0,
                              stripeWidth * scaleFactorX,
                              stripeHeight * scaleFactorY);
    }

    for (int i = 0; i < STRIPES_NUMBER; ++i)
        for (int j = 0; j < SQUARES_NUMBER + 1; ++j)
            Graphics::drawTexture(
                items[stripes[i][SQUARES_NUMBER - j]].c_str(),
                i * stripeWidth * scaleFactorX,
                (j + 1) * stripeWidth * scaleFactorY + (int)offsets[i] - stripeWidth * scaleFactorY,
                stripeWidth * scaleFactorX,
                stripeWidth * scaleFactorY
            );

    for (std::vector<Line>::const_iterator it = lines.begin();
         it != lines.end();
         ++it)
    {
        // TODO: render lines
    }
}

void GameClass::updateStatic()
{
    Game::getInstance().update();
}

void GameClass::update()
{
    static int stopTimer = 0;

    if (stopping)
    {
        stopTimer += MS_PER_FRAME;

        for (int i = 0; i < STRIPES_NUMBER; ++i)
        {
            if (stripesSpeeds[i] > 0.0f)
            {
                if (stopTimer >= 300 &&
                    abs((int)offsets[i]) < OFFSET_EPS)
                {
                    stripesSpeeds[i] = 0.0f;
                    stopTimer = 0;
                }

                break;
            } else if (i == STRIPES_NUMBER - 1 && stopping) {
                // everything's been stopped
                stopping = false;
                stopped = true;
                startButton->setEnabled(true);
                calculateResult();
            }
        }
    } else {
        startTimer += MS_PER_FRAME;
        if (!stopped && startTimer >= gameTime)
            stopGame();
    }

    // updating stripes
    stripeHeight = stripeWidth * scaleFactorY;
    for (int i = 0; i < STRIPES_NUMBER; ++i)
    {
        offsets[i] -= stripesSpeeds[i];
        if (offsets[i] < -stripeHeight)
        {
            offsets[i] += stripeHeight;
            for (int j = SQUARES_NUMBER; j >= 1; --j)
                stripes[i][j] = stripes[i][j - 1];
            stripes[i][0] = rand() % items.size();
        }
    }

    Graphics::redraw();
}

void GameClass::calculateResult()
{
    int field[STRIPES_NUMBER][SQUARES_NUMBER];
    for (int i = 0; i < STRIPES_NUMBER; ++i)
    {
        int k = 0;
        int offset = 0;

        offset = (int)(offsets[i] / (stripeWidth * scaleFactorY));

        for (int j = 0; j < SQUARES_NUMBER; ++j)
            field[i][j] = stripes[i][j + offset];
    }

    /*std::cout << std::endl;
    for (int j = 0; j < SQUARES_NUMBER; ++j)
    {
        for (int i = 0; i < STRIPES_NUMBER; ++i)
        {
            std::cout << field[i][j] << ' ';
        }
        std::cout << std::endl;
    }*/

    for (int j = 0; j < SQUARES_NUMBER; ++j)
    {
        int match = 0;  // index of last matched object
        for (int i = 1; i < STRIPES_NUMBER; ++i)
        {
            if (field[i][j] != field[match][j] || i == STRIPES_NUMBER - 1)
            {
                if (i == STRIPES_NUMBER - 1 && field[i][j] == field[match][j])
                    ++i;
                if (i - match >= 3)
                {
                    Line line;
                    line.square = SQUARES_NUMBER - j - 1;
                    line.stripe0 = match;
                    line.stripe1 = i - 1;
                    lines.push_back(line);
                }
                match = i;
            }
        }
    }
}

void GameClass::run() const
{
    glutMainLoop();
}

void GameClass::mouseEvent(int button, int state, int x, int y)
{
    if (state == 0)
        Game::getInstance().mousePress(x, Graphics::screenHeight() - y);
}

void GameClass::mousePress(int x, int y)
{
    if (startButton->getEnabled() && Util::pointInRect(x, y, startButton))
        startGame();
    else if (stopButton->getEnabled() && Util::pointInRect(x, y, stopButton)) 
        stopGame();

    Graphics::redraw();
}

void GameClass::startGame()
{
    stopping = false;
    stopped = false;
    startTimer = 0;
    gameTime = 4000 + rand() % 1000;

    lines.clear();

    startButton->setEnabled(false);
    stopButton->setEnabled(true);

    // randomizing stripes' speeds
    for (int i = 0; i < STRIPES_NUMBER; ++i)
    {
        do
            stripesSpeeds[i] = MIN_SPEED + rand() % (MAX_SPEED - MIN_SPEED + 1);
        while (i > 0 && std::abs(stripesSpeeds[i] - stripesSpeeds[i - 1]) < 3);
    }
}

void GameClass::stopGame()
{
    stopButton->setEnabled(false);

    // run stop timer
    stopping = true;
}
