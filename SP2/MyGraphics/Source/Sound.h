#include "irrKlang.h"
#include <string>
using std::string;

#pragma comment(lib, "irrKlang.lib")


class Sound
{
public:
	irrklang::ISoundEngine* engine;
	irrklang::ISound* Song;
	
	Sound();
	~Sound();
	void playMusic(string Music);

private:
};