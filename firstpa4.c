#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct node {
	int val;
	char var[50];	
	struct node* next;
};
struct gate {
	char op[50];
	char in1[50];
	char in2[50];
	char out[50];
	struct gate* next;
}; 
struct node* add(struct node* head, char* name){ //adds node to LL
	if (head==NULL){
		head=(struct node*)malloc(sizeof(struct node));
		strcpy(head->var,name);
		head->next=NULL;
		return head;
	}
	struct node* x=(struct node*)malloc(sizeof(struct node));
	x->next=NULL;
	x->val=-1;
	strcpy(x->var,name);
	struct node* curr=head;
	while(curr->next!=NULL){
		curr=curr->next;
	}
	curr->next=x;
	return head;
}
struct gate* addg(struct gate *head, char* op, char* in1, char* in2, char* out){ //adds node to gate/instruction LL
	if (head==NULL){
		head=(struct gate*)malloc(sizeof(struct gate));
		strcpy(head->op,op);
		strcpy(head->in1,in1);
		strcpy(head->in2,in2);
		strcpy(head->out,out);
		head->next=NULL;
		return head;
	}
	struct gate* curr=head;
	struct gate* x=(struct gate*)malloc(sizeof(struct gate));
	x->next=NULL;
	strcpy(x->op,op);
	strcpy(x->in1,in1);
	strcpy(x->in2,in2);
	strcpy(x->out,out);
	while(curr->next!=NULL){
		curr=curr->next;
	}
	curr->next=x;
	return head;
}
int findo(struct node* head,char *key){ //checks if output variable exists in output LL already
	struct node* track=head;
	while(track!=NULL){
		if (strcmp(track->var,key)==0){
			return 1;
		}
	track=track->next;
	}
	return 0;
}
int outin(struct node* head, char *key){ //returns node # of output location in LL, for inserting into output array
	struct node* track=head;
	int count=1;
	while(track!=NULL){
		if (strcmp(track->var,key)==0)
			return count;
		track=track->next;
		count++;
	}
	return count;
}	
struct node* findi(struct node* head, char *key){ //finds node in LL and returns it, helps to load values
	struct node* track=head;
	while(track!=NULL){
		if (strcmp(track->var,key)==0){
			return track;
		}
		track=track->next;
	}
	return NULL;
}
int main(int argc, char* argv[]){
	FILE *fp;
	fp=fopen(argv[1],"r");
	if (fp==NULL) return 0;
	int inputnum,outputnum,i,j,k;
	char vname[50];
	char op[50];
	char in1[50];
	char in2[50];
	char out[50];
	fscanf(fp,"INPUTVAR %d", &inputnum);
	struct node* ihead=NULL;
	struct node* ohead=NULL;
	for (i=0;i<inputnum;i++){
		fscanf(fp," %s",vname);	
		ihead=add(ihead,vname);
	}
 	fscanf(fp,"\n");
	fscanf(fp,"OUTPUTVAR %d",&outputnum);
	for (i=0;i<outputnum;i++){
		fscanf(fp,"%s",vname);
		ohead=add(ohead,vname);
	}
	fscanf(fp,"\n");
	struct gate* gate=NULL;
	while(fscanf(fp,"%s",op)==1){
		if(op[0]=='N'&&op[2]=='T'){
			fscanf(fp," %s",in1);
			fscanf(fp," %s",out);
			fscanf(fp,"\n");
			gate=addg(gate,op,in1,in1,out);
		}
		else{
			fscanf(fp," %s",in1);
			fscanf(fp," %s",in2);
			fscanf(fp," %s",out);
			fscanf(fp,"\n");
			gate=addg(gate,op,in1,in2,out);
		}
	}
	//binary truth table
	int combos= pow(2,inputnum);
	int row=combos,col=inputnum;
	int bin[row][col];
	for (j=0;j<row;j++){
		for(k=0;k<col;k++){
			bin[j][k]=0;
	}}
	for (i=1;i<row;i++){
		int carry=0;
		int tempc=col-1;	
		bin[i][col-1]=bin[i-1][col-1]+1;
		while (bin[i][tempc]==2){
			bin[i][tempc]=0;
			carry=1;
			tempc--;
			bin[i][tempc]=bin[i-1][tempc]+carry;
		}
		for(k=0;k<tempc;k++){
			if(bin[i-1][k]==1)
				bin[i][k]=1;		
		}
	}
	//creating output array
	int y=inputnum+outputnum;
	int res[combos][y];
	for (i=0;i<combos;i++){
		for(j=0;j<y;j++){
			res[i][j]=0;
		}
	}
	for (i=0;i<row;i++){
		for(j=0;j<col;j++){
			res[i][j]=bin[i][j];
		}
	}
	struct node* temp=ihead;
	struct node* temphead=NULL;
	struct gate* temp2=gate;
	for(i=0;i<combos;i++){
		temp=ihead;
		temp2=gate;
		for(j=0;j<inputnum;j++){
			if(temp==NULL) break;
			temp->val=res[i][j];	
			temp=temp->next;
		}
		while(temp2!=NULL){
			if(temp2->op[0]=='A'){ //and 
				int found=findo(ohead, temp2->out);
				if (found==1){
					int outindex=outin(ohead, temp2->out);
					struct node* input1=findi(ihead,temp2->in1);
					if (input1==NULL)
						input1=findi(ohead, temp2->in1);
					if (input1==NULL)
						input1=findi(temphead, temp2->in1);
					struct node* input2=findi(ihead, temp2->in2);
					if (input2==NULL)
						input2=findi(ohead, temp2->in2);
					if (input2==NULL)
						input2=findi(temphead, temp2->in2);
					int ans=input1->val&&input2->val;
					struct node *out1=findi(ohead, temp2->out);
					out1->val=ans;
					res[i][inputnum-1+outindex]=ans;
				}
				else if (found==0){
					temphead=add(temphead,temp2->out);
					struct node* out1=findi(temphead, temp2->out);
					struct node* input1=findi(ihead, temp2->in1);
					if (input1==NULL)
						input1=findi(ohead, temp2->in1);
					if (input1==NULL)
						input1=findi(temphead, temp2->in1);
					struct node* input2=findi(ihead, temp2->in2);
					if (input2==NULL)
						input2=findi(ohead, temp2->in2);
					if (input2==NULL)
						input2=findi(temphead, temp2->in2);
					out1->val=input1->val&&input2->val;
				}
			}
			else if (temp2->op[0]=='N'&&temp2->op[2]=='N'){ //nand
				int found=findo(ohead, temp2->out);
				if (found==1){
					int outindex=outin(ohead, temp2->out);
					struct node* input1=findi(ihead,temp2->in1);
					if (input1==NULL)
						input1=findi(ohead, temp2->in1);
					struct node* input2=findi(ihead, temp2->in2);
					if (input2==NULL)
						input2=findi(ohead, temp2->in2);
					struct node* out1=findi(ohead, temp2->out);
					if (input1->val==1&&input2->val==1){
						res[i][inputnum-1+outindex]=0;
						out1->val=0;}
					else{
						res[i][inputnum-1+outindex]=1;
						out1->val=1;}
				}
				else if (found==0){
					temphead=add(temphead,temp2->out);
					struct node* out1=findi(temphead, temp2->out);
					struct node* input1=findi(ihead, temp2->in1);
					if (input1==NULL)
						input1=findi(ohead, temp2->in1);
					if (input1==NULL)
						input1=findi(temphead, temp2->in1);
					struct node* input2=findi(ihead, temp2->in2);
					if (input2==NULL)
						input2=findi(ohead, temp2->in2);
					if (input2==NULL)
						input2=findi(temphead, temp2->in2);
					if (input1->val==1&&input2->val==1)
						out1->val=0;
					else
						out1->val=1;
				}
			}
			else if (temp2->op[0]=='N'&&temp2->op[2]=='T'){//not
			int found=findo(ohead, temp2->out);
				if (found==1){
					int outindex=outin(ohead, temp2->out);
					struct node* input1=findi(ihead,temp2->in1);
					if (input1==NULL)
						input1=findi(ohead, temp2->in1);
					if (input1==NULL)
						input1=findi(temphead, temp2->in1);
					struct node* out1=findi(ohead, temp2->out);
					if (input1->val==1){
						res[i][inputnum-1+outindex]=0;
						out1->val=0;}
					else{
						res[i][inputnum-1+outindex]=1;
						out1->val=1;}
				}
				else if (found==0){ //temp variables case: output not found in ohead LL
					temphead=add(temphead, temp2->out);
					struct node* input1=findi(temphead, temp2->out);
					struct node* input2=findi(ihead,temp2->in1);
					if (input2==NULL)
						input2=findi(ohead, temp2->in1);
					if (input2==NULL)
						input2=findi(temphead, temp2->in1);
					if (input2->val==1)
						input1->val=0;
					else
						input1->val=1;
				}
			}
			else if (temp2->op[0]=='O'){//or
			int found=findo(ohead, temp2->out);
				if (found==1){
					int outindex=outin(ohead, temp2->out);
					struct node* input1=findi(ihead,temp2->in1);
					if (input1==NULL)
						input1=findi(ohead, temp2->in1);
					if (input1==NULL)
						input1=findi(temphead, temp2->in1);
					struct node* input2=findi(ihead, temp2->in2);
					if (input2==NULL)
						input2=findi(ohead, temp2->in2);
					if (input2==NULL)
						input2=findi(temphead, temp2->in2);
					int ans=input1->val||input2->val;
					struct node* out1=findi(ohead, temp2->out);
					res[i][inputnum-1+outindex]=ans;
					out1->val=ans;
				}
				else if (found==0){
					temphead=add(temphead,temp2->out);
					struct node* out1=findi(temphead, temp2->out);
					struct node* input1=findi(ihead, temp2->in1);
					if (input1==NULL)
						input1=findi(ohead, temp2->in1);
					if (input1==NULL)
						input1=findi(temphead, temp2->in1);
					struct node* input2=findi(ihead, temp2->in2);
					if (input2==NULL)
						input2=findi(ohead, temp2->in2);
					if (input2==NULL)
						input2=findi(temphead, temp2->in2);
					out1->val=input1->val||input2->val;
				}
			}
			else if (temp2->op[0]=='N'&&temp2->op[2]=='R'){ //nor
			int found=findo(ohead, temp2->out);
				if (found==1){
					int outindex=outin(ohead, temp2->out);
					struct node* input1=findi(ihead,temp2->in1);
					if (input1==NULL)
						input1=findi(ohead, temp2->in1);
					if (input1==NULL)
						input1=findi(temphead, temp2->in1);
					struct node* input2=findi(ihead, temp2->in2);
					if (input2==NULL)
						input2=findi(ohead, temp2->in2);
					if (input2==NULL)
						input2=findi(temphead, temp2->in2);
					struct node* out1=findi(ohead, temp2->out);
					if (input1->val==0&&input2->val==0){
						res[i][inputnum-1+outindex]=1;
						out1->val=1;}
					else{
						res[i][inputnum-1+outindex]=0;
						out1->val=0;}
				}
				else if (found==0){
					temphead=add(temphead,temp2->out);
					struct node* out1=findi(temphead, temp2->out);
					struct node* input1=findi(ihead, temp2->in1);
					if (input1==NULL)
						input1=findi(ohead, temp2->in1);
					if (input1==NULL)
						input1=findi(temphead, temp2->in1);
					struct node* input2=findi(ihead, temp2->in2);
					if (input2==NULL)
						input2=findi(ohead, temp2->in2);
					if (input2==NULL)
						input2=findi(temphead, temp2->in2);
					if (input1->val==0&&input2->val==0)
						out1->val=1;
					else
						out1->val=0;
				}	
			}
			else if (temp2->op[0]=='X'){//xor
			int found=findo(ohead, temp2->out);
				if (found==1){
					int outindex=outin(ohead, temp2->out);
					struct node* input1=findi(ihead,temp2->in1);
					if (input1==NULL)
						input1=findi(ohead, temp2->in1);
					if (input1==NULL)
						input1=findi(temphead, temp2->in1);

					struct node* input2=findi(ihead, temp2->in2);
					if (input2==NULL)
						input2=findi(ohead, temp2->in2);
					if (input2==NULL)
						input2=findi(temphead, temp2->in2);
					int ans=input1->val^input2->val;
					res[i][inputnum-1+outindex]=ans;
					struct node* out1=findi(ohead, temp2->out);
					out1->val=ans;
				}
				else if (found==0){
					temphead=add(temphead,temp2->out);
					struct node* out1=findi(temphead, temp2->out);
					struct node* input1=findi(ihead, temp2->in1);
					if (input1==NULL)
						input1=findi(ohead, temp2->in1);
					if (input1==NULL)
						input1=findi(temphead, temp2->in1);
					struct node* input2=findi(ihead, temp2->in2);
					if (input2==NULL)
						input2=findi(ohead, temp2->in2);
					if (input2==NULL)
						input2=findi(temphead, temp2->in2);
					out1->val=input1->val^input2->val;
				}
			}
			temp2=temp2->next;
		}		
	}
	for (i=0;i<combos;i++){
		for (j=0;j<inputnum+outputnum;j++){
			printf("%d ",res[i][j]);
		}	
		printf("\n");
	}				
	fclose(fp);
	return 0;
}
