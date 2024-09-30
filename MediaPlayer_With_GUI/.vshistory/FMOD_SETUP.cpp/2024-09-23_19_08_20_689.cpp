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
	int indexOfSong = 1;
	cout << "Enter number of song you wanna play: " << endl;
	cin >> indexOfSong;
	PlayAudio(indexOfSong);
	return 0;
}