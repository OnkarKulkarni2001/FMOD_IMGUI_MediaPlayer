#pragma once
#include "fmod.hpp"
#include <vector>

class cChannelGroupManager
{
	FMOD::ChannelGroup* pChannelGroup;
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