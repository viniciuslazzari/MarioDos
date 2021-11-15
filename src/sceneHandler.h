#ifndef _SCENE_HANDLER_
#define _SCENE_HANDLER_
#include "globals.h"
#include "scenes/menu.h"
#include "scenes/game.h"
#include "scenes/highscores.h"
#include "scenes/about.h"

// Define o tipo para a manipulação de cenas com
// cada cena e a opção de cena selecionada
typedef struct SceneHandler
{
	// Cenas
	Menu menu;
	Game newGame;
	Highscores highscores;
	About about;

	// Cena atual
	SceneOption currentScene;
} SceneHandler;

SceneHandler initScenes();
void handleScene(SceneHandler *sceneHandler);
void drawScene(SceneHandler *sceneHandler);

#endif