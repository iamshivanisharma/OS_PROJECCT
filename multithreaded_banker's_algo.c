#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

int main()
{

  int processes=0,resources=0;
  printf("Enter number of processes: "); 
  scanf("%d",&processes);
  printf("Enter number of resources: ");
  scanf("%d",&resources);
 // int s[processes];
int f[processes], ans[processes], ind = 0; 
  

  int allocation[processes][resources];
  int maximum[processes][resources];
  int available[resources];
  int need[processes][resources];
 for(int i=0;i<processes;i++)
  {
    printf("Enter the allocated resources: ");
    for(int j=0;j<resources;j++)
    {
       
        scanf("%d",&allocation[i][j]);
    }
   
  }
for(int i=0;i<processes;i++)
  {
      printf("Enter the maximum  resources which can be provided: ");
    for(int j=0;j<resources;j++)
    {
         
        scanf("%d",&maximum[i][j]);

    }
   
  }
for(int i=0;i<processes;i++)
  {
      printf("\n Number of instances needed: ");
    for(int j=0;j<resources;j++)
    {
        
        need[i][j] = maximum[i][j] - allocation[i][j];
       printf(" %d ", need[i][j]);
 
    }
   
  }



       printf("\n Enter the available resources: ");
    for(int j=0;j<resources;j++)
    {
    
      scanf("%d",&available[j]);
    }
  //**************


    int s,i;
  int  work[processes][resources],finish[processes],flag=1,safe_sequence[processes],index=0;
    
for(int i=0;i<processes;i++)
    {   for(int j=0;j<resources;j++)
        {work[processes][resources]=available[resources];
        }
    }
    for(int i=0;i<processes;i++)
    {
        finish[i]=0;
    }

    for(int i=0;i<processes;i++)

    {
        for(int j=0;j<resources;j++)
        {
        if(finish[i]==0 && need[i][j]<=work[i][j])
        { safe_sequence[i++]=i;
            flag=0;
          work[i][j]=work[i][j]+allocation[i][j];
          finish[i]=1;
	break;

        }





        
        }
    }
    if(flag==1)
    {
        for(int i=0;i<processes;i++)
        finish[i]=1;
        printf("System in safe state\n");
    }

  
printf("Safe Sequence as follows");

    for(int i=0;i<processes-1;i++)
   	 printf(" P%d->",safe_sequence[i] );
    printf(" P%d", safe_sequence[processes - 1]); 

return (0);


}
