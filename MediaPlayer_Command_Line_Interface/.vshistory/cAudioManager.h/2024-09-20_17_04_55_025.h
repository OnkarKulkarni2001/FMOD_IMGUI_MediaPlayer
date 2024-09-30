#pragma once
class cAudioManager {
public:
	void loadAssets(FMOD::Sound &sound);
	void unloadAssets();

	void play();
	void pause();
	void stop();
	void setPitch();
	void setVolume();
	void setPan();
};