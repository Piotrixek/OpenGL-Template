#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "camera/Camera.h"
#include "rendering/Sky.h"
#include "ui/UI.h"
#include <memory>
#include <glm/glm.hpp>

class App
{
public:
    App();
    ~App();
    void run();

private:
    GLFWwindow* window;
    Camera camera;
    std::unique_ptr<Sky> sky;
    std::unique_ptr<UI> ui;

    glm::mat4 projection;
    int screenWidth, screenHeight;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    void init();
    void mainLoop();
    void cleanup();

    void processInput();

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
