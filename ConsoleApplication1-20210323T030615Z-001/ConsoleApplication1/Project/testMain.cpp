#include <iostream>
#include <fmod.h>

FMOD_SYSTEM* gFmodSystem;
FMOD_SOUND* gFmodeSound;

int main()
{
	FMOD_System_Create(&gFmodSystem);
	FMOD_System_Init(gFmodSystem, 32, FMOD_INIT_NORMAL, NULL);
	FMOD_System_CreateSound(gFmodSystem, "test.mp3", FMOD_DEFAULT, 0, &gFmodeSound);

	return 0;
}