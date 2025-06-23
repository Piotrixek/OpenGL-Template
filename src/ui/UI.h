#pragma once

struct GLFWwindow;

#include "camera/Camera.h"
#include "rendering/Sky.h"

class UI
{
public:
    void init(GLFWwindow* window);
    void render(Camera& camera, Sky& sky);
    void cleanup();

private:
    void controlsWindow(Camera& camera, Sky& sky);
};
