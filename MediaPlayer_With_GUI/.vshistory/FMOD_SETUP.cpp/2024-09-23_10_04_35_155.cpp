#include "FMODInitialization.h"
#include "AudioUtils.hpp"
#include "fmod.h"
#include <iostream>
#include "cMediaPlayer.h"
#include "cAudioManager.h"
using namespace std;

int main()
{
	FMODInitialization initializationObject;

	cAudioManager audioManager;
	cMediaPlayer mediaPlayer;

	audioManager.loadAssets();

	mediaPlayer.PlayAudio();

	audioManager.unloadAssets();
	return 0;
}