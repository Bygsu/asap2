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

link *list;
int h;
int w;


void addEdge(int s, int d, int p){
	moreEdge(s,d,p);
	if (s<w*h && d<w*h){
		moreEdge(d,s,p);
	}

}


void moreEdge(int s, int d, int p){
	link temp = (link) malloc(sizeof(link));
	temp->value=p;
	temp->nodeId=d;
	link ref = list[s];
	if (ref==NULL) list[s]=temp;
	else{
		while(ref->next!=NULL) ref=ref->next;
		temp->previous=ref;
		ref->next=temp;
	}
	return;
}



int main(){
	

	scanf("%d", &h);
	scanf("%d", &w);

	if (h<1 || w<1) return -1;

	list = (link*) malloc(sizeof(link*)*((h*w)+2));

	int i;
	int j;
	int t;
	for(i=0;i<h;i++){
		for(j=0;j<w;j++){
			t=0;
			scanf("%d",&t);
			addEdge(h*w, i*w+j, t);
		}
	}

	for(i=0;i<h;i++){
		for(j=0;j<w;j++){
			t=0;
			scanf("%d",&t);
			addEdge(i*w+j, h*w+1, t);
		}
	}

	for(i=0;i<h;i++){
		for(j=0;j<w-1;j++){
			t=0;
			scanf("%d",&t);
			addEdge(i*w+j, (i*w+j)+1, t);
		}
	}

	for(i=0;i<h-1;i++){
		for(j=0;j<w;j++){
			t=0;
			scanf("%d",&t);
			addEdge(i*w+j, (i+1)*w+j, t);
		}
	}



}