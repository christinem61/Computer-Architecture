#include <stdlib.h>
#include <stdio.h>

typedef struct node{
	int data;
	struct node* next;
} node;
typedef node* ll;
typedef node* ht;

int insert(ht* ht2, node* add){
	int collision=0;
	int index=add->data%10000;
	if (index<0)
		index=index+10000;
	node* head=*(ht2+index);
	if (head==NULL) //nsert into empty bucket
		*(ht2+index)=add;
	else{		//insert into occupied bucket
		collision=1;
		node* present=head;
		while(present!=NULL){
			present=present->next;
		}
		add->next=head;
		*(ht2+index)=add;
	}
	return collision;
}
int search(ht* ht2, int target){
	int pass=0;
	int index=target%10000;
	if (index<0)
		index=index+10000;
	node* head=*(ht2+index);
	if (head!=NULL){
		node* present=head;
		while(present){
			if (present->data==target){
				pass=1;
				break;
			}
			present=present->next;
		}
	}
	return pass;
}

int main(int argc, char* argv[]){
	int collision=0;
	node** ht2=(node**) malloc(10000*sizeof(node*));
	int x,num;
	int snum=0,cnum=0;
	for (x=0;x<10000;x++){
		*(ht2+x)=NULL;
	}
	char job;
	FILE *fptr=fopen(argv[1],"r");
	if (fptr==NULL)
		return 0;
	int y= fscanf(fptr,"%c%d\n",&job,&num);
	while(y!=EOF){
		if (job=='i'){
			node* add=(node*) malloc(sizeof(node));
			add->data=num;
			add->next=NULL;
			collision=insert(ht2,add);
			if (collision==1)
				cnum++;
		}
		else if (job=='s'){
			int success=search(ht2,num);
			if (success==1)
				snum++;
		}
		y=fscanf(fptr,"%c%d\n",&job,&num);
	}
	fclose(fptr);
	printf("%d\n",cnum);
	printf("%d",snum);
	if (*ht2){
		int k;
		for (k=0;k<10000;k++){
			ll temp=*(ht2+k);
			if (temp){
				node* freex=temp;
				while (freex){
					node* temp2=freex;
					freex=freex->next;
					free(temp2);
				}	
			}
		}
		free(ht2);
	}
	return 0;
}
