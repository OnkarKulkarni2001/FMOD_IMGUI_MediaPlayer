#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h> // Include glfw3.h after our OpenGL definitions
#include <iostream>

// Setup function (initialize ImGui)
void SetupImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
}

// Main loop
void MainLoop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Example GUI code
        ImGui::Text("Hello, world!");

        // Rendering
        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

// Cleanup function
void CleanupImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

int main() {
    // Initialize GLFW, create a window, etc.
    // ...

    SetupImGui();
    MainLoop(window);
    CleanupImGui();

    // Clean up GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
