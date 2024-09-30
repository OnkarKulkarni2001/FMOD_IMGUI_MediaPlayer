#include <glad/glad.h> 
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "cMediaPlayer.h"
#include <GLFW/glfw3.h> // Include glfw3.h after our OpenGL definitions
#include <iostream>

cMediaPlayer mediaPlayer;
bool bIsStarted = true;
bool bIsRunning = false;

void SetupImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
}

void MainLoop(GLFWwindow* window) {
    mediaPlayer.RunMediaPlayer(window);
    //while (!glfwWindowShouldClose(window)) {
    //    // Start the ImGui frame
    //    ImGui_ImplOpenGL3_NewFrame();
    //    ImGui_ImplGlfw_NewFrame();
    //    ImGui::NewFrame();

    //    // Rendering
    //    ImGui::Render();
    //    glClear(GL_COLOR_BUFFER_BIT);
    //    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //    // Swap buffers
    //    glfwSwapBuffers(window);
    //    glfwPollEvents();
    //}
}

void CleanupImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui + GLFW Example", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Setup ImGui context
    SetupImGui();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330"); // Specify your OpenGL version

    // Main application loop
    MainLoop(window);

    // Cleanup
    CleanupImGui();

    // Cleanup GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}