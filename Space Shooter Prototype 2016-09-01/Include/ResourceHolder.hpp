#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Thor/Resources.hpp>
#include <filesystem>
#include <regex>
#include <atomic>

namespace fs = std::experimental::filesystem;

template<typename R>
class ResourceHolder
{
public:
									ResourceHolder(std::vector<std::string> extensions, std::string relativePath = "");
	R&								get(const std::string& id);
	const R&						get(const std::string& id) const;
	float							getProgress();
	bool							isFinished();
	void							load();

private:
	void							loadResources();

private:
	thor::ResourceHolder<R, std::string>	m_resources;
	std::vector<std::string>				m_extensions;
	std::string								m_relativePath;

private:
	sf::Thread								m_loader;
	std::atomic<size_t>						m_loaded;
	std::atomic<size_t>						m_found;
	std::atomic<bool>						m_finished;
};

using FontHolder = ResourceHolder<sf::Font>;
using SoundHolder = ResourceHolder<sf::SoundBuffer>;
using TextureHolder = ResourceHolder<sf::Texture>;