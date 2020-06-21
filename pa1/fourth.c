#include <stdlib.h>
#include <stdio.h>

void multiply(int rownum1, int colnum1, int row2num, int col2num, int *x, int *y, int *z){
	int i,j,k;
	for(i=0;i<rownum1;i++){
		for(j=0;j<col2num;j++){
			int sum=0;
			for (k=0;k<colnum1;k++){
				int e=k+i*colnum1;
				int f=j+k*col2num;
				sum+=(*(x+e))*(*(y+f));
			}
			int g=j+i*col2num;
			*(z+g)=sum;
		}
	}
}

int main(int argc, char** argv){
	FILE *fptr=fopen(argv[1],"r");
	if (fptr==NULL){
		printf("error");
		return 0;
	}
	else{
		int *x=NULL,*y=NULL,*z=NULL;
		int rownum,colnum;
		int a=fscanf(fptr, "%d\t%d\n",&rownum,&colnum);
		if(a==2)
			x=(int*)malloc((rownum*colnum)*sizeof(int));
		int i;
		for(i=0;i<rownum*colnum;i++){
			int col=i%colnum;
			int b,temp;
			if (col+1==colnum)
				b=fscanf(fptr,"%d\n",&temp);
			else
				b=fscanf(fptr,"%d\t",&temp);
			if (b==1)
				*(x+i)=temp;
		}
		int rownum2,colnum2;
		int c=fscanf(fptr,"%d\t%d\n",&rownum2,&colnum2);
		if (c==2){
		if (colnum!=rownum2){
			printf("bad-matrices");
			free(x);
			free(y);
			free(z);
			return 0;
		}
		else
			y=(int*)malloc((rownum2*colnum2)*sizeof(int));
		}
		for (i=0;i<rownum2*colnum2;i++){
			int col=i%colnum2;
			int b, temp;
			if(col+1==colnum2)
				b=fscanf(fptr,"%d\n",&temp);
			else
				b=fscanf(fptr,"%d\t",&temp);
			if (b==1)
				*(y+i)=temp;
		}
		fclose(fptr);
		/*int l,m;   //code to output mat 1 or mat 2 (must change rownum/2, colnum/2, x/y)
		for(l=0;l<rownum2;l++){
			for(m=0;m<colnum2;m++){
				int temp2=*(y+(m+l*colnum2));
				printf("%d ",temp2);
				if(m!=colnum2-1)
					printf("\t");
				else
					printf("\n");
			}
		}*/
		z=(int*)malloc((rownum*colnum2)*sizeof(int));
		multiply(rownum, colnum, rownum2, colnum2, x,y,z);
		int l,m;
		for (l=0;l<rownum;l++){
			for(m=0;m<colnum2;m++){
				int temp2=*(z+(m+l*colnum2));
				printf("%d",temp2);
				if(m!=colnum2-1)
					printf("\t");
				else
					printf("\n");
			}
		}
		free(x);
		free(y);
		free(z);
		return 0;
	}
}
