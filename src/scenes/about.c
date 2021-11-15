#include <math.h>
#include "about.h"
#include "../globals.h"
#include "../colors.h"

// Função para carregar o sobre, suas variaveis e componentes
About initAbout()
{
	About about;

	// Inicializa variaveis de texto da tela de "Sobre"
	about.title = "Mario Bros. desenvolvido em C";
	about.subtitle = "Trabalho final - INF01202";
	about.credits = "Autor: Vinicius Lazzari";
	about.repository = "https://github.com/viniciuslazzari/MarioBros";

	// Carrega assets do Mario
	Texture2D marioSprites = LoadTexture("assets/sprites/mario.png");

	about.marioSprites = marioSprites;

	about.currentMarioSprite = 1;

	return about;
}

// Função para manipular o comportamento do sobre
void handleAbout(About *about, SceneOption *currentScene)
{
	drawAbout(about);

	// Se pressionar enter, volta para o Menu
	if (IsKeyPressed(KEY_ENTER))
	{
		*currentScene = MENU;
	}
}

// Função para desenha o "Sobre"
void drawAbout(About *about)
{
	drawAboutMarioSprites(about->marioSprites, &about->currentMarioSprite);
	drawAboutText(*about);
	drawAboutOptions();
}

// Desenha parte do texto da tela
void drawAboutText(About about)
{
	// Desenha título
	DrawTextEx2(about.title, 350, 200, 36, blue);

	// Desenha sub-título
	DrawTextEx2(about.subtitle, 350, 250, 30, red);

	// Desenha os créditos
	DrawTextEx2(about.credits, 350, 330, 24, WHITE);

	// Desenha o repositório
	DrawTextEx2(about.repository, 350, 380, 24, WHITE);
}

// Desenha os sprites do Mario
void drawAboutMarioSprites(Texture2D marioSprites, int *currentMarioSprite)
{
	int rotation = 0;

	// Define os tamanhos do retangulo a ser desenhado
	int frameWidth = marioSprites.width / 8;
	int frameHeight = marioSprites.height;

	// Do sprite original (que contém todas a imagens), seleciona apenas o retangulo
	// desejado e fica trocando ele a cada pouco tempo
	Rectangle sourceRec = {0.0f, 0.0f, (float)frameWidth, (float)frameHeight};
	sourceRec.x = (float)*currentMarioSprite * (float)marioSprites.width / 8;

	// Define na tela aonde esse retangulo selecionado deve ficar
	Rectangle destRec = {130.0f, 200.0f, frameWidth * 10.0f, frameHeight * 10.0f};

	// Define os tamanhos do retangulo na tela
	Vector2 origin = {(float)frameWidth, (float)frameHeight};

	// Desneha o Sprite
	DrawTexturePro(marioSprites, sourceRec, destRec, origin, rotation, WHITE);

	// #IMPORTANT Esse estado que esta sendo mudado que altera o retangulo selecionado
	// para a proxima iteração
	*currentMarioSprite = (frameCount / 5) % 3 + 1;
}

// Função para desenhar as opções
void drawAboutOptions()
{
	DrawTextEx2("Voltar", halfScreenWidth - MeasureText("Voltar", 24) / 2.0f, 500, 24, yellow);
}
