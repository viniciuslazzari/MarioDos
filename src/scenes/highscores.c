#include <math.h>
#include <stdio.h>
#include <string.h>
#include "highscores.h"
#include "../services/highscoresServices.h"
#include "../globals.h"
#include "../colors.h"

// Função para carregar o sobre, suas variaveis e componentes
Highscores initHighscores()
{
	Highscores highscores;

	highscores.scoresLoaded = 0;

	return highscores;
}

// Função para manipular o comportamento do sobre
void handleHighscores(Highscores *highscores, SceneOption *currentScene)
{
	drawHighscores(highscores);

	// Se pressionar enter, volta para o Menu
	if (IsKeyPressed(KEY_ENTER))
	{
		highscores->scoresLoaded = 0;
		*currentScene = MENU;
	}
}

// Função para desenha o "Sobre"
void drawHighscores(Highscores *highscores)
{
	drawScores(highscores);
	drawHighscoresOptions();
}

// Função que desenha as maiores pontuações na tela
void drawScores(Highscores *highscores)
{
	int fontSize = 28;
	int padding = 60;
	float posY = 100;
	float posX = 300;

	// Teste para apenas carregar as pontuações do arquivo uma vez
	if (!highscores->scoresLoaded)
	{
		loadScores(highscores->scores);
		highscores->scoresLoaded = 1;
	}

	// Desenha o cabeçalho
	DrawTextEx2("Nome", posX + 50, posY, fontSize, yellow);
	DrawTextEx2("Pont.", posX + 500, posY, fontSize, yellow);

	posY += padding;

	// Para cada pontuação
	for (int i = 0; i < highscoresMaxOptions; i++)
	{
		char valueString[6], positionString[4];

		// Converte variaives de int para char para printar na tela
		sprintf(valueString, "%d", highscores->scores[i].value);
		sprintf(positionString, "%d.", i + 1);

		// Printa uma linha da tabela
		DrawTextEx2(positionString, posX, posY, fontSize, WHITE);
		DrawTextEx2(highscores->scores[i].name, posX + 50, posY, fontSize, WHITE);
		DrawTextEx2(valueString, posX + 500, posY, fontSize, WHITE);

		// Incrementa o padding entre as linhas
		posY += padding;
	}
}

// Função para desenhar as opções
void drawHighscoresOptions()
{
	DrawTextEx2("Voltar", halfScreenWidth - MeasureText("Voltar", 24) / 2.0f, 500, 24, yellow);
}
