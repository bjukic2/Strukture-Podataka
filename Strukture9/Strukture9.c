#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_NUM 90
#define MIN_NUM 10
#define MAX_SIZE 64

struct _tree;
typedef struct _tree* TreeP;
typedef struct _tree {
    int el;
    TreeP right;
    TreeP left;
}Tree;

TreeP Insert(TreeP root, int el);
TreeP CreateEl(int el);
int AddThenReplace(TreeP root);
int FindRandom();
int PrintInDat(TreeP root, char* fileName);


int main()
{
    TreeP root = NULL;
    int choice = 0;
    char fileName[MAX_SIZE] = { 0 };
    
    printf("Type in name of file: ");
    scanf(" %s", fileName);
    
    printf("Choices:\n");
    printf("1: Numbers from task\n");
    printf("2: Random numbers\n");
    printf("0: Exit\n");
    printf("Your choice: ");

    do {
        switch (choice)
        {
        case 1:
            root = Insert(root, 2);
            root = Insert(root, 5);
            root = Insert(root, 7);
            root = Insert(root, 8);
            root = Insert(root, 11);
            root = Insert(root, 1);
            root = Insert(root, 4);
            root = Insert(root, 2);
            root = Insert(root, 3);
            root = Insert(root, 7);

            PrintInDat(root, fileName);
            AddThenReplace(root);
            PrintInDat(root, fileName);

            break;

        case 2:
            root = Insert(root, FindRandom());
            root = Insert(root, FindRandom());
            root = Insert(root, FindRandom());
            root = Insert(root, FindRandom());
            root = Insert(root, FindRandom());
            root = Insert(root, FindRandom());
            root = Insert(root, FindRandom());
            root = Insert(root, FindRandom());
            root = Insert(root, FindRandom());
            root = Insert(root, FindRandom());

            PrintInDat(root, fileName);
            AddThenReplace(root);
            PrintInDat(root, fileName);
            break;

        case 0:
            break;

        default:
            printf("Wrong input!\nTry again!\n");
        }
        scanf("%d", &choice);
    } while (choice);

    return EXIT_SUCCESS;
}

TreeP Insert(TreeP root, int el)
{
    if (!root)
        root = CreateEl(el);

    else if (el >= root->el)
        root->left = Insert(root->left, el);

    else
        root->right = Insert(root->right, el);

    return root;
}

TreeP CreateEl(int el)
{
    TreeP newEl = NULL;
    
    newEl = (TreeP)malloc(sizeof(Tree));
    if (!newEl)
    {
        perror("Error while allocating!\n");
        return NULL;
    }

    newEl->el = el;
    newEl->left = NULL;
    newEl->right = NULL;

    return newEl;
}

int AddThenReplace(TreeP root)
{
    int right = 0, left = 0;

    if (root->right)
        right = root->right->el + AddThenReplace(root->right);

    if (root->left)
        left = root->left->el + AddThenReplace(root->left);

    root->el = right + left;

    return root->el;
}

int FindRandom()
{
    int number = 0;
    
    number = MIN_NUM + (rand() % (MAX_NUM - MIN_NUM + 1));
    
    return number;
}
int PrintInDat(TreeP root, char* fileName)
{
    TreeP current = root;

    if (current != NULL)
    {
        PrintInDat(current->el, fileName);
        fprintf(fileName, "%d ", current->el);
        PrintInDat(current->right, fileName);
    }

    return EXIT_SUCCESS;
}
