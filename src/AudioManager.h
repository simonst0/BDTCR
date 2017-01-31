#pragma once
#include "stdafx.h"
#include "sfml\Audio.hpp"
#include "IObserverPattern.h"

class AudioManager
{
public:
	static AudioManager& GetInstance();
	void Init();
	void PlayAudioById(std::string id);
	void Update(float deltaTime);
	void addSound(std::string path, std::string id);
	void addMusic(std::string path, std::string id);
	void setLoopById(std::string id, bool loop);
	void removeAudioById(std::string id);
	void ClearAudio();
	void setVolumeById(std::string id, float volume);
	void stopAudioById(std::string id);
	void pauseAudioById(std::string id);
	void changePitchById(std::string id, float pitch);
	void PauseAll();
	void RestartAllPaused();
	void StopAll();
private:
	AudioManager() = default;
	std::map<std::string, sf::Sound*> m_sounds;
	std::map<std::string, sf::SoundBuffer*> m_soundBuffers;
	std::map<std::string, sf::Music*> m_music;
	std::vector<std::string> m_pausedAudio;
	void DeleteMaps();
};