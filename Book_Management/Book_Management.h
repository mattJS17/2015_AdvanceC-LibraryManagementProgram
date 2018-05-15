#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define INSERT					1
#define RETRIEVE				2
#define DELETE					3
#define BORROW_RETURN			4 
#define PRINT_LIST				5
#define ABOUT					6	
#define EXIT					0

// define for retrieve
#define ByBookName		1
#define ByAuthorName	2
#define ByBookNum		3

// define for borrow/return
#define BorrowBook	1
#define ReturnBook	2


typedef struct _ListNode {
	char BookName[60];
	char AuthorName[40];
	int Place;
	char BookNum[40];
	int State;

	struct _ListNode * link;
}ListNode;

ListNode * FirstPoint;

int displayMenu();

void insertbook();
ListNode * get_Node();

void retrievebook();
void Ret_BookName();
void Ret_AuthorName();
void Ret_BookNum();

ListNode * Check_BookNum(char * BookNum);

void deletebook();

void borrow_returnbook();
void borrow_book();
void return_book();
void print_listbook();

int displayPrintMenu();

void aboutprogram();
