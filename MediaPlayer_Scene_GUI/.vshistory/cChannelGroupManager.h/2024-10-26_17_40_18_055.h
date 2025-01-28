#pragma once
#include "fmod.hpp"

class cChannelGroupManager
{
	FMOD::ChannelGroup* pChannelGroup;
	void PrintChannelGroupInfo();
	void PlayAudio();
	void StopAudio();
	void AdjustVolume();
	void ApplyDSP();
};