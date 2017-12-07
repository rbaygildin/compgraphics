//
// Created by Max Heartfield on 22.11.17.
//

#ifndef OPENGL_START_WINDOW_H
#define OPENGL_START_WINDOW_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <boost/log/trivial.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "shaders/Shader.h"
#include "figures/Figure.h"
#include "figures/Cube.h"
#include "figures/NoelTree.h"

using namespace std;

enum Mode{
    X, Y
};

class Window {
public:
    Window();

    ~Window();

    void run();

private:
    void initLighting();

    void loadShaders();

    void deleteShaders();

    void createBuffers();

    void deleteBuffers();

private:
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    GLFWwindow *wnd;
    Shader *shader;
    Shader *lightShader;
    GLuint program;
    vector<Figure *> figures;
    Mode mode = Mode::X;
};


#endif //OPENGL_START_WINDOW_H