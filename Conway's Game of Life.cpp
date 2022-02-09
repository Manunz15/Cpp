#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <unistd.h>

int pop(int arr[],int a, int b, int c);

int main()
{
	srand(time(NULL));
	
	int n=3;
	int i=0;
	int j=0;
	int h=0;
	int k=0;
	int gen=1;
	int c=0;
	int m=0;
	
	printf("Inserisci il lato del quadrato:\n");
	scanf("%d",&n);
	
	for(;(n<3)||(n>18);){
		printf("\n");
		printf("Il lato non può essere minore di 3 o maggiore di 18:\n");
		scanf("%d",&n);}
		
	int nq=n*n;
	//printf("%d\n\n",nq);
	
	int square[nq];
	int popul[nq];
	
	printf("\nQuante generazioni vuoi?\n");
	scanf("%d",&gen);
	
	printf("\nGenerazione 0\n\n");
	
	for(i=-2;i<n;i++){				//Contorno		
		printf("-");
		}
	printf("\n");
	
	for(i=0;i<nq;i++){				//Generazione 0
		if((i==0)||(i%n==0))
			printf("|");
			
		square[i]=rand()%2;
		if(square[i]==1)
			printf("%d",0);
		else 
			printf(".");
		
		if((i+1)%n==0)
			printf("|\n");
		}	
	
	for(i=-2;i<n;i++){				//Contorno	
		printf("-");
		}
	printf("\n");
	
	sleep(1);
	
	for(i=0;i<gen;i++){				
		printf("\nGenerazione %d\n\n",i+1);
		
		for(j=0;j<nq;j++){
			popul[j]=pop(square,j,n,nq);
		}
		
		for(j=-2;j<n;j++){			//Contorno		
			printf("-");
			}
		printf("\n");
			
		for(j=0;j<nq;j++){
		
			if((j==0)||(j%n==0))
				printf("|");
			
			//printf("%d",popul[j]);
			
			if(popul[j]==3)		//Nascita e morte
				square[j]=1;
				
			else if((square[j]==1)&&(popul[j]==2))
				square[j]=1;
				
			else				
				square[j]=0;
				
				
			if(square[j]==1)		//Scrittura cellule
				printf("0");
			else 
				printf(".");
				
			if((j+1)%n==0)
				printf("|\n");
		}
	
		for(j=-2;j<n;j++){			//Contorno		
			printf("-");
			}
		printf("\n");
		
		sleep(1);
	}
	
	return 0;
}

int pop(int arr[],int a,int b,int c)
{
	int s=0;
	int m=0;
	int i=0;
	
	if((arr[a-b-1]==1)&&(a>(b-1))&&(a%b!=0))
		s++;
	if((arr[a-b]==1)&&(a>(b-1)))
		s++;
	if((arr[a-b+1]==1)&&(a>(b-1))&&((a+1)%b!=0))
		s++;
		
		
	if((arr[a-1]==1)&&(a!=0)&&(a%b!=0))
		s++;
	if((arr[a+1]==1)&&((a+1)%b!=0))
		s++;
		
		
	if((arr[a+b-1]==1)&&(a<(c-b))&&(a%b!=0))
		s++;
	if((arr[a+b]==1)&&(a<(c-b)))
		s++;
	if((arr[a+b+1]==1)&&(a<(c-b)&&((a+1)%b!=0)))
		s++;

	return s;
}
