#ifndef GAME_H
#define GAME_H

#include "Button.h"
#include <vector>

const int STRIPES_NUMBER = 5;
const int SQUARES_NUMBER = 3;
const int MIN_SPEED = 9;
const int MAX_SPEED = 20;
const int MS_PER_FRAME = 1000 / 45;
const int OFFSET_EPS = 20;
const int BUTTON_WIDTH = 150;

struct Line
{
    int square;
    int stripe0;
    int stripe1;
};

class GameClass
{
    Button* startButton;
    Button* stopButton;

    std::vector<std::string> items;
    std::vector<Line> lines;  // lines to draw

    int stripeWidth;
    float scaleFactorY;

    float offsets[STRIPES_NUMBER];   // graphical stripes' y offset
    float stripesSpeeds[STRIPES_NUMBER];
    
    int stripes[STRIPES_NUMBER][SQUARES_NUMBER + 1];  // current visible squares

    bool stopping;
    bool stopped;

    int stripeHeight;
    int gameTime;
    int startTimer;

public:
    GameClass();
    virtual ~GameClass();
    void run() const;

    void startGame();
    void stopGame();

private:
    static void mouseEvent(int button, int state, int x, int y);
    void mousePress(int x, int y);

    static void renderStatic();
    void render();
    static void updateStatic();
    void update();
    void calculateResult();

    void renderUi() const;
    void renderStripes(int stripeWidth,
                       float scaleFactorX,
                       float scaleFactorY) const;
};

typedef Singleton<GameClass> Game;

#endif
