#include "Audio.h"
Audio::Audio()
    : placeSound(placeBuffer),
      captureSound(captureBuffer),
      gameOverSound(gameOverBuffer)
{
    placeBuffer.loadFromFile("assets/sounds/place.wav");
    captureBuffer.loadFromFile("assets/sounds/capture.wav");
    gameOverBuffer.loadFromFile("assets/sounds/gameover.wav");
    backgroundMusic.openFromFile("assets/sounds/music.ogg");
    backgroundMusic.setLooping(true);
}
void Audio::playPlace(float volume)
{
    placeSound.setVolume(volume);
    placeSound.play();
}
void Audio::playCapture(float volume)
{
    captureSound.setVolume(volume);
    captureSound.play();
}
void Audio::playGameOver(float volume)
{
    gameOverSound.setVolume(volume);
    gameOverSound.play();
}
