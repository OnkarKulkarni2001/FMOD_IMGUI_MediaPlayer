#pragma once
#include "imgui/imgui.h"
#include "cChannelGroupManager.h"
#include "GLFW/glfw3.h"
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

class cMediaPlayer {
public:
	// Definitions of functions
	void RunMediaPlayer(GLFWwindow* window);
	void PlayAudio(int index);
	void PauseAudio();
	void StopAudio();
	void AdjustPitch();
	void AdjustVolume();
	void AdjustPan();
	void Update();

	cChannelGroupManager channelGroupManager;
};

