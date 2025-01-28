#pragma once
#include "fmod.hpp"
#include <vector>

class cChannelGroupManager
{
	std::vector<FMOD::Sound*> pSounds;
	std::vector<FMOD::ChannelGroup*> pChannelGroups;

	void LoadScenes();					// This will load channel group as those are scenes
	void CreateChannelGroup();
	void Add3DSoundListener();
	void PrintChannelGroupInfo();
	void LoadAssets();
	void UnloadAssets();
	void ApplyDSP();
	void PlayAudio();
	void StopAudio();
	void AdjustVolume();
};