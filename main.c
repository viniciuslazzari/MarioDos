#include "raylib.h"
#include "src/sceneHandler.h"
#include "src/colors.h"

Font defaultFont;
int frameCount;

int main(void)
{
	// Inicializa variáveis de tela
	const int gameFps = 60;
	const char *screenTitle = "Mario Bros. v1.0";
	SceneHandler sceneHandler;

	// Abre a janela do jogo
	InitWindow(screenWidth, screenHeight, screenTitle);

	// Carregar assets padrões
	Image screenIcon = LoadImage("assets/images/ScreenIcon.png");
	defaultFont = LoadFont("assets/fonts/SuperMario256.ttf");

	// Inicializa todas cenas que serão usadas
	sceneHandler = initScenes();

	// Seta icone do jogo
	SetWindowIcon(screenIcon);

	// Define o fps do jogo
	SetTargetFPS(gameFps);

	// Loop do jogo
	while (!WindowShouldClose())
	{
		// Framecount que fica sendo atualizado para manipular
		// manipular quando um sprite deve ser mudado
		if (frameCount == 59)
			frameCount = 0;
		else
			frameCount++;

		BeginDrawing(); // Início da renderização

		ClearBackground(backgroudColor);

		// Manipula o comportamento da tela
		handleScene(&sceneHandler);

		EndDrawing(); // Fim da renderização
	}

	// Fecha a janela do jogo
	CloseWindow();

	return 0;
}
