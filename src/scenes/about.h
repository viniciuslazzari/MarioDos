#ifndef _ABOUT_
#define _ABOUT_
#include "../globals.h"

typedef struct About
{
	const char *title;			    // Título da cena de ajuda
	const char *subtitle;			// Sub-titulo da cena de ajuda
	const char *credits;			// Créditos da cena de ajuda
	const char *repository;			// Repositório do projeto

	Texture2D marioSprites;			// Textura do mario para ficar animado na tela
	int currentMarioSprite;			// Controle do sprite atual da tela
} About;

About initAbout();
void handleAbout(About *about, SceneOption *currentScene);
void drawAbout(About *about);
void drawAboutText(About about);
void drawAboutMarioSprites(Texture2D marioSprites, int *currentMarioSprite);
void drawAboutOptions();

#endif
