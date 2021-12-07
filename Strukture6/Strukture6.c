#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define MAX_NAME_A 128
#define MAX_A_STRING 1024
#define MAX_NAME_B 128
#define MAX_LINE 1024
#define MAX_D_STRING 10 //2000 + 01 + 01 + - + \0
#define MAX_FILE_NAME 1024

struct _date;
typedef struct _date* DateP;
typedef struct _date {
    int year;
    int month;
    int day;
} Date;

struct _article;
typedef struct _article* ArticleP;
typedef struct _article {
    char name[MAX_NAME_A];
    int count;
    float price;
    ArticleP next;
} Article;

struct _bill;
typedef struct _bill* BillP;
typedef struct _bill {
    char name[MAX_NAME_B];
    DateP date;
    Article articleHead;
    BillP next;
} Bill;

struct _filter;
typedef struct _filter* FilterP;
typedef struct _filter {
    DateP from;
    DateP to;
    char name[MAX_NAME_A];
} Filter;

FilterP CreateFilter(char* dateFromStr, char* dateToStr, char* articleName);
int DeleteFilter(FilterP filter);
DateP CreateDate(char* str);
int DateToString(char* destination, DateP date);
int PrintDate(DateP date);
int Datecmp(DateP date1, DateP date2);
bool RangeofDate(DateP date, DateP from, DateP to);
BillP CreateBill(char* billFileName);
int InsertBillAfter(BillP position, BillP bill);
int InsertBSorted(BillP head, BillP bill);
int ReadBillsFromFile(BillP head, char* fileName);
int PrintBill(BillP bill);
int PrintAllBills(BillP head);
int DeleteBill(BillP bill);
int DeleteBillAfter(BillP position);
int DeleteAllBills(BillP head);
int InitializeArticle(ArticleP article);
ArticleP CreateArticle(char* str);
int ArticleToString(char* destination, ArticleP article);
int PrintArticle(ArticleP article);
ArticleP FindArticleByName(ArticleP head, char* name);
int DeleteArticleAfter(ArticleP position);
int DeleteAllArticles(ArticleP head);
int InsertArticleAfter(ArticleP position, ArticleP article);
int InsertASorted(ArticleP head, ArticleP article);
int SearchAinRange(BillP head);
int searchArticleInRange(BillP head, FilterP filter);

int main(int argc, char* argv[]) {
    Bill head;
    char fileName[MAX_FILE_NAME] = { 0 };
    int status = EXIT_SUCCESS;

    do {
        printf("Filename: ");
        scanf(" %s", fileName);

        status = ReadBillsFromFile(&head, fileName);
    } while (status > EXIT_SUCCESS);
    if (status != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    PrintAllBills(&head);
    SearchAinRange(&head);
    DeleteAllBills(&head);

    return EXIT_SUCCESS;
}

int SearchAinRange(BillP head) {
    char article[MAX_NAME_A] = { 0 };
    char dateFromString[MAX_D_STRING] = { 0 };
    char dateToString[MAX_D_STRING] = { 0 };
    FilterP filter = NULL;

    printf("\nSearch:\n");
    printf("<article> <from date> <to date>\n");
    printf("Example: kruh 1992-01-03 1992-02-08\n");

    do {
        printf("Your input: ");
        scanf(" %s %s %s", article, dateFromString, dateToString);

        filter = CreateFilter(dateFromString, dateToString, article);
    } while (!filter);

    searchArticleInRange(head, filter);
    DeleteFilter(filter);

    return EXIT_SUCCESS;
}

int searchArticleInRange(BillP head, FilterP filter) {
    BillP bill = NULL;
    int totalCount = 0;
    float totalPrice = 0.0;

    printf("Result:\n");

    for (bill = head->next; bill != NULL; bill = bill->next)
        if (RangeofDate(bill->date, filter->from, filter->to)) 
        {
            ArticleP article = FindArticleByName(&bill->articleHead, filter->name);
            if (article) 
            {
                PrintArticle(article);
                totalCount += article->count;
                totalPrice += article->count * article->price;
            }
        }


    printf("Search result for \"%s\"\nCount: %d\nTotal profit: %.02f\n", filter->name, totalCount, totalPrice);

    return EXIT_SUCCESS;
}

int InitializeArticle(ArticleP article) {
    article->count = 0;
    article->price = 0.0f;
    memset(article->name, 0, MAX_NAME_A);
    article->next = NULL;

    return EXIT_SUCCESS;
}

ArticleP CreateArticle(char* str) {
    ArticleP article = NULL;
    int status = 0;

    if (!str) {
        printf("String passed as null to create article!\r\n");
        return NULL;
    }

    article = (ArticleP)malloc(sizeof(Article));
    if (!article) {
        perror("Article allocation failed!");
        return NULL;
    }

    InitializeArticle(article);

    status = sscanf(str, "%s %d %f",
        &article->name,
        &article->count,
        &article->price
    );

    if (status != 3) {
        printf("Invalid article \"%s\", should be in format - <name> <count> <price>!\r\n", str);
        free(article);
        return NULL;
    }

    return article;
}

int ArticleToString(char* destination, ArticleP article) {
    if (!destination) {
        printf("Destination string is null!\r\n");
        return -1;
    }

    if (!article) {
        sprintf(destination, "##INVALID ARTICLE");
        return -1;
    }

    sprintf(destination, "%s %d %.02f", article->name, article->count, article->price);
    return EXIT_SUCCESS;
}

int PrintArticle(ArticleP article) {
    char articleAsString[MAX_A_STRING] = { 0 };

    ArticleToString(articleAsString, article);
    printf(articleAsString);

    return EXIT_SUCCESS;
}

ArticleP FindArticleByName(ArticleP head, char* name) {
    ArticleP article = NULL;

    for (article = head; article != NULL; article = article->next) {
        if (strcmp(article->name, name) == 0) {
            return article;
        }
    }

    return NULL;
}

int DeleteArticleAfter(ArticleP position) {
    ArticleP toDelete = position->next;

    if (!toDelete) {
        return EXIT_SUCCESS;
    }

    position->next = toDelete->next;
    free(toDelete);

    return EXIT_SUCCESS;
}

int DeleteAllArticles(ArticleP head) {
    while (head->next) {
        DeleteArticleAfter(head);
    }

    return EXIT_SUCCESS;
}

int InsertArticleAfter(ArticleP position, ArticleP article) {
    article->next = position->next;
    position->next = article;

    return EXIT_SUCCESS;
}

int InsertASorted(ArticleP head, ArticleP article) {
    ArticleP position = head;

    while (position->next != NULL && strcmp(position->next->name, article->name) < 0) {
        position = position->next;
    }

    InsertArticleAfter(position, article);

    return EXIT_SUCCESS;
}

BillP CreateBill(char* BFile) {
    FILE* fp = NULL;
    BillP bill = NULL;
    int status = EXIT_SUCCESS;
    char fileLine[MAX_LINE] = { 0 };

    fp = fopen(BFile, "r");
    if (!fp) {
        perror("Bill not opened!");
        return NULL;
    }

    bill = (BillP)malloc(sizeof(Bill));
    if (!bill) {
        perror("Bill not allocated!");
        fclose(fp);
        return NULL;
    }

    strcpy(bill->name, BFile);

    fgets(fileLine, MAX_LINE, fp);
    bill->date = CreateDate(fileLine);
    if (!bill->date) {
        fclose(fp);
        DeleteBill(bill);
        return NULL;
    }

    while (!feof(fp)) {
        ArticleP article = NULL;
        fgets(fileLine, MAX_LINE, fp);

        if (strlen(fileLine) == 0) {
            continue;
        }

        article = CreateArticle(fileLine);
        if (!article) {
            fclose(fp);
            DeleteBill(bill);
            return NULL;
        }

        InsertASorted(&bill->articleHead, article);
    }

    fclose(fp);

    return bill;
}

int InsertBillAfter(BillP position, BillP bill) 
{
    bill->next = position->next;
    position->next = bill;

    return EXIT_SUCCESS;
}

int InsertBSorted(BillP head, BillP bill) 
{
    BillP position = head;

    while (position->next != NULL && Datecmp(position->next->date, bill->date) < 0) {
        position = position->next;
    }

    InsertBillAfter(position, bill);

    return EXIT_SUCCESS;
}


int ReadBillsFromFile(BillP head, char* fileName) {
    FILE* fp = NULL;
    char fileLine[MAX_LINE] = { 0 };

    fp = fopen(fileName, "r");
    if (!fp) {
        perror("File with bills not opened!");
        return -1;
    }

    while (!feof(fp)) {
        BillP bill = NULL;
        fscanf(fp, "%s", fileLine);

        if (strlen(fileLine) == 0) {
            continue;
        }

        bill = CreateBill(fileLine);
        if (!bill) {
            fclose(fp);
            DeleteAllBills(head);
            return -1;
        }

        InsertBSorted(head, bill);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

int PrintBill(BillP bill) {
    ArticleP article = NULL;

    printf("\t============================\r\n");
    printf("\t\t** Date => ");
    PrintDate(bill->date);
    printf("\r\n");
    printf("\t\t** Articles (name, count, price) \r\n");

    for (article = bill->articleHead.next; article != NULL; article = article->next) {
        printf("\t\t\t * ");
        PrintArticle(article);
        printf("\r\n");
    }

    return EXIT_SUCCESS;
}

int PrintAllBills(BillP head) {
    BillP bill = NULL;

    for (bill = head->next; bill != NULL; bill = bill->next) {
        PrintBill(bill);
    }

    return EXIT_SUCCESS;
}

int DeleteBill(BillP bill) {
    if (!bill) {
        return EXIT_SUCCESS;
    }

    if (bill->date) {
        free(bill->date);
    }

    DeleteAllArticles(&bill->articleHead);
    free(bill);

    return EXIT_SUCCESS;
}

int DeleteBillAfter(BillP position) {
    BillP toDelete = position->next;

    if (!toDelete) {
        return EXIT_SUCCESS;
    }

    position->next = toDelete->next;
    DeleteBill(toDelete);

    return EXIT_SUCCESS;
}

int DeleteAllBills(BillP head) {
    while (head->next) {
        DeleteBillAfter(head);
    }

    return EXIT_SUCCESS;
}

DateP CreateDate(char* str) {
    DateP date = NULL;
    int status = 0;

    if (!str) {
        printf("Invalid string.\n");
        return NULL;
    }

    date = (DateP)malloc(sizeof(Date));

    if (!date) {
        perror("Error while allocating.\n");
        return NULL;
    }

    status = sscanf(str, "%d %d %d", &date->year, &date->month, &date->day);

    if (status != 3) {
        printf("Invalid date.\n");
        free(date);
        return NULL;
    }

    return date;
}

int DateToString(char* destination, DateP date) {
    if (!destination) {
        printf("Destination string is null!\r\n");
        return -1;
    }

    if (!date) {
        printf(destination, "-");
        return EXIT_SUCCESS;
    }

    printf(destination, "%d-%d-%d", date->year, date->month, date->day);

    return EXIT_SUCCESS;
}

int PrintDate(DateP date) {
    char datestr[MAX_D_STRING] = { 0 };

    DateToString(datestr, date);
    printf(datestr);

    return EXIT_SUCCESS;
}

int Datecmp(DateP date1, DateP date2) {
    int result = date1->year - date2->year;

    if (result == 0) {
        result = date1->month - date2->month;

        if (result == 0) {
            result = date1->day - date2->day;
        }
    }

    return result;
}

bool RangeofDate(DateP date, DateP from, DateP to) 
{
    return Datecmp(date, from) >= 0 && Datecmp(date, to) <= 0;
}

FilterP CreateFilter(char* FromDate, char* ToDate, char* articleName) {
    FilterP filter = NULL;

    filter = (FilterP)malloc(sizeof(Filter));
    if (!filter) {
        perror("Error while allocating.");
        return NULL;
    }

    filter->from = CreateDate(FromDate);
    if (!filter->from) {
        DeleteFilter(filter);
        return NULL;
    }

    filter->to = CreateDate(ToDate);
    if (!filter->to) {
        DeleteFilter(filter);
        return NULL;
    }

    strcpy(filter->name, articleName);

    return filter;
}

int DeleteFilter(FilterP filter) 
{    
    while (filter->from)
        free(filter->from);

    while (filter->to)
        free(filter->to);

    free(filter);

    return EXIT_SUCCESS;
}