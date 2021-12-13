#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

struct _stablo;
typedef struct _stablo* StabloP;
typedef struct _stablo {
	int el;
	StabloP left;
	StabloP right;
}Stablo;

StabloP CreateEl(int x);
StabloP InsertEl(int x, StabloP root);
int PrintInOrder(StabloP root);
int PrintPreOrder(StabloP root);
int PrintPostOrder(StabloP root);
StabloP FindEl(int x, StabloP root);
StabloP FindMaxInLeft(StabloP root);
StabloP DeleteEl(int x, StabloP root);

int main()
{
	StabloP root = NULL, temp = NULL;
	int choice = 0, el = 0;

	do
	{
		printf("Choose action:\n");
		printf("1 - Insert element\n");
		printf("2 - Search element\n");
		printf("3 - Delete element\n");
		printf("4 - Inorder Print\n");
		printf("5 - Postorder Print\n");
		printf("6 - Preorder Print\n");
		printf("7 - Exit\n");

		scanf("%d", &choice);
		switch (choice)
		{
		case 1:

			printf("Type in element you want to insert: ");
			scanf("%d", &el);
			root = InsertEl(el, root);
			break;

		case 2:

			printf("\nType in element you want to find: ");
			scanf("%d", &el);
			temp = FindEl(el, root);
			printf("Element: |%d| is on adress: |%d|", temp->el, temp);
			break;

		case 3:

			printf("\nType in element you want to delete: ");
			scanf("%d", &el);
			root = DeleteEl(el, root);
			break;

		case 4:

			printf("\nInorder print: ");
			PrintInOrder(root);
			break;

		case 5:

			printf("\nPostorder print: ");
			PrintPostOrder(root);
			break;

		case 6:

			printf("\nPreorder print: ");
			PrintPreOrder(root);
			break;

		case 7:

			break;

		default:

			printf("\nInvalid choice. Please try again.\n");
		}
	} while (choice != '7');

	return EXIT_SUCCESS;
}

StabloP CreateEl(int x)
{
	StabloP newEl = NULL;

	newEl = (StabloP)malloc(sizeof(Stablo));
	if (!newEl)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}

	newEl->el = x;
	newEl->left = NULL;
	newEl->right = NULL;

	return newEl;
}

StabloP InsertEl(int x, StabloP root)
{
	if (root == NULL)
		return CreateEl(x);
	
	else if (x < root->el)
		root->left = InsertEl(x, root->left);
	
	else if (x > root->el)
		root->right = InsertEl(x, root->right);

	return root;
}

int PrintInOrder(StabloP root)
{
	if (root)
	{
		PrintInOrder(root->left);
		printf("%d\n", root->el);
		PrintInOrder(root->right);
	}

	return EXIT_SUCCESS;
}

int PrintPreOrder(StabloP root)
{
	if (root)
	{
		printf("%d\n", root->el);
		PrintPreOrder(root->left);
		PrintPreOrder(root->right);
	}

	return EXIT_SUCCESS;
}

int PrintPostOrder(StabloP root)
{
	if (root)
	{
		PrintPostOrder(root->left);
		PrintPostOrder(root->right);
		printf("%d\n", root->el);
	}

	return EXIT_SUCCESS;
}

StabloP DeleteEl(int x, StabloP root)
{
	StabloP temp = NULL;

	if (root == NULL)
		return root;

	else if (x < root->el)
		root->left = DeleteEl(x, root->left);

	else if (x > root->el)
		root->right = DeleteEl(x, root->right);

	else
	{
		if (root->left && root->right)
		{
			temp = FindMaxInLeft(root->left);
			root->el = temp->el;
			root->right = DeleteEl(temp->el, root->right);
		}
		else
		{
			temp = root;
			if (root->left == NULL)
				root = root->right;
			else if (root->right == NULL)
				root = root->left;
			free(temp);
		}
	}
	return root;
}

StabloP FindMaxInLeft(StabloP root)
{
	while (root->right)
		root = root->right;

	return root;
}

StabloP FindEl(int x, StabloP root)
{
	if (root == NULL)
		return root;

	else if (x < root->el)
		return FindEl(x, root->left);

	else if (x > root->el)
		return FindEl(x, root->right);

	return root;
}

