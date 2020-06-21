#include <stdio.h>
#include <stdlib.h>
	
typedef struct node{
	int data;
	struct node* left;
	struct node* right;
}node;
typedef node* tree;

void freetree(tree* ptr){
	if ((*ptr)!=NULL){
		freetree(&((*ptr)->left));
		freetree(&((*ptr)->right));
		free(*ptr);
	}
}
int search(int target, tree* ptr){	
	node* curr=*ptr;
	while(curr!=NULL){
		if (curr->data==target)
			return 0;
		else if (curr->data>target)
			curr=curr->left;
		else
			curr=curr->right;
	}	
	return 1;
}
void insert(node* add, tree* ptr){
	if(*ptr==NULL){
		*ptr=add;		
		return;
	}
	else{
		node* curr=(*ptr);
		node* par=NULL;
		while(1){
			par=curr;
			if(add->data < curr->data){
				curr=curr->left;
				if(curr==NULL){
					par->left=add;
					return;
				}
			}
			else if (add->data > curr->data){
				curr=curr->right;
				if (curr==NULL){
					par->right=add;
					return;
				}
			}
			else
				return;
		}
	}
}
void inorder(node *ptr,int second){
	//if (ptr==NULL)
	//	printf("000");
	if(ptr!=NULL){
		inorder(ptr->left,second);
		if (ptr->data==second)
			printf("%d",ptr->data);
		else
			printf("%d\t",ptr->data);
		inorder(ptr->right,second);
	}
	
}
int findmax(struct node* root){
	if (root==NULL)
		return -2147483648;
	int res=root->data;
	int lres=findmax(root->left);
	int rres=findmax(root->right);
	if (lres>res)
		res=lres;
	if (rres>res)
		res=rres;
	return res;
}
int main(int argc, char** argv){
	tree bst=NULL;
	FILE *fptr=fopen(argv[1],"r");
	if (fptr==NULL){
		return 0;
	}
	else{
		char job;
		int num;
		int y=fscanf(fptr, "%c\t%d\n",&job,&num);
		while(y!=EOF){
			if (job=='i'){
				//node* add=(node*)malloc(sizeof(node));
				//add->data=num;
				//add->left=NULL;
				//add->right=NULL;
				int searched=search(num, &bst);
				if(searched==1){
					node* add=(node*)malloc(sizeof(node));
					add->data=num;
					add->left=NULL;
					add->right=NULL;
					insert(add,&bst);
				}
			}
		y=fscanf(fptr,"%c\t%d\n",&job,&num);
		}
	}
	node* temp=bst;
	//2nd largest code
	int second=findmax(temp);
	//end
	inorder(temp,second);		
	fclose(fptr);
	freetree(&bst);	
	return 0;
}
