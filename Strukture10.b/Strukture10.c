#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGHT 1024

struct _cities;
typedef struct _cities* PositionL;
typedef struct _cities {
	char name[LENGHT];
	int population;
	PositionL next;
}cities;

struct _states;
typedef struct _states* PositionT;
typedef struct _states {
	char name[LENGHT];
	PositionT left;
	PositionT right;
	PositionL city;
}states;

PositionL CreateElInList(char* Name, int population);
PositionL InsertElInList(PositionL head, PositionL newEl);
PositionT TreeFromFile(char* fileName);
PositionT InsertElInTree(PositionT current, PositionT newEl);
PositionT CreateElInTree(char* Name);
PositionL ListFromFile(char* fileName);
int PrintInorder(PositionT root);
int PrintList(PositionL head);

int main()
{
	PositionT root = NULL;
	char* fileName = "drzave.txt";

	root = TreeFromFile(fileName);

	PrintInorder(root);

	return EXIT_SUCCESS;
}

PositionL CreateElInList(char* Name, int population)
{
	PositionL newEl = NULL;

	newEl = (PositionL)malloc(sizeof(states));
	if (!newEl)
	{
		perror("Can't allocate memory!");
		return NULL;
	}

	strcpy(newEl->name, Name);
	newEl->population = population;
	newEl->next = NULL;

	return newEl;
}

PositionL InsertElInList(PositionL head, PositionL newEl)
{
	PositionL temp = head;

	while ((temp->next != NULL) && (strcmp(temp->next->name, newEl->name) < 0))
		temp = temp->next;

	newEl->next = temp->next;
	temp->next = newEl;

	return newEl;
}

PositionT TreeFromFile(char* fileName)
{
	FILE* fp = NULL; 
	char _fileName[LENGHT] = { 0 };
	char buffer[LENGHT] = { 0 };
	char* _buffer = NULL;
	char state_name[LENGHT] = { 0 };
	int n = 0;
	int population = 0;
	PositionT root = NULL;
	int numberOfStates = 0;

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
			if (sscanf(_buffer, " %s %n", state_name, &n) == 1)
			{
				if (!numberOfStates)
				{
					root = CreateElInTree(state_name);
					
					root->city = ListFromFile(root->name);
					numberOfStates++;
				}
				else
				{
					root = InsertElInTree(root, CreateElInTree(state_name));
					root->city = ListFromFile(root->name);
				}
			}
			_buffer += n;
		}
	}


	fclose(fp);

	return root;
}

PositionT InsertElInTree(PositionT current, PositionT newEl)
{
	if (current == NULL)
		return newEl;
	
	if (strcmp(current->name, newEl->name) > 0)
		current->right = InsertElInTree(current->right, newEl);
	else if (strcmp(current->name, newEl->name) < 0)
		current->left = InsertElInTree(current->left, newEl);

	return current;
}

PositionT CreateElInTree(char* Name)
{
	PositionT newEl = NULL;

	newEl = (PositionT)malloc(sizeof(cities));
	if (!newEl)
	{
		perror("Can't allocate memory!");
		return NULL;
	}

	strcpy(newEl->name, Name);
	newEl->city = NULL;
	newEl->left = NULL;
	newEl->right = NULL;

	return newEl;
}

PositionL ListFromFile(char* fileName)
{
	FILE* fp = NULL; 
	char buffer[LENGHT] = { 0 };
	char* _buffer = NULL;
	char city_name[LENGHT] = { 0 };
	int n = 0;
	char _fileName[LENGHT] = { 0 };
	PositionL temp = NULL;
	int population = 0;

	strcpy(_fileName, fileName);
	strcat(_fileName, ".txt");

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
			if (sscanf(_buffer, " %s %d %d", city_name, &population, &n) == 2)
			{
				temp = InsertElInList(temp, CreateElInList(city_name, population));
			}
			_buffer += n;
		}
	}

	fclose(fp);

	return temp;
}

int PrintInorder(PositionT root)
{
	if (root != NULL)
	{
		PrintInorder(root->left);
		printf("%s", root->name);
		PrintList(root->city);
		PrintInorder(root->right);
	}

	return EXIT_SUCCESS;
}

int PrintList(PositionL head)
{
	if (head == NULL)
		return NULL;

	else
	{
		head = head->next;
		while (head != NULL)
		{
			printf(" %s	%d", head->name, head->population);
			head = head->next;
		}
	}

	return EXIT_SUCCESS;
}

