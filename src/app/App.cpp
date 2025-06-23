#include "App.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

App::App()
    : window(nullptr),
    camera(glm::vec3(0.0f, 0.0f, 3.0f)),
    sky(nullptr),
    ui(nullptr),
    screenWidth(1280),
    screenHeight(720)
{}

App::~App()
{
    cleanup();
}

void App::run()
{
    init();
    mainLoop();
}

void App::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL Sky", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "failed to create glfw window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "failed to init glad" << std::endl;
        exit(-1);
    }

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    sky = std::make_unique<Sky>();
    ui = std::make_unique<UI>();
    ui->init(window);
}

void App::mainLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        projection = glm::perspective(glm::radians(camera.getZoom()), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();

        sky->draw(projection, view);
        ui->render(camera, *sky);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void App::cleanup()
{
    if (ui) ui->cleanup();
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
}

void App::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (camera.isActive())
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.processKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.processKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.processKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.processKeyboard(RIGHT, deltaTime);
    }
}

void App::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    app->screenWidth = width;
    app->screenHeight = height;
    glViewport(0, 0, width, height);
}

void App::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    if (app->camera.isActive())
    {
        app->camera.processMouseMovement(static_cast<float>(xpos), static_cast<float>(ypos));
    }
}

void App::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    if (app->camera.isActive())
    {
        app->camera.processMouseScroll(static_cast<float>(yoffset));
    }
}

void App::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        app->camera.toggle();
        if (app->camera.isActive()) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}
