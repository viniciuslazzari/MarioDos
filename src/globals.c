#include "globals.h"

// Constante de tamanho de tela
const int screenWidth = 1200;
const int screenHeight = 700;
const int halfScreenWidth = 600;
const int halfScreenHeight = 350;

// Constante de tamanho do mapa
const int mapHeightChars = 28;
const int mapWidthChars = 120;

// Constantes do tamanho do elemento definido por cada caractere
const int elementHeight = 25;
const int elementWidth = 10;

// Constante para movimentação na tela
const int deltha = 5;

// Constante para definir a que altura o chão deve ser renderizado
const int floorPosY = 675;

// Função global padrão para desenhar textos na tela com a fonte padrão
// Sempre usar essa função para desenhar textos
void DrawTextEx2(const char *text, float posX, float posY, int fontSize, Color color)
{
	DrawTextEx(defaultFont, text, (Vector2){posX, posY}, fontSize, 1, color);
}
