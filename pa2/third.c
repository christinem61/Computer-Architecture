#include <stdio.h>
#include <stdlib.h>

int pal( int i, unsigned short num){
	unsigned short orig=num;
	num>>=i;
	num=num&01;
	orig>>=15-i;
	orig=orig&01;
	if (orig==num)
		return 1;
	else
		return 0;
}
int main(int argc, char* argv[]){
	int i,y=0;
	unsigned short num=atoi(argv[1]);
	for (i=15;i>7;i--){
		y=pal(i,num);
		if (y==0){
			printf("Not-Palindrome\n");
			return 0;
		}
	}
	printf("Is-Palindrome\n");
	return 0;
}
