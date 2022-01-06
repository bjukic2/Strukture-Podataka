#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGHT 1024

struct _cities;
typedef struct _cities* PositionT;
typedef struct _cities {
	char name[LENGHT];
	int population;
	PositionT left;
	PositionT right;
}cities;

struct _states;
typedef struct _states* PositionL;
typedef struct _states {
	char name[LENGHT];
	PositionL next;
	PositionT city;
}states;

PositionL CreateElInList(char* Name);
int InsertElInList(PositionL head, PositionL newEl);
PositionT TreeFromFile(char* fileName);
PositionT InsertElInTree(PositionT current, PositionT newEl);
PositionT CreateElInTree(char* Name, int population);
int ListFromFile(PositionL head, char* fileName);
int PrintInorder(PositionT root);
int PrintList(PositionL head);

int main()
{
	states head = { .name = { 0 }, .next = NULL, .city = NULL };
	char* fileName = "drzave.txt";

	ListFromFile(&head, fileName);

	PrintList(&head);

	return EXIT_SUCCESS;
}

PositionL CreateElInList(char* Name)
{
	PositionL newEl = NULL;

	newEl = (PositionL)malloc(sizeof(states));
	if (!newEl)
	{
		perror("Can't allocate memory!");
		return NULL;
	}

	strcpy(newEl->name, Name);
	newEl->city = NULL;
	newEl->next = NULL;

	return newEl;
}

int InsertElInList(PositionL head, PositionL newEl)
{
	PositionL temp = head;

	while ((temp->next != NULL) && (strcmp(temp->next->name, newEl->name) < 0))
		temp = temp->next;

	newEl->next = temp->next;
	temp->next = newEl;
	newEl->city = TreeFromFile(newEl->name);

	return EXIT_SUCCESS;
}

PositionT TreeFromFile(char* fileName)
{
	FILE* fp = NULL; 
	char _fileName[LENGHT] = { 0 };
	char buffer[LENGHT] = { 0 };
	char* _buffer = NULL;
	char city_name[LENGHT] = { 0 };
	int n = 0;
	int population = 0;
	PositionT temp = NULL;

	strcpy(_fileName, fileName);
	strcat(_fileName, ".txt");

	fp = fopen(_fileName, "r");
	if (!fp)
	{
		perror("Can't open file!");
		return NULL;
	}

	while (!feof(fp)) 
	{
		fgets(buffer, LENGHT, fp);
		_buffer = buffer;

		while (strlen(_buffer))
		{
			if (sscanf(_buffer, " %s %d %n", city_name, &population, &n) == 2)
				temp = InsertElInTree(temp, CreateElInTree(city_name, population));
			_buffer += n;
		}
	}

	fclose(fp);

	return temp;
}

PositionT InsertElInTree(PositionT current, PositionT newEl)
{
	if (current == NULL)
		return newEl;
	
	if ((current->population) > (newEl->population))
		current->right = InsertElInTree(current->right, newEl);
	else if ((current->population) < (newEl->population))
		current->left = InsertElInTree(current->left, newEl);

	return current;
}

PositionT CreateElInTree(char* Name, int population)
{
	PositionT newEl = NULL;

	newEl = (PositionT)malloc(sizeof(cities));
	if (!newEl)
	{
		perror("Can't allocate memory!");
		return NULL;
	}

	strcpy(newEl->name, Name);
	newEl->population = population;
	newEl->left = NULL;
	newEl->right = NULL;

	return newEl;
}

int ListFromFile(PositionL head, char* fileName)
{
	FILE* fp = NULL; 
	char buffer[LENGHT] = { 0 };
	char* _buffer = NULL;
	char state_name[LENGHT] = { 0 };
	int n = 0;

	fp = fopen(fileName, "r");
	if (!fp)
	{
		perror("Can't open file!");
		return -1;
	}

	while (!feof(fp))
	{
		fgets(buffer, LENGHT, fp);
		_buffer = buffer;

		while (strlen(_buffer))
		{
			if (sscanf(_buffer, " %s %d", state_name, &n) == 1)
			{
				InsertElInList(head, CreateElInList(state_name));
			}
			_buffer += n;
		}
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int PrintInorder(PositionT root)
{
	if (root != NULL)
	{
		PrintInorder(root->left);
		printf("%s %d", root->name, root->population);
		PrintInorder(root->right);
	}

	return EXIT_SUCCESS;
}

int PrintList(PositionL head)
{
	while (head)
	{
		printf(" %s\n", head->name);
		PrintInorder(head->city);
		head = head->next;
	}

	return EXIT_SUCCESS;
}

