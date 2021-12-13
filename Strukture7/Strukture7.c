#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1024

struct _directory;
typedef struct _directory* Position;
typedef struct _directory {
	char name[MAX_LENGTH];
	Position sibling;
	Position child;
}Directory;

struct _stack;
typedef struct _stack* StackP;
typedef struct _stack {
	Position data;
	StackP next;
}Stack;

Position Pop(StackP head);
int Push(Position current, StackP head);
Position ChangeToPrevious(StackP head);
Position ChangeDirectory(Position current, StackP head, char* name);
Position MakeDirectory(Position current, char* name);
int cmd(Position current, StackP head);
int PrintDirectory(Position current);

int main()
{
	Directory C = { .sibling = NULL, .child = NULL };
	strcpy(C.name, "C:");

	Stack head = { .data = NULL, .next = NULL };

	Push(&C, &head);

	cmd(&C, &head);

	return EXIT_SUCCESS;
}

Position Pop(StackP head)
{
	StackP temp = head->next;
	StackP prev = NULL; 
	Position element = NULL;

	if (!temp->next)
		return NULL;

	while (temp->next)
	{
		prev = temp;
		temp = temp->next;
	}

	element = temp->data;
	prev->next = temp->next;
	free(temp);

	return element;
}

int Push(Position current, StackP head)
{
	StackP newEl = NULL; 
	StackP temp = head;

	newEl = (StackP)malloc(sizeof(Directory));
	if (!newEl) {
		perror("Can't allocate memory!");
		return EXIT_FAILURE;
	}

	while (temp->next)
		temp = temp->next;

	newEl->data = current;
	newEl->next = temp->next;
	temp->next = newEl;

	return EXIT_SUCCESS;
}

Position ChangeToPrevious(StackP head)
{
	return Pop(head);
}

Position ChangeDirectory(Position current, StackP head, char* name)
{
	Position temp = NULL;

	if (!current->child)
	{
		printf("Empty!");
		return current;
	}
	else
	{
		temp = current->child;
		
		while (temp)
			if (!strcmp(temp->name, name))
			{
				Push(temp, head);
				return temp;
			}
	}

	return current;
}

Position MakeDirectory(Position current, char* name)
{
	Position newDir = NULL;
	Position temp = NULL;

	newDir = (Position)malloc(sizeof(Directory));
	if (!newDir)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}

	strcpy(newDir->name, name);

	if (!current->child)
		current->child = newDir;

	else
	{
		temp = current->child;

		while (temp->sibling)
			temp = temp->sibling;

		temp->sibling = newDir;
	}

	return current;
}

int PrintDirectory(Position current)
{
	if (!current->child)
		printf("Directory is empty!\n");
	else
	{
		current = current->child;
		while (current)
		{
			printf("%s\n", current->name);
			current = current->sibling;
		}
	}

	return EXIT_SUCCESS;
}

int cmd(Position current, StackP head)
{
	Position C = current;
	char buffer[MAX_LENGTH];
	char input[5] = { 0 };
	char dirName[MAX_LENGTH];

	do
	{
		fgets(buffer, MAX_LENGTH, stdin);
		sscanf(buffer, " %s %s", input, dirName);
		if (!strcmp(input, "md"))
		{
			current = MakeDirectory(current, dirName);
		}
		else if (!strcmp(input, "cd"))
		{
			current = ChangeDirectory(current, head, dirName);
		}
		else if (!strcmp(input, "cd.."))
		{
			if ((current = ChangeToPrevious(head)) == NULL)
				current = C;
		}
		else if (!strcmp(input, "dir"))
		{
			PrintDirectory(current);
		}
		else if (!strcmp(input, "exit"))
		{
			remove(current);
		}
		else
		{
			printf("Wrong choice. Try again.\n");
		}
	} while (strcmp(input, "exit"));

	return EXIT_SUCCESS;
}