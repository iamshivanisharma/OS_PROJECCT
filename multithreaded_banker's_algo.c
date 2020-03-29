#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int r;
	int Allocation[100][100];
	int Maximum[100][100];
	int Need[100][100];
	int Work[1][100];
	int n,m,pid,choice,p;
void show(int x[][100],int n,int m){
	int i,j;
	for(i=0;i<n;i++){
		printf("\n");
		for(j=0;j<m;j++){
			printf("%d\t",x[i][j]);
		}
	}	
}

//RESOURCE REQUEST ALGORITHM
void *resource_request()
{   pid=pid-1;
	int X[100][100],Y[100][100],Available[100][100],Allocation[100][100];
	for(int i=0;i<100;i++)
		for(int j=0;j<100;j++)
		   {
			   X[i][j]=Allocation[i][j];
		   }
for(int i=0;i<100;i++)
		for(int j=0;j<100;j++)
		   {
			   Y[i][j]=Need[i][j];
		   }
		   for(int i=0;i<100;i++)
			for(int j=0;j<100;j++)
		   {
			   Available[i][j]=Work[i][j];
		   }

	int request[1][100];
	int i;
	printf("\n Enter additional request :- \n");
	for(i=0;i<m;i++){
		printf(" Request for resource %d : ",i+1);
		scanf("%d",&request[0][i]);
	}
	
	for(i=0;i<m;i++)
		if(request[0][i] > Y[pid][i]){
			printf("\n Error encountered (process has exceeded it's maximum claim ).\n");
			//break;
			exit(0);
	}

	for(i=0;i<m;i++)
		if(request[0][i] > Available[0][i]){
			printf("\n Resources unavailable.\n");
			//break;
			exit(0);
		}
	
	for(i=0;i<m;i++){
		Available[0][i]-=request[0][i];
		X[pid][i]+=request[0][i];
		Y[pid][i]-=request[0][i];
	}
   
}

//SAFETY ALGORITHM
int safetyAlgo(int Allocation[][100],int Need[][100],int Available[1][100],int n,int m,int a[]){

	int i,j,k,x=0;
	int Finish[100],Work[1][100];
	int flag1=0,flag=0;
	for(i=0;i<n;i++)
		Finish[i]=0;
	for(i=0;i<m;i++)
		Work[0][i]=Available[0][i];

	for(k=0;k<n;k++){
		for(i=0;i<n;i++){
			if(Finish[i] == 0){
				flag=0;
				for(j=0;j<m;j++){
					if(Need[i][j] > Work[0][j])
						flag=1;
				}
				if(flag == 0 && Finish[i] == 0){
					for(j=0;j<m;j++)
						Work[0][j]+=Allocation[i][j];
					Finish[i]=1;
					flag1++;
					a[x++]=i;
				}
			}
		}
		if(flag1 == n)
			return 1;
	}
	return 0;
}


//BANKER'S ALGORITHM
void get(int Allocation[][100],int Need[][100],int M[100][100],int Work[1][100],int *n,int *m){
	int i,j;
	printf("\n Enter total number of processes : ");
	scanf("%d",n);
	printf("\n Enter total number of resources : ");
	scanf("%d",m);
	for(i=0;i<*n;i++){
		printf("\n Process %d\n",i+1);
		for(j=0;j<*m;j++){
			printf(" Allocation for resource %d : ",j+1);
			scanf("%d",&Allocation[i][j]);
			printf(" Maximum for resource %d : ",j+1);
			scanf("%d",&Maximum[i][j]);
		}
	}
	printf("\n Available resources : \n");
	for(i=0;i<*m;i++){
		printf(" Resource %d : ",i+1);
		scanf("%d",&Work[0][i]);
	}

	for(i=0;i<*n;i++)
		for(j=0;j<*m;j++)
			Need[i][j]=Maximum[i][j]-Allocation[i][j];

	printf("\n Allocation Matrix");
	show(Allocation,*n,*m);
	printf("\n Maximum Requirement Matrix");
	show(Maximum,*n,*m);
	printf("\n Need Matrix");
	show(Need,*n,*m);

}

int bankerAlgo(int Allocation[][100],int Need[][100],int Work[1][100],int n,int m){
	int j,i,a[100];
	j=safetyAlgo(Allocation,Need,Work,n,m,a);
	if(j != 0 ){
		printf("\n\n");
		for(i=0;i<n;i++)
		     printf(" P%d  ",a[i]);
		printf("\n A safety sequence has been detected.\n");
		return 1;
	}else{
		printf("\n Deadlock has occured.\n");
		return 0;
		
	}
}
void create_thread(int n)
{
	for(int i=0;i<n;i++)
	{	printf("\n Enter process number: ");
		scanf("%d",&pid);
		pthread_t pid;
		pthread_create(&pid,NULL,resource_request,NULL);
		pthread_join(pid,NULL);
		int val=bankerAlgo(Allocation,Need,Work,n,m);
   if(val==0)
   {
	   exit(0);
   }
	}


}


int main(){

	printf("\n MULTITHREADED DEADLOCK AVOIDANCE PROGRAM USING BANKER'S ALGORITHM\n");
	get(Allocation,Need,Maximum,Work,&n,&m);
	r=bankerAlgo(Allocation,Need,Work,n,m);
	if(r !=0 ){
		printf("\n Do you want make an additional request ? (1=Yes|0=No)");
		scanf("%d",&choice);
		if(choice == 1){
            printf("Enter number of requests: ");
            scanf("%d",&n);
			create_thread(n);
            
		}
	}else
		exit(0);
	return 0;
}
