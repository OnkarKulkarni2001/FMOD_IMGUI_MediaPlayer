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
	
	mediaPlayer.RunMediaPlayer();
	if (!audioManager.bIsPlaying) {
		mediaPlayer.StopMediaPlayer();
	}
	return 0;
}