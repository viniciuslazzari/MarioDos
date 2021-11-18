#ifndef _HIGHSCORES_
#define _HIGHSCORES_
#include "../globals.h"

typedef struct Score
{
	char name[20];					            // O que vai ser escrito na tela
	int value;					                // Valor da op��o
} Score;

typedef struct Highscores
{
	int scoresLoaded;				            // Flag para saber se o ranking j� foi carregado
	Score scores[highscoresMaxOptions];		    // Array com as op��es
} Highscores;

Highscores initHighscores();
void handleHighscores(Highscores *highscores, SceneOption *currentScene);
void drawHighscores(Highscores *highscores);
void drawScores(Highscores *highscores);
void drawHighscoresOptions();

#endif
