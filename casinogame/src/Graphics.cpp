#include "Graphics.h"
#include "ResourceManager.h"

Graphics::Graphics(int* argc, char* argv[], const char* windowName)
{
    glutInit(argc, argv);
    glutCreateWindow(windowName);
    glutReshapeWindow(800, 600);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
}

Graphics::~Graphics()
{
}

void Graphics::beginFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH),
            0.0, glutGet(GLUT_WINDOW_HEIGHT),
            -1.0,
            1.0);
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
}

void Graphics::endFrame()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();
}

void Graphics::drawTexture(const char* textureName, int x, int y, int width, int height)
{
    const Texture* texture = ResourceManager::getInstance().getTexture(textureName);

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, 0.0f);

    glBindTexture(GL_TEXTURE_2D, texture->id);

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
    glTexCoord2f(0, 1); glVertex3f(0, height, 0);
    glTexCoord2f(1, 1); glVertex3f(width, height, 0);
    glTexCoord2f(1, 0); glVertex3f(width, 0, 0);

    glEnd();

    glPopMatrix();
}

void Graphics::drawTexture(const char* textureName, int x, int y, int width, int height, int frame, int frames)
{
    const Texture* texture = ResourceManager::getInstance().getTexture(textureName);

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, 0.0f);

    glBindTexture(GL_TEXTURE_2D, texture->id);

    glBegin(GL_QUADS);

    float h0 = (float)frame / (float)frames;
    float h1 = ((float)frame + 1) / (float)frames;

    glTexCoord2f(0, h0); glVertex3f(0, 0, 0);
    glTexCoord2f(0, h1); glVertex3f(0, height, 0);
    glTexCoord2f(1, h1); glVertex3f(width, height, 0);
    glTexCoord2f(1, h0); glVertex3f(width, 0, 0);

    glEnd();

    glPopMatrix();
}

void Graphics::setClip(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

void Graphics::resetClip()
{
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    // TODO: check for different resolutions, reset flag
}

int Graphics::screenWidth()
{
    return glutGet(GLUT_WINDOW_WIDTH);
}

int Graphics::screenHeight()
{
    return glutGet(GLUT_WINDOW_HEIGHT);
}

void Graphics::redraw()
{
    glutPostRedisplay();
}
