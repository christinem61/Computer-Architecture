#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[]){
	int i;
	for(i=1;i<argc;i++){
		int j;
		for(j=0;argv[i][j]!='\0';j++){
		char l=argv[i][j];
		if (l=='a'||l=='e'||l=='i'||l=='o'||l=='u'||l=='A'||l=='E'||l=='I'||l=='O'||l=='U')
			printf("%c",l);
		}
	}		
	return 0;
}
