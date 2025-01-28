#pragma once
#include "fmod.hpp"
#include <vector>

class cChannelGroupManager {
public:
	FMOD::Channel* channel; 
	std::vector<FMOD::Sound*> sounds; // Vector to hold multiple sound pointers
	FMOD::ChannelGroup* m_ChannelGroup = nullptr;

	void CreateChannelGroup();
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
	void play(int index, FMOD::Channel* channel);
	void pause(int index, FMOD::Channel* channel);
	void resume(int index, FMOD::Channel* channel);
	void stop(int index, FMOD::ChannelGroup* channelGroup);
	void setPitch(float pitchValue, FMOD::Channel* channel);
	void setVolume(float volumeValue, FMOD::Channel* channel);
	void setPan(float panValue, FMOD::Channel* channel);
};