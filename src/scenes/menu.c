#include <math.h>
#include "menu.h"
#include "../colors.h"

// Função para carregar o menu, suas variaveis e componentes
Menu initMenu()
{
	Menu menu;

	// Carrega a imagem de titulo
	Texture2D menuTitle = LoadTexture("assets/images/GameTitle.png");

	menu.menuTitle = menuTitle;

	// Carrega as opções do menu
	MenuOption newGameOption = {"Novo Jogo", NEWGAME};
	MenuOption loadGameOption = {"Continuar", LOADGAME};
	MenuOption loadMapOption = {"Carregar Mapa", LOADMAP};
	MenuOption highscoresOption = {"Ranking", HIGHSCORES};
	MenuOption aboutOption = {"Sobre", ABOUT};
	MenuOption exitOption = {"Sair", EXIT};

	menu.options[0] = newGameOption;
	menu.options[1] = loadGameOption;
	menu.options[2] = loadMapOption;
	menu.options[3] = highscoresOption;
	menu.options[4] = aboutOption;
	menu.options[5] = exitOption;

	// Define "Novo jogo" como a opção padrão do menu
	menu.currentOption = NEWGAME;

	return menu;
}

// Função para manipular o comportamento do menu
void handleMenu(Menu *menu, SceneOption *currentScene)
{
	// Receber o valor da opção atualmente selecionada
	int currentOptionValue = menu->currentOption;

	drawMenu(*menu);

	if (IsKeyPressed(KEY_UP))
	{
		// Decrementa próxima opção
		currentOptionValue--;

		// Teste de erro para caso o valor seja menor que 0 ir direto para
		// a ultima opção
		if (currentOptionValue < 0)
			currentOptionValue = menuMaxOptions - 1;
	}
	else if (IsKeyPressed(KEY_DOWN))
	{
		// Incrementa próxima opção
		currentOptionValue++;

		// Teste de erro para caso o valor seja maior que a quantidade de
		// opções. vai para a primeira opção
		if (currentOptionValue > (menuMaxOptions - 1))
			currentOptionValue = 0;
	}
	else if (IsKeyPressed(KEY_ENTER))
	{
		// Se for clicado "enter", define a tela atual com a opção selecionada
		*currentScene = menu->options[currentOptionValue].value;
	}

	// Define a próxima opção selecionada
	menu->currentOption = menu->options[currentOptionValue].value;
}

// Função para desenhar o menu
void drawMenu(Menu menu)
{
	drawMenuTitle(menu);
	drawMenuOptions(menu);
}

// Função para desenhar o titulo
void drawMenuTitle(Menu menu)
{
	// Define posicionamento na tela
	Rectangle sourceRec = {0.0f, 0.0f, (float)menu.menuTitle.width, (float)menu.menuTitle.height};

	Rectangle destRec = {halfScreenWidth - menu.menuTitle.width / 2.0f, halfScreenHeight - menu.menuTitle.height / 2.0f - 200,
						 menu.menuTitle.width * 3.0f, menu.menuTitle.height * 3.0f};

	Vector2 origin = {(float)menu.menuTitle.width, (float)menu.menuTitle.height};

	int rotation = 0;

	// Printa na tela
	DrawTexturePro(menu.menuTitle, sourceRec, destRec, origin, (float)rotation, WHITE);
}

// Função para desenhar as opções do menu
// #TODO: esse posicionamento das opções tta todo errado
void drawMenuOptions(Menu menu)
{
	int fontSize = 28;
	int padding = 50;
	float posY = 300;
	float posX;

	// Laço para iterar pela opções
	for (int i = 0; i < menuMaxOptions; i++)
	{
		// Define posicionamento da opção na tela
		posX = halfScreenWidth - MeasureText(menu.options[i].label, fontSize) / 2.0f;

		// Verifica se a opção é a opção atualmente selecionada para pintar de amarelo
		if (menu.options[i].value == menu.currentOption)
			DrawTextEx2(menu.options[i].label, posX, posY, fontSize, yellow);
		else
			DrawTextEx2(menu.options[i].label, posX, posY, fontSize, WHITE);

		// Incrementa a altura para desenhar a próxima abaixo
		posY += padding;
	}
}
