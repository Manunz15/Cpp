#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <unistd.h>
#include <conio.h>

void map(int col, int rig, int mariox, int marioy, int heady,int blockx[],int blocky[],int type[],int ground[],int n,int world,int time,int gold,int monx,int mony,int mushx,int mushy,int goomba[],int life,int immunity);

void controls(int* dir,int* jump,int* mariox,int* marioy, int* heady,int* salto, int* gravity,int col,int* world,int blockx[],int blocky[],int type[],int ground[],int n,int* gold,int* monx, int* mony,int* mushx,int* mushy);

void mappa(int blockx[],int blocky[], int type[],int i);

void enemy(int goomba[],int time,int* life,int* mariox, int* marioy,int* heady,int* immunity,int *salto,int* world,int* dir);

int main()
{
	int i,j,x,y,world=1,col=256,rig=18;		//1
	int mariox=15,marioy=3,heady=3,life=3;	//15	
	int dir=0, jump=0;
	int salto=0, gravity=0;
	int n=256;
	int time=0,gold=0;
	int monx=-1, mony=-1;
	int mushx=-1, mushy=-1;
	int immunity=0,win=0;
	int flag;
	
	int blockx[n];
	int blocky[n];
	int type[n];
	int ground[col];
	int goomba[16]={21,38,62,64,90,92,110,112,126,128,136,138,141,143,195,197};
		
	for(i=0;i<n;i++){
		mappa(blockx,blocky,type,i);
		}
	
	for(i=1;i<=col;i++){
		ground[i-1]=i;
		switch(i){
			case 80:
			case 81:
			case 82:
			case 99:
			case 100:
			case 101:
			case 102:
			case 171:
			case 172:
				ground[i-1]=-1;
		}
	}

	for(time=0;(life>0)&&(win!=1);time++){
map(col,rig,mariox,marioy,heady,blockx,blocky,type,ground,n,world,time,gold,monx,mony,mushx,mushy,goomba,life,immunity);
	controls(&dir,&jump,&mariox,&marioy,&heady,&salto,&gravity,col,&world,blockx,blocky,type,ground,n,&gold,&monx,&mony,&mushx,&mushy);
		
		enemy(goomba,time,&life,&mariox,&marioy,&heady,&immunity,&salto,&world,&dir);
		
	if((mariox>224)&&(marioy>3))
		win=1;
	usleep(100000);
	}
	
	if(win==1){
		usleep(500000);
		marioy++;
		heady++;
		blocky[233]=4;
		if((marioy>13)&&(marioy==heady)){
			marioy=14;
			heady=14;}
		else if((marioy>13)&&(marioy!=heady)){
			marioy=14;
			heady=15;}
		if(heady<13)
			flag=heady;
		else
			flag=12;
			
		for(i=0;i<16;i++)
			goomba[i]=-10;
			
		for(;mariox!=-1;time++){
			map(col,rig,mariox,marioy,heady,blockx,blocky,type,ground,n,world,time,gold,monx,mony,mushx,mushy,goomba,life,immunity);
			if(marioy!=3){
				mariox=226;
				marioy--;
				heady--;
			}
			else if(mariox!=244)
				mariox++;
			else
				mariox=-5;
			if(blocky[233]<flag)
				blocky[233]++;
			usleep(250000);
		}
	}
	
	return 0;
}
void enemy(int goomba[],int time,int* life,int* mariox, int* marioy,int* heady,int* immunity,int *salto,int* world,int* dir)
{
	static int a=1;
	int i;
	
	if(*marioy<0){
		*life=*life-1;
		*mariox=15;
		*marioy=3;
		*heady=3;
		*world=0;
		*dir=0;
		}
		
	if(*immunity!=0)
		*immunity=*immunity-1;
		
	if((*marioy==3)&&(*immunity==0)){
		for(i=0;i<16;i++){
			if(*mariox==goomba[i]){
				if(*marioy==*heady){
					*life=*life-1;
					*mariox=15;
					*marioy=3;
					*heady=3;
					*world=1;
					*dir=0;}
				else{
					*heady=*marioy;
					*immunity=20;}}
		}
	}
	else if(*marioy==4){
		for(i=0;i<16;i++){
			if(*mariox==goomba[i]){
				goomba[i]=-10 ;
				*salto=4;
			}
		}
	}
	
	if(time%4==0){
		for(i=0;i<16;i++){
			if(a>0)
				goomba[i]++;
			else
				goomba[i]--;
		}
		a++;
		if(a==5)
			a=-3;
		}
	if((*marioy==3)&&(*immunity==0)){
		for(i=0;i<16;i++){
			if(*mariox==goomba[i]){
				if(*marioy==*heady){
					*life=*life-1;
					*mariox=15;
					*marioy=3;
					*heady=3;
					*world=1;
					*dir=0;}
				else{
					*heady=*marioy;
					*immunity=20;}}
		}
	}
	else if(*marioy==4){
		for(i=0;i<16;i++){
			if(*mariox==goomba[i]){
				goomba[i]=-10;
				*salto=4;
			}
		}
	}
}


void map(int col, int rig, int mariox, int marioy, int heady,int blockx[],int blocky[],int type[],int ground[],int n,int world,int time,int gold,int monx,int mony,int mushx,int mushy,int goomba[],int life,int immunity)
{
	int c=0;
	int i;
	int x,y;
	printf("\n\n\n\n      MARIO %4d\t\tVITE x%d\t\t\tMONETE x%d\n\n",time/10,life,gold);
	for(y=rig+1;y>0;y--){
		for(x=world;x<=world+76;x++){
			c=0;
			if((immunity%2==0)&&(x==mariox)&&((y==marioy)||(y==heady))){
				c=1;
				printf("M");}
			for(i=0;i<n;i++){
					if((c==0)&&(x==blockx[i])&&(y==blocky[i])){
						c=1;
						switch(type[i]){
							case 1:
							case 6:
							case 7:
								printf("B");
								break;
							case 2:
							case 3:
								printf("?");
								break;
							case 4:
								printf("G");
								break;
							case 5:
								printf("V");
								break;
							case 8:
							case 11:
								printf("F");
								break;
							case 9:
								printf("|");
								break;
							case 10:
								printf("o");
								break;
							case 12:
								printf("<");
							}
				}}
			for(i=world-1;i<world+77;i++){
				if(((y==1)||(y==2))&&(ground[i]==x)){
					c=1;
					printf("T");}
			}
			if((y==3)&&(c==0)){
				for(i=0;i<16;i++){
					if(x==goomba[i]){
						c=1;
						printf("Q");
						}
				}}
			if((c==0)&&(x==monx)&&(y==mony))
				printf("0");
			else if((c==0)&&(x==mushx)&&(y==mushy))
				printf("O");
			else if(c==0)
				printf(" ");
		}
	}	
	printf("\n");
}

void controls(int* dir,int* jump,int* mariox,int* marioy, int* heady,int* salto, int* gravity,int col,int* world,int blockx[],int blocky[],int type[],int ground[],int n,int* gold,int* monx,int* mony,int* mushx, int* mushy)
{
	int d=0;
	int i=0;
	static int a=0,b=0;
	static int mushdir=0;
	*gravity=1;
	int gravmush=1,f=0;
	int dx=0,sx=0;
	*monx=-1;
	*mony=-1;
	int nope=0;
	if(kbhit()){
		switch(getch())
		{
			case 'a':
				*dir=1;
				a++;
				break;
			case 'd':
				*dir=2;
				b++;
				break;
			case ' ':
				*jump=1;
				break;
		}
	}
	dx=0;
	sx=0;
	for(i=0;i<n;i++){
		if(((*marioy==blocky[i])||(*heady==blocky[i]))&&(*mariox==blockx[i]-1)&&(type[i]!=9)&&(type[i]!=10)&&(type[i]!=11))
			dx=1;
		if(((*marioy==blocky[i])||(*heady==blocky[i]))&&(*mariox==blockx[i]+1)&&(type[i]!=9)&&(type[i]!=10)&&(type[i]!=11))
			sx=1;
	}
	for(i=*world-1;i<*world+77;i++){
		if((*marioy==3)&&(*mariox==ground[i]))
			*gravity=0;
		if((*mushy==3)&&(*mushx==ground[i]))
			gravmush=0;
		}
	if(((*mariox==80)||(*mariox==100))&&(*marioy<4)&&(*dir==1))
		*dir=0;
	else if(((*mariox==82)||(*mariox==102))&&(*marioy<4)&&(*dir==2))
		*dir=0;
		
	if((a==2)||(b==2)){
		*dir=0;}
	if(*dir==0){
		a=0;
		b=0;
		}
		
	if((*mariox!=1)&&(*dir==1)&&(sx==0)){		//Mario direction
		*mariox=*mariox-1;
		b=0;
		}
	else if((*mariox!=col)&&(*dir==2)&&(dx==0)){
		*mariox=*mariox+1;
		a=0;
		}
		
	if((*world!=col-76)&&(*dir==2)&&(dx==0)&&(*mariox>20)&&(sx==0))//Map scroll
		*world=*world+1;
	else if((*world!=1)&&(*dir==1)&&(sx==0)&&(*mariox<col-55)&&(dx==0))
		*world=*world-1;
	
	for(i=0;i<n;i++){
		if((*mariox==blockx[i])&&(*marioy==blocky[i]+1))
			*gravity=0;}
			
	if((*jump==1)&&(*gravity==0)){				//Jump
		*salto=4;
		*jump=0;}
	else
		*jump=0;
			
	for(i=0;i<n;i++){					//Blocchi solidi
		nope=0;	
		if((*mariox==blockx[i])&&(*heady==blocky[i]-1)&&(*salto!=0)){
			*salto=0;
			nope=1;
			}
		else if((*mariox==blockx[i])&&(*heady==blocky[i]-1)&&(*salto==4)){
			*salto=0;
			nope=1;
			}
		else if((*mariox==blockx[i])&&(*heady==blocky[i]-2)&&(*salto==4)){
			*salto=1;
			nope=1;
			}
		if(nope==1){
			if(type[i]==2){
				type[i]=4;
				*gold=*gold+1;
				*monx=*mariox;
				*mony=blocky[i]+1;}
			else if(type[i]==6){
				*gold=*gold+1;
				*monx=*mariox;
				*mony=blocky[i]+1;
				type[i]=1;}
			else if(type[i]==3){
				*mushx=*mariox;
				*mushy=blocky[i]+1;	
				type[i]=4;
				f=1;}
			else if(type[i]==1)
				blocky[i]=-10;
		}
		if((*mushx==blockx[i])&&(*mushy==blocky[i]+1))
			gravmush=0;
			
			}
			
	if(*salto!=0){						//Salto
		if(*salto==4){			
			*marioy=*marioy+2;
			*heady=*heady+2;
		}
		else{						
			*marioy=*marioy+1;
			*heady=*heady+1;}
		*salto=*salto-1;
		}
			
	else if((*gravity==1)&&(*salto==0)){
		*marioy=*marioy-1;
		*heady=*heady-1;
		}
	if((*mariox==*mushx)&&((*heady==*mushy)||(*marioy==*mushy))){
		*mushx=-1;
		*mushy=-1;
		mushdir=0;
		*heady=*marioy+1;}
	
	
	if((*mushx<0)||(*mushy<0)){
		*mushx=-1;
		*mushy=-1;
		mushdir=0;
		}
		
	else if((*mushx!=-1)&&(*mushy!=-1)&&(gravmush==0)&&(f==0)&&(mushdir==0)){
		*mushx=*mushx+1;
		}
	else if((*mushx!=-1)&&(*mushy!=-1)&&(gravmush==0)&&(f==0)&&(mushdir==1)){
		*mushx=*mushx-1;
		}
		
	else if((*mushx!=-1)&&(*mushy!=-1)&&(gravmush==1)){
		*mushy=*mushy-1;
		}
	

			
	if((*mushx==29)||(*mushx==151))
			mushdir=1;
			
	if((*mariox==*mushx)&&((*heady==*mushy)||(*marioy==*mushy))){
		*mushx=-1;
		*mushy=-1;
		mushdir=0;
		*heady=*marioy+1;}
	
}

void mappa(int blockx[],int blocky[], int type[],int i)
{
	//1=Blocco
	//2=Luckyblock
	//3=Fungo
	//4=LuckyPreso
	//5=Tubo
	//6=BloccoMon
	//7=Star
	//8=Solido
	//9=Bandiera
	//10=Punta
	//11=Castle
	
	int arr1[256]={15,19,20,21,21,22,23/*Tubo1*/,30,31,32,30,31,32/*Tubo2*/,45,46,47,45,46,47,45,46,47/*Tubo3*/,55,56,57,55,56,57,55,56,57,55,56,57/*Tubo4*/,70,71,72,70,71,72,70,71,72,70,71,72/*Blocchi2*/,90,91,92,93,94,95,96,97,98,99,100,105,106,107,108/*Blocchi3*/,108,114,115,120,123,123,126/*Blocchi4*/,135,138,139,140,145,146,146,147,147,148/*Scala1*/,152,153,154,155,153,154,155,154,155,155,158,159,160,161,158,159,160,158,159,158/*Scala2*/,166,167,168,169,170,167,168,169,170,168,169,170,169,170,173,174,175,176,173,174,175,173,174,173/*Tubo5*/,185,186,187,185,186,187,185,186,187,205,206,207,205,206,207,205,206,207/*Blocchi*/,193,194,195,196/*Scala*/,210,211,212,213,214,215,216,217,218,211,212,213,214,215,216,217,218,212,213,214,215,216,217,218,213,214,215,216,217,218,214,215,216,217,218,215,216,217,218,216,217,218,217,218/*Fine*/,225,225,225,225,225,225,225,225,225,225,225/*Castle*/,240,241,242,245,246,247,240,241,242,245,246,247,240,241,242,243,244,245,246,247,241,243,244,246,241,243,244,246,241,242,243,244,245,246/*Altro*/,224};
	
	int arr2[256]={6,6,6,6,9,6,6/*Tubo1*/,3,3,3,4,4,4/*Tubo2*/,3,3,3,4,4,4,5,5,5/*Tubo3*/,3,3,3,4,4,4,5,5,5,6,6,6/*Tubo4*/,3,3,3,4,4,4,5,5,5,6,6,6/*Blocchi2*/,6,6,6,9,9,9,9,9,9,9,9,9,9,9,9/*Blocchi3*/,6,6,6,6,6,9,6/*Blocchi4*/,6,9,9,9,9,9,6,9,6,9/*Scala1*/,3,3,3,3,4,4,4,5,5,6,3,3,3,3,4,4,4,5,5,6/*Scala2*/,3,3,3,3,3,4,4,4,4,5,5,5,6,6,3,3,3,3,4,4,4,5,5,6/*Tubo5*/,3,3,3,4,4,4,5,5,5,3,3,3,4,4,4,5,5,5/*Blocchi*/,6,6,6,6/*Scala*/,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,6,6,6,6,6,6,7,7,7,7,7,8,8,8,8,9,9,9,10,10/*Fine*/,3,4,5,6,7,8,9,10,11,12,13/*Castle*/,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,8,8/*Altro*/,-1};
	
	int arr3[256]={2,1,3,1,2,2,1/*Tubo1*/,5,5,5,5,5,5/*Tubo2*/,5,5,5,5,5,5,5,5,5/*Tubo3*/,5,5,5,5,5,5,5,5,5,5,5,5/*Tubo4*/,5,5,5,5,5,5,5,5,5,5,5,5/*Blocchi2*/,1,3,1,1,1,1,1,1,1,1,1,1,1,1,2/*Blocchi3*/,6,1,6,2,2,3,2/*Blocchi4*/,1,1,1,1,1,2,1,2,1,1/*Scala1*/,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8/*Scala2*/,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8/*Tubo5*/,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5/*Blocchi*/,1,1,2,1/*Scala*/,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8/*Fine*/,8,9,9,9,9,9,9,9,9,9,10/*Castle*/,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11/*Altro*/,12};
	blockx[i]=arr1[i];
	blocky[i]=arr2[i];
	type[i]=arr3[i];
}
