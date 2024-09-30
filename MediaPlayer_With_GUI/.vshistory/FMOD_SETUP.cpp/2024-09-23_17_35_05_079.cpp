#include "FMODInitialization.h"
#include "AudioUtils.hpp"
#include "fmod.h"
#include <iostream>
#include "cMediaPlayer.h"
#include "cAudioManager.h"
using namespace std;

int main()
{
	cAudioManager audioManager;
	cMediaPlayer mediaPlayer;

	audioManager.loadAssets();
	int n = 1;
	cout << "Enter number of song you wanna play: " << endl;
	cin >> n;
	cout << "Commands:\n1) V: Set Volume\n2) I: Set Pitch\n3) A: Set Pan\n4) U: Pause Song\n5) R: Resume Song\n6) S: Stop Song\n";
	mediaPlayer.PlayAudio(n);

	if (!audioManager.bIsPlaying) {
		audioManager.unloadAssets();
	}

	return 0;
}