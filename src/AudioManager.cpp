#include "stdafx.h"
#include "AudioManager.h"
#include "EventBus.h"
#include <iostream>

AudioManager& AudioManager::GetInstance()
{
	static AudioManager instance;
	return instance;
}
void AudioManager::Init()
{
	addMusic("Nonstop.ogg", StaticStrings::MenuMusic);
	setLoopById(StaticStrings::MenuMusic, true);
	setVolumeById(StaticStrings::MenuMusic, 20);

	addMusic("Exit_the_Premises.ogg", StaticStrings::MainMusic);
	addSound("car-crash.ogg", StaticStrings::MainCrash);
	addSound("ignition.ogg", StaticStrings::MainIgnition);
	addSound("car-horn.ogg", StaticStrings::MainHorn);
	addSound("tire_bump.ogg", StaticStrings::MainTireBump);
	addSound("barrel_bump.ogg", StaticStrings::MainBarrelBump);
	addSound("tick.ogg", StaticStrings::MenuTick);
	addSound("car_hit.ogg", StaticStrings::MainCarHit);
	addSound("race_countdown.ogg", StaticStrings::MainCountdown);
	addSound("metall_grind.ogg", StaticStrings::MainMetallGrind);
	setLoopById(StaticStrings::MainMusic, true);
	setVolumeById(StaticStrings::MainMusic, 20);
	setVolumeById(StaticStrings::MainIgnition, 60);
}
void AudioManager::PlayAudioById(std::string id)
{
	if (m_sounds.count(id) != 0)
	{
		m_sounds[id]->play();
	}
	if (m_music.count(id) != 0)
	{
		m_music[id]->play();
	}
}
void AudioManager::Update(float deltaTime)
{
	
}
void AudioManager::addSound(std::string path, std::string id)
{
	if (m_sounds.count(id) > 0)
		return;
	sf::SoundBuffer* buffer = new sf::SoundBuffer();
	if (!buffer->loadFromFile(StaticStrings::AudioPath + path))
		return;
	m_soundBuffers[id] = buffer;
	sf::Sound* sound = new sf::Sound(*buffer);
	sound->setBuffer(*buffer);
	m_sounds[id] = sound;
}
void AudioManager::addMusic(std::string path, std::string id)
{
	if (m_music.count(id) > 0)
		return;
	sf::Music* music = new sf::Music();
	if (!music->openFromFile(StaticStrings::AudioPath + path))
		return;
	m_music[id] = music;
}
void AudioManager::setLoopById(std::string id, bool loop)
{
	if (m_sounds.count(id) != 0)
		m_sounds[id]->setLoop(loop);
	if (m_music.count(id) != 0)
		m_music[id]->setLoop(loop);
}
void AudioManager::removeAudioById(std::string id)
{
	delete m_sounds[id];
	delete m_music[id];
	delete m_soundBuffers[id];
	m_sounds.erase(id);
	m_music.erase(id);
	m_soundBuffers.erase(id);
	for(auto& it = m_pausedAudio.begin(); it != m_pausedAudio.end();)
	{
		if (*it == id)
		{
			m_pausedAudio.erase(it);
		}
		else
			++it;
	}
}
void AudioManager::ClearAudio()
{
	DeleteMaps();
	m_sounds.clear();
	m_music.clear();
	m_soundBuffers.clear();
	m_pausedAudio.clear();
}
void AudioManager::setVolumeById(std::string id, float volume)
{
	if (volume > 100 || volume < 0)
		return;
	if (m_music.count(id) != 0)
		m_music[id]->setVolume(volume);
	if (m_sounds.count(id) != 0)
		m_sounds[id]->setVolume(volume);
}
void AudioManager::changePitchById(std::string id, float pitch)
{
	if (m_music.count(id) > 0)
		m_music[id]->setPitch(pitch);
	if (m_sounds.count(id) > 0)
		m_sounds[id]->setPitch(pitch);
}
void AudioManager::stopAudioById(std::string id)
{
	if (m_music.count(id) != 0)
		m_music[id]->stop();
	if (m_sounds.count(id) != 0)
		m_sounds[id]->stop();
	for (auto& it = m_pausedAudio.begin(); it != m_pausedAudio.end();)
	{
		if (*it == id)
		{
			m_pausedAudio.erase(it);
		}
		else
			++it;
	}
}
void AudioManager::pauseAudioById(std::string id)
{
	if (m_music.count(id) != 0)
		m_music[id]->pause();
	if (m_sounds.count(id) != 0)
		m_sounds[id]->pause();
	m_pausedAudio.push_back(id);
}
void AudioManager::PauseAll()
{
	for (auto& id : m_sounds)
	{
		if(id.second->getStatus() == sf::SoundSource::Status::Playing)
		pauseAudioById(id.first);
	}
	for (auto& id : m_music)
	{
		if (id.second->getStatus() == sf::SoundSource::Status::Playing)
		pauseAudioById(id.first);
	}
}
void AudioManager::RestartAllPaused()
{
	for (auto& id : m_pausedAudio)
	{
		PlayAudioById(id);
	}
	m_pausedAudio.clear();
}
void AudioManager::StopAll()
{
	for (auto& id : m_music)
	{
		id.second->stop();
	}
	for (auto& id : m_sounds)
	{
		id.second->stop();
	}
}
void AudioManager::DeleteMaps()
{
	for (auto it = m_music.begin(); it != m_music.end(); it++)
	{
		delete it->second;
	}
	for (auto it = m_sounds.begin(); it != m_sounds.end(); it++)
	{
		delete it->second;
	}
	for (auto it = m_soundBuffers.begin(); it != m_soundBuffers.end(); it++)
	{
		delete it->second;
	}
}