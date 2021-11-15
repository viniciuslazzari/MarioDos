#ifndef _MENU_
#define _MENU_
#include "../globals.h"

// Tipo de opção do menu
typedef struct MenuOption
{
	const char *label; // O que vai ser escrito na tela
	SceneOption value; // Valor da opção
} MenuOption;

typedef struct Menu
{
	Texture2D menuTitle;				// Textura 2D da imagem do titulo
	MenuOption options[menuMaxOptions]; // Array de opções
	SceneOption currentOption;			// Variavel para saber a opção selecionada atualmente
} Menu;

Menu initMenu();
void handleMenu(Menu *menu, SceneOption *currentScene);
void drawMenu(Menu menu);
void drawMenuTitle(Menu menu);
void drawMenuOptions(Menu menu);

#endif