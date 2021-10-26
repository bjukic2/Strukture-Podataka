#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

struct _Person;
typedef struct _Person* Position;
typedef struct _Person{
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

int PrependList(Position head, char* name, char* surname, int birthYear);
int AppendList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
Position FindBySurname(Position first, char* surname);
Position FindBefore(Position first);
int DeleteAfter(Position first);
int DeleteMember(Position person);

int main(int argc, char** argv)
{
	Person Head = { .name = {0}, .surname = {0}, .birthYear = 0, .next = NULL };
	Position p = &Head;
	int d = 0;
	int i;
	int a = 0;
	char name[MAX_SIZE], surname[MAX_SIZE] = {0};
	int birthyear = 0;

	printf("What action do you want to do?\n");
	printf("1. Prepend a list.\n2. Append a list.\n3. Search by a surname.\n4. Delete a member.\n");
	scanf_s("%d", &a);

	switch (a) {
	case 1: 
		printf("Type in a number of members you want to insert: ");
		scanf_s("%d", &d);

		printf("\nType in information:\n");
		for (i = 1; i <= d; i++) {
			printf("%d. person: ", i);
			printf("\n");
			printf("Name: ");
			scanf_s(" %s", name, sizeof(name));
			printf("Surname: ");
			scanf_s(" %s", surname, sizeof(surname));
			printf("Birthyear: ");
			scanf_s("%d", &birthyear);

		}
		PrependList(p, name, surname, birthyear);

		break;

	case 2: 
		printf("Type in a number of members you want to insert: ");
		scanf_s("%d", &d);

		printf("\nType in information:\n");
		for (i = 1; i <= d; i++) {
			printf("%d. person: ", i);
			printf("\n");
			printf("Name: ");
			scanf_s(" %s", name, sizeof(name));
			printf("Surname: ");
			scanf_s(" %s", surname, sizeof(surname));
			printf("Birthyear: ");
			scanf_s("%d", &birthyear);
		}
		AppendList(p, name, surname, birthyear);

		break;

	case 3:
		printf("Surname: ");
		scanf_s(" %s", surname, sizeof(surname));
		
		FindBySurname(p, surname);

		break;

	case 4:
		DeleteAfter(p);

		break;

	default:
		break;
	}

	PrintList(p);

	return EXIT_SUCCESS;
}

int PrependList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson)
	{
		return -1;
	}

	InsertAfter(head, newPerson);

	return EXIT_SUCCESS;
}

int AppendList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson)
	{
		return -1;
	}
 
	last = FindLast(head);
	InsertAfter(last, newPerson);

	return EXIT_SUCCESS;
}

int PrintList(Position first)
{
	Position temp = first;

	temp = temp->next;

	while (temp)
	{
		printf("\n\nList:\n");
		printf("Name: %s\nSurname: %s\nBirthyear: %d\n\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson)
	{
		perror("Can't allocate memory!");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}

int InsertAfter(Position position, Position newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;

	return EXIT_SUCCESS;
}

Position FindLast(Position head)
{
	Position temp = head;

	while (temp->next)
	{
		temp = temp->next;
	}

	return temp;
}

Position FindBySurname(Position first, char* surname)
{
	Position temp = first;

	while (temp)
	{
		if (strcmp(temp->surname, surname) == 0)
			return temp;
	}

	return NULL;
}

Position FindBefore(Position first)
{
	Position temp = first;
	Position _selected = NULL;
	char* surname = { 0 };

	printf("Type the surname of the person before whom you want to find a member: ");
	scanf_s(" %s", surname, sizeof(surname));


	_selected = FindBySurname(first, surname);
	if (!_selected)
	{
		printf("Surname does not exist or some other error appeared.");
		return NULL;
	}

	while (temp)
	{
		if (temp->next = _selected)
			return temp;
	}

	return NULL;
}

int DeleteAfter(Position first)
{
	Position temp1 = first;
	Position temp2 = NULL;

	temp2 = FindBefore(first);
	if (!temp2)
	{
		printf("Error!");
		return -1;
	}

	while (temp1)
		if (temp1 = temp2->next)
			DeleteMember(temp1);

	return EXIT_SUCCESS;
}

int DeleteMember(Position person)
{
	person = NULL;

	return EXIT_SUCCESS;
}

