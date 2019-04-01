// Level-1-Fixed-priority-preemptive-Scheduling-Level-2-Round-Robin-Scheduling
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>
int n;
int bt[20],at[20],pri[20];
int pn[20];
int ta[20],wt[20],flag[20]={0},exec[20];
int avgta,avgw,wait,turn;
int a[20];

int disp()
{
  	printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n"); 
	int i=0;
	for(i=0;i<n;i++)
	{
		printf("P[%d]\t|\t%d\t|\t%d\n",pn[i],ta[i],wt[i]); 
	}
	printf("\nAverage Waiting Time= %f\n",wait*1.0/n); 
  printf("Avg Turnaround Time = %f",turn*1.0/n); 
}
int idel(int checker[],int i)
{
	int j=0;
	for(j=0;j<i;j++)
	{
		if(exec[checker[j]]==0)
			break;
	}
	return j;
}
void prioritysort()		
{
	int i=0,j=0,k=n-1,max;
	while(j<n)
	{
		max=-1;
		for(i=0;i<n;i++)
		{
			if(max<pri[i] && flag[i]==0)
			{
				max=pri[i];
				a[k]=i;
			}
		}
		for(i=0;i<n;i++)
		{
			if(max==pri[i])
			{
				flag[i]=1;
			}
		}
		j++;
		k--;
	}
}
int isin(int c,int b)			
{
	int  i;
	i=-1;
	int j;
	if(b!=-1)
	{
	for(j=0;j<n;j++)
	{
		if(at[j]==at[b])
		{
			continue;
		}
		else
		{if(at[j]==c)
		{
			return j;
		}
		}
		
	}
}
	else
	{
		for(j=0;j<n;j++)
	{
		if(at[j]==c)
		{
			return j;
		
		}
	}
	
	}
	return i;
}
int min(int time)    
{
	int i,j=-1;
	for(i=0;i<n;i++)
	{
		if(at[i]==time && flag[i] ==0)
		{
			j=i;
			break;
		}
	}
	if(j!=-1)
	{
		flag[j]=1;
	}
	return j;

}
int main()
{
	
printf("Topic : \n \t Level 1 : Fixed priority preemptive Scheduling \n\t Level 2 : Round Robin Scheduling  \n");
	int i=0,j,temp,temp1;
	printf("Please Enter no of processes  :  ");
	scanf("%d",&n);
	int rt[n];
	int queue2[n];
	int q2size=0;
	for(i=0;i<n;i++)
	{
		pn[i]=i;
	}
	for(i=0;i<n;i++)
	{
		printf("Please Enter burst time of process %d :-",i);
		scanf("%d",&bt[i]);
		rt[i]=bt[i];
		printf("Please Enter arrival time of process %d :-",i);
		scanf("%d",&at[i]);	
		printf("Please Enter Priority of process %d :-",i);
		scanf("%d",&pri[i]);	
	}
	int timeline=0;
	int remaining = n;
	int checker[20];
	int k=0;
	prioritysort();
	int index;

	for(i=0;i<n;i++)
		flag[i]=0;
	i=0;
	while(remaining!=0)
	{
		while((k = min(timeline))!=-1)
		{
			checker[i]=k;
			i++;
		}
		if(i==0 || idel(checker,i)==i)
		{
			timeline++;
			continue;
		}

		int index= INT_MAX;
	for(j=0;j<i;j++)			
		{
			if(exec[checker[j]]!=1)
				{
			for(k=0;k<n;k++)
			{
				if(checker[j]==a[k])
			{
				
					
						if(k<index)			
						{
							index=k;		
							break;
						}
					}
				}
			
			}
		}
		if(index==INT_MAX)
			continue;
		else{
			temp1=a[index];	
		index=temp1;
		temp=rt[index];
		}
	
		for(j=0;j<=temp&&(isin(timeline,index))==-1&& rt[index]>0;j++)   
		{
			rt[index]--;
			timeline++;
		}
		if(rt[index]>0)
		{
				while((k = min(timeline))!=-1)
				{
					checker[i]=k;
					i++;
					while(pri[k]>pri[index]&&isin(timeline,k)==-1&&rt[index]!=0)
					{	rt[index]--;
						timeline++;
						if(isin(timeline,-1)!=-1)
							break;
					}
				}
			
				
			if(pri[isin(timeline,-1)]<pri[index]&&isin(timeline,-1)!=-1)		
			{

				queue2[q2size]=index;
				q2size++;
				remaining--;
				exec[index]=1;
			}
		}
		if(rt[index]==0)	
		{
			wt[index]=timeline-at[index]-bt[index];   
			wait=wait+wt[index];
			ta[index]=timeline-at[index];
			turn=turn+ta[index];
			exec[index]=1;
			remaining--;
		}	
		
	}
	
	int timeq=2;
	remaining = q2size;
	i=0;
	int check[20]={0};
	while(remaining!=0)
	{
		 if(rt[queue2[i]]<=timeq && rt[queue2[i]]>0) 
    { 
      timeline+=rt[queue2[i]]; 
      rt[queue2[i]]=0;  
    } 
    else if(rt[queue2[i]]>0)
    { 
      rt[queue2[i]]-=timeq; 
      timeline+=timeq; 
    } 
    if(rt[queue2[i]]==0&&check[queue2[i]]==0) 
    { 							
      remaining--;  
     	wt[queue2[i]]+=timeline-at[queue2[i]]-bt[queue2[i]];   
		wait=wait+wt[queue2[i]];
		ta[queue2[i]]+=timeline-at[queue2[i]];
		turn=turn+ta[queue2[i]];
		check[queue2[i]]=1; 
    } 
    if(i==q2size-1)
      i=0;  
    else 			
      i++; 
	}
	disp();
}


