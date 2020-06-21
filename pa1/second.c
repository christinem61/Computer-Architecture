#include <stdio.h>
#include <stdlib.h>

struct node{
int data;
struct node* next;
};

struct node* add(struct node* head, int num){
	struct node* x=(struct node*) malloc(sizeof(struct node));
	x->next=NULL;
	x->data=num;
	struct node* temp=head;
	struct node* prev=NULL;
	while(temp!=NULL){
		if (num<=temp->data)
			break;
		prev=temp;
		temp=temp->next;
	}
	x->next=temp;
	if (prev!=NULL)
		prev->next=x;
	else
		head=x;
	return head;
}
struct node* del(struct node* head, int num){
	struct node* temp=head;
	struct node* prev=NULL;
	while(temp!=NULL){
		if(num<temp->data)
			return head;
		else if (num==temp->data)
			break;
		prev=temp;
		temp=temp->next;;
	}
	if (temp==NULL)
		return head;
	if(prev==NULL)
		head=temp->next;
	else
		prev->next=temp->next;
	free(temp);
	return head;
}
int main(int argc, char* argv[]){ //error if file dont exist and 0 if empty LL
	FILE *fptr;
	struct node* head=NULL;
	char job;
	int n;
	fptr=fopen(argv[1],"r");
	if(fptr==NULL){
		printf("error");
		return 0;
	}
	int y=fscanf(fptr,"%c\t%d\n",&job,&n);
	if (y==0){
		printf("0\n\n");
		return 0;
	}
	while(y!=EOF){
		if (job=='i'){
			head=add(head,n);
		}
		else if (job=='d'){
			head=del(head,n);
		}
	y=fscanf(fptr,"%c\t%d\n",&job,&n);
	}
	struct node* temp=head;
	int count=0;
	while(temp!=NULL){
		count++;
		temp=temp->next;
	}
	if (count==0){
		printf("0\n\n");
		return 0;
	}
	printf("%d\n",count);
	struct node* temp2=head;
	int repeat=2147483647;
	while (temp2!=NULL){
		int u=0;
		if(temp2->data!=repeat){
			u=1;
			printf("%d",temp2->data);
		}
		repeat=temp2->data;
		temp2=temp2->next;
		if(u==0)
			continue;
		else if(temp2==NULL)
			break;
		else if(temp2!=NULL&&temp2->data==repeat&&temp2->next!=NULL)
			printf("\t");
		else if(temp2!=NULL&&temp2->data==repeat&&temp2->next==NULL)
		{}
		else if(temp2!=NULL)
			printf("\t");
	}
	fclose(fptr);
	return 0;
}
