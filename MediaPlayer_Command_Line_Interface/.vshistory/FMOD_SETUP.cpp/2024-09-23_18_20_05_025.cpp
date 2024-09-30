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
	//cAudioManager audioManager;
	cMediaPlayer mediaPlayer;
	
	mediaPlayer.RunMediaPlayer();
	if (_kbhit()) {
		int key = 27;
		if (key == 27) {
			mediaPlayer.StopMediaPlayer();
		}
	}

	return 0;
}