O trabalho foi realizado utilizando a biblioteca da raylib.
Comecei a fazer o trabalho em dupla com o João Raphael, que acabou abandonando o projeto no seu início.
Infelizmente, devido a alguns imprevistos e dificuldade com a raylib, o projeto ficou inacabado, porém grande parte dos requisitos foram atendidos.

Sobre as estruturas do projeto:

// Estrutura do Sobre
typedef struct About
{
	const char *title;				// Título da cena de ajuda
	const char *subtitle;				// Sub-titulo da cena de ajuda
	const char *credits;				// Créditos da cena de ajuda
	const char *repository;				// Repositório do projeto

	Texture2D marioSprites;				// Textura do mario para ficar animado na tela
	int currentMarioSprite;				// Controle do sprite atual da tela
} About;

// Estrutura de opção do menu
typedef struct MenuOption
{
	const char *label; 				// O que vai ser escrito na tela
	SceneOption value; 				// Valor da opção
} MenuOption;

// Estrutura do menu
typedef struct Menu
{
	Texture2D menuTitle;				// Textura 2D da imagem do titulo
	MenuOption options[menuMaxOptions]; 		// Array de opções
	SceneOption currentOption;			// Variavel para saber a opção selecionada atualmente
} Menu;

// Estrutura da opção do ranking
typedef struct Score
{
	char name[20];					// O que vai ser escrito na tela
	int value;					// Valor da opção
} Score;

// Estrutura do ranking
typedef struct Highscores
{
	int scoresLoaded;				// Flag para saber se o ranking já foi carregado
	Score scores[highscoresMaxOptions];		// Array com as opções
} Highscores;

// Estrutura de posição genérica
typedef struct VectorXY
{
	int x;						// Coordenada X
	int y;						// Coordenada Y
} VectorXY;

// Estrutura de posição do cano
typedef struct PipePosition {
    int x;						// Coordenada X
    int y;						// Coordenada Y
    int leftSideOfScreen;				// Flag para saber de qual lado da tela o cano está
} PipePosition;

// Estrutura do mapa
typedef struct Map
{
	// Sprites do mapa
	Texture2D plataform;				
	Texture2D powerUp;
	Texture2D floor;
	Texture2D pipeToLeft;
	Texture2D flatPipe;
	Texture2D pipeToRigth;

	int numBlockingElements;			// Número de bloqueios na tela
	VectorXY blockingElements[1000];		// Vetor com a posição dos elementos
	int blockingElementsLoaded;			// Flag para saber se os elementos já foram carregados

	int numPipePositions;				// Número de canos na tela
	PipePosition pipePositions[10];			// Vetor com a posição dos canos
	int pipePositionsLoaded;			// Flag para saber se os canos já foram carregados
} Map;

// Estrutura do mario
typedef struct Mario
{
	int x;						// Coordenada X
	int y;						// Coordenada Y
	Texture2D sprite;				// Sprite do mario
	int positionLoaded;				// Flag para saber se a posição inicial do mario já foi carregada
	int isBlocked;					// Flag para saber se o mario está bloqueado
	int jumpingSequence;				// Timer de controle do pulo
} Mario;

// Estrutura de jogador
typedef struct Player
{
	int lifes;					// Quantidade de vidas
	int points;					// Pontos
	Texture2D sprite;				// Sprite das vidas
} Player;

// Estrutura de posição da moeda
typedef struct CoinPosition {
    int x;						// Coordenada X
    int y;						// Coordenada Y
    int isBlocked;					// Flag para saber se a moeda está bloqueada
    int goingToRight;					// Flag para saber para qual direção a moeda está indo
    int isCollected;					// Flag para saber se a moeda já foi coletada
} CoinPosition;

// Estrutura da moeda
typedef struct Coin
{
    int numCoins;					// Número de moedas geradas
    int coinKey;					// Chave para a geração da moeda
    int genereationSequence;				// Timer para a geração das moedas
    Texture2D sprite;					// Sprite da moeda
    CoinPosition positions[100];			// Array com todas moedas
} Coin;

// Estrutura de posição das tartarugas
typedef struct TurtlePosition {
    int x;						// Coordenada X
    int y;						// Coordenada Y
    int isBlocked;					// Flag para saber se a tartaruga está bloqueada
    int goingToRight;					// Flag para saber para qual direção a tartaruga está indo
    int isDead;						// Flag para saber se a tartaruga já foi derrotada
} TurtlePosition;

// Estrutura da tartaruga
typedef struct Turtle
{
    int numTurtles;					// Quantidade de tartarugas geradas
    int numTurtlesExpected;				// Quantidade de tartarugas do nivel
    int genereationSequence;				// Timer para a geração das tartarugas
    Texture2D sprite;					// Sprite das tartarugas
    TurtlePosition positions[100];			// Array com todas tartarugas
} Turtle;

// Estrutura de posição dos caranguejos
typedef struct CrabPosition {
    int x;						// Coordenada X
    int y;						// Coordenada Y
    int isBlocked;					// Flag para saber se o caranguejo está bloqueado
    int goingToRight;					// Flag para saber para qual direção o caranguejo está indo
    int isDead;						// Flag para saber se o caranguejo já foi derrotado
} CrabPosition;

// Estrutura do caranguejo
typedef struct Crab
{
    int numCrabs;					// Quantidade de caranguejos gerados
    int numCrabsExpected;				// Quantidade de caranguejos do nivel
    int genereationSequence;				// Timer para a geração dos caranguejos
    Texture2D sprite;					// Sprite dos caranguejos
    CrabPosition positions[100];			// Array com todos os caranguejos
} Crab;

// Estrutura do jogo
typedef struct Game
{
    char *fileMap;					// Caminho do .txt com o nível atual
    int isGameConfigRead;				// Flag para saber se as configurações do jogo já foram lidas
    int timeBetweenEnemies;				// Tempo em segundos entre a geração dos inimigos
    Map map;						// Informações do mapa
    Mario mario;					// Informações do mario
    Player player;					// Informações do player
    Coin coin;						// Informações sobre as moedas do jogo
    Turtle turtle;					// Informações sobre as tartarugas do jogo
    Crab crab;						// Informações sobre os caranguejos do jogo
} Game;