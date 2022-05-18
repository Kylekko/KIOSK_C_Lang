#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#include<time.h>

void gotoxy(int x, int y);
void cls();

int menu();
void intro();
void coffee();

void coffee_list();
void choice(int choice, int itemNo, int stock);
void payment(int price);

void checkPW();
void adminSetting();
void itemCount();
void addItem();
void delItem();

void gotoxy(int x, int y) {
	COORD Pos = {x-1, y-1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void cls(){
    system("cls");
}

void intro() {
	char welcome1[50]="WELCOME";
	char welcome2[50]=" TO THE";
	char welcome3[50]=" COFFEE SHOP!";

	int i;

	gotoxy(40, 9);
    for(i=0; i<strlen(welcome1);i++){
		printf(" %c",welcome1[i]);
		Sleep(100);
	}

	gotoxy(45, 11);
    for(i=0; i<strlen(welcome2);i++){
		printf(" %c",welcome2[i]);
		Sleep(100);
	}

	gotoxy(50, 13);
    for(i=0; i<strlen(welcome3);i++){	
		printf(" %c",welcome3[i]);
		Sleep(100);
	}
	Sleep(300);
	cls();
    menu();
}

int menu(){
    int num;
	cls();

	gotoxy(45, 8);
    printf(">> 1. Coffee List\n"); 
    Sleep(400);

	gotoxy(45, 10);
    printf(">> 2. Admin Setting\n"); 
    Sleep(400);

	gotoxy(45, 12);
    printf(">> 3. Exit\n");  
    Sleep(400);

	gotoxy(45, 15);
    scanf("%d", &num);

    switch(num) {
        case 1:
            cls();
            coffee_list();

        case 2:
            cls();
			checkPW();
			break;

        case 3:
            cls();
			exit(1);
            break;

        default:
            cls();
            menu();
    }
}

typedef struct Item{
	int itemNo;
	char coffeeList[20];
	int price;
    int quantity;
} Item;
struct Item *ptr;
Item item[50];
int totalCash = 0;

void coffee_list() {
	int i, cnt=0;

	ptr = item;

	cls();
	gotoxy(30, 3);
	printf("   =============================================================");
	gotoxy(30, 4);
	printf("   |  Item No.  |    Item Name       |   Price   | Max Quantity|");
	gotoxy(30, 5);
	printf("   =============================================================");

	for(i=0; i<sizeof(item)/sizeof(Item); i++) {
		if(item[i].itemNo != NULL) {
			printf("\n\t\t\t\t");
			printf("| %6d     |  %16s  |  %7d  | %7d     |", (ptr + i)->itemNo, 
															 (ptr + i)->coffeeList, 
															 (ptr + i)->price, 
														     (ptr + i)->quantity);
			printf("\n\t\t\t\t");
			printf("-------------------------------------------------------------");
			printf("\t\t\t\t");

			Sleep(150);
		}
		else {
			cnt++;
		}
		if(cnt == sizeof(item)/sizeof(Item)) {
			gotoxy(55, 15);
			printf("No Data");
			Sleep(1000);

			cls();

			gotoxy(55, 15);
			printf("Go to Admin Setting");
			Sleep(1000);

			checkPW();
		}
	} printf("\n\n\t\t\tMaximum purchaseable quantity once is \"Max Quantity\"");
	return choice(ptr->itemNo, ptr->price, ptr->quantity);
}

void choice(int choice, int itemNo, int stock) {
	int payPrice;

	printf("\n\n");
	printf("\t\t\tOrder 1\n\t\t\tMain Menu 2\t\t");
	scanf("%d", &choice);

	if(choice == 1) {
		cls();
		gotoxy(45, 11);
		printf("Enter ItemNo and enter quantity");

		gotoxy(45, 13);
		scanf("%d %d", &itemNo, &stock);

		if(itemNo < sizeof(ptr->itemNo)) {
			if((item[itemNo-1].quantity < stock) || stock <= 0) {
				cls();
				gotoxy(55, 13);
				printf("Please check the available quantity");
				Sleep(1000);
				coffee_list();
			}

			payPrice = (ptr + itemNo-1)->price * stock;

			gotoxy(45, 17);
			printf("Choice item %s its price is %d", (ptr + itemNo-1)->coffeeList, payPrice);
			Sleep(2000);

			payment(payPrice);
		}
		else {
			cls();
			gotoxy(55, 13);
			printf("Please check the menu");
			Sleep(1000);
			coffee_list();
		}
	}
	else if(choice == 2) {
		menu();
	}
	else {
		cls();
		gotoxy(55, 13);
		printf("Choses 1 or 2");
		Sleep(1000);
		menu();
	}
}

void payment(int price) {
	char ch;

	cls();
	gotoxy(20, 15);
	printf("Would you like to pay? y/n");
	
	gotoxy(20, 17);
	scanf("%s", &ch);

	if(ch=='y') {
		gotoxy(20, 19);
		printf("Payment has been completed!");
		totalCash += price;
		Sleep(1000);

		cls();
		gotoxy(20, 19);
		printf("Would you like more order? y/n");
		gotoxy(20, 20);
		scanf("%s", &ch);

		if(ch=='y') {
			coffee_list();
		} 
		else {
			cls();
			gotoxy(55, 13);
			printf("Thank you!\n");
			Sleep(1000);
			menu();
		} 
	} 
	else {
		cls();
		gotoxy(20, 13);
		printf("Do you want exit? y/n");
		gotoxy(20, 14);
		scanf("%s", &ch);

		if(ch=='y') {
			cls();
			gotoxy(55, 13);
			printf("Thank you!\n");
			Sleep(500);
			exit(1);
		} 
		else {
			coffee_list();
		}
	}
}

void checkPW() {
	int pw;

	cls();
	gotoxy(40, 8);
    printf(">> 1. Main Menu\n"); 
    Sleep(400);

	gotoxy(40, 10);
    printf(">> Please Enter Password or (1 to Back in Main Menu) :\n"); 
	gotoxy(40, 12);
	scanf("%d", &pw);

	if(pw==20171052) {
		cls();
		adminSetting();
	}
	else if(pw==1) {
		cls();
		menu();
	}
	else {
		cls();
		checkPW();
	}
}

void adminSetting() {
	int choice;

	cls();
	gotoxy(45, 8);
    printf(">> 1. Total Cash Today"); 
    Sleep(400);
	gotoxy(45, 10);
    printf(">> 2. Item Counter\n"); 
    Sleep(400);
	gotoxy(45, 12);
    printf(">> 3. Add Coffee Item\n"); 
    Sleep(400);
	gotoxy(45, 14);
    printf(">> 4. Delete Item\n"); 
    Sleep(400);
	gotoxy(45, 16);
    printf(">> 0. Main Menu\n"); 
    Sleep(400);

	gotoxy(45, 18);
	scanf("%d", &choice);

	switch(choice) {
	case 0:
		cls();
		menu();
		break;

	case 1:
		cls();
		gotoxy(40, 5);
		printf("Today Total Cash : %d", totalCash);
		Sleep(2000);
		adminSetting();
		break;

	case 2:
		cls();
		itemCount();
		break;

	case 3:
		cls();
		addItem();
		break;
		
	case 4:
		cls();
		delItem();
		break;

	default:
		cls();
		checkPW();
		break;

	}
}

void itemCount() { 
	int i, cnt=0;
	for(i=0; i<sizeof(item)/sizeof(Item); i++) {
		if(item[i].itemNo == NULL)
			continue;
		cls();
		gotoxy(45, 5);
		printf("Item Counting: %d", i+1);
		cnt++;
		Sleep(200);
	}
	Sleep(1000);
	cls();
	gotoxy(45, 5);
	printf("Total Item is %d", cnt);
	Sleep(2000);
	adminSetting();
}

void addItem() { 
	int i = 0, cnt; 
	char check;
	ptr = item;
	while(1) {
		cls();
		gotoxy(40, 8);

		if(item[i].itemNo == NULL) {
			printf("Input ItemNo, Name, Price, Quantity : ");
			gotoxy(55, 10);
			scanf("%d %s %d %d", &item[i].itemNo, 
								 &item[i].coffeeList, 
								 &item[i].price, 
								 &item[i].quantity);

			cls();
			i++;
		}
		else {
			i++;
			continue;
		}

		Sleep(500);
		gotoxy(45, 13);
		printf("SUCCESE!!");
		Sleep(1000);
		cls();

		gotoxy(40, 13);
		printf("Continue adding items? (y/n) ");
		gotoxy(55, 15);
		scanf("%s", &check);
		cls();

		if(check == 'n') 
			break;
	}
	menu();
}

void delItem() {
	int delItem;
	char check;

	while(1) {
		gotoxy(55, 13);
		printf("Item number to delete : ");

		gotoxy(55, 15);
		scanf("%d", &delItem);

		item[delItem-1].itemNo = NULL;
		strcpy(item[delItem-1].coffeeList, " ");
		item[delItem-1].price = NULL;
		item[delItem-1].quantity = NULL;

		cls();
		gotoxy(55, 13);
		printf("SUCCSE");
		Sleep(1000);

		cls();
		gotoxy(55, 13);
		printf("Continue? (y/n) ");
		scanf("%s", &check);
		
		if(check == 'n') {
			menu();
		}
	}
}

void main() {
	cls();
    intro();
}