
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>


struct Profile{
	char username[25];
	char password[25];
	Profile *prev;
	Profile *next;
}*head=NULL,*tail=NULL;

struct Friend{
	char username[25];
	Friend *prev;
	Friend *next;
}*friendHead=NULL, *friendTail=NULL;

struct Request{
	char username[25];
	Request *prev;
	Request *next;
}*requestHead=NULL, *requestTail=NULL;

struct Note{
	char message[260];
	char category[20]; // backlog, in progress, peer review, dll.
	int likes;
	bool announce; // buat nentuin announce atau ga
	bool privated; // buat nentuin private atau ga
	Note *prev;
	Note *next;
}*noteHead=NULL, *noteTail=NULL;

Profile* createNewProfile(char username[25],char password[25]){
	Profile* newProfile = (Profile*) malloc(sizeof(Profile));
	strcpy(newProfile->username,username);
	strcpy(newProfile->password,password);
	newProfile->next=NULL;
	newProfile->prev=NULL;
	return newProfile;
}

void pushHead(char username[25],char password[25]){
	Profile *newProfile = createNewProfile(username,password);
	if(!head){
		head = tail = newProfile;
	} else {
		newProfile->next = head;
		head->prev = newProfile;
		head = newProfile;
	}
}

void pushTail(char username[25],char password[25]){
	Profile *newProfile = createNewProfile(username,password);
	if(!head){
		head = tail = newProfile;
	} else {
		tail->next =newProfile;
		newProfile->prev=tail;
		tail=newProfile;
	}
}

void pushMid(char username[25],char password[25]){
	Profile *newProfile = createNewProfile(username,password);
	if(!head){
		head = tail = newProfile;
	} else {
		//ascending(?)
		if(strcmp(username,head->username)<0){
			pushHead(username,password);
		} else if(strcmp(username,tail->username)>=0){
			pushTail(username,password);
		} else {
			Profile *temp = head;
			while(strcmp(username,temp->username)>=0){
				temp = temp->next;
			}
			temp->prev->next=newProfile;
			newProfile->prev=temp->prev;
			newProfile->next=temp;
			temp->prev=newProfile;
		}
	}
}

void viewAllProfile(){
	if(!head){
		return;
	}
	Profile *currentProfile = head;
	int number=1;
	while(currentProfile){
		printf("%d. %s\n", number, currentProfile->username);
		number++;
		currentProfile = currentProfile->next;
	}
}
int profileCount(){
	int number=0;
	Profile *temp= head;
	while(temp){
		number++;
		temp=temp->next;
	}
	return number;
}
//buat nyari friends yang mau di hapus
//tar kalo udah bikin friendsnya ganti aja semua profile jadi friends
Profile* popHead(){
	if(!head){
		return NULL;
	}
	Profile* toBeDeleted = head;
	head= head->next;
	toBeDeleted->next=NULL;
	head->prev=NULL;
	return toBeDeleted;
}

//buat nyari friends yang mau di hapus
//tar kalo udah bikin friendsnya ganti aja semua profile jadi friends

Profile* popTail(){
	if(!head){
		return NULL;
	}
	Profile* toBeDeleted = tail;
	tail=tail->prev;
	tail->next=NULL;
	toBeDeleted->prev=NULL;
	return toBeDeleted;
}
//yg di bawah ini aku gak tau apaan but my friend told me
//he said it might be useful(?)

Profile* popSearch(int number){
	if(!head){
		return NULL;
	}
	if(number==1){
		return popHead();
	} else if(number==profileCount()){
		return popTail();
	} else {
		Profile *toBeDeleted=head;
		for(int i=1;i<number;i++){
			toBeDeleted = toBeDeleted->next;
		}
		Profile *prevProfile = toBeDeleted->prev;
		Profile *nextProfile = toBeDeleted->next;
		prevProfile->next=nextProfile;
		nextProfile->prev=prevProfile;
		toBeDeleted->next=NULL;
		toBeDeleted->prev=NULL;
		return toBeDeleted;
	}
}


void enterToContinue(){
	printf("Press enter to continue!");
	getchar();
}

void viewAllFriends()
{

}



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

// bikin pop, push, view buat semua struct yg udh dideclare
//
// BUAT REQUEST
// view inbox = view all requests, bisa kasih pilihan mo accept yg mana
// klo di accept, pop request, push friend
//
// view sent request = view all request
//
// BUAT NOTES
// add->push->defaultnya ntar public, announce=false, ditanyain konten notes, category, mo dibikin private?
// klo dibikin private->suruh input brp user mo dikasih access (0..3 validasi)
// edit->search nodes trs edit
// announce->add new note, bool announce = true, ntar user page diedit aja, jadi paling atas print requests if announce=true
// delete->pop
// ntar bikin recycle bin = popSearch kepake di sini, ntar user klo milih recover tinggal di push lagi, klo ga ya pop beneran
// ntar bikin menu baru buat view notes
// ntar user ditanyain mo like, comment ato return?
// klo mo like/comment ditanyain mo like/comment yg mana
// yg tambahin comment gw masih ga ngerti lol
//
//
// yg category (backlog, in progress dll) gw ga ngerti, mending tanya ke penyihir kode aka elpan celpano
//
// --- OPTIONS ---
// 1. note, request, profile, friend struct dipisah
// 2. note, request, profile, friend itu dibikin jadi struct, tapi itu bagian elemen dari profile
// jadi ntar struct profile{
// 	char username[25];
// 	char password[25];
// 	Note notes;
// 	Request requests;
// 	Friend friends;
// 	Profile *prev;
// 	Profile *next;
// }
//

