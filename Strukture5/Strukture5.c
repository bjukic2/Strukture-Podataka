#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

struct _stack;
typedef struct _stack* Position;
typedef struct _stack {
	double number;
	Position next;
}stack;

Position CreateElement(double number);
int InsertAfter(Position position, Position newElement);
int DeleteAfter(Position position);
int Push(Position first, double number);
int Pop(double* resultDestination, Position first);
int DeleteEverything(Position first);
int Operation(Position first, char operation);
int FilePostfixCalculation(double* resultDestination, char* fileName);

int main(int argc, char* argv[])
{
	double result = 0;
	char* _fileName = "postfix.txt";

	FilePostfixCalculation(&result, _fileName);

	printf("Result of postfix: %0.2lf\n", result);

	return EXIT_SUCCESS;
}

Position CreateElement(double number)
{
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(stack));
	if (!newElement)
	{
		perror("Can't allocate memory!");
		return -1;
	}

	newElement->number = number;
	newElement->next = NULL;

	return newElement;
}

int InsertAfter(Position position, Position newElement)
{
	newElement->next = position->next;
	position->next = newElement;

	return EXIT_SUCCESS;
}

int DeleteAfter(Position position)
{
	Position temp = position->next;

	if (!temp)
	{
		return EXIT_SUCCESS;
	}

	position->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

int Push(Position first, double number)
{
	Position newElement = NULL;

	newElement = CreateElement(number);
	if (!newElement)
	{
		return -1;
	}

	InsertAfter(first, newElement);

	return EXIT_SUCCESS;
}

int Pop(double* resultDestination, Position first)
{
	Position temp = first->next;

	if (!temp)
	{
		perror("Invalid postfix!");
		return -1;
	}

	*resultDestination = first->number;
	DeleteAfter(first);

	return EXIT_SUCCESS;
}

int DeleteEverything(Position first)
{
	while (first->next)
	{
		DeleteAfter(first);
	}

	return EXIT_SUCCESS;
}

int Operation(Position first, char operation)
{
	double op1 = 0;
	double op2 = 0;
	double res = 0;
	int status1 = EXIT_SUCCESS;
	int status2 = EXIT_SUCCESS;

	status2 = Pop(&op2, first);
	if (status2 != EXIT_SUCCESS)
	{
		return -1;
	}

	status1 = Pop(&op1, first);
	if (status1 != EXIT_SUCCESS)
	{
		return -2;
	}

	switch (operation)
	{
	case '+':
		res = op1 + op2;
		break;

	case '-':
		res = op1 - op2;
		break;

	case '*':
		res = op1 * op2;
		break;

	case '/':
		if (op2 == 0)
		{
			perror("Can't divide with zero!\n");
			return -3;
		}
		res = op1 / op2;
		break;

	default:
		printf("Invalid operation entry!");
		break;
	}

	return Push(first, res);
}

int FilePostfixCalculation(double* resultDestination, char* fileName)
{
	FILE* fp = NULL;
	int fileLength = 0;
	char* buffer = NULL;
	char* _buffer = NULL;
	int value = 0;
	int n = 0;
	double number = 0.0;
	stack head = { .number = 0, .next = NULL };
	char operation = 0;


	fp = fopen(fileName, "rb");
	if (!fp)
	{
		perror("Can't open file!\n");
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	fileLength = ftell(fp);

	buffer = (char*)calloc(fileLength + 1, sizeof(char));
	if (!buffer)
	{
		perror("Can't allocate memory!\n");
		return -2;
	}

	rewind(fp);
	fread(buffer, sizeof(char), fileLength, fp);
	printf("|%s|\n", buffer);
	fclose(fp);

	_buffer = buffer;

	while (strlen(_buffer) > 0)
	{
		value = sscanf(_buffer, " %lf %n", &number, &n);
		if (value == 1)
		{
			value = Push(&head, number);
			if (value != EXIT_SUCCESS)
			{
				free(buffer);
				DeleteEverything(&head);
				return -3;
			}
			_buffer += n;
		}
		else
		{
			sscanf(_buffer, " %c %n", &operation, &n);
			value = Operation(&head, operation);
			if (value != EXIT_SUCCESS)
			{
				free(buffer);
				DeleteEverything(&head);
				return -4;
			}
			_buffer += n;
		}
	}

	free(buffer);

	value = Pop(resultDestination, &head);
	if (value != EXIT_SUCCESS)
	{
		DeleteEverything(&head);
		return -5;
	}

	if (head.next)
	{
		printf("Postfix invalid!\n");
		DeleteEverything(&head);
		return -6;
	}

	return EXIT_SUCCESS;
}