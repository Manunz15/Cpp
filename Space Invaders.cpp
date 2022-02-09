#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <unistd.h>
#include <conio.h>

void alien(int alienX[],int alienY[],int alienType[]);

void draw(int playerX,int playerY,int alienX[],int alienY[],int alienType[],int shotX[],int shotY[],int rayX[],int rayY[],int life,int score,int breaking[]);

void alienMove(int alienX[],int alienY[],int alienType[],int time,int shotX[],int shotY[],int* score);

void control(int* playerX, int* shot,int* life,int rayX[],int rayY[]);

void shoot(int* shot, int playerX, int playerY,int shotX[],int shotY[],int breaking[]);

void alienRay(int rayX[],int rayY[],int alienX[],int alienY[],int alienType[],int breaking[]);

int main()
{
	srand(time(NULL));
	
	int playerX=39,playerY=3,life=3,score=0,shot=0;
	int x,y,i,j,time=0;
	int alienX[55],alienY[55],alienType[55];
	int shotX[5]={0,0,0,0,0};
	int shotY[5]={25,25,25,25,25};
	int rayX[5]={0,0,0,0,0};
	int rayY[5]={-5,-5,-5,-5,-5};
	int breaking[4]={30,30,30,30};
	
	alien(alienX,alienY,alienType);	
	
	for(;life>0;time++){	
		draw(playerX,playerY,alienX,alienY,alienType,shotX,shotY,rayX,rayY,life,score,breaking);
		control(&playerX,&shot,&life,rayX,rayY);
		shoot(&shot,playerX,playerY,shotX,shotY,breaking);
		alienMove(alienX,alienY,alienType,time,shotX,shotY,&score);
		alienRay(rayX,rayY,alienX,alienY,alienType,breaking);
		
		if(score>0 && score%990==0){
			alien(alienX,alienY,alienType);
			score+=10;
			for(i=0;i<5;i++){
				rayY[i]=-5;
				}
			
			if(life<3)
				life++;
				}
		usleep(100000);
	}
	return 0;
}

void draw(int playerX,int playerY,int alienX[],int alienY[],int alienType[],int shotX[],int shotY[],int rayX[],int rayY[],int life,int score,int breaking[])
{
	int i,c=0,x,y,col=77,rig=19;
	
	printf("\n\n\n");
	printf("\tVITE x%d\n\tSCORE %d\n",life,score);
	for(y=rig;y>0;y--){
		printf("\n          ");
		for(x=10;x<=col-10;x++){
			for(i=0;i<55;i++){
				if(x==alienX[i] && y==alienY[i]){
					if(alienType[i]==3)
						printf("T");
					else if(alienType[i]==2)
						printf("W");
					else if(alienType[i]==1)
						printf("V");
					else if(alienType[i]==4){
						printf("O");
						alienY[i]=-50;}
					c=1;
					break; 
					}
				}
			if(y==6){
				for(i=0;i<4;i++){
					int a=((i+1)*15)+1;
					if((x==a || x==a-1 || x==a+1)&& breaking[i]>0){
						printf("D");
						c=1;}
				}
			}
			if(c==0){
				for(i=0;i<5;i++){
					if((x==shotX[i] && y==shotY[i])||(x==rayX[i] && y==rayY[i])){
						printf("|");
						c=1;
						}
				}
			}
			if(c==0){
				if(x==playerX && y==playerY)
					printf("A");
				else if(x==playerX && y==playerY-1)
					printf("H");
				else if(x==playerX && y==playerY-2)
					printf("X");
				else
					printf(" ");
			}
			c=0;
		}
		//printf("|");
	}
}
void control(int* playerX, int* shot,int* life,int rayX[],int rayY[])
{
	int i=0;
	static int dir=0,immunity=10;
	if(immunity>0)
		immunity--;
		
	if(kbhit()){
		switch(getch())
		{
			case 'a':
				if(dir==1)
					dir=0;
				else
					dir=1;
				break;
			case 'd':
				if(dir==2)
					dir=0;
				else
					dir=2;
				break;
			case ' ':
				if(*shot==0)
					*shot=5;
				break;
		}
	}
	if(dir==1 && *playerX>10)
		*playerX=*playerX-1;
	else if(dir==2 && *playerX<67)
		*playerX=*playerX+1;
	
	for(i=0;i<5;i++){
		if(*playerX==rayX[i] && rayY[i]<5 && rayY[i]>0 && immunity==0){
			for(int j=0;j<5;j++){
				rayY[j]=-5;}
			*life=*life-1;
			immunity=20;
			*playerX=39;
			dir=0;
			usleep(500000);
		}
	
	}
}

void shoot(int* shot, int playerX, int playerY,int shotX[],int shotY[],int breaking[])
{
	for(int i=0;i<5;i++){
		if(shotY[i]<25)
			shotY[i]++;
		if(shotY[i]==5){
			switch (shotX[i]){
				case 15:
				case 16:
				case 17:
					if(breaking[0]>0){
						shotY[i]=25;
						breaking[0]--;}
					break;
				case 30:
				case 31:
				case 32:
					if(breaking[1]>0){
						shotY[i]=25;
						breaking[1]--;}
					break;
				case 45:
				case 46:
				case 47:
					if(breaking[2]>0){
						shotY[i]=25;
						breaking[2]--;}
					break;
				case 60:
				case 61:
				case 62:
					if(breaking[3]>0){
						shotY[i]=25;
						breaking[3]--;}
					break;	
				}	
		}
	}
	if(*shot==5){
		for(int i=0;i<5;i++){
			if(shotY[i]>20){
				shotY[i]=playerY+1;
				shotX[i]=playerX;
				break;}
		}
	}
	if(*shot>0)
		*shot=*shot-1;
}	

void alienMove(int alienX[],int alienY[],int alienType[],int time,int shotX[],int shotY[],int* score)
{
	static int ritmo=9;
		for(int i=0;i<55;i++){
			for(int j=0;j<5;j++){
				if(shotX[j]==alienX[i] && shotY[j]==alienY[i]){
					shotY[j]=25;
					*score=*score+(alienType[i]*10);
					alienType[i]=4;
					break;
				}
			}
			if(time%5==0){
				if(ritmo==20)
					alienY[i]--;
				else if(ritmo==0)
					alienY[i]++;
				else if(ritmo>0)
					alienX[i]++;
				else
					alienX[i]--;
				}
		}
	if(time%5==0){
		if(ritmo==20)
			ritmo=-20;
		ritmo++;
		}

}

void alienRay(int rayX[],int rayY[],int alienX[],int alienY[],int alienType[],int breaking[])
{
	int ray=rand()%10+1;
	int i=0,j=0;
	for(i=0;i<5;i++){
		rayY[i]--;
		if(rayY[i]==5){
			switch (rayX[i]){
				case 15:
				case 16:
				case 17:
					if(breaking[0]>0){
						rayY[i]=-5;
						breaking[0]--;}
					break;
				case 30:
				case 31:
				case 32:
					if(breaking[1]>0){
						rayY[i]=-5;
						breaking[1]--;}
					break;
				case 45:
				case 46:
				case 47:
					if(breaking[2]>0){
						rayY[i]=-5;
						breaking[2]--;}
					break;
				case 60:
				case 61:
				case 62:
					if(breaking[3]>0){
						rayY[i]=-5;
						breaking[3]--;}
					break;	
				}	
		}
	}
	if(ray==1){
		for(i=0;i<5;i++){
			if(rayY[i]<0){
				for(;;){
					j=rand()%55;
					if(alienType[j]!=4){
						rayX[i]=alienX[j];
						rayY[i]=alienY[j];
						break;}
						}
				break;
			}
		}
	}
}

void alien(int alienX[],int alienY[],int alienType[])
{
	int alienXMap[55]={24,27,30,33,36,39,42,45,48,51,54,24,27,30,33,36,39,42,45,48,51,54,24,27,30,33,36,39,42,45,48,51,54,24,27,30,33,36,39,42,45,48,51,54,24,27,30,33,36,39,42,45,48,51,54};
	int alienYMap[55]={19,19,19,19,19,19,19,19,19,19,19,17,17,17,17,17,17,17,17,17,17,17,15,15,15,15,15,15,15,15,15,15,15,13,13,13,13,13,13,13,13,13,13,13,11,11,11,11,11,11,11,11,11,11,11};
	int alienTypeMap[55]={3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	for(int i=0;i<55;i++){
		alienX[i]=alienXMap[i];
		alienY[i]=alienYMap[i];
		alienType[i]=alienTypeMap[i];
	}
}
