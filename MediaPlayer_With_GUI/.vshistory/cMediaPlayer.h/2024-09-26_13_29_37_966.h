#pragma once
#include "imgui/imgui.h"
#include "GLFW/glfw3.h"
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

class cMediaPlayer {
public:
	void StartMediaPlayer();
	void RunMediaPlayer(GLFWwindow* window);
	void StopMediaPlayer(GLFWwindow* window);
	void ListSongs();
	void PlayAudio(int index);
	void PauseAudio();
	void StopAudio();
	void AdjustPitch();
	void AdjustVolume();
	void AdjustPan();
};

