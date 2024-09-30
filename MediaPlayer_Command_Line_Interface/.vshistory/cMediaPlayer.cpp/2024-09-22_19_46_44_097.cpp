#include "cMediaPlayer.h"
#include "cAudioManager.h"
#include <iostream>
using namespace std;

cAudioManager audioManager;

void cMediaPlayer::PlayAudio() {
	int index = 0;
	cout << "Enter the index of song you want to play: " << endl;
	cin >> index;

	audioManager.play(index);
}

void cMediaPlayer::PauseAudio() {
	audioManager.pause();
}

void cMediaPlayer::StopAudio() {
	audioManager.stop();
}

void cMediaPlayer::AdjustPitch() {
	audioManager.setPitch();
}

void cMediaPlayer::AdjustVolume() {
	audioManager.setVolume();
}

void cMediaPlayer::AdjustPan() {
	audioManager.setPan();
}