#include <stdio.h>
#include "sceneHandler.h"
#include "globals.h"
#include "./services/gameServices.h"

// Inicia todas as cenas que serão usadas
SceneHandler initScenes()
{
	SceneHandler sceneHandler;

	// Inicia cenas
	Menu menu;
	menu = initMenu();
	sceneHandler.menu = menu;

	Game game;
	game = initGame();
	sceneHandler.newGame = game;

	Highscores highscores;
	highscores = initHighscores();
	sceneHandler.highscores = highscores;

	About about;
	about = initAbout();
	sceneHandler.about = about;

	// Define a cena atual como o "Menu" por padrão
	sceneHandler.currentScene = MENU;

	return sceneHandler;
}

// Função para manipular o comportamento das cenas
void handleScene(SceneHandler *sceneHandler)
{
	drawScene(sceneHandler);
}

// Função para desenhar a cena atual
void drawScene(SceneHandler *sceneHandler)
{
    Game game;

	// Switch para saber qual é a cena atual
	switch (sceneHandler->currentScene)
	{
	case MENU:
		handleMenu(&sceneHandler->menu, &sceneHandler->currentScene);
		break;
	case NEWGAME:
        sceneHandler->newGame.fileMap = "data/phases/nivel1.txt";
		handleGame(&sceneHandler->newGame, &sceneHandler->currentScene);
		break;
	case LOADGAME:
	    game = loadGame();
	    handleGame(&game, &sceneHandler->currentScene);
		break;
	case LOADMAP:
	    sceneHandler->newGame.fileMap = "data/phases/single.txt";
	    handleGame(&sceneHandler->newGame, &sceneHandler->currentScene);
		break;
	case HIGHSCORES:
		handleHighscores(&sceneHandler->highscores, &sceneHandler->currentScene);
		break;
	case ABOUT:
		handleAbout(&sceneHandler->about, &sceneHandler->currentScene);
		break;
	case EXIT:
		CloseWindow(); //#TODO Erro ao fechar janela dessa maneira
		break;
	}
}
