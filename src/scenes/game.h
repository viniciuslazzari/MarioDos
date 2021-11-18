#ifndef _GAME_
#define _GAME_
#include "../globals.h"

typedef struct VectorXY
{
	int x;						                // Coordenada X
	int y;						                // Coordenada Y
} VectorXY;

typedef struct PipePosition {
    int x;						                // Coordenada X
    int y;						                // Coordenada Y
    int leftSideOfScreen;				        // Flag para saber de qual lado da tela o cano está
} PipePosition;

typedef struct Map
{
	// Sprites do mapa
	Texture2D plataform;
	Texture2D powerUp;
	Texture2D floor;
	Texture2D pipeToLeft;
	Texture2D flatPipe;
	Texture2D pipeToRigth;

	int numBlockingElements;			        // Número de bloqueios na tela
	VectorXY blockingElements[1000];		    // Vetor com a posição dos elementos
	int blockingElementsLoaded;			        // Flag para saber se os elementos já foram carregados

	int numPipePositions;				        // Número de canos na tela
	PipePosition pipePositions[10];			    // Vetor com a posição dos canos
	int pipePositionsLoaded;			        // Flag para saber se os canos já foram carregados
} Map;

typedef struct Mario
{
	int x;						                // Coordenada X
	int y;						                // Coordenada Y
	Texture2D sprite;				            // Sprite do mario
	int positionLoaded;				            // Flag para saber se a posição inicial do mario já foi carregada
	int isBlocked;					            // Flag para saber se o mario está bloqueado
	int jumpingSequence;				        // Timer de controle do pulo
} Mario;

typedef struct Player
{
	int lifes;					                // Quantidade de vidas
	int points;					                // Pontos
	Texture2D sprite;				            // Sprite das vidas
} Player;

typedef struct CoinPosition {
    int x;						                // Coordenada X
    int y;						                // Coordenada Y
    int isBlocked;					            // Flag para saber se a moeda está bloqueada
    int goingToRight;					        // Flag para saber para qual direção a moeda está indo
    int isCollected;					        // Flag para saber se a moeda já foi coletada
} CoinPosition;

typedef struct Coin
{
    int numCoins;					            // Número de moedas geradas
    int coinKey;					            // Chave para a geração da moeda
    int genereationSequence;				    // Timer para a geração das moedas
    Texture2D sprite;					        // Sprite da moeda
    CoinPosition positions[100];			    // Array com todas moedas
} Coin;

typedef struct TurtlePosition {
    int x;						                // Coordenada X
    int y;						                // Coordenada Y
    int isBlocked;					            // Flag para saber se a tartaruga está bloqueada
    int goingToRight;					        // Flag para saber para qual direção a tartaruga está indo
    int isDead;						            // Flag para saber se a tartaruga já foi derrotada
} TurtlePosition;

typedef struct Turtle
{
    int numTurtles;					            // Quantidade de tartarugas geradas
    int numTurtlesExpected;				        // Quantidade de tartarugas do nivel
    int genereationSequence;				    // Timer para a geração das tartarugas
    Texture2D sprite;					        // Sprite das tartarugas
    TurtlePosition positions[100];			    // Array com todas tartarugas
} Turtle;

typedef struct CrabPosition {
    int x;						                // Coordenada X
    int y;						                // Coordenada Y
    int isBlocked;					            // Flag para saber se o caranguejo está bloqueado
    int goingToRight;					        // Flag para saber para qual direção o caranguejo está indo
    int isDead;						            // Flag para saber se o caranguejo já foi derrotado
} CrabPosition;

typedef struct Crab
{
    int numCrabs;					            // Quantidade de caranguejos gerados
    int numCrabsExpected;				        // Quantidade de caranguejos do nivel
    int genereationSequence;				    // Timer para a geração dos caranguejos
    Texture2D sprite;					        // Sprite dos caranguejos
    CrabPosition positions[100];			    // Array com todos os caranguejos
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
