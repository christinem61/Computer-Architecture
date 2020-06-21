#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get(unsigned short x, int n){
	x>>=n;
	printf("%d\n",x&01);
}
unsigned short comp(unsigned short x, int n){
	int y=1;
	y<<=n;
	printf("%d\n",x^y);
	return x^y;
}
unsigned short set(unsigned short x, int n, int v){
	int y=1;
	y<<=n;
	if(v==1){	
		x=x|y;
		printf("%d\n",x|y);
	}
	else if (v==0){
		y=~y;
		x=x&y;
		printf("%d\n",x);
	}
	return x;
}
int main(int argc, char* argv[]){
	FILE *fptr;
	int n,v;
	char job[4];
	unsigned short x;
	fptr=fopen(argv[1],"r");
	if (fptr==NULL)
		return 0;
	int y=fscanf(fptr,"%hu\n",&x);
	//y=fscanf(fptr,"%s\t%d\t%d\n",job,&n,&v);
	fgets(job,5,fptr);
	y=fscanf(fptr,"%d\t%d\n",&n,&v);
//	printf("%s %d %d",job,n,v);
	while (y!=EOF){
	//	printf("%s %d %d",job,n,v);
	
		if (job[0]=='s')
			x=set(x,n,v);
		else if (job[0]=='g')
			get(x,n);
		else if (job[0]=='c')
			x=comp(x,n);
		//if (feof(fptr))
		//	break;
		fgets(job,5,fptr);
		y=fscanf(fptr,"%d\t%d\n",&n,&v);
	}
	fclose(fptr);
	return 0;
} 
