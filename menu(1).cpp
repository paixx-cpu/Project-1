#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>
#include "dataHead.h"


void loginSuccessful(struct Profile *choosen){
	int input;
	time_t t;
	time(&t);
	do{
		system("cls");
		printf("Welcome %s!\n", choosen->username);
		printf("Logged in: %s\n", ctime(&t));
		printf("--------------------\n\n");
		printf("All friends of %s\n", choosen->username);
		printf("No.   Username\n");
//		viewAllFriends(); //Buat nanti kalo udah bikin yang Friends
		printf("--------------------\n");
		printf("     >>MENU<<\n");
		printf("--------------------\n");
		printf("[1]Add Friend\n");
		printf("[2]Remove Friend\n");
		printf("[3]View Inbox\n");
		printf("[4]View Sent Request\n");
		printf("[5]Add,Edit,Announce,Delete Note\n");
		printf("[6]Logout\n");
		printf("--------------------\n");
		printf(">>");
		scanf("%d",&input);getchar();
		if(input==0) return;
		printf("--------------------\n");
		switch(input)
		{
			case 1:
//				addFriends();//Belum dibuat
				break;

			case 2:
//				removeFriends();//Belum dibuat
				break;

			case 3:
//				viewInbox();//Belum dibuat
				break;

			case 4:
//				viewSentRequest();//Belum dibuat
				break;

			case 5:
//				addEditAnnouceDeleteNote();//Belum dibuat
				break;
		}
	}while(input!=6);

};

int checkUnique(char name[]){
	Profile *curr=head;
	while(curr){
      if(strcmp(name, curr->username)==0){
        return -1;
      }
      curr=curr->next;
    }
	return 1;
}

void register_Page()
{
	char inputUsername[150]="";
	char inputPassword[150]="";
	int flag=1;
	do{
		printf("Please type in your username [lowercase || 1..24]: ");
		scanf("%[^\n]",inputUsername);getchar();
		if(strcmp(inputUsername,"0")==0) return;

		flag=checkUnique(inputUsername);

		for(int i=0;i<strlen(inputUsername);i++){
			if(islower(inputUsername[i])==0){
				flag=-1;
				break;
			}
		}
	}while(strlen(inputUsername)<1 || strlen(inputUsername)>24 || flag!=1);
	flag=1;
	do{
		printf("Please type in your password [lowercase || 1..24]: ");
		scanf("%[^\n]",inputPassword);getchar();
		if(strcmp(inputPassword,"0")==0) return;
		for(int i=0; i<strlen(inputPassword); i++){
			if(islower(inputPassword[i])==0){
				flag=-1;
				break;
			}
		}
	}while(strlen(inputPassword)<1 || strlen(inputPassword)>24 || flag!=1);
	pushTail(inputUsername,inputPassword);

	puts("");
	puts("--- Registration Successful ---");
	enterToContinue();
}

void login_Page()
{
	int input;
	printf(">> ");
	scanf("%d",&input);getchar();
	if(input==0) return;	// opsi 0 = keluar fungsi
	Profile *choosen = head;
	for(int i=1;i<input;i++)
	{
		choosen=choosen->next;
	}
	printf("---------------------------------------\n");
	int match=-1;	//base statement kecocokan = -1
	char inputUsername[25];
	char inputPassword[25];
	do
	{
		printf("Username: ");
		scanf("%[^\n]",inputUsername);getchar();
		if(strcmp(inputUsername,"0")==0) return;	// kalo 0 , keluar
		printf("Password: ");
		scanf("%[^\n]",inputPassword);getchar();
		if(strcmp(inputPassword,"0")==0) return;	//kalo 0 , keluar
		if(strcmp(inputUsername,choosen->username)==0&&strcmp(inputPassword,choosen->password)==0) match=1;
	}
	while(match == -1);
	printf("\n---Login Successful---\n");
	enterToContinue();
	loginSuccessful(choosen);
}

void mainMenu(){
	int input;
	do
	{
		system("cls");
		printf("=========================\n");
		printf("      STUDY NETWORK      \n");
		printf("=========================\n");
		printf("\n[All User]\n");
		printf("No.   Username\n");
		viewAllProfile();
		printf("-----------------\n");
		printf("[1]Register\n");
		printf("[2]Login\n");
		printf("[3]Exit\n");
		printf("---------------------------------------\n");
		printf("Press 0 and enter to abort an operation\n");
		printf("---------------------------------------\n");
		printf(">>");
		scanf("%d",&input);getchar();
		switch(input)
		{
			case 1:
				register_Page();
				break;

			case 2:
				login_Page();
				break;
		}
	}
	while(input!=3);
}

int main()
{
	mainMenu();
	return 0;
}
