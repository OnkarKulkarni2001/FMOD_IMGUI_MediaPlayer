#pragma once
class cMediaPlayer {
public:
	FMOD_RESULT result;

	void PlayAudio();
	void PauseAudio();
	void StopAudio();
	void AdjustPitch();
	void AdjustVolume();
	void AdjustPan();
};

