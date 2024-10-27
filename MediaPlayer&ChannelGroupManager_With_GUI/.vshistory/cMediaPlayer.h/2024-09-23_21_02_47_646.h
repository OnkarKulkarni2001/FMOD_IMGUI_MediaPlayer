#pragma once
class cMediaPlayer {
public:
	void StartMediaPlayer();
	void RunMediaPlayer();
	int StopMediaPlayer();
	void PlayAudio(int index);
	void PauseAudio();
	void StopAudio();
	void AdjustPitch();
	void AdjustVolume();
	void AdjustPan();
};

