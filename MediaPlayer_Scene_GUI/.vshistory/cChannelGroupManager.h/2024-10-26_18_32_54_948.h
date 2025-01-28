#pragma once
#include "fmod.hpp"
#include <vector>

class cChannelGroupManager
{
	std::vector<FMOD::Sound*> pSounds;
	std::vector<FMOD::ChannelGroup*> pChannelGroups;

	void LoadScenes();					// This will load channel group as those are scenes (scenes are folders in directory)
	void CreateChannelGroup();			// This will create a channel group as well as a folder in scenes folder
	void Add3DSoundListener();			// For bonus marks
	void ShowAvailableChannelGroups();	// This will iterate over scenes folder and show the available channel groups/scenes
	void PrintChannelGroupInfo();		// This will print channel group info
	void LoadAssets();					// This will load the songs which are already present in scene folder/channel group folder
	void UnloadAssets();				// This will unload ~~~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void ApplyDSP();					// This will apply DSP to channel group
	void ApplyDSPToSound();				// This will apply DSP to individual sound in channel group
	void PlayAudio();					// This will play a scene/channel group
	void StopAudio();					// This will stop a scene/channel group
	void AdjustVolume();				// This will adjust volume of whole scene/channel group
	void PlayIndividualAudio();
	void StopIndividualAudio();
	void AdjustIndividualAudioVolume();
};