#ifndef _GAME_
#define _GAME_
#include "../globals.h"

typedef struct VectorXY
{
	int x;
	int y;
} VectorXY;

typedef struct PipePosition {
    int x;
    int y;
    int leftSideOfScreen;
} PipePosition;

typedef struct Map
{
	Texture2D plataform;
	Texture2D powerUp;
	Texture2D floor;
	Texture2D pipeToLeft;
	Texture2D flatPipe;
	Texture2D pipeToRigth;

	int numBlockingElements;
	VectorXY blockingElements[1000];
	int blockingElementsLoaded;

	int numPipePositions;
	PipePosition pipePositions[10];
	int pipePositionsLoaded;
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

typedef struct CoinPosition {
    int x;
    int y;
    int isBlocked;
    int goingToRight;
    int isCollected;
} CoinPosition;

typedef struct Coin
{
    int numCoins;
    int coinKey;
    int genereationSequence;
	Texture2D sprite;
	CoinPosition positions[100];
} Coin;

typedef struct TurtlePosition {
    int x;
    int y;
    int isBlocked;
    int goingToRight;
    int isDead;
} TurtlePosition;

typedef struct Turtle
{
    int numTurtles;
    int numTurtlesExpected;
    int genereationSequence;
	Texture2D sprite;
	TurtlePosition positions[100];
} Turtle;

typedef struct CrabPosition {
    int x;
    int y;
    int isBlocked;
    int goingToRight;
    int isDead;
} CrabPosition;

typedef struct Crab
{
    int numCrabs;
    int numCrabsExpected;
    int genereationSequence;
	Texture2D sprite;
	CrabPosition positions[100];
} Crab;

typedef struct Game
{
    char *fileMap;
	int isGameConfigRead;
	int timeBetweenEnemies;
	Map map;
	Mario mario;
	Player player;
	Coin coin;
	Turtle turtle;
	Crab crab;
} Game;

Game initGame();
Map initMap();
Mario initMario();
Player initPlayer();
Coin initCoin();
Turtle initTurtle();
Crab initCrab();
void handleGame(Game *game, SceneOption *currentScene);
void drawGame(Game *game);
void drawInterface(Game *game);
void drawMap(Game *game);
void getGameConfig(Game *game);
void drawElementInScreen(char element, int posX, int posY, Game *game);
Texture2D getTextureByChar(char element, Map map);
void drawFloor(Texture2D floor);
void drawPipeBody(int posX, int posY, Texture2D flatPipe, int isPipeInLeftSide);
void updateMario(Game *game);
void generateCoins(Game *game);
void generateTurtles(Game *game);
void generateCrabs(Game *game);

#endif
