#pragma once
#include "fmod.hpp"

class cChannelGroupManager
{
	FMOD::ChannelGroup* pChannelGroup;
	void CreateChannelGroup();
	void Add3DSoundListener();
	void PrintChannelGroupInfo();
	void LoadAssets();
	void UnloadAssets();
	void PlayAudio();
	void StopAudio();
	void AdjustVolume();
	void ApplyDSP();
};