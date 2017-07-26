#include "..\Include\SoundSystem.hpp"
#include "..\Include\Player.hpp"

SoundSystem::SoundSystem(SoundHolder & soundHolder)
: m_soundHolder{soundHolder}
, m_musicHolder{}
, m_sounds{}
, m_music{}
{
    // TODO: Load music resources via ResourceHolder
    m_musicHolder["GameTheme"] = "Resources/Music/GameTheme.ogg";
    m_musicHolder["LoadingTheme"] = "Resources/Music/LoadingTheme.ogg";
}

void SoundSystem::playSound(const std::string & name)
{
    recycleSounds();
    m_sounds.push_back(sf::Sound(m_soundHolder.get(name)));

    auto& sound = m_sounds.back();
    sound.play();
}

void SoundSystem::playSound(const std::string & name, float volume)
{
    recycleSounds();
    m_sounds.push_back(sf::Sound(m_soundHolder.get(name)));

    auto& sound = m_sounds.back();
    sound.setVolume(volume);
    sound.play();
}

void SoundSystem::playSound(const std::string & name, float volume, float pitch)
{
    recycleSounds();
    m_sounds.push_back(sf::Sound(m_soundHolder.get(name)));

    auto& sound = m_sounds.back();
    sound.setVolume(volume);
    sound.setPitch(pitch);
    sound.play();
}

void SoundSystem::playMusic(const std::string & name)
{
    m_music.openFromFile(m_musicHolder[name]);
    m_music.setVolume(100.f);
    m_music.setPitch(1.f);
    m_music.play();
}

void SoundSystem::playMusic(const std::string & name, float volume)
{
    m_music.openFromFile(m_musicHolder[name]);
    m_music.setVolume(volume);
    m_music.play();
}

void SoundSystem::playMusic(const std::string & name, float volume, float pitch)
{
    m_music.openFromFile(m_musicHolder[name]);
    m_music.setVolume(volume);
    m_music.setPitch(pitch);
    m_music.play();
}

void SoundSystem::recycleSounds()
{
    if (m_sounds.size() >= 16)
        m_sounds.remove_if([](const sf::Sound& sound){ return sound.getStatus() != sf::Sound::Playing; });
}

void SoundSystem::onNotify(Object * obj, unsigned int code)
{
    if (obj->getType() == Type::Player)
    {
        auto event = static_cast<Event::Type>(code);
        switch (event)
        {
            case Event::WeaponFired:
                playSound("PlayerLaser");
                break;
            case Event::PickupTaken:
                playSound("PlayerHeal");
                break;
            case Event::TakenDamage:
                playSound("DamageTaken");
                break;
            default:
                break;
        }
    }
}
