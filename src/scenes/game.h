#ifndef _GAME_
#define _GAME_
#include "../globals.h"

typedef struct VectorXY
{
	int x;
	int y;
} VectorXY;

typedef struct Map
{
	Texture2D plataform;
	Texture2D powerUp;
	Texture2D floor;
	Texture2D pipeToLeft;
	Texture2D flatPipe;
	Texture2D pipeToRigth;

	VectorXY blockingElements[1000];
	int numBlockingElements;
	int blockingElementsLoaded;
} Map;

typedef struct Mario
{
	int x;
	int y;
	Texture2D sprite;
	int positionLoaded;
	int isBlocked;
	int jumpingSequence;
} Mario;

typedef struct Player
{
	int lifes;
	int points;
	Texture2D sprite;
} Player;

typedef struct Game
{
	const char *fileMap;
	Map map;
	Mario mario;
	Player player;
} Game;

Game initGame();
Map initMap();
Mario initMario();
Player initPlayer();
void handleGame(Game *game, SceneOption *currentScene);
void drawGame(Game *game);
void drawInterface(Game *game);
void drawMap(Game *game);
void drawElementInScreen(char element, int posX, int posY, Map map);
Texture2D getTextureByChar(char element, Map map);
void drawFloor(Texture2D floor);
void drawPipeBody(int posX, int posY, Texture2D flatPipe);
void updateMario(Game *game);

#endif
