#ifndef _HIGHSCORES_
#define _HIGHSCORES_
#include "../globals.h"

typedef struct Score
{
	char name[20];
	int value;
} Score;

typedef struct Highscores
{
	int scoresLoaded;
	Score scores[highscoresMaxOptions];
} Highscores;

Highscores initHighscores();
void handleHighscores(Highscores *highscores, SceneOption *currentScene);
void drawHighscores(Highscores *highscores);
void drawScores(Highscores *highscores);
void drawHighscoresOptions();

#endif