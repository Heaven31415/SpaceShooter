#include "ResourceHolder.hpp"

template<typename R>
ResourceHolder<R>::ResourceHolder(std::vector<std::string> extensions, std::string relativePath)
: m_resources()
, m_extensions(extensions)
, m_relativePath(relativePath)

, m_loader(&ResourceHolder<R>::loadResources, this)
, m_loaded(0)
, m_found(0)
, m_finished(false)
{
}

template<typename R>
R& ResourceHolder<R>::get(const std::string& id)
{
    return m_resources[id];
}

template<typename R>
const R& ResourceHolder<R>::get(const std::string& id) const
{
    return m_resources[id];
}

template<typename R>
void ResourceHolder<R>::load()
{
    m_loader.launch();
}

template<typename R>
bool ResourceHolder<R>::isFinished()
{
    return m_finished.load();
}

template<typename R>
float ResourceHolder<R>::getProgress()
{
    return m_finished.load() ? 1.f : static_cast<float>(m_loaded.load()) / m_found.load();
}

template<typename R>
void ResourceHolder<R>::loadResources()
{
    // get current path and add m_relativePath to it
    fs::path path = fs::current_path();
    path /= m_relativePath;

    // check whether created path is indeed a directory from which we can load resources
    if (!fs::is_directory(path))
        throw std::runtime_error("\"" + path.u8string() + "\" is not a valid directory!");

    // create contaiener with information about resources
    std::vector <std::pair<std::string, std::string>> resourcesNames;

    // now we are in directory, let's search for resources
    for (auto& p : fs::recursive_directory_iterator(path))
    {
        // if path contains regular file, analyze it
        if (fs::is_regular_file(p.path()))
        {
            // check whether path is valid using regular expression
            const std::string& target = p.path().u8string();
            std::smatch match;
            std::regex regex(R"(.+\\([\w\(\)\[\] -]+)\.(\w+))");
            if (!std::regex_search(target, match, regex))
                throw std::runtime_error("\"" + target + "\" is not a valid filepath!");

            // create references to filename and extension
            const std::string& filename = match[1];
            const std::string& extension = match[2];

            // check whether file extension is supported
            bool validExtension = false;
            for (auto& e : m_extensions)
                if (extension == e) validExtension = true;

            // if we have file with good extension, let's add it
            if (validExtension)
            {
                resourcesNames.push_back({ filename, p.path().u8string() });
                m_found++;
            }
        }
    }

    // if no resources have been found, let's end the show
    if (m_found.load() == 0)
    {
        m_finished = true;
        return;
    }
    else
    {
        // every resource have been found, let's load them
        for (auto& r : resourcesNames)
        {
            m_resources.acquire(r.first, thor::Resources::fromFile<R>(r.second));
            m_loaded++;
        }

        // everything went well, we are done
        m_finished = true;
    }
}

template class ResourceHolder<sf::Font>;
template class ResourceHolder<sf::SoundBuffer>;
template class ResourceHolder<sf::Texture>;