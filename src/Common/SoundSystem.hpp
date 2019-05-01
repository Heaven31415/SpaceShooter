#pragma once

#include "ResourceHolder.hpp"

using MusicHolder = std::map<std::string, std::string>;

class SoundSystem
{
public:
                                    SoundSystem(SoundHolder& soundHolder);

    void                            playSound(const std::string& name);
    void                            playSound(const std::string& name, float volume);
    void                            playSound(const std::string& name, float volume, float pitch);

    void                            playMusic(const std::string& name);
    void                            playMusic(const std::string& name, float volume);
    void                            playMusic(const std::string& name, float volume, float pitch);

    void                            recycleSounds();

private:
    SoundHolder&                    m_soundHolder;
    MusicHolder                     m_musicHolder;
    std::list<sf::Sound>            m_sounds;
    sf::Music                       m_music;
};
