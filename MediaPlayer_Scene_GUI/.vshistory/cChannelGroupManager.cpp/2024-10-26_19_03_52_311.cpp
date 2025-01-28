#include "cChannelGroupManager.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include "AudioUtils.hpp"

void cChannelGroupManager::CreateChannelGroup()
{
}

void cChannelGroupManager::Add3DSoundListener()
{
}

void cChannelGroupManager::ShowAvailableChannelGroups()
{
	FMOD_RESULT result;
	char name[256];

	for (int channelGroupIndex = 0; channelGroupIndex != pChannelGroups.size(); channelGroupIndex++) {
		result = pChannelGroups[channelGroupIndex]->getGroup(channelGroupIndex, &m_ChannelGroup);
		
		if (result != FMOD_OK) {
			FMODCheckError(result);
			return;
		}

		result = m_ChannelGroup->getName(name, sizeof(name));
		
		if (result != FMOD_OK) {
			FMODCheckError(result);
			return;
		}
		else {
			std::cout << result << std::endl;
		}
	}
}

void cChannelGroupManager::PrintChannelGroupInfo()
{
	char name[256];
	m_ChannelGroup->getName(name, sizeof(name));

	float volume = 0.0f;
	m_ChannelGroup->getVolume(&volume);

	float pitch = 0.0f;
	m_ChannelGroup->getPitch(&pitch);

	std::cout << name << " channel group has a volume of " << volume << std::endl;
	std::cout << name << " channel group has a pitch of " << pitch << std::endl;
}

void cChannelGroupManager::LoadAssets()
{
}

void cChannelGroupManager::UnloadAssets()
{
}

void cChannelGroupManager::ApplyDSP()
{
}

void cChannelGroupManager::ApplyDSPToSound()
{
}

void cChannelGroupManager::PlayAudio()
{
}

void cChannelGroupManager::StopAudio()
{
}

void cChannelGroupManager::AdjustVolume()
{
}

void cChannelGroupManager::PlayIndividualAudio()
{
}

void cChannelGroupManager::StopIndividualAudio()
{
}

void cChannelGroupManager::AdjustIndividualAudioVolume()
{
}
