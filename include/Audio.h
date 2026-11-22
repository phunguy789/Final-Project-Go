#pragma once
#include <SFML/Audio.hpp>
class Audio
{
    public:
    sf::SoundBuffer placeBuffer;
    sf::SoundBuffer captureBuffer;
    sf::SoundBuffer gameOverBuffer;

    sf::Sound placeSound;
    sf::Sound captureSound;
    sf::Sound gameOverSound;

    sf::Music backgroundMusic;

    Audio();

    void playPlace(float volume);
    void playCapture(float volume);
    void playGameOver(float volume);
};
