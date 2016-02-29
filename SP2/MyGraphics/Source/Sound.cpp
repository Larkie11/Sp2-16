#include "Sound.h"

Sound::Sound()
{
	musicEngine = irrklang::createIrrKlangDevice();
}
Sound::~Sound()
{

}
void Sound::playMusic(string Music)
{
	Song = musicEngine->play2D(Music.c_str(), true, false, true);
}
void Sound::playSE(string Music)
{
	SoundEffect = musicEngine->play2D(Music.c_str(), false, false, false);
}
void Sound::stopMusic(string Music)
{
	Song->stop();
}
void Sound::stopAll()
{
	Song->setIsPaused();
}
void Sound::startAgain()
{
	Song->setIsPaused(false);
}