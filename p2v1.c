#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 999

typedef struct{			//Do we really need this?
	int id;
	int P;		//1o plano
	int C;		//Cenario
	char class;
} node;

typedef struct chain{
	int value;
	int nodeId;
	int curr;
	struct chain *next;
	struct chain *previous; 
} *link;

typedef struct vert{
	int id;
	struct vert *next;
}* point;

typedef struct {
	point head;
	point tail;
}BFList;

link *list;
int h;
int w;
BFList* queue; 
int * parentList;
int * currentCapacity;
char * position;

void enQueue(int v){
	point temp = (point) malloc(sizeof(struct vert));
	temp->id=v;
	temp->next=NULL;
	if (queue->head==NULL){queue->head=temp;}
	else {queue->tail->next=temp;}
	queue->tail=temp;
}	

int deQueue(){
	point temp = queue->head;
	//if (temp==NULL) return NULL;
	queue->head=temp->next;
	if (queue->head==NULL) queue->tail=NULL;
	int t=temp->id;
	free(temp);
	return t;
}

int isEmpty(){
	if (queue->head==NULL) return 1;
	return 0;
}




int min(int a, int b){
	if (b<a) return b;
	else return a;
}


void moreEdge(int s, int d, int p){
	link temp = (link) malloc(sizeof(struct chain));
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

void addEdge(int s, int d, int p){
	moreEdge(s,d,p);
	if (s<w*h && d<w*h){
		moreEdge(d,s,p);
	}

}


int bfs(int start, int end){

	memset(parentList, -1, sizeof(parentList[0])*((h*w)+2));
	memset(currentCapacity, 0, sizeof(currentCapacity[0])*((h*w)+2));

	enQueue(start);

	parentList[start]=-2;
	currentCapacity[start]=MAX;

	while(!isEmpty()){
		int curr = deQueue();
		link to = list[curr];
		while(to!=NULL){
			int toId=to->nodeId;
			if (parentList[toId]==-1){
				if ((to->value - to->curr)>0){
					parentList[toId]=curr;
					currentCapacity[toId]=min(currentCapacity[curr],(to->value-to->curr));
					if (toId==end) return currentCapacity[toId];
					enQueue(toId);
				}
			to=to->next;

			}


		}


	}
	return 0;
}




int edmondsKarp(int start, int end){
	int max = 0;
	while (1){
		int flow = bfs(start, end);
		if (flow==0) break;
		max+=flow;
		int curr = end;
		while(curr!=start){
			int previous=parentList[curr];
			link temp = list[previous];
			while(temp!=NULL && temp->nodeId!=curr) temp = temp->next;
			if (temp!=NULL) temp->curr+=flow;
			temp = list[curr];
			while(temp!=NULL && temp->nodeId!=previous) temp = temp->next;
			if (temp!=NULL) temp->curr-=flow;
			curr=previous;

		}

	}
	return max;

}


void dfs(int s){
	position[s]='P';
	link to = list[s];
	while(to!=NULL){
		if (position[to->nodeId]=='C' && to->value==to->curr){
			dfs(to->nodeId);
		}
		to=to->next;
	}
}




int main(){
	

	scanf("%d", &h);
	scanf("%d", &w);

	if (h<1 || w<1) return -1;

	list = (link*) malloc(sizeof(link)*((h*w)+2));
	parentList = (int*) malloc(sizeof(int)*((h*w)+2));
	currentCapacity = (int*) malloc(sizeof(int)*((h*w)+2));
	queue = (BFList*) malloc(sizeof(BFList));
	position = (char *) malloc(sizeof(char)*(h*w)+2);

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

	edmondsKarp(h*w, h*w+1);

	//printf("Fiz o Karps\n");

	memset(position, 'C', sizeof(position[0])*(h*w)+2);

	dfs(w*h);

	//printf("Fiz a dfs\n");

	//position[h*w]='C';

	int maxFlow=0;

	for (i=0; i<(h*w)+2; i++){
		link help = list[i];
		while(help!=NULL){
			if(position[i]!=position[help->nodeId]){
				maxFlow+=help->value;
			}
			help=help->next;
		}

	}

	printf("%d\n", maxFlow);
	printf("\n");
	for(i=0;i<h;i++){
		for(j=0; j<w;j++){
			printf("%c ", position[(i*w)+j]);
		}
		printf("\n");
	}
}