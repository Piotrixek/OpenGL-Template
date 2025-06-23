#include "UI.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void UI::init(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void UI::render(Camera& camera, Sky& sky)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    controlsWindow(camera, sky);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UI::controlsWindow(Camera& camera, Sky& sky)
{
    ImGui::Begin("controls");
    ImGui::Text("press 'C' to toggle camera");
    ImGui::Text(camera.isActive() ? "camera is active" : "camera is locked");
    ImGui::Text("app average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Separator();
    ImGui::Text("Sky Settings");
    ImGui::SliderFloat3("Sun Direction", &sky.sunDirection[0], -1.0f, 1.0f);
    if (ImGui::Button("Normalize Sun Direction")) {
        sky.sunDirection = glm::normalize(sky.sunDirection);
    }
    ImGui::End();
}
