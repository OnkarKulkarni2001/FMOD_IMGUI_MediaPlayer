#pragma once
#include "fmod.hpp"
#include <vector>

class cChannelGroupManager {
public:
	FMOD::Channel* channel; 
	std::vector<FMOD::Sound*> sounds; // Vector to hold multiple sound pointers
	FMOD::ChannelGroup* m_ChannelGroup = nullptr;

	FMOD::ChannelGroup CreateChannelGroup(char* channel_name);
	void SetChannelGroupDSP();
	void PrintChannelGroupInfo();
	FMOD::ChannelGroup* getChannelGroup();

	bool bIsPlaying = false;
	bool bIsPaused = false;
	float pitchValue = 0;
	float panValue = 0;
	float volumeValue = 0;

	// Load and unload function definitions
	void loadAssets();
	void unloadAssets();

	// Sound control function definitions
	void play(int index);
	void pause();
	void resume();
	void stop();
	void setPitch(float pitchValue);
	void setVolume(float volumeValue);
	void setPan(float panValue);
};