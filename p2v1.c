#include <stdio.h>
#include <stdlib.h>

typedef struct{			//Do we really need this?
	int id;
	int P;		//1o plano
	int C;		//Cenario
	char class;
} node;

typedef struct chain{
	int value;
	int nodeId;
	chain *next;
	chain *previous; 
} *link;



int main(){
	int h;
	int w;

	scanf("%d", &h);
	scanf("%d", &w);

	if (h<1 || w<1) return -1;

	link *list = (link*) malloc(sizeof(link*)*((h*w)+2));

	int i;
	int j;
	for(i=0;i<h;i++){
		for(j=0;j<w;j++){
			int t=0;
			scanf("%d",&t);


		}

	}



}