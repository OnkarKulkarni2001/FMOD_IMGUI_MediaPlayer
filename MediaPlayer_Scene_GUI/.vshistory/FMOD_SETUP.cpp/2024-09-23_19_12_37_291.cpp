#include "FMODInitialization.h"
#include "AudioUtils.hpp"
#include "fmod.h"
#include <iostream>
#include "cMediaPlayer.h"
#include "cAudioManager.h"
#include <conio.h>

using namespace std;

int main()
{
	cAudioManager audioManager;
	cMediaPlayer mediaPlayer;
	
	do {
		mediaPlayer.RunMediaPlayer();
	} while (!audioManager.bIsPlaying);

	return 0;
}