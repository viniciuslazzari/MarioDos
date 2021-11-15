#ifndef _GLOBALS_
#define _GLOBALS_

#include <raylib.h>

// Define a quantidade maxima de itens no menu
#define menuMaxOptions 6

// Define a quantidade maxima de itens no highscores
#define highscoresMaxOptions 5

extern Font defaultFont;

extern int frameCount;

// Constante de tamanho de tela
extern const int screenWidth;
extern const int screenHeight;
extern const int halfScreenWidth;
extern const int halfScreenHeight;

// Constante de tamanho do mapa
extern const int mapHeightChars;
extern const int mapWidthChars;

// Constantes do tamanho do elemento definido por cada caractere
extern const int elementHeight;
extern const int elementWidth;

extern const int deltha;

extern const int floorPosY;

// Define um enum com os tipos de cenas
// Usado no menu e para saber a cena atual
typedef enum
{
	MENU = -1,
	NEWGAME = 0,
	LOADGAME = 1,
	LOADMAP = 2,
	HIGHSCORES = 3,
	ABOUT = 4,
	EXIT = 5
} SceneOption;

// Função padrão que deve ser usada para escrever texto na tela
void DrawTextEx2(const char *text, float posX, float posY, int fontSize, Color color);

#endif
