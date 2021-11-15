#ifndef _ABOUT_
#define _ABOUT_
#include "../globals.h"

typedef struct About
{
	const char *title;
	const char *subtitle;
	const char *credits;
	const char *repository;

	Texture2D marioSprites;
	int currentMarioSprite;
} About;

About initAbout();
void handleAbout(About *about, SceneOption *currentScene);
void drawAbout(About *about);
void drawAboutText(About about);
void drawAboutMarioSprites(Texture2D marioSprites, int *currentMarioSprite);
void drawAboutOptions();

#endif