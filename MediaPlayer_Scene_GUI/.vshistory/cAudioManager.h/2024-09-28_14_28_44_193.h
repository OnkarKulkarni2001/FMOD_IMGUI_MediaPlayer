#pragma once
#include <glad/glad.h> 
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h> // Include glfw3.h after our OpenGL definitions
#include "fmod.hpp"
#include <vector>

class cAudioManager {
public:
	FMOD::Channel* channel; 
	std::vector<FMOD::Sound*> sounds; // Vector to hold multiple sound pointers

	bool bIsPlaying = false;
	bool bIsPaused = false;
	float pitchValue = 0;
	float panValue = 0;
	float volumeValue = 0;
	void loadAssets(GLFWwindow* window);
	void unloadAssets();

	void play(int index);
	void pause();
	void resume();
	void stop();
	void setPitch(float pitchValue);
	void setVolume(float volumeValue);
	void setPan(float panValue);
};