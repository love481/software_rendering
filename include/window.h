#pragma once
#ifndef _WINDOW_H_
#define _WINDOW_H_
#include"defines.h"
#include"errorCheck.h"
class Window {
public:
    GLFWwindow* mainWindow;
    int bufferWidth;
    int bufferHeight;
    Window(const char* title, const int WindowWid, const int WindowHei) {

        WindowWidth = WindowWid;
        WindowHeight = WindowHei;
        init_GLFW();
        init_window(title);
        init_GLEW();
        init_OpenGLOptions();
    }
    ~Window()
    {
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
    }
private:
    int WindowWidth;
    int WindowHeight;
    void init_GLFW()
    {
        //initialize GLFW
        if (!glfwInit())
        {
            cout << "GLFW Initilization failed";
            glfwTerminate();
        }
    }
    void init_window(const char* titleName)
    {

        //setup glfw window properties
        //opengl version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        mainWindow = glfwCreateWindow(WindowWidth, WindowHeight, titleName, NULL, NULL);
        if (!mainWindow)
        {
            cout << "GLFW window creation failed!";
            glfwTerminate();
        }
        glfwSetFramebufferSizeCallback(mainWindow, resize_framebuffer);
        glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
        glViewport(0, 0, bufferWidth, bufferHeight);
        glfwMakeContextCurrent(mainWindow);
    }
    void init_GLEW()
    {
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {

            cout << "Glew Initilization failed";
            glfwDestroyWindow(mainWindow);
            glfwTerminate();
        }

    }
    void init_OpenGLOptions()
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    }
    static void resize_framebuffer(GLFWwindow* mainwin, int bufferWid, int  bufferHe)
    {
        glViewport(0, 0, bufferWid, bufferHe);
    }
};

#endif //!_WINDOW_H_