#include "Sound.h"

Sound::Sound()
{
	engine = irrklang::createIrrKlangDevice();
}
Sound::~Sound()
{
	
}
void Sound::playMusic(string Music)
{
	Song = engine->play2D(Music.c_str(), true, false, true);
}