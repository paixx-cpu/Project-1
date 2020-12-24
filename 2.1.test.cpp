#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>

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
