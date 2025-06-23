#pragma once

#include "Shader.h"
#include <glm/glm.hpp>

class Sky
{
public:
    Sky();
    void draw(const glm::mat4& projection, const glm::mat4& view);

    glm::vec3 sunDirection;

private:
    Shader skyShader;
    unsigned int skyVAO, skyVBO;
    void setupSkybox();
};
