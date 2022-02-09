#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <unistd.h>
#include <conio.h>


void draw(int fruitx,int fruity,int n,int i,int x,int y,int col,int rig,int arrx[],int arry[],int pos,int score,int gameover);

void fruit(int* fruitx,int* fruity,int arrx[],int arry[],int* score,int col,int rig,int n);

void eat(int* flag,int* wasd, int score,int arrx[],int arry[],int* xs, int* ys);

void over(int* gameover,int xs,int ys,int arrx[],int arry[],int col,int rig,int score);

int main()
{
	srand(time(NULL));
	 
	int i,j,xs,ys;
	int wasd=0,flag=3,gameover=0,score=3,n=1000;
	int pos=0;

	int x,y,col=20,rig=20;
	int arrx[n],arry[n];
	int fruitx=0, fruity=0 ;
	
	for(i=0;i<n;i++){
		if(i==0){
			arrx[i]=9;
			arry[i]=1;}
		else if(i==1){
			arrx[i]=9;
			arry[i]=2;}
		else if(i==2){
			arrx[i]=9;
			arry[i]=3;}
		else{
			arrx[i]=-1;
			arry[i]=-1;
			}
	
			}
		
	fruit(&fruitx,&fruity,arrx,arry,&score,col,rig,n);
		
	for(;gameover!=1;){
	draw(fruitx,fruity,score,i,x,y,col,rig,arrx,arry,pos,score,gameover);
		if(kbhit())
		{
			switch(getch())
			{
				case 'w':
					flag=1;
					break;
				case 'a':
					flag=2;
					break;
				case 's':
					flag=3;
					break;
				case 'd':
					flag=4;
					break;
			}
			}
		
		eat(&flag,&wasd,score,arrx,arry,&xs,&ys);
		
		over(&gameover,xs,ys,arrx,arry,col,rig,score);
		
		if(gameover!=1){
		if((xs==fruitx)&&(ys==fruity)){
			arrx[score]=xs;
			arry[score]=ys;
			fruit(&fruitx,&fruity,arrx,arry,&score,col,rig,n);
			}
		else{
			for(i=0;i<score-1;i++){
				arrx[i]=arrx[i+1];
				arry[i]=arry[i+1];}
			arrx[score-1]=xs;
			arry[score-1]=ys;}
		}
				
	usleep(200000);
	}
	
	draw(fruitx,fruity,score,i,x,y,col,rig,arrx,arry,pos,score,gameover);
	
	return 0;
}	

void draw(int fruitx,int fruity,int n,int i,int x,int y,int col,int rig,int arrx[],int arry[],int pos,int score,int gameover)
{	
	printf("\nScore=%d\n\n",score-3);
	
	for(y=0;y<rig;y++){
		for(x=0;x<col;x++){
			
			if((gameover==1)&&(y==rig/2)&&(x==(col/2)-5)){
				printf("GAME OVER");
			}
			else if((gameover!=1)||((gameover==1)&&((y!=rig/2)||((y==rig/2)&&((x<(col/2)-5)||(x>(col/2)+3)))))){
			for(i=0;i<n;i++){
					if((arrx[i]==x)&&(arry[i]==y))
						pos=1;
						}
			if(pos==1){
				printf("0");
				pos--;
				}
			else{
				if((fruitx==x)&&(fruity==y))
					printf("o");
					
				else if((y==0)||(y==rig-1))
					printf("-");
				else if((x==0)&&(y!=0)&&(y!=rig-1))
					printf("|");
				else if((x==col-1)&&(y!=0)&&(y!=rig-1))
					printf("|");
				else
					printf(" ");
				}
			}	
			if(x==col-1)
				printf("\n");
				}
				}
	
}

void fruit(int* fruitx,int* fruity,int arrx[],int arry[],int* score,int col,int rig,int n)
{
	int i;
	if((*fruitx==arrx[*score])&&(*fruity==arry[*score])){
		//arrx[*score]=*fruitx;
		//arry[*score]=*fruity; 
		*score=*score+1;
		for(;;){
			*fruitx=rand()%(col-2)+1;
			*fruity=rand()%(rig-2)+1;
			for(i=0;i<n;i++){
				if((*fruitx==arrx[i])&&(*fruity==arry[i])){
					i=0;
					break;}
					}
			if(i==n)
				break;
		}		
		}
		
	else if(*fruitx==0){
		for(;;){
			*fruitx=rand()%(col-2)+1;
			*fruity=rand()%(rig-2)+1;
			for(i=0;i<n;i++){
				if((*fruitx==arrx[i])&&(*fruity==arry[i])){
					i=0;
					break;}
					}
			if(i==n)
				break;
		}
	}
}

void eat(int* flag,int* wasd,int score,int arrx[],int arry[],int* xs, int* ys)
{
	*xs=arrx[score-1];
	*ys=arry[score-1];
	switch(*flag){	
		case 1:
			if(*wasd!=3){	
				*ys=arry[score-1]-1;
				*wasd=1;}
			else{
				*flag=3;
				*ys=arry[score-1]+1;
			}
			break;
		case 2:
			if(*wasd!=4){
				*xs=arrx[score-1]-1;
				*wasd=2;}
			else{
				*flag=4;
				*xs=arrx[score-1]+1;
			}
			break;
		case 3:
			if(*wasd!=1){
				*ys=arry[score-1]+1;
				*wasd=3;}
			else{
				*flag=1;
				*ys=arry[score-1]-1;
			}
			break;
		case 4:
			if(*wasd!=2){
				*xs=arrx[score-1]+1;
				*wasd=4;}
			else{
				*flag=3;
				*xs=arrx[score-1]-1;
			}
			break;	
	}
}

void over(int* gameover,int xs,int ys,int arrx[],int arry[],int col,int rig,int score){
	int i;
	if((xs==0)||(xs==col-1)||(ys==0)||(ys==rig-1))
		*gameover=1;
	else
		for(i=0;i<score-1;i++){
			if((xs==arrx[i])&&(ys==arry[i]))
				*gameover=1;
		}
}
