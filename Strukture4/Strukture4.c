#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_SIZE 50

struct _poly;
typedef struct _poly* Position;
typedef struct _poly
{
	int coeff;
	int exp;
	Position next;
}poly;

int ReadFile(Position p1, Position p2, char* FileName);
int FileName(char* filename);
Position CreateElement(int coeff, int exp);
int InsertAfter(Position position, Position Element);
int DeleteAfter(Position Before);
int MergeAfter(Position position, Position Element);
int CreateAndInsertAfter(Position position, int coeff, int exp);
int SortInsert(Position first, Position element);
int PolyMultiplication(Position multiplication, Position p1, Position p2);
int PolySum(Position sum, Position p1, Position p2);
int FreeMemory(Position first);
int ParseElements(Position first, char* buffer);
int PrintPoly(Position first);

int main(int argc, char** argv)
{
	poly head1 = { .coeff = 0, .exp = 0, .next = NULL };
	poly head2 = { .coeff = 0, .exp = 0, .next = NULL };
	poly sum = { .coeff = 0, .exp = 0, .next = NULL };
	poly multiplication = { .coeff = 0, .exp = 0, .next = NULL };
	char* fileName = "Poly.txt";

	//FileName(fileName);

	if (ReadFile(&head1, &head2, fileName) == EXIT_SUCCESS)
	{
		printf("Polynomial1: ");
		PrintPoly(head1.next);

		printf("\nPolynomial2: ");
		PrintPoly(head2.next);

		PolySum(&sum, &head1, &head2);
		PolyMultiplication(&multiplication, &head1, &head2);

		printf("\nPolynomial sum:");
		PrintPoly(sum.next);

		printf("\nPolynomial multiplication:");
		PrintPoly(multiplication.next);
		printf("\n");

		FreeMemory(&head1);
		FreeMemory(&head2);
		FreeMemory(&sum);
		FreeMemory(&multiplication);
	}
	else
		perror;

	return EXIT_SUCCESS;
}

int ReadFile(Position p1, Position p2, char* FileName)
{
	FILE* fp = NULL;
	char buffer[MAX_LINE] = { 0 };
	int value = EXIT_SUCCESS;

	fp = fopen(FileName, "r");
	if (!fp)
	{
		perror("Error while opening file!\n");
		return -1;
	}

	fgets(buffer, MAX_LINE, fp);
	value = ParseElements(p1, buffer);
	if (value != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LINE, fp);
	value = ParseElements(p2, buffer);
	if (value != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int FileName(char* filename)
{
	printf("Insert a file name: ");
	scanf_s(" %s", filename, sizeof(filename));

	return EXIT_SUCCESS;
}

Position CreateElement(int coeff, int exp)
{
	Position Element = NULL;

	Element = (Position)malloc(sizeof(poly));
	if (!Element)
	{
		perror("Error while allocating memory!");
		return NULL;
	}

	Element->coeff = coeff;
	Element->exp = exp;
	Element->next = NULL;

	return Element;
}

int InsertAfter(Position position, Position Element)
{
	Element->next = position->next;
	position->next = Element;

	return EXIT_SUCCESS;
}

int DeleteAfter(Position Before)
{
	Position Remove = NULL;

	Remove = Before->next;
	Before->next = Remove->next;
	free(Remove);

	return EXIT_SUCCESS;
}

int MergeAfter(Position position, Position Element)
{
	int coeffSum = 0;

	if (position->next == NULL || position->next->exp != Element->exp)
	{
		InsertAfter(position, Element);
	}
	else
	{
		int coeffSum = position->next->coeff + Element->coeff;
		if (coeffSum == 0)
			DeleteAfter(position);
		else
			position->next->coeff = coeffSum;

		free(Element);
	}

	return EXIT_SUCCESS;
}

int CreateAndInsertAfter(Position position, int coeff, int exp)
{
	Position newElement = CreateElement(coeff, exp);
	if (!newElement)
		return -1;

	InsertAfter(position, newElement);

	return EXIT_SUCCESS;
}

int SortInsert(Position first, Position Element)
{
	Position temp = first;

	while (temp->next != NULL && temp->next->exp < Element->exp)
		temp = temp->next;

	MergeAfter(temp, Element);

	return EXIT_SUCCESS;
}

int PolyMultiplication(Position multiplication, Position p1, Position p2)
{
	Position x = NULL;
	Position y = NULL;
	Position newElement = NULL;

	for (x = p1->next; x != NULL; x = x->next)
	{
		for (y = p2->next; y != NULL; y = y->next)
		{
			newElement = CreateElement(x->coeff * y->coeff, x->exp + y->exp);
			if (!newElement)
				return -1;

			SortInsert(multiplication, newElement);
		}
	}

	return EXIT_SUCCESS;
}

int PolySum(Position sum, Position p1, Position p2)
{
	Position x = NULL; 
	Position y = NULL; 
	Position newElement = NULL;

	for (x = p1->next; x != NULL; x = x->next)
	{
		newElement = CreateElement(x->coeff, x->exp);
		if (!newElement)
			return -1;

		SortInsert(sum, newElement);
	}

	for (y = p2->next; y != NULL; y = y->next)
	{
		newElement = CreateElement(y->coeff, y->exp);
		if (!newElement)
			return -1;

		SortInsert(sum, newElement);
	}

	return EXIT_SUCCESS;
}

int FreeMemory(Position first)
{
	Position temp = first; 

	while (temp->next)
	{
		DeleteAfter(temp);
	}

	return EXIT_SUCCESS;
}

int ParseElements(Position first, char* buffer)
{
	Position newElement = NULL;
	char* _buffer = buffer;
	int coeff = 0;
	int exp = 0;
	int n = 0;
	int value = 0;

	while (strlen(_buffer) > 0)
	{
		value = sscanf(_buffer, " %d %d %n", &coeff, &exp, &n);
		if (value != 2)
		{
			printf("File not good!");
			return EXIT_FAILURE;
		}

		newElement = CreateElement(coeff, exp);
		if (!newElement)
		{
			return EXIT_FAILURE;
		}

		SortInsert(first, newElement);

		_buffer += n;
	}

	return EXIT_SUCCESS;
}

int PrintPoly(Position first)
{
	Position temp = first;

	if (temp) {
		printf("%dx^%d", temp->coeff, temp->exp);
		temp = temp->next;
	}

	for (; temp != NULL; temp = temp->next)
	{
		if (temp->coeff < 0)
			printf(" - %dx^%d", temp->coeff, temp->exp);
		else
			printf(" + %dx^%d", temp->coeff, temp->exp);
	}

	return EXIT_SUCCESS;
}