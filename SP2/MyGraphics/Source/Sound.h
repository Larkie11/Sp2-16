#ifndef SOUND_H
#define SOUND_H

#include "irrKlang.h"
#include <string>
using std::string;

#pragma comment(lib, "irrKlang.lib")


class Sound
{
public:
	irrklang::ISoundEngine* musicEngine;
	irrklang::ISound* Song;
	
	Sound();
	~Sound();
	void playMusic(string Music);
	void stopMusic(string Music);
	void playSE(string Music);

private:
};
#endif