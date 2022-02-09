#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <unistd.h>
#include <conio.h>

void draw(int col, int rig,int score1,int score2,int player1[],int player2[],int px, int py);

void controls(int* com1,int* com2,int player1[],int player2[],int rig);

void ballgen(int* ball,int* px,int* py, int* vx, int* vy, int col, int rig);

void ballmove(int* px, int* py, int* vx, int* vy, int* score1, int* score2, int* ball,int col, int rig,int player1[],int player2[]);

int main()
{
	srand(time(NULL));
	
	int rig=18;
	int col=50;
	int i,j,x,y;
	int vx,vy,px,py,ball=1;
	int score1=0, score2=0;
	int player1[3]={(rig/2)-1,rig/2,(rig/2)+1};
	int player2[3]={(rig/2)-1,rig/2,(rig/2)+1};
	int com1=0;
	int com2=0;
	
	for(;;){
		
		
		ballgen(&ball,&px,&py,&vx,&vy,col,rig);
		
		draw(col,rig,score1,score2,player1,player2,px,py);
		
		controls(&com1,&com2,player1,player2,rig);
		
	ballmove(&px,&py,&vx,&vy,&score1,&score2,&ball,col,rig,player1,player2);
		
		
		usleep(200000);	
	}
	return 0;
}


void draw(int col, int rig,int score1,int score2,int player1[],int player2[],int px,int py)
{
	int i,j,x,y,c=0;
	
	printf("\n\n\t\t        %d-%d\n",score1,score2);
	for(i=0;i<col;i++)
		printf("-");
	
	printf("\n");
	for(y=1;y<=rig;y++){
		for(x=1;x<=col;x++){
			c=0;
			if(x==5)
				for(i=0;i<3;i++){
					if(y==player1[i]){
						printf("H");
						c=1;
						}}
			else if(x==(col-4))
				for(i=0;i<3;i++){
					if(y==player2[i]){
						printf("H");
						c=1;
						}}
			if(c!=1){
				
				if((x==px)&&(y==py)){
					printf("o");
					}
				else if(x==1)
					printf("|");
				else if(x==col)
					printf("|\n");
				else
					printf(" ");
			
			}
		}
	}
	for(i=0;i<col;i++)
		printf("-");
	
	printf("\n");
}

void controls(int* com1,int* com2,int player1[],int player2[],int rig)
{
	int i,j;
	
	if(kbhit())
	{
		switch(getch())
		{
			case 'w':
				*com1=1;
				break;
			case 's':
				*com1=2;
				break;
			case 'o':
				*com2=1;
				break;
			case 'l':
				*com2=2;
				break;
		}
	}
	
	for((i=2)&&(j=0);(i>-1)&&(j<3);(i--)&&(j++)){
	if((*com1==1)&&(player1[0]!=1)){
		player1[i]=player1[i]-1;
		}
	else if((*com1==2)&&(player1[2]!=rig)){
		player1[j]=player1[j]+1;
	}
	if((*com2==1)&&(player2[0]!=1)){
		player2[i]=player2[i]-1;
	}
	else if((*com2==2)&&(player2[2]!=rig)){
		player2[j]=player2[j]+1;
	}
	}
}

void ballgen(int* ball,int* px,int* py, int* vx, int* vy, int col, int rig)
{
	if(*ball==1){
		*px=col/2;
		*py=rig/2;
		for(;;){
			*vx=rand()%5-2;
			if(*vx!=0)
				break;
		}
		*vy=rand()%5-2;
		*ball=0;}
		}
void ballmove(int* px, int* py, int* vx, int* vy, int* score1, int* score2, int* ball,int col, int rig,int player1[],int player2[])
{	
	int i;
	for(i=0;i<3;i++){
		if((*px+*vx>=4)&&(*px+*vx<=7)&&(*py==player1[i])){
			if(*vy==1)
				*vy+=rand()%2;
			else if(*vy==2)
				*vy-=rand()%2;
			else if(*vy==0)
				*vy-=rand()%5-2;
			else if(*vy==-1)
				*vy-=rand()%2;
			else if(*vy==-2)
				*vy+=rand()%2;
			*vx=rand()%2+1;
		}
		else if((*px+*vx<=col-3)&&(*px+*vx>=col-6)&&(*py==player2[i])){
			if(*vy==1)
				*vy+=rand()%2;
			else if(*vy==2)
				*vy-=rand()%2;
			else if(*vy==0)
				*vy-=rand()%5-2;
			else if(*vy==-1)
				*vy-=rand()%2;
			else if(*vy==-2)
				*vy+=rand()%2;
			*vx=rand()%2-2;
		}
	}
	if(*px+*vx<=0){
		*score2=*score2+1;
		*ball=1;}
	else if(*px+*vx>=col){
		*score1=*score1+1;
		*ball=1;}
	else if((*px+*vx<col)&&(*px+*vx>0)&&(*py+*vy<=0)){
		if(*vx==1)
			*vx+=rand()%2;
		else if(*vx==2)
			*vx-=rand()%2;
		else if(*vx==-1)
			*vx-=rand()%2;
		else if(*vx==-2)
			*vx+=rand()%2;
		*vy=rand()%2+1;
		}
	else if((*px+*vx<col)&&(*px+*vx>0)&&(*py+*vy>=rig)){
		if(*vx==1)
			*vx+=rand()%2;
		else if(*vx==2)
			*vx-=rand()%2;
		else if(*vx==-1)
			*vx-=rand()%2;
		else if(*vx==-2)
			*vx+=rand()%2;
		*vy=rand()%2-2;
	}
	else{
		*px+=*vx;
		*py+=*vy;}
}
