// created by Alice McConnell
// audio for UI

#include <SFML/Audio.hpp>

int main()
{
    sf::SoundBuffer buffer("ding.mp3"); // Throws sf::Exception if an error occurs

    // OR

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("ding.mp3"))
        return -1;
        
}

class MyMusic
{
public:
    MyMusic(sf::Music&& music) : m_music(std::move(music))
    {
        
    }

private:
    sf::Music m_music;
};

sf::Music music("ding.mp3");
