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
	//cMediaPlayer mediaPlayer;

	audioManager.loadAssets();
	int n = 1;
	cout << "Enter number of song you wanna play: " << endl;
	cin >> n;
	audioManager.play(n);

	audioManager.unloadAssets();
	return 0;
}