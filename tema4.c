#include "utils.h"
#include <stdlib.h>


void* (* Abilities[4])(void* x) = {RotateMatrix, DecodeString, InvertArray, KillPlayer};

char *fromEnumtoString(PlayerRoles playerRole)
{
	char *str = calloc(MAX_LEN_STR_ATR, sizeof(char));
	switch(playerRole)
	{
		case Rotator:
			str = strcpy(str, "Rotator");
			break;
		case Decoder:
			str = strcpy(str, "Decoder");
			break;
		case Invertor:
			str = strcpy(str, "Invertor");
			break;
		case Impostor:
			str = strcpy(str, "Impostor");
			break;
	}
	return str;
}

// Task 1
void *RotateMatrix(void *input)
{
	/*Castez void pointerul la int pointer
	si valoarea o salvez in variabila n*/
	int n = *((int *)input);

	/*Initializez cu NULL variabila
	buffer care va contine matricea*/
	char *buffer = NULL;
	int i, j, nr = 0, nr_alloc, len = 0;
	
	//Calculez numarul de cifre ale lui n
	int copie = n;
	while (copie != 0) {
		copie = copie / 10;
		nr++;
	}

	//Formula pentru alocarea matricei
	nr_alloc = 1 + n * (n + 2 * nr * n);

	buffer = malloc(nr_alloc * sizeof(char));

	//Verific daca alocarea a avut loc cu succes
	if (buffer == NULL) {
		printf("Could not allocate \n");
		exit(1);		
	}

	for (i = 1; i <= n; i++) {
		for (j = n; j >= 1; j--) {
			//Adaug in buffer elementele matricei
			len += sprintf(buffer + len, "%d%d ", j, i);
		}
		len--;
		len += sprintf(buffer + len, "\n");
	}

	//Adaug sfarsitul de sir
	buffer[len - 1] = '\0';
	
	return (void *)buffer;
}

// Task 2
void *DecodeString(void *input)
{
	//Castez void pointerul la char pointer
	char *string = (char *)input;
	char *buffer;
	int sum = 0, nr;
	char *number, *pch = NULL;

	//Aloc șirului de caractere 16 octeti, multiplu de 4
	buffer = malloc(16 * sizeof(char));

	//Verific dacă alocarea a avut loc cu succes
	if (buffer == NULL) {
		printf("Could not allocate \n");
		exit(1);		
	}

	//Despart sirul de caractere pentru a calcula suma 
	number = strtok(string, "_\n");
	while (number != NULL) {
		//retin in variabila nr valoarea intreaga a lui number
		nr = strtol(number, &pch, 10);
		sum = sum + nr;
		number = strtok(NULL, "_\n");
	}

	//adaug sum in sirul de caractere buffer
	sprintf(buffer, "%d", sum);

	return (void *)buffer;
}

//Task 3
void *InvertArray(void *input)
{
	//Castez void pointerul la int pointer
	int *array = (int *)input;
	int aux, i, nr, len = 0;
	char *buffer;

	// Inițializez intregul nr cu prima valoare din vector
	nr = *(array);

	//Aloc șirului de caractere 16 octeti, multiplu de 4
	buffer = malloc(16 * nr * sizeof(char));

	//Verific dacă alocarea a avut loc cu succes
	if (buffer == NULL) {
		printf("Could not allocate \n");
		exit(1);		
	}
	
	//Verific daca primul numar este par sau impar
	if (nr % 2 == 0) {
		/*Daca nr este par atunci interschimb
		elementele de pe pozitiile 2k + 1 cu 
		elementele de pe pozitiile 2k + 2*/
		for (i = 1; i < nr; i += 2) {
			aux = *(array + i);
			*(array + i) = *(array + i + 1);
			*(array + i + 1) = aux;
		}
	}
	else {
		//Daca nr este impar atunci inversez vectorul
		for (i = 1; i <= nr / 2; i++) {
			aux = *(array + i);
			*(array + i) = *(array + nr + 1 - i);
			*(array + nr + 1 - i) = aux;
		}
	}

	//Adaug elementele in buffer
	for (i = 1; i <= nr; i++) {
		len += sprintf(buffer + len, "%d ", *(array + i));
	}
	
	//Adaug sfarsitul de sir
	buffer[len - 1] = '\0';

	return (void *)buffer;
}

//Task 4
Player *allocPlayer()
{
	/*Aloc structura si campurile acesteia.
	Verific daca alocarile au avut succes.*/
	Player *player = calloc(1, sizeof(Player));
	if (player == NULL) {
		printf("Could not allocate \n");
		exit(1);		
	}

	player->name = calloc(MAX_LEN_STR_ATR, sizeof(char));
	if (player->name == NULL) {
		printf("Could not allocate \n");
		exit(1);		
	}

	player->color = calloc(MAX_LEN_STR_ATR, sizeof(char));
	if (player->color == NULL) {
		printf("Could not allocate \n");
		exit(1);		
	}

	player->hat = calloc(MAX_LEN_STR_ATR, sizeof(char));
	if (player->hat == NULL) {
		printf("Could not allocate \n");
		exit(1);		
	}

	//Setez valoarea intregului alive cu 1	
	player->alive = 1;
	
	return player;
}

//Task 4
Game *allocGame()
{
	/*Aloc structura si campul name al acesteia.
	Verific daca alocarea a avut loc cu succes.*/
	Game *game = calloc(1, sizeof(Game));
	if (game == NULL) {
		printf("Could not allocate \n");
		exit(1);		
	}
	
	game->name = calloc(MAX_LEN_STR_ATR, sizeof(char));
	if (game->name == NULL) {
		printf("Could not allocate \n");
		exit(1);		
	}
	return game;
}

//Task 5
Player *ReadPlayer(FILE *inputFile)
{	
	//Apelez functia de alocare a jucatorului
	Player *player = allocPlayer();

	//Aloc dinamic variabila role care retine rolul jucatorului
	char *role = malloc(MAX_LEN_STR_ATR * sizeof(char));

	//Verific daca alocarea a avut loc cu succes
	if (role == NULL) {
		printf("Could not allocate \n");
		exit(1);		
	}
	
	int i;

	//Citesc fiecare camp din structura
	fscanf(inputFile, "%s\n", player->name);
	fscanf(inputFile, "%s\n", player->color);
	fscanf(inputFile, "%s\n", player->hat);
	fscanf(inputFile, "%d\n", &(player->numberOfLocations));

	//Aloc dinamic vectorul de structuri de tip Location
	player->locations = calloc(player->numberOfLocations, sizeof(Location));

	//Verific daca alocarea a avut loc cu succes
	if (player->locations == NULL) {
		printf("Could not allocate \n");
		exit(1);		
	}

	//Citesc cordonatele locatiilor
	for (i = 0; i < player->numberOfLocations; i++) {
		while (fgetc(inputFile) != '(');
		fscanf(inputFile, "%d", &(player->locations[i].x));
		fgetc(inputFile); 
		fscanf(inputFile, "%d", &(player->locations[i].y));
    }

	//Citesc ultima paranteza si endline
	fgetc(inputFile);
	fgetc(inputFile);
	fscanf(inputFile, "%s\n", role);

	//Verific rolul jucatorului si setez abilitatea
	if (role[1] == 'o') {
		player->playerRole = Rotator;
		player->ability = Abilities[0];
	}
	else if (role[1] == 'e') {
		player->playerRole = Decoder;
		player->ability = Abilities[1];
	}
	else if (role[1] == 'n') {
		player->playerRole = Invertor;
		player->ability = Abilities[2];
	}
	else {
		player->playerRole = Impostor;
		player->ability = Abilities[3];
	}

	//Dezaloc sirul de caractere role
	free(role);

	return player;
}

// Task 5
Game *ReadGame(FILE *inputFile)
{
	//Apelez functia allocGame
	Game *game = allocGame();
	int i;

	//Citesc fiecare camp din structura
	fscanf(inputFile, "%s\n", game->name);
	fscanf(inputFile, "%d\n", &(game->killRange));
	fscanf(inputFile, "%d\n", &(game->numberOfCrewmates));
	game->crewmates = calloc(game->numberOfCrewmates, sizeof(Player *));

	//Verific daca alocarea a avut loc cu succes
	if (game->crewmates == NULL) {
		printf("Could not allocate \n");
		exit(1);		
	}

	//Apelez functia ReadPlayer pentru fiecare jucator si impostor
	for (i = 0; i < game->numberOfCrewmates; i++) {
		game->crewmates[i] = ReadPlayer(inputFile);
	}

	game->impostor = ReadPlayer(inputFile);
	return game;
}

// Task 6
void WritePlayer(Player *player, FILE *outputFile)
{   
	//Variabila role retine sirul de caractere ce contine rolul jucatorului
	char *role = fromEnumtoString(player->playerRole);

	//Afisez campurile jucatorului conform formatului dorit
	fprintf(outputFile, "Player %s with color %s, hat %s and role %s has entered the game.\n", 
	player->name, player->color, player->hat, role);
	fprintf(outputFile, "Player's locations: ");
	
	//Pentru fiecare jucator afisez locatiile acestuia
	for (int i = 0; i < player->numberOfLocations; i++) {
		fprintf(outputFile, "(%d,%d) ", player->locations[i].x, player->locations[i].y);
	}

	//Dezaloc sirul de caractere role
	free(role);
}

// Task 6
void WriteGame(Game *game, FILE *outputFile)
{
	//Afisez fiecare camp din structura conform formatului cerut
	fprintf(outputFile, "Game %s has just started!\n\t", game->name);
	fprintf(outputFile, "Game options:\n");
	fprintf(outputFile, "Kill Range: %d\n", game->killRange);
	fprintf(outputFile, "Number of crewmates: %d\n\n\t", game->numberOfCrewmates);
	fprintf(outputFile, "Crewmates:\n");
	
	//Pentru fiecare jucator apelez functia de afisare WritePlayer
	for (int i = 0; i < game->numberOfCrewmates; i++) {
		WritePlayer(game->crewmates[i], outputFile);
		fprintf(outputFile, "\n");
	}

	//Apelez functia de afisare pentru impostor
    fprintf(outputFile, "\n\tImpostor:\n");
	WritePlayer(game->impostor, outputFile);

}

//Task 7
void *KillPlayer(void *input)
{
	/*Declar un pointer de tip game care 
	preia valoarea castata la game pointer de input*/
	Game *structura = (Game *)input;
	int Min, dis, len = 0, index;
	
	//Variabila buffer va retine numele jucatorului
	char *buffer;

	//Aloc dinamic variabila output in care retin sirul de caractere final
	char *output = calloc(MAX_LEN_STR_ATR, sizeof(char));

	//Verific dacă alocarea a avut loc cu succes
	if (output == NULL) {
		printf("Could not allocate \n");
		exit(1);		
	}

	//Initializez indexul primului jucator si ale impostorului
	int j = structura->crewmates[0]->indexOfLocation,
		k = structura->impostor->indexOfLocation;

	//Initializez distanta minima cu distanta dintre primul jucator si impostor
    Min = fabs(structura->crewmates[0]->locations[j].x -
		structura->impostor->locations[k].x) +
		fabs(structura->crewmates[0]->locations[j].y -
		structura->impostor->locations[k].y);

	//Inițializez cu -1 pozitia jucatorului
	index = -1;

	//Parcurg cu un for jucatorii si calculez distanta dintre locatia lor si impostor
	for (int i = 0; i < structura->numberOfCrewmates; i++) {
		j = structura->crewmates[i]->indexOfLocation;
		dis = fabs(structura->crewmates[i]->locations[j].x -
		structura->impostor->locations[k].x) +
		fabs(structura->crewmates[i]->locations[j].y -
		structura->impostor->locations[k].y);
		
		/*Verific daca dis este mai mic sau egal cu killRange
		si jucatorul este in viata*/
		if (dis <= structura->killRange && structura->crewmates[i]->alive) {
			/*Daca dis este maic sau egal cu Min, 
			actualizez Min si retin numele impreuna cu indexul*/
			if (dis <= Min) {
				Min = dis;
				buffer = structura->crewmates[i]->name;
				index = i;
			}
		}
	}

	//Daca indexul a ramas -1 adaug in sirul de caractere output mesajul cerut
	if (index == -1) {
		len += sprintf(output + len, "Impostor %s couldn't kill anybody.", structura->impostor->name);
	}
	/*In sirul de caractere output adaug mesajul
	dorit impreuna cu numele jucatorului*/
	else {
		len += sprintf(output + len, "Impostor %s has just killed crewmate %s from distance %d.", 
		structura->impostor->name, buffer, Min);
		//Setez valoarea intregului alive cu 0
		structura->crewmates[index]->alive = 0;
	}

	//Apoi returnez variabila output castata la void pointer.
	return (void *)output;
}

// Task 8
void CalcuateNextCycleOfGame(Game *game, FILE *outputFile, void **inputMatrix)
{
	int i;

	/*Varaibila buffer reține numele jucatorului,
	iar variabila out retine output-ul jucatorului*/
	char *buffer, *out;
	
	/*Aloc dinamic sirul de caractere buffer si verific
	daca alocarea a avut loc cu succes*/
	buffer = calloc(MAX_LEN_STR_ATR, sizeof(char));
		if (buffer == NULL) {
		printf("Could not allocate \n");
		exit(1);		
	}

	//Parcurg jucatorii si verific daca sunt in viata
	for (i = 0; i < game->numberOfCrewmates; i++) {
		if (game->crewmates[i]->alive == 0) {
            fprintf(outputFile, "Crewmate %s is dead.\n", game->crewmates[i]->name);
		}
		else {
			//Verific daca jucatorul a ajuns la pozitia finala si o resetez cu 0
			if (game->crewmates[i]->indexOfLocation == game->crewmates[i]->numberOfLocations - 1) {
				game->crewmates[i]->indexOfLocation = 0;
			}
			//Daca jucatorul nu a ajuns la final ii maresc indexul
			else {
				game->crewmates[i]->indexOfLocation++;
			}

			//Afisez locatia si output-ul fiecarui jucator
			fprintf(outputFile, "Crewmate %s went to location (%d,%d).\n", game->crewmates[i]->name, game->crewmates[i]->locations[game->crewmates[i]->indexOfLocation].x, game->crewmates[i]->locations[game->crewmates[i]->indexOfLocation].y);
			fprintf(outputFile, "Crewmate %s's output:\n", game->crewmates[i]->name);

			//Sirul de caractere out preia output-ul fiecarui jucator
			out = (char *)game->crewmates[i]->ability(inputMatrix[i]);
			fprintf(outputFile, "%s\n", out);
			free(out);
        }
    }

	//Verific daca impostorul a ajuns la pozitia finala si o resetez cu 0
	if (game->impostor->indexOfLocation == (game->impostor->numberOfLocations) - 1) {
		game->impostor->indexOfLocation = 0;
	}
	//Daca impostorul nu a ajuns la final ii maresc indexul
	else {
		(game->impostor->indexOfLocation)++;
	}
	
	//Afisez locatia impostorului si output-ul acestuia
	fprintf(outputFile, "Impostor %s went to location (%d,%d).\n",
			game->impostor->name,
			game->impostor->locations[game->impostor->indexOfLocation].x,
			game->impostor->locations[game->impostor->indexOfLocation].y);
	fprintf(outputFile, "Impostor %s's output:\n", game->impostor->name);

	//Sirul de caractere out preia output-ul impostorului
	out = (char *)(game->impostor->ability((void *)game));
	fprintf(outputFile, "%s\n", out);

	//Dezaloc sirurile de caractere out si buffer
	free(out);
	free(buffer);
	return;
}

// Task 9
void FreePlayer(Player *player)
{
	//Dezaloc fiecare camp din structura player
	free(player->name);
	free(player->color);
	free(player->hat);

	//Dezaloc vectorul de structuri de tip Location
	free(player->locations);

	//Dezaloc strucura player
	free(player);

	return;
}

// Task 9
void FreeGame(Game *game)
{
	//Dezaloc fiecare camp din structura game
	free(game->name);

	/*Parcurg fiecare jucator si apelez functia 
	FreePlayer pentru fiecare dintre ei*/
	for (int i = 0; i < game->numberOfCrewmates; i++) {
		FreePlayer(game->crewmates[i]);
	}

	//Dezaloc vectorul de pointeri la structuri de tip Player
	free(game->crewmates);

	//Apelez funcția FreePlayer pentru impostor  
	FreePlayer(game->impostor);

	//Dezaloc structura game
	free(game);
	return;
}