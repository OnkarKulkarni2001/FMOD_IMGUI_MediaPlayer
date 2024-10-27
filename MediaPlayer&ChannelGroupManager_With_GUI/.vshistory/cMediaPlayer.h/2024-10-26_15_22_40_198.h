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
	void PlayAudio(int index, FMOD::Channel* channel);
	void PauseAudio(int index, FMOD::Channel* channel);
	void StopAudio(int index, FMOD::Channel* channel);
	void AdjustPitch(FMOD::Channel* channel);
	void AdjustVolume(FMOD::Channel* channel);
	void AdjustPan(FMOD::Channel* channel);

	cChannelGroupManager channelGroupManager;
};

