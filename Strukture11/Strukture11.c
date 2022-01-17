#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 126
#define HASH_SIZE 11

struct _cities; 
typedef struct _cities* PositionT;
typedef struct _cities
{
	char city_name[LENGTH];
	int population;
	PositionT right;
	PositionT left;
}cities;

struct _countries;
typedef struct _countries* PositionL;
typedef struct _countries
{
	char country_name[LENGTH];
	PositionT city;
	PositionL next;
}countries;

int HashKey(char* name);
int CreateCountry(PositionL head, char* countryName, char* cityFileName);
int CreateCity(PositionT root, char* cityFileName);
PositionT AddElInTree(PositionT root, char* name, int population);
int PrintCountries(PositionL head);
int PrintCities(PositionT root);
int FindCity(PositionT root, int population);
int Find(PositionL head, char* countryName, int population);

int main()
{
	countries head = { .next = NULL, .city = NULL, .country_name = { 0 } };
	//countries hash = { .next = NULL, .city = NULL, .country_name = { 0 } };
	countries hash[HASH_SIZE];
	int i;
	int hashKey = 0;
	char name[LENGTH] = { 0 }, cityFileName[LENGTH] = { 0 };
	FILE* fp = NULL;
	int population;

	for (i = 0; i < HASH_SIZE; i++)
	{
		hash[i].city = NULL;
		hash[i].next = NULL;
		strcpy(hash[i].country_name, "");
	}

	fp = fopen("countries.txt", "r");
	if (!fp)
	{
		perror("Can't open file!");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %s", name, cityFileName);

		hashKey = HashKey(name);

		CreateCountry(&hash[hashKey], name, cityFileName);
	}

	fclose(fp);

	for (i = 0; i < HASH_SIZE; i++)
		PrintCountries(hash[i].next);

	printf("\nType in country you want to search: ");
	scanf(" %s", name);
	printf("\nType in population: ");
	scanf("%d", &population);

	hashKey = HashKey(name);

	Find(hash[hashKey].next, name, population);

	return EXIT_SUCCESS;
}

int Find(PositionL head, char* countryName, int population)
{
	while (head != NULL && strcmp(head->country_name, countryName) != 0)
		head = head->next;

	FindCity(head->city, population);

	return EXIT_SUCCESS;
}

int FindCity(PositionT root, int population)
{
	if (root != NULL)
	{
		if (root->population > population)
			printf("%s", root->city_name);

		FindCity(root->left, population);
		FindCity(root->right, population);
	}

	return EXIT_SUCCESS;
}

int PrintCities(PositionT root)
{
	if (root != NULL)
	{
		PrintCities(root->left);
		printf(" %s %d", root->city_name, root->population);
		PrintCities(root->right);
	}

	return EXIT_SUCCESS;
}

int PrintCountries(PositionL head)
{
	while (!head->next)
	{
		printf(" %s\n", head->country_name);
		PrintCities(head->city);

		head = head->next;
	}

	return EXIT_SUCCESS;
}

PositionT AddElInTree(PositionT root, char* name, int population)
{
	PositionT newEl = NULL; 

	if (root = NULL)
	{
		newEl = (PositionT)malloc(sizeof(cities));
		if (!newEl)
		{
			perror("Can't allocate memory!");
			return -1;
		}

		strcpy(newEl->city_name, name);
		newEl->population = population;
		newEl->left = NULL;
		newEl->right = NULL;

		return newEl;
	}

	else if (root->population > population)
		root->left = AddElInTree(root->left, name, population);

	else if (root->population < population)
		root->right = AddElInTree(root->right, name, population);

	else if (root->population == population)
	{
		if (strcmp(root->city_name, name) > 0)
			root->left = AddElInTree(root->left, name, population);

		else
			root->right = AddElInTree(root->right, name, population);
	}

	return root;
}

int CreateCity(PositionT root, char* cityFileName)
{
	char cityName[LENGTH];
	int population = 0;
	FILE* fp = NULL;

	fp = fopen(cityFileName, "r");
	if (!fp)
	{
		perror("Can't open file!");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %d", cityName, &population);
		root = AddElInTree(root, cityName, population);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int CreateCountry(PositionL head, char* countryName, char* cityFileName)
{
	PositionL newElInList = NULL;
	PositionT newElInTree = NULL;

	newElInList = (PositionL)malloc(sizeof(countries));
	if (!newElInList)
	{
		perror("Can't allocate memory!");
		return -1;
	}

	newElInTree = (PositionT)malloc(sizeof(cities));
	if (!newElInTree)
	{
		perror("Can't allocate memory!");
		return -1;
	}

	strcpy(newElInTree->city_name, "");
	newElInTree->population = 0;
	newElInTree->left = NULL;
	newElInTree->right = NULL;

	strcpy(newElInList->country_name, countryName);
	newElInList->city = newElInTree;
	CreateCity(newElInList->city, cityFileName);

	while (head->next != NULL && strcmp(head->next->country_name, countryName) < 0)
		head = head->next;
	
	newElInList->next = head->next;
	head->next = newElInList;

	return EXIT_SUCCESS;
}

int HashKey(char* name)
{
	int i = 0, sum = 0;
	
	for (i = 0; i < 5; i++)
		sum += (int)name[i];

	return sum % HASH_SIZE;
}
