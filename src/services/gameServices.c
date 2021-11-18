#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "gameServices.h"

const char *filenameToSave = "data/phases/save.bin";

// Função para carregar um jogo salvo
Game loadGame(void)
{
	FILE *ptrGame;
	Game game;

	// Abre o arquivo padrão de salvamento
	ptrGame = fopen(filenameToSave, "rb");

	if (ptrGame != NULL)
	{
	    // Le os dados para a estrutura de Jogo
        if (fread(&game, sizeof(struct Game), 1, ptrGame) != 1)
            printf("Erro na leitura!\n");

        // Fecha o ponteiro
		fclose(ptrGame);
	}
	else
	{
		printf("Erro ao abrir arquivo de salvamento!\n");
	}

	// Retorna o jogo
	return game;
}

// Função para salvar o jogo atual em um arquivo
void saveGame(Game game)
{
	FILE *ptrGame;

	// Abre o arquivo padrão
	ptrGame = fopen(filenameToSave, "wb");

	if (ptrGame != NULL)
	{
	    // Verifica se foi possível salvar o jogo
		if (fwrite(&game, sizeof(struct Game), 1, ptrGame) != 1){
            printf("Erro na escrita!\n");
		}

		// Fecha o ponteiro
		fclose(ptrGame);
	}
	else
	{
		printf("Erro ao abrir arquivo de salvamento!\n");
	}
}
