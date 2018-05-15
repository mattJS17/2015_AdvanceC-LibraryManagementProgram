#include "Book_Management.h"

int main()
{
	int selectMenu;
	int condition=1;
	FILE * fpIn, * fpOut;
	ListNode * pVisited;
	int CheckNum;

	ListNode *pData;

	FirstPoint = NULL;

	fpIn = fopen("BookData(Data_Only).txt","r");

	if(fpIn == NULL){
		printf("\t            Can't open the %s file\n","BookData(Data_Only).txt");
		return;
	} //if

	while(TRUE){
		
		pData = (ListNode *)malloc(sizeof(ListNode)); 
		if(fscanf(fpIn,"%d",&CheckNum) == EOF){
			free(pData);
			break;
		} 
		fscanf(fpIn, "%s",pData->BookName);
		fscanf(fpIn, "%s",pData->AuthorName);
		fflush(stdin);
		fscanf(fpIn, "%d", &(pData->Place));
		fflush(stdin);
		fscanf(fpIn,"%s",pData->BookNum);
		fflush(stdin);
		fscanf(fpIn, "%d", &(pData->State));
		fflush(stdin);

		pData->link = NULL;

		pData->link = FirstPoint;
		FirstPoint = pData;
	}

	//----------------------------------------------------------------------------------

	while (condition) {

		selectMenu = displayMenu();

		switch (selectMenu) {

		case INSERT: 
			insertbook();
			break;

		case RETRIEVE:
			retrievebook();
			break;

		case DELETE:
			deletebook();
			break;

		case BORROW_RETURN:
			borrow_returnbook();
			break;

		case PRINT_LIST:
			print_listbook();
			break;

		case ABOUT:
			aboutprogram();
			break;

		case EXIT:
			pVisited = FirstPoint;
			fpOut = fopen("�м������� ���� ����.txt","wt");
			if (fpOut == NULL) {
				printf("error");
				return -1;
			}

			fprintf(fpOut,"\t������������������������������\n");
			fprintf(fpOut,"\t                �ءء� �м������� ���� ���� �ءء�\n");
			fprintf(fpOut,"\t---------------------------------------------------------------------\n");
			while(pVisited != NULL) {
				fprintf(fpOut,"\t      å ���� : %s \n",pVisited->BookName);
				fprintf(fpOut,"\t      ���� �̸� : %s \n",pVisited->AuthorName);
				fprintf(fpOut,"\t      ���� : %d�� \n",pVisited->Place );
				fprintf(fpOut,"\t      û�� ��ȣ : %s \n",pVisited->BookNum );		

				if (pVisited->State==1) {
					fprintf(fpOut,"\t      ���� ���� : ������ \n");
				} else {
					fprintf(fpOut,"\t      ���� ���� : ���Ⱑ�� \n");
				} // if-else
				fprintf(fpOut,"\t---------------------------------------------------------------------\n");

				pVisited = pVisited->link;
			} // while
			fprintf(fpOut,"\t������������������������������\n");

			fclose(fpOut);

			pVisited = FirstPoint;
			fpOut = fopen("BookData(Data_Only).txt","wt");
			if (fpOut == NULL) {
				printf("error");
				return -1;
			}
			while(pVisited != NULL) {
				fprintf(fpOut,"%s\n",pVisited->BookName);
				fprintf(fpOut,"%s\n",pVisited->AuthorName);
				fprintf(fpOut,"%d\n",pVisited->Place);
				fprintf(fpOut,"%s\n",pVisited->BookNum);
				fprintf(fpOut,"%d\n",pVisited->State);				

				pVisited = pVisited->link;
			} // while
			

			condition=0;
			printf("\n\t  Book Management Program is shutting down.. ");
			Sleep(1000);
			printf("3..");
			Sleep(1000);
			printf("2..");
			Sleep(1000);
			printf("1..\n\n");
			break;

		default:
			printf("\n\n\t    Wrong Number Input!! Try again \n");

		} // switch

		system("pause");

	} // while
	fcloseall();

	return 0;
} // main()

int displayMenu() {
	int nMenu;

	system("cls"); 
	printf("\n\n");

	printf("\t����������������������\n");
	printf("\t	�ڡ�BOOK MANAGEMENT MENU�ڡ�\n");
	printf("\t------------------------------------------\n");
	printf("\t      1. INSERT\n");
	printf("\t      2. RETRIEVE\n");	
	printf("\t      3. DELETE\n");	
	printf("\t      4. BORROW&RETURN\n");	
	printf("\t      5. PRINT LIST\n");
	printf("\t      6. ABOUT\n");	
	printf("\t------------------------------------------\n");
	printf("\t      0. EXIT\n");
	printf("\t------------------------------------------\n");
	printf("\t      Choose Menu >> ");
	scanf("%d", &nMenu);	

	return nMenu;

} // displayMenu();

void insertbook()	{
	ListNode *pInput;
	int placeCheck;
	char numCheck[40];
	int StateCheck;
	ListNode * CheckNum;

	pInput = get_Node();
	
	system("cls");
	printf("\n\n");
	printf("\t����������������������\n");
	printf("\t        ### Insert Book Data ###\n");
	printf("\t------------------------------------------\n");
	fflush(stdin);
	printf("\t      å ���� : ");
	scanf("%s",pInput->BookName);

	printf("\t      ���� �̸� : ");
	scanf("%s",pInput->AuthorName);

	fflush(stdin);
	printf("\t      ���� (5��, 6��, 9��) : ");
	scanf("%d", &placeCheck);
	if (placeCheck==5 || placeCheck==6 || placeCheck==9) {
		pInput->Place = placeCheck;
	} else {
		printf("\n\t     Place does not exist!! \n");
		free(pInput);
		return;
	}

	fflush(stdin);
	printf("\t      û�� ��ȣ : ");
	scanf("%s",numCheck);
	CheckNum = Check_BookNum(numCheck);
	if (CheckNum==NULL) {
		strcpy(pInput->BookNum, numCheck);
	} else {
		printf("\n\t     û����ȣ�� �ߺ��˴ϴ�!! \n\n");
		free(pInput);
		return;
	} 

	fflush(stdin);
	printf("\t      ���� ���� (������-1, ���Ⱑ��-0) : ");
	scanf("%d", &StateCheck); 
	if (StateCheck==1 || StateCheck==0) {
		pInput->State=StateCheck;
	} else {
		printf("\n\t     Wrong Input!! \n");
		free(pInput);
		return;
	}
	
	pInput->link = FirstPoint;
	FirstPoint = pInput;

	printf("\n\t      Book Data is Registered !! \n");
	
} // insertbook();

ListNode * get_Node()	{
	
	ListNode * pInput;

	pInput = (ListNode *)malloc(sizeof(ListNode));
	pInput->link = NULL;

	return pInput;

} // get_Node();

void retrievebook()	{
	
	int RMenu;

	system("cls");
	printf("\n\n");

	printf("\t����������������������\n");
	printf("\t        ### Retrieve Book Data ###\n");
	printf("\t------------------------------------------\n");
	printf("\t      1. Retrieve by BookName\n");
	printf("\t      2. Retrieve by AuthorName\n");	
	printf("\t      3. Retrieve by BookNum\n");	
	printf("\t------------------------------------------\n");
	printf("\t      >> ");
	scanf("%d", &RMenu);

	switch (RMenu) {

	case ByBookName:
		Ret_BookName();
		break;

	case ByAuthorName:
		Ret_AuthorName();
		break;

	case ByBookNum:
		Ret_BookNum();
		break;

	default:
		printf("\n\n\t    Wrong Number Input!! Try again \n");

	} // switch

} // retrievebook();

void Ret_BookName()	{
	ListNode *pVisited;
	char BookName[40];
	int check=0;
	int num=0;

	system("cls");
	printf("\n\n");
	fflush(stdin);
	printf("\t������������������������������\n");
	printf("\t        ### Retrieve By Book Name ###\n");
	printf("\t----------------------------------------------------------\n");
	printf("\t      >> ");
	gets(BookName);

	pVisited = FirstPoint;
	while (pVisited != NULL) {
		check = strcmp(BookName,(pVisited->BookName));
		if (check == 0) {
			printf("\t----------------------------------------------------------\n");
			printf("\t      å ���� : %s \n",pVisited->BookName);
			printf("\t      ���� �̸� : %s \n",pVisited->AuthorName);
			printf("\t      ���� : %d�� \n",pVisited->Place );
			printf("\t      û�� ��ȣ : %s \n",pVisited->BookNum );
			if (pVisited->State==1) {
				printf("\t      ���� ���� : ������ \n");
			} else {
				printf("\t      ���� ���� : ���Ⱑ�� \n");
			} // if-else
			printf("\t----------------------------------------------------------\n");
			num++;
		} // if
		pVisited = pVisited->link;
		if (pVisited==NULL) break;
	} // while
	printf("\t������������������������������\n");
	if (num==0) {
		printf("\n\t      �ش� ������ �м��������� �����ϴ�\n\n");
	}

} // Ret_BookName();

void Ret_AuthorName()	{
	ListNode *pVisited;
	char AuthorName[40];
	int check=0;
	int num=0;

	system("cls");
	printf("\n\n");
	fflush(stdin);
	printf("\t������������������������������\n");
	printf("\t        ### Retrieve By Author Name ###\n");
	printf("\t----------------------------------------------------------\n");
	printf("\t      >> ");
	gets(AuthorName);

	pVisited = FirstPoint;
	while (pVisited != NULL) {
		check = strcmp(AuthorName,(pVisited->AuthorName));
		if (check == 0) {
			printf("\t----------------------------------------------------------\n");
			printf("\t      å ���� : %s \n",pVisited->BookName);
			printf("\t      ���� �̸� : %s \n",pVisited->AuthorName);
			printf("\t      ���� : %d�� \n",pVisited->Place );
			printf("\t      û�� ��ȣ : %s \n",pVisited->BookNum );
			if (pVisited->State==1) {
				printf("\t      ���� ���� : ������ \n");
			} else {
				printf("\t      ���� ���� : ���Ⱑ�� \n");
			} // if-else
			printf("\t----------------------------------------------------------\n");
			num++;
		} // if
		pVisited = pVisited->link;
		if (pVisited==NULL) break;
	} // while
	printf("\t������������������������������\n");
	if (num==0) {
		printf("\n\t      �ش� ������ �м��������� �����ϴ�\n\n");
	}

} // Ret_Author();

void Ret_BookNum()	{
	ListNode *pVisited;
	char BookNum[40];
	int check=0;
	int num=0;

	system("cls");
	printf("\n\n");
	fflush(stdin);
	printf("\t������������������������������\n");
	printf("\t        ### Retrieve By Book Number ###\n");
	printf("\t----------------------------------------------------------\n");
	printf("\t      >> ");
	gets(BookNum);

	pVisited = FirstPoint;
	while (pVisited != NULL) {
		check = strcmp(BookNum,(pVisited->BookNum));
		if (check == 0) {
			printf("\t----------------------------------------------------------\n");
			printf("\t      å ���� : %s \n",pVisited->BookName);
			printf("\t      ���� �̸� : %s \n",pVisited->AuthorName);
			printf("\t      ���� : %d�� \n",pVisited->Place );
			printf("\t      û�� ��ȣ : %s \n",pVisited->BookNum );
			if (pVisited->State==1) {
				printf("\t      ���� ���� : ������ \n");
			} else {
				printf("\t      ���� ���� : ���Ⱑ�� \n");
			} // if-else
			printf("\t----------------------------------------------------------\n");
			num++;
		} // if
		pVisited = pVisited->link;
		if (pVisited==NULL) break;
	} // while
	printf("\t������������������������������\n");
	if (num==0) {
		printf("\n\t      �ش� ������ �м��������� �����ϴ�\n\n");
	}

}// Ret_BookNum();

void deletebook()	{
	ListNode *pVisited, *pPrev;
	char BookNum[40];
	int num=0;

	system("cls");
	printf("\n\n");
	fflush(stdin);
	printf("\t������������������������������\n");
	printf("\t      ### Delete Book Data ###\n");
	printf("\t----------------------------------------------------------\n");
	printf("\t      û����ȣ >> ");
	gets(BookNum);

	pVisited = FirstPoint;
	pPrev = NULL;

	while (pVisited != NULL) {
		while(strcmp(BookNum,(pVisited->BookNum))) {
			pPrev=pVisited;
			pVisited = pVisited->link;
			if(pVisited==NULL) break;
		}
		if(pVisited==NULL) break;

		if(pPrev==NULL){
			FirstPoint=FirstPoint->link;
		} else {
			pPrev->link=pVisited->link;
		}
		pVisited->link=NULL;
		free(pVisited);
		num++;

		if(pPrev==NULL){
			pVisited=FirstPoint;
		}else{
			pVisited=pPrev->link;
		}
	} // while
	printf("\t������������������������������\n");

	if (num==0) {
		printf("\n\t      �ش� ������ �м��������� �����ϴ�\n");
		printf("\t������������������������������\n");
		return;
	} else {
		printf("\n\t      Successfully Deleted!\n");
		printf("\t������������������������������\n");
		return;
	}

} // deletebook();

void borrow_returnbook()	{

	int BRMenu;

	system("cls");
	printf("\n\n");

	printf("\t����������������������\n");
	printf("\t        ### Borrow & Return Book Data ###\n");
	printf("\t------------------------------------------\n");
	printf("\t      1. ���� ����\n");
	printf("\t      2. ���� �ݳ�\n");		
	printf("\t------------------------------------------\n");
	printf("\t      >> ");
	scanf("%d", &BRMenu);

	switch (BRMenu) {

	case BorrowBook:
		borrow_book();
		break;

	case ReturnBook:
		return_book();
		break;

	default:
		printf("\n\n\t    Wrong Number Input!! Try again \n");

	} // switch

} // borrow_returnbook();

void borrow_book()		{
	char BookNum[40];
	ListNode * pPoint;
	char borrow;

	system("cls");
	printf("\n\n");
	fflush(stdin);
	printf("\t������������������������������\n");
	printf("\t      ### Borrow Book Data ###\n");
	printf("\t----------------------------------------------------------\n");
	printf("\t  �����Ϸ��ϴ� å�� û����ȣ�� �Է��ϼ��� >> ");
	gets(BookNum);

	pPoint = Check_BookNum(BookNum);

	if (pPoint==NULL) {
		printf("\n\t      �ش� ������ �м��������� �����ϴ�\n");
		printf("\t������������������������������\n");
		return;
	} // if

	if (pPoint->State == 1) {
		printf("\n\t  ��%s��(��)�� ���� �������Դϴ�.\n",(pPoint->BookName));
	}  else {
		printf("\n\t  ��%s��(��)�� ���� ���Ⱑ���մϴ�.\n",(pPoint->BookName));
		printf("\t  ��%s��(��)�� �����Ͻðڽ��ϱ�?(y/n) >> ",(pPoint->BookName));
		scanf("%c",&borrow);
		printf("\n\t----------------------------------------------------------\n");
		switch(borrow) {

		case 'y':
			printf("\n\t  ��%s��(��)�� ����Ǿ����ϴ� \n",(pPoint->BookName));
			pPoint->State=1;
			break;

		case 'n':
			printf("\n\t  ��%s��(��)�� �������� �ʽ��ϴ� \n",(pPoint->BookName));
			break;

		default:
			printf("\n\n\t    Wrong Number Input!! Try again \n");

		} // switch

	} // if-else
	printf("\n\t������������������������������\n");
} // borrow_book()

void return_book()		{
	char BookNum[40];
	ListNode * pPoint;
	char return_book;

	system("cls");
	printf("\n\n");
	fflush(stdin);
	printf("\t������������������������������\n");
	printf("\t      ### Return Book Data ###\n");
	printf("\t----------------------------------------------------------\n");
	printf("\t  �ݳ��Ϸ��ϴ� å�� û����ȣ�� �Է��ϼ��� >> ");
	gets(BookNum);

	pPoint = Check_BookNum(BookNum);

	if (pPoint==NULL) {
		printf("\n\t      �ش� ������ �м��������� �����ϴ�\n");
		printf("\t������������������������������\n");
		return;
	} // if

	if (pPoint->State == 1) {
		printf("\n\t  ��%s��(��)�� ���� �������Դϴ�.\n",(pPoint->BookName));
		printf("\t  ��%s��(��)�� �ݳ��Ͻðڽ��ϱ�?(y/n) >> ",(pPoint->BookName));
		scanf("%c",&return_book);
		printf("\n\t----------------------------------------------------------\n");
		switch(return_book) {

		case 'y':
			printf("\n\t  ��%s��(��)�� �ݳ��Ǿ����ϴ� \n",(pPoint->BookName));
			pPoint->State=0;
			break;

		case 'n':
			printf("\n\t  ��%s��(��)�� �ݳ����� �ʽ��ϴ� \n",(pPoint->BookName));
			break;

		default:
			printf("\n\n\t    Wrong Number Input!! Try again \n");

		} // switch

	}  else {
		printf("\n\t  ��%s��(��)�� ���� ���Ⱑ���մϴ�.\n",(pPoint->BookName));

	} // if-else
	printf("\n\t������������������������������\n");
} // return_book();

ListNode * Check_BookNum(char * BookNum)	{
	ListNode * pVisited;
	int num=0;
	int check;
	ListNode * pPoint;

	pVisited = FirstPoint;
	pPoint=NULL;
	while (pVisited != NULL) {
		check = strcmp(BookNum,(pVisited->BookNum));
		if (check == 0) {
			printf("\t----------------------------------------------------------\n");
			printf("\t      å ���� : %s \n",pVisited->BookName);
			printf("\t      ���� �̸� : %s \n",pVisited->AuthorName);
			printf("\t      ���� : %d�� \n",pVisited->Place );
			printf("\t      û�� ��ȣ : %s \n",pVisited->BookNum );
			if (pVisited->State==1) {
				printf("\t      ���� ���� : ������ \n");
			} else {
				printf("\t      ���� ���� : ���Ⱑ�� \n");
			} // if-else
			printf("\t----------------------------------------------------------\n");
			pPoint=pVisited;
			num++;
		} // if
		pVisited = pVisited->link;
		if (pVisited==NULL) break;
	} // while

	return pPoint;

} // check_BookNum()
void print_listbook()	{
	ListNode * pVisited;
	int PMenu;
	int num=0;

	pVisited = FirstPoint;

	if (FirstPoint == NULL) {
		system("cls");
		printf("\n\n");
		printf("\t����������������������\n");
		printf("\t        ### Book Data is EMPTY ###\n");
		printf("\t------------------------------------------\n");
	} else {
		PMenu = displayPrintMenu();

		switch (PMenu) {

		case 1:
			system("cls");
			printf("\n\n");
			printf("\t������������������������������\n");
			printf("\t      �ءء� Print Every Book Data �ءء�\n");
			printf("\t----------------------------------------------------------\n");
			if (FirstPoint == NULL) {
				printf("List is EMPTY!! \n");
			} else {
				while (pVisited != NULL) {
					printf("\t      å ���� : %s \n",pVisited->BookName);
					printf("\t      ���� �̸� : %s \n",pVisited->AuthorName);
					printf("\t      ���� : %d�� \n",pVisited->Place );
					printf("\t      û�� ��ȣ : %s \n",pVisited->BookNum );
					if (pVisited->State==1) {
						printf("\t      ���� ���� : ������ \n");
					} else {
						printf("\t      ���� ���� : ���Ⱑ�� \n");
					} // if-else
					printf("\t----------------------------------------------------------\n");

					pVisited = pVisited->link;
				} // while
				printf("\t������������������������������\n");
			} // if-else

			break;

		case 5:
			system("cls");
			printf("\n\n");
			printf("\t������������������������������\n");
			printf("\t      �ءء� Print 5 Floor Book Data �ءء�\n");
			printf("\t----------------------------------------------------------\n");
			if (FirstPoint == NULL) {
				printf("List is EMPTY!! \n");
			} else {
				while (pVisited != NULL) {
					if (pVisited->Place == 5) {
						printf("\t      å ���� : %s \n",pVisited->BookName);
						printf("\t      ���� �̸� : %s \n",pVisited->AuthorName);
						printf("\t      ���� : %d�� \n",pVisited->Place );
						printf("\t      û�� ��ȣ : %s \n",pVisited->BookNum );
						if (pVisited->State==1) {
							printf("\t      ���� ���� : ������ \n");
						} else {
							printf("\t      ���� ���� : ���Ⱑ�� \n");
						} // if-else
						printf("\t----------------------------------------------------------\n");
						num++;
					} // if
					pVisited = pVisited->link;

				} // while
				printf("\t������������������������������\n");
				if (num==0) {
					printf("\n\t      This Floor is EMPTY!! \n");
				}
			} // if-else

			break;

		case 6:
			system("cls");
			printf("\n\n");
			printf("\t������������������������������\n");
			printf("\t      �ءء� Print 6 Floor Book Data �ءء�\n");
			printf("\t----------------------------------------------------------\n");
			if (FirstPoint == NULL) {
				printf("List is EMPTY!! \n");
			} else {
				while (pVisited != NULL) {
					if (pVisited->Place == 6) {
						printf("\t      å ���� : %s \n",pVisited->BookName);
						printf("\t      ���� �̸� : %s \n",pVisited->AuthorName);
						printf("\t      ���� : %d�� \n",pVisited->Place );
						printf("\t      û�� ��ȣ : %s \n",pVisited->BookNum );
						if (pVisited->State==1) {
							printf("\t      ���� ���� : ������ \n");
						} else {
							printf("\t      ���� ���� : ���Ⱑ�� \n");
						} // if-else
						printf("\t----------------------------------------------------------\n");
						num++;
					} // if
					pVisited = pVisited->link;

				} // while
				printf("\t������������������������������\n");
				if (num==0) {
					printf("\n\t      This Floor is EMPTY!! \n");
				}
			} // if-else

			break;

		case 9:
			system("cls");
			printf("\n\n");
			printf("\t������������������������������\n");
			printf("\t      �ءء� Print 9 Floor Book Data �ءء�\n");
			printf("\t----------------------------------------------------------\n");
			if (FirstPoint == NULL) {
				printf("List is EMPTY!! \n");
			} else {
				while (pVisited != NULL) {
					if (pVisited->Place == 9) {
						printf("\t      å ���� : %s \n",pVisited->BookName);
						printf("\t      ���� �̸� : %s \n",pVisited->AuthorName);
						printf("\t      ���� : %d�� \n",pVisited->Place );
						printf("\t      û�� ��ȣ : %s \n",pVisited->BookNum );
						if (pVisited->State==1) {
							printf("\t      ���� ���� : ������ \n");
						} else {
							printf("\t      ���� ���� : ���Ⱑ�� \n");
						} // if-else
						printf("\t----------------------------------------------------------\n");
						num++;
					} // if
					pVisited = pVisited->link;

				} // while
				printf("\t������������������������������\n");
				if (num==0) {
					printf("\n\t      This Floor is EMPTY!! \n");
				}
			} // if-else

			break;

		case 0:
			printf("\n\t      Return to the Main Menu\n");
			break;

		default:
			printf("\n\t      Wrong Input\n");

		} // switch

	} // if-else

} // print_listbook();

int displayPrintMenu()	{
	int PMenu;

	system("cls");
	printf("\n\n");
	printf("\t����������������������\n");
	printf("\t        ### Print Book Data List ###\n");
	printf("\t------------------------------------------\n");
	printf("\t      ��ü	- Press ��\n");
	printf("\t      5��	- Press �� \n");
	printf("\t      6��	- Press ��\n");	
	printf("\t      9��	- Press ��\n");
	printf("\t------------------------------------------\n");
	printf("\t      Press 0 to go back\n");
	printf("\t------------------------------------------\n");
	printf("\t      >> ");
	scanf("%d", &PMenu);

	return PMenu;
} // displayPrintMenu()

void aboutprogram() {

	system("cls");
	printf("\n\n");
	printf("\t����������������������������\n");
	printf("\t	�м������� ���� ���� ���α׷� ver 1.0 \n");
	printf("\t------------------------------------------------------\n");
	printf("\t      Programmed by JaeHoon Shim\n");
	printf("\t      Programmed by JongHoon Lee\n");	
	printf("\t------------------------------------------------------\n");
	printf("\t                   6��. ڱ������          \n");
	printf("\t      15010979 JaeHoon Shim, Computer engineering\n");	
	printf("\t      15010967 JongHoon Lee, Computer engineering\n");	
	printf("\t      15011026 YoungJoon Park, Computer engineering\n");	
	printf("\t      15011057 JooHungLee, Computer engineering\n");
	printf("\t------------------------------------------------------\n");
	printf("\n\t      copyright@ ڱ������\n");	
	printf("\t����������������������������\n");

} // aboutprogram();