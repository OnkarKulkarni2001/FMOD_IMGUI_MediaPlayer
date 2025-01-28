#pragma once
#include "fmod.hpp"
#include <vector>

class cChannelGroupManager
{
public:
	std::vector<FMOD::Sound*> pSounds;
	FMOD::ChannelGroup* m_ChannelGroup;
	std::vector<FMOD::ChannelGroup*> pChannelGroups;

	void CreateChannelGroup();			// This will create a channel group
	void Add3DSoundListener();			// For bonus marks
	void ShowAvailableChannelGroups();	// This will iterate over scenes and show the available channel groups/scenes
	void PrintChannelGroupInfo();		// This will print channel group info
	void LoadAssets();					// This will load the songs which are already present in scene/channel group
	void UnloadAssets();				// This will unload ~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void ApplyDSP();					// This will apply DSP to channel group
	void ApplyDSPToSound();				// This will apply DSP to individual sound in channel group
	void PlayAudio();					// This will play a scene/channel group
	void StopAudio();					// This will stop a scene/channel group
	void AdjustVolume();				// This will adjust volume of whole scene/channel group
	void PlayIndividualAudio();			// This will play individual song
	void StopIndividualAudio();			// This will stop individual song
	void AdjustIndividualAudioVolume();	// This will adjust individual song volume
};