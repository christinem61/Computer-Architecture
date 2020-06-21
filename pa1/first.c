#include <stdlib.h>
#include <stdio.h>

void swap(int *x, int *y){
	int temp=*x;
	*x=*y;
	*y=temp;
}
void sort(int arr[], int n){
	int i,j,min;
	for(i=0;i<n-1;i++){
		min=i;
		for(j=i+1;j<n;j++)
			if(arr[j]<arr[min])
				min=j;
	swap(&arr[min],&arr[i]);
	}
}

int main(int argc, char* argv[]){
FILE *fptr;
fptr=fopen(argv[1],"r");
if(fptr==NULL){
	return 0;
}
int size,i,j,even=0,odd,k,l;
int indexe=0,indexo=0;
fscanf(fptr,"%d\n",&size);
int array[size];
for (i=0;i<size;i++){
	int num;
	fscanf(fptr,"%d\t",&num);
	array[i]=num;
	if(num%2==0)
		even++;
}
odd=size-even;
int odds[odd],evens[even];
for(k=0;k<size;k++){
	if(array[k]%2==0){
		evens[indexe]=array[k];	
		indexe++;
	}
	else{
		odds[indexo]=array[k];
		indexo++;
	}
}
sort(evens,even);
sort(odds,odd);
for(j=0;j<even;j++){
	printf("%d\t",evens[j]);
}
for (l=odd-1;l>=0;l--){
	if (l!=0)
		printf("%d\t",odds[l]);
	else
		printf("%d",odds[l]);
}
/*
//printing array
for(j=0;j<size;j++){
	if(j==size-1)
		printf("%d",array[j]);
	else
	printf("%d\t",array[j]);
}*/
fclose(fptr);
return 0;
}
