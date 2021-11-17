#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "game.h"
#include "../globals.h"
#include "../colors.h"

// Função para iniciar o jogo
Game initGame()
{
	Game game;

	// Define qual é a fase inicial do jogo
	game.fileMap = "data/phases/nivel1.txt";

	// Os elementos do jogo são retornados através de uma função
	game.map = initMap();
	game.mario = initMario();
	game.player = initPlayer();
	game.coin = initCoin();

	return game;
}

// Função para retornar as texturas que serão usadas no mapa
Map initMap()
{
	Map map;

	// Define as texturas
	map.plataform = LoadTexture("assets/sprites/plataform.png");
	map.powerUp = LoadTexture("assets/sprites/powerUp.png");
	map.floor = LoadTexture("assets/sprites/floor.png");
	map.pipeToLeft = LoadTexture("assets/sprites/pipeToLeft.png");
	map.flatPipe = LoadTexture("assets/sprites/flatPipe.png");
	map.pipeToRigth = LoadTexture("assets/sprites/pipeToRigth.png");

	map.blockingElementsLoaded = 0;
	map.numBlockingElements = 0;

    map.pipePositionsLoaded = 0;
	map.numPipePositions = 0;

	return map;
}

// Função para inicializar o elemento do mario
Mario initMario()
{
    Mario mario;

    // Carrega assets do Mario
	mario.sprite = LoadTexture("assets/sprites/mario.png");
	mario.positionLoaded = 0;
	mario.isBlocked = 0;
	mario.jumpingSequence = 0;

	return mario;
}

// Função para iniciar o elemento de jogador
Player initPlayer()
{
    Player player;

    // Carrega assets do Mario
    player.lifes = 3;
    player.points = 0;
    player.sprite = LoadTexture("assets/sprites/lifes.png");

	return player;
}

// Função para iniciar o elemento de moeda
Coin initCoin(){
    Coin coin;

    coin.numCoins = 0;
	coin.sprite = LoadTexture("assets/sprites/coin.png");
	coin.coinKey = 11;
	coin.genereationSequence = 0;

    return coin;
}

// Função para controlar os estados do jogo
void handleGame(Game *game, SceneOption *currentScene)
{
	drawGame(game);
	drawInterface(game);
}

// Função para desenhar todo jogo
void drawGame(Game *game)
{
	drawMap(game);
	updateMario(game);
	generateCoins(game);
}

// Função para desenhar a interface do jogo
void drawInterface(Game *game){
    int posX = 20, posY = 20;
    char pointsString[6];

    // Converte os pontos para string
    sprintf(pointsString, "%d", game->player.points);

    // Printa os pontos na tela
    DrawTextEx2(pointsString, posX, posY, 28, WHITE);

    // Adiciona o espaçamento para as vidas
    posX += 100;

    // Inicializa as posições padrão
    Rectangle sourceRec = {0.0f, 0.0f, (float)game->player.sprite.width, (float)game->player.sprite.height};
	Vector2 origin = {(float)game->player.sprite.width, (float)game->player.sprite.height};
	int rotation = 0;

	// Para cada vida do jogador
    for (int i = 0; i < game->player.lifes; i++){
        Rectangle destRec = {(float)posX, (float)posY, (float)30, (float)30};

        // Desenha o elemento na tela
        DrawTexturePro(game->player.sprite, sourceRec, destRec, origin, (float)rotation, WHITE);

        // Adiciona o espaçamento entre as vidas
        posX += 50;
    }
}

// Função para desenhar o mapa do jogo
void drawMap(Game *game)
{
	FILE *ptrGame;
	char element;
	int g = 0;

	int posX = 0, posY = 0;

	// Abre o arquivo da fase
	ptrGame = fopen(game->fileMap, "r");

	// Testa para ver se conseguiu abrir o arquivo
	if (ptrGame != NULL)
	{
		// Para cada elemento no arquivo
		// (mapWidthChars * mapHeightChars) + mapHeightChars para considerar os "\n"
		for (int i = 0; i < (mapWidthChars * mapHeightChars); i++)
		{
			// Tentar ler o char do arquivo
			if (fread(&element, sizeof(char), 1, ptrGame) == 1)
			{
				// Se for "quebra de linha", ignora
				if ((int)element == 10)
					continue;

				// Função para resetar a posição X cada vez que for para uma nova linha
				// (mapWidthChars + 1) para considerar os "\n"
				if (i % (mapWidthChars + 1) == 0)
				{
					posX = 0;
					posY += elementHeight;
				}
				else
				{
					posX += elementWidth;
				}

				// Se for o elemento neutro "-" ou "m" de mario, pula
                if (element != '-' && element != 'm'){
                    // Desenha o elemento na tela
                    drawElementInScreen(element, posX, posY, game);

                    // Adiciona os elementos de bloqueio no array
                    if (game->map.blockingElementsLoaded == 0){
                        game->map.blockingElements[g].x = posX;
                        game->map.blockingElements[g].y = posY;

                        ++g;
                    }
                }

                // Deve carregar as posições do mario apenas uma vez
                if (element == 'm' && game->mario.positionLoaded == 0){
                    game->mario.x = posX;
                    game->mario.y = posY;
                    game->mario.positionLoaded = 1;
                }
			}
			else
				printf("Erro na leitura!\n");
		}

		// Fecha o ponteiro
		fclose(ptrGame);
	}
	else
	{
		printf("Erro ao abrir arquivo do mapa!\n");
	}

    if (game->map.blockingElementsLoaded == 0){
        game->map.numBlockingElements = g - 1;
    }

    game->map.pipePositionsLoaded = 1;
	game->map.blockingElementsLoaded = 1;

	// Função para desenhar o chão do jogo, que não muda
	drawFloor(game->map.floor);
}

// Função para desenhar um elemento (char), na tela
void drawElementInScreen(char element, int posX, int posY, Game *game)
{
    int width = elementWidth;
    int height = elementHeight;
	Texture2D elementTexture;

	if (element == 'b') {
        width = 40;
        height = 40;
	}

	// Função que retorna a textura a ser utilizada pelo char
	elementTexture = getTextureByChar(element, game->map);

	// Posicionamento padrão na tela
	Rectangle sourceRec = {0.0f, 0.0f, (float)elementTexture.width, (float)elementTexture.height};
	Rectangle destRec = {(float)posX, (float)posY, (float)width, (float)height};
	Vector2 origin = {(float)elementTexture.width, (float)elementTexture.height};
	int rotation = 0;

	// Desenha o elemento na tela
	DrawTexturePro(elementTexture, sourceRec, destRec, origin, (float)rotation, WHITE);

	// Se o elemento for um cano, é necesário desenhar o resto do corpo dele
	if (isdigit(element) || element == 's'){
        PipePosition pipePosition;
        int isPipeInLeftSide = 1;

        // Verifica se o cano está do lado direito da tela
        if (posX > halfScreenWidth)
            isPipeInLeftSide = 0;

        // Função que desenha o corpo do cano
		drawPipeBody(posX, posY, game->map.flatPipe, isPipeInLeftSide);

		if (game->map.pipePositionsLoaded == 0 && element == 's'){
            pipePosition.x = posX;
            pipePosition.y = posY;
            pipePosition.leftSideOfScreen = isPipeInLeftSide;

            game->map.pipePositions[game->map.numPipePositions] = pipePosition;
            game->map.numPipePositions++;
		}
	}
}

// Função que retorna a textura que deve ser utilizada pelo char
Texture2D getTextureByChar(char element, Map map)
{
	Texture2D elementTexture;

	// Escolhe textura pelo char
	switch (element)
	{
	case 'p':
		elementTexture = map.plataform;
		break;

	case 'b':
		elementTexture = map.powerUp;
		break;

	case 's':
		elementTexture = map.flatPipe;
		break;

	default:
		break;
	}

	// Se for cano, retorna flatPipe
	if (isdigit(element))
		elementTexture = map.flatPipe;

	// Retorna a textura
	return elementTexture;
}

// Função para desenhar o chão do mapa
void drawFloor(Texture2D floor)
{
	// posY padrão
	int posX = 0, posY = floorPosY;

	// Posicionamento na tela
	Rectangle sourceRec = {0.0f, 0.0f, (float)floor.width, (float)floor.height};
	Vector2 origin = {(float)floor.width, (float)floor.height};

	int rotation = 0;

	// Para cada linha
	for (int i = 0; i < mapHeightChars; i++)
	{
		// Reseta a posição em X
		posX = 0;

		// Para cada coluna
		for (int j = 0; j < mapWidthChars + 1; j++)
		{
			// Desenha a textura de chão na posicão X, Y
			Rectangle destRec = {(float)posX, (float)posY, (float)elementWidth, (float)elementHeight};
			DrawTexturePro(floor, sourceRec, destRec, origin, (float)rotation, WHITE);

			// Aumenta a posição em X para próxima iteração
			posX += elementWidth;
		}

		// Após desenhar todas as colunas de uma linha, aumenta Y
		posY += elementHeight;
	}
}

// Função para desenhar o corpo do cano
void drawPipeBody(int posX, int posY, Texture2D flatPipe, int isPipeInLeftSide)
{
	// Posicionamento na tela padrão
	Rectangle sourceRec = {0.0f, 0.0f, (float)flatPipe.width, (float)flatPipe.height};
	Vector2 origin = {(float)flatPipe.width, (float)flatPipe.height};
	int rotation = 0;

	// Checa em qual lado da tela o cano está
	if (isPipeInLeftSide)
	{
		// Se estiver na esquerda, itera a posição de X, desenhando o corpo do cano, diminuindo X
		// pelo tamanho do elemento desenhado, até que X = 0, o canto da tela
		while (posX != 0)
		{
			Rectangle destRec = {(float)posX, (float)posY, (float)elementWidth, (float)80};
			DrawTexturePro(flatPipe, sourceRec, destRec, origin, (float)rotation, WHITE);

			posX -= elementWidth;
		}
	}
	else
	{
		// Se estiver na direita, itera a posição de X, desenhando o corpo do cano, aumentando X
		// pelo tamanho do elemento desenhado, até que X = screenWidth, o canto da tela
		while (posX != screenWidth)
		{
			Rectangle destRec = {(float)posX, (float)posY, (float)elementWidth, (float)80};
			DrawTexturePro(flatPipe, sourceRec, destRec, origin, (float)rotation, WHITE);

			posX += elementWidth;
		}
	}
}

// Função que fica atualizando a posição do mario
void updateMario(Game *game){
    int sprite = 0;
    int widthDivider = 8;

    game->mario.isBlocked = 0;

    // Se o mario esta nos limites de um bloco de travamento ou está no chão, seta a flag de bloqueio
    for(int i = 0; i <= game->map.numBlockingElements; i++){
        if (game->map.blockingElements[i].y == (game->mario.y + 75) &&
            (game->mario.x >= game->map.blockingElements[i].x && game->mario.x <= (game->map.blockingElements[i].x + 50)))
        {
            game->mario.isBlocked = 1;
        }

        if ((game->mario.y + 75) == floorPosY){
            game->mario.isBlocked = 1;
        }
    }

	// Se a tecla para esquerda for pressionada, move o mario para esquerda
    if (IsKeyDown(KEY_LEFT))
	{
	    game->mario.x -= deltha;
	    sprite = 1;
	    widthDivider = -widthDivider;
	}

	// Se a tecla para direita for pressionada, move o mario para direita
	if (IsKeyDown(KEY_RIGHT))
	{
	    game->mario.x += deltha;
	    sprite = 1;
	}

    // Se o mario não estiver bloqueado e não estiver pulando, faz ele cair
    if (game->mario.isBlocked == 0 && game->mario.jumpingSequence == 0){
        game->mario.y += deltha;
        sprite = 6;
    }

    // Se o mario não estiver pulando e tentar pular, atualiza sua altura
    if (IsKeyPressed(KEY_UP) && game->mario.jumpingSequence == 0)
	{
	    game->mario.jumpingSequence = 30;
	    sprite = 4;
	}

    // Se o Mario estiver pulando, atualiza sua altura
    if (game->mario.jumpingSequence != 0){
        game->mario.y -= deltha;
        game->mario.jumpingSequence--;
        sprite = 4;
    }

    for (int i = 0; i < game->coin.numCoins; i++){
        if (game->mario.x == game->coin.positions[i].x && game->mario.y == game->coin.positions[i].y && game->coin.positions[i].isCollected == 0){
            game->player.points += 400;
            game->coin.positions[i].isCollected = 1;
        }
    }

    // Posicionamento padrão na tela
	Rectangle sourceRec = {(float)game->mario.sprite.width / 8 * sprite, 0.0f, (float)game->mario.sprite.width / widthDivider, (float)game->mario.sprite.height};
	Rectangle destRec = {(float)game->mario.x, (float)game->mario.y, 50, 75};
	Vector2 origin = {50, 8};
	int rotation = 0;

	// Desenha o elemento na tela
	DrawTexturePro(game->mario.sprite, sourceRec, destRec, origin, (float)rotation, WHITE);
}

// Função para gerar moedas aleatóriamente e desenhar na tela
void generateCoins(Game *game){
    int r = 0;
    int coinWidth = 50;
    int coinHeight = 75;
    CoinPosition position;
    int pipePositionOfCoin = 0;

    // Gera um número aleatório até 15
    srand(time(NULL));
    r = rand() % 15;

    // Se uma moeda tiver sido gerada recentemente, decrementa o timer
    if (game->coin.genereationSequence != 0){
        game->coin.genereationSequence--;
    }

    // Se o número gerado for igual a chave de geração e nenhuma moeda tenha sido gerada recentemente
    if (game->coin.coinKey == r && game->coin.genereationSequence == 0) {
        // Gera uma nova chave
        game->coin.coinKey = rand() % 15 - 2;

        // Reseta o time
        game->coin.genereationSequence = 300;

        // Recebe a posição de um cano aleatório
        pipePositionOfCoin = rand() % game->map.numPipePositions;

        // Cria um elemento de posição de moeda
        position.x = game->map.pipePositions[pipePositionOfCoin].x;
        position.y = game->map.pipePositions[pipePositionOfCoin].y;
        position.goingToRight = game->map.pipePositions[pipePositionOfCoin].leftSideOfScreen;
        position.isBlocked = 0;
        position.isCollected = 0;

        // Incrementa as variáveis
        game->coin.positions[game->coin.numCoins] = position;
        game->coin.numCoins++;
    }

    // Posicionamento padrão na tela
	Rectangle sourceRec = {0.0f, 0.0f, (float)game->coin.sprite.width, (float)game->coin.sprite.height};
	Vector2 origin = {0, 3};
	int rotation = 0;

	// Reseta o bloqueio de todas moedas
	for (int i = 0; i < game->coin.numCoins; i++){
	    game->coin.positions[i].isBlocked = 0;
	}

    for (int i = 0; i < game->coin.numCoins; i++){

        // Se a moeda esta nos limites de um bloco de travamento ou está no chão, seta a flag de bloqueio
        for(int j = 0; j <= game->map.numBlockingElements; j++){
            if (game->map.blockingElements[j].y == (game->coin.positions[i].y + coinHeight) &&
               (game->coin.positions[i].x >= game->map.blockingElements[j].x) && game->coin.positions[i].x <= (game->map.blockingElements[j].x + 5))
            {
                game->coin.positions[i].isBlocked = 1;
            }

            if ((game->coin.positions[i].y + coinHeight) == floorPosY){
                game->coin.positions[i].isBlocked = 1;
            }
        }

        // Controla a movimentação da moeda
        if (game->coin.positions[i].isBlocked == 1){

            // Muda a posição horizontal conforme orientação
            if (game->coin.positions[i].goingToRight){
                game->coin.positions[i].x += deltha;
            } else {
                game->coin.positions[i].x -= deltha;
            }

            // Reseta posição se ficar na borda
            if (game->coin.positions[i].x >= screenWidth && game->coin.positions[i].goingToRight == 1){
                game->coin.positions[i].x = 0;
            }

            // Reseta posição se ficar na borda
            if (game->coin.positions[i].x == 0 && game->coin.positions[i].goingToRight == 0){
                game->coin.positions[i].x = screenWidth;
            }
        }

        // Se a moeda estiver caindo, atualiza posição
        if (game->coin.positions[i].isBlocked == 0){
            game->coin.positions[i].y += deltha;
        }

        // Se a moeda não tiver sido coletada, printa ela na tela
        if (game->coin.positions[i].isCollected == 0){
            Rectangle destRec = {(float)game->coin.positions[i].x, (float)game->coin.positions[i].y, coinWidth, coinHeight};

            // Desenha o elemento na tela
            DrawTexturePro(game->coin.sprite, sourceRec, destRec, origin, (float)rotation, WHITE);
        }
    }
}
