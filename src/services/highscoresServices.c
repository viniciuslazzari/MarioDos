#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "highscoresServices.h"

const char *filename = "data/scores/highscores.bin";

// Função para carregar um array de estruturas que será passado por parâmetro
// com todos os dados das maiores pontuações
void loadScores(Score *scores)
{
	FILE *ptrScores;
	Score singleScore, arrayScores[5];

	// Essa função pode ser util para popular o .bin, por isso não tirar
	/////////////////////////////////
	// Score teste[5] = {
	// 	[0] = {"Vinicius", 10000},
	// 	[1] = {"Julia", 5000},
	// 	[2] = {"Diogo", 4500},
	// 	[3] = {"Amanda", 600},
	// 	[4] = {"Paulo", 5},
	// };

	// ptrScores = fopen(filename, "wb");

	// if (ptrScores != NULL)
	// {
	// 	for (int i = 0; i < 5; i++)
	// 	{
	// 		if (fwrite(&teste[i], sizeof(struct Score), 1, ptrScores) != 1)
	// 			printf("Erro na escrita !\n");
	// 	}

	// 	fclose(ptrScores);
	// }
	/////////////////////////////////

	// Abre o arquivo
	ptrScores = fopen(filename, "rb");

	// Testa se conseguiu abrir o arquivo
	if (ptrScores != NULL)
	{
		// Para cada estrutura esperada de pontuação
		for (int i = 0; i < highscoresMaxOptions; i++)
		{
			// Tenta ler a estrutura do arquivo e adicionar no array "arrayScores"
			if (fread(&singleScore, sizeof(struct Score), 1, ptrScores) == 1)
				arrayScores[i] = singleScore;
			else
				// Se não der, estoura erro
				printf("Erro na leitura!\n");
		}

		// Fecha o arquivo
		fclose(ptrScores);
	}
	else
	{
		printf("Erro ao abrir arquivo de pontuações!\n");
	}

	// Após o array estar populado, popula o array que foi passado por parâmetro
	// Possível melhoria no futuro
	for (int i = 0; i < highscoresMaxOptions; i++)
	{
		*scores = arrayScores[i];
		scores++;
	}
}

// Função que receb uma struct de pontuação e caso a pontuação esteja entre as 5
// maiores, insere no arquivo, senão retorna nulo
void insertScore(Score newScore)
{
	FILE *ptrScores;
	int insertPosition = -1;
	Score arrayScores[5], arrayScoresBkp[5];

	// Carrega todas as pontuações
	loadScores(arrayScores);

	// Cria um array de backup que sera usado depois
	for (int i = 0; i < highscoresMaxOptions; i++)
	{
		arrayScoresBkp[i] = arrayScores[i];
	}

	// Loop que verifica se a pontuação passada por parâmetro está entre as 5 maiores
	for (int i = 0; i < highscoresMaxOptions; i++)
	{
		if (arrayScores[i].value < newScore.value)
		{
			insertPosition = i;
			break;
		}
	}

	// Se não estiver, retorna
	if (insertPosition == -1)
		return;

	// Se estiver, move todos os itens a direita da posição que o item ficará para a direita
	for (int i = insertPosition + 1; i < highscoresMaxOptions; i++)
	{
		arrayScores[i] = arrayScoresBkp[i - 1];
	}

	// Insere a pontuação na pontuação correta
	arrayScores[insertPosition] = newScore;

	// Abre o arquivo de pontuações
	ptrScores = fopen(filename, "wb");

	// Testa se o arquivo foi aberto
	if (ptrScores != NULL)
	{
		// Com o array pronto, para cada item do array, insere o item no arquivo
		for (int i = 0; i < highscoresMaxOptions; i++)
		{
			if (fwrite(&arrayScores[i], sizeof(struct Score), 1, ptrScores) != 1)
				printf("Erro na escrita !\n");
		}

		// Fecha o arquivo
		fclose(ptrScores);
	}
	else
	{
		printf("Erro ao abrir arquivo de pontuações!\n");
	}
}
