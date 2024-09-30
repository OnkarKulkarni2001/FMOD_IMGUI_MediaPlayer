#pragma once
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
	void loadAssets(void* window);
	void unloadAssets();

	void play(int index);
	void pause();
	void resume();
	void stop();
	void setPitch(float pitchValue);
	void setVolume(float volumeValue);
	void setPan(float panValue);
};