#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50
#define MAX_LINE 1024

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;
typedef struct _Sorted {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Sorted;

int PrependList(Position head, char* name, char* surname, int birthYear);
int AppendList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
Position FindBySurname(Position first, char* surname);
Position FindBefore(Position first, char* surname);
int DeleteAfter(Position first, char* surname);
Position AddAfter(Position first, char* _surname, char* name, char* surname, int birthYear);
Position AddBefore(Position first, char* name, char* surname, int birthYear);
Position FindPrevious(Position first, Position Member);
int InsertSorted(Position first, char* name, char* surname, int birthYear);
int PrintInFile(Position first, char* file);
int ReadFromFile(char* file);
int PrintFromFile(char* file);


int main(int argc, char** argv)
{
	Person Head = { .name = {0}, .surname = {0}, .birthYear = 0, .next = NULL };
	Sorted head = { .name = {0}, .surname = {0}, .birthYear = 0, .next = NULL };
	Position p = &Head;
	Position s = &head;
	Position temp = NULL;
	int a = 0, numb = 0;
	char name[MAX_SIZE] = { 0 };
	char surname[MAX_SIZE] = { 0 };
	char _surname[MAX_SIZE] = { 0 };
	int birthyear = 0;
	char* file = "lista.txt";

	printf("What action do you want to do?\n\n"
		"1. Add first member of a list.\n"
		"2. Add a member to the list.\n"
		"3. Print list.\n"
		"4. Find a member by surname.\n"
		"5. Delete a member from a list.\n"
		"6. Add a member after.\n"
		"7. Add a member before.\n"
		"8. Print a list into file.\n"
		"9. Print a list from a file.\n"
		"10. Print a sorted list.\n"
		"0. Leave and quit.\n");
	printf("Your choice: ");
	scanf_s("%d", &a);

	while (a) 
	{
		switch (a) 
		{		
		case 1:
			printf("\nType in information:\n");
			printf("\n");
			printf("Name: ");
			scanf_s(" %s", name, sizeof(name));
			printf("Surname: ");
			scanf_s(" %s", surname, sizeof(surname));
			printf("Birthyear: ");
			scanf_s("%d", &birthyear);

			PrependList(p, name, surname, birthyear);
			InsertSorted(s, name, surname, birthyear);

			break;

		case 2:
			printf("\nType in information:\n");
			printf("\n");
			printf("Name: ");
			scanf_s(" %s", name, sizeof(name));
			printf("Surname: ");
			scanf_s(" %s", surname, sizeof(surname));
			printf("Birthyear: ");
			scanf_s("%d", &birthyear);

			AppendList(p, name, surname, birthyear);
			InsertSorted(s, name, surname, birthyear);

			break;

		case 3:
			printf("List:\n");

			PrintList(p->next);

			break;

		case 4:
			printf("Type in a surname: ");
			scanf_s(" %s", surname, sizeof(surname));
			temp = FindBySurname(p, surname);
			if (!temp) {
				printf("Person is not on the list.\n");
			}
			printf("\nName: %s\n Surname: %s\n Birthyear: %d\n\n", temp->name, temp->surname, temp->birthYear);

			break;

		case 5:
			printf("Type in a surname of a person you want to remove from list: ");
			scanf_s(" %s", surname, sizeof(surname));
			DeleteAfter(p, surname);
			DeleteAfter(s, surname);

			break;

		case 6:
			printf("\nSurname of person after you want to add: ");
			scanf_s(" %s", _surname, sizeof(_surname));
			printf("Type in information:\n");
			printf("Name: ");
			scanf_s(" %s", name, sizeof(name));
			printf("\nSurname: ");
			scanf_s(" %s", surname, sizeof(surname));
			printf("\nBirthyear:");
			scanf_s("%d", &birthyear);

			AddAfter(p, _surname, name, surname, birthyear);
			InsertSorted(s, name, surname, birthyear);

			break;

		case 7:
			printf("\nSurname of person before you want to add: ");
			scanf_s(" %s", _surname, sizeof(_surname));
			printf("Type in information:\n");
			printf("Name: ");
			scanf_s(" %s", name, sizeof(name));
			printf("\nSurname: ");
			scanf_s(" %s", surname, sizeof(surname));
			printf("\nBirthyear:");
			scanf_s("%d", &birthyear);

			AddBefore(p, _surname, name, surname, birthyear);
			InsertSorted(s, name, surname, birthyear);

			break;

		case 8:
			PrintInFile(p->next, "lista.txt");

			break;

		case 9:
			numb = ReadFromFile("lista.txt");
			PrintFromFile("lista.txt");

			break;

		case 10:
			printf("List sorted:\n");
			PrintList(s->next);

			break;

		default:
			printf("Incorrect number!");
			break;
		}
		printf("\nYour choice:");
		scanf_s("%d", &a);
	}

	return EXIT_SUCCESS;
}

int PrependList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson)
		return -1;

	InsertAfter(head, newPerson);

	return EXIT_SUCCESS;
}

int AppendList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position last = head;

	newPerson = CreatePerson(name, surname, birthYear);

	if (!newPerson)
		return -1;

	last = FindLast(head);
	InsertAfter(last, newPerson);

	return EXIT_SUCCESS;
}

int PrintList(Position first)
{
	Position temp = first;

	while (temp)
	{
		printf("%s %s %d\n", temp->name, temp->surname, temp->birthYear);
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
		temp = temp->next;
	}

	return NULL;
}

Position FindBefore(Position first, char* surname)
{
	Position temp = first;

	for (temp; temp->next; temp = temp->next)
		if (!strcmp(surname, temp->next->surname))
			return temp;

	return NULL;
}

int DeleteAfter(Position first, char* surname)
{
	Position prev = NULL;
	Position Member = NULL;

	prev = FindBefore(first, surname);
	if (prev == 0)
	{
		printf("Person is not on the list.");
		return -1;
	}
	else
	{
		Member = prev->next;
		prev->next = Member->next;
		free(Member);
	}

	return EXIT_SUCCESS;
}

Position AddAfter(Position first, char* _surname, char* name, char* surname, int birthYear)
{
	Position temp = NULL;
	Position newPerson = NULL;

	temp = FindBySurname(first->next, _surname);
	if (!temp)
	{
		printf("There is no one with that surname!");

		return NULL;
	}

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson)
	{
		printf("Error!");

		return NULL;
	}

	InsertAfter(temp, newPerson);

	return NULL;
}

Position AddBefore(Position first, char* _surname, char* name, char* surname, int birthYear)
{
	Position temp = NULL;
	Position newPerson = NULL;

	temp = FindBefore(first, _surname);
	if (!temp)
	{
		printf("There is no one with that surname!");

		return NULL;
	}

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson)
	{
		printf("Error");

		return NULL;
	}

	InsertAfter(temp, newPerson);

	return NULL;
}

int PrintInFile(Position first, char* fileName)
{
	FILE* f = NULL;
	Position temp = first;

	f = fopen(fileName, "w");
	if (!f)
	{
		printf("Error while opening file!");
		return -1;
	}

	while (temp)
	{
		fprintf(f, "%s %s %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	fclose(f);

	return EXIT_SUCCESS;
}

int ReadFromFile(char* fileName)
{
	FILE* f = NULL;
	int Counter = 0;
	char line[MAX_LINE] = { 0 };

	f = fopen(fileName, "r");
	if (!f)
	{
		printf("Error!");
		return -1;
	}

	while (!feof(f))
	{
		fgets(line, MAX_LINE, f);
		Counter++;
	}

	fclose(f);

	return Counter;
}

int PrintFromFile(char* fileName)
{
	FILE* f = NULL;
	char buffer;

	f = fopen(fileName, "r");
	if (!f)
		return -1;

	while (!feof(f))
	{
		buffer = fgetc(f);
		printf("%c", buffer);
	}

	fclose(f);

	return EXIT_SUCCESS;
}

int InsertSorted(Position first, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position before = NULL;
	Position temp = first->next;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson)
		return -1;

	if (!temp)
	{
		InsertAfter(first, newPerson);
	}
	else
	{
		while (temp && strcmp(surname, temp->surname))
			temp = temp->next;
		
		before = FindPrevious(first, temp);
		InsertAfter(before, newPerson);
	}

	return EXIT_SUCCESS;
}

Position FindPrevious(Position first, Position Member)
{
	Position temp = first;

	while (temp->next != Member)
		temp = temp->next;

	return temp;
}