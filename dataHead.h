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
#include <stdio.h>
#include <stdlib.h>

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
		//ascending(?) gatau iya atau engga yg penting gaya :"D
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
//gatau bisa atau engga kayak gini tapi yaudahlah
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