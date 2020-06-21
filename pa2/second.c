#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	unsigned short num=atoi(argv[1]); //converts string input into integer
	//printf("%d\n",num);
	int pairs=0, ones=0,bit, prev=0;
	while(num){
		bit=num&01;
	//	printf("%d\n",bit);
		if (prev&&bit){
			pairs++;
			prev=0;
		}
		else
			prev=bit;
		if(bit==1)
			ones++;
		num>>=1; //right shifts bits by 1 digit 
	}
	//printf("%d\n",ones);
	if (ones%2==0)
		printf("Even-Parity\t%d\n",pairs);
	else
		printf("Odd-Parity\t%d\n",pairs);
}
