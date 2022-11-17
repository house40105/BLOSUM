#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>

int rescore(char S1,char S2,int blosum[][21])
{
	char protein[]={'A','R','N','D','C','Q','E','G','H','I','L','K','M','F','P','S','T','W','Y','V','-'};
	int n1=0,n2=0;

	for(int i=0;i<21;i++)
	{
		if(S1==protein[i])
			n1=i;
		if(S2==protein[i])
			n2=i;
	}
	return blosum[n1][n2];

}
int main (void)
{
	FILE *ptr;
	FILE *blptr;
	FILE *wptr;
	char temp;
	int s1count=0,s2count=0;
	int blosum[21][21];

	ptr=fopen("1.txt","r");
	blptr=fopen("blosum50.txt","r");
	wptr=fopen("µ²ªG.txt","w");

	while(!feof(blptr))
	{
		for(int i=0;i<21;i++)
		{
			fscanf(blptr,"%c",&temp);
			for(int j=0;j<21;j++)
				fscanf(blptr,"%d",&blosum[i][j]);
			fscanf(blptr,"%c",&temp);
		}
	}
	int check=0;
	while(!feof(ptr))
	{
		fscanf(ptr,"%c",&temp);
		if(temp=='\n')
			check=1;
		if(check==0)
		{
			if(temp!='$')
				s1count++;
		}
		else if(check==1)
		{
			if(temp!='\n'&&temp!='$')
				s2count++;
		}
	}
	rewind(ptr);
	char *s1=(char *)malloc(sizeof(char)*s1count);
	char *s2=(char *)malloc(sizeof(char)*s2count);
	check=0;s1count=0;s2count=0;
	while(!feof(ptr))
	{
		fscanf(ptr,"%c",&temp);
		if(temp=='\n')
			check=1;
		if(check==0)
		{
			if(temp!='$')
			{
				s1[s1count]=temp;
				s1count++;
			}
		}
		else if(check==1)
		{
			if(temp!='\n'&&temp!='$')
			{
				s2[s2count]=temp;
				s2count++;
			}
		}
	}

	int **G = (int **)malloc(sizeof(void *)*(s1count+1));
	for (int i = 0; i < s1count+1; i++)
		G[i] = (int *)malloc(sizeof(int *)*(s2count+1));
	for(int i=0;i<s1count+1;i++)
		for(int j=0;j<s2count+1;j++)
			G[i][j]=0;
	int **W = (int **)malloc(sizeof(void *)*(s1count+1));
	for (int i = 0; i < s1count+1; i++)
		W[i] = (int *)malloc(sizeof(int *)*(s2count+1));

	int tempsc=0,maxsc=0;
	for(int i=1;i<=s1count;i++)
	{
		for(int j=1;j<=s2count;j++)
		{
			maxsc=0;
			if(G[i-1][j-1]+rescore(s1[i],s2[j],blosum)>maxsc)
			{
				maxsc=G[i-1][j-1]+rescore(s1[i],s2[j],blosum);
				W[i-1][j-1]=3;
			}
			if(G[i-1][j]+rescore(s1[i],'-',blosum)>maxsc)
			{
				maxsc=G[i-1][j-1]+rescore(s1[i],s2[j],blosum);
				W[i-1][j]=2;
			}
			if(G[i][j-1]+rescore('-',s2[j],blosum)>maxsc)
			{
				maxsc=G[i-1][j-1]+rescore(s1[i],s2[j],blosum);
				W[i][j-1]=1;
			}
			if(maxsc<0)
				maxsc=0;
			G[i][j]=maxsc;
		}
	}
	int max=0,x=0,y=0;
	for(int i=1;i<=s1count;i++)
	{
		for(int j=1;j<=s2count;j++)
		{
			if(max<G[i][j])
			{
				max=G[i][j];
				x=j;y=i;
			}
		}
	}
	int *s1r=(int *)malloc(sizeof(int)*s1count);
	int *s2r=(int *)malloc(sizeof(int)*s2count);
	for(int i=0;i<s1count;i++)
		s1r[i]=0;
	for(int i=0;i<s2count;i++)
		s2r[i]=0;

	while(1)
	{
		if(G[y][x]==0)
			break;
		s1r[y]=1;
		s2r[x]=1;
		if(W[y][x]==1)//to left
		{
			x--;
		}
		if(W[y][x]==2)//to up
		{
			y--;
		}
		if(W[y][x]==3)//to v
		{
			x--;y--;
		}
	}
	for(int i=0;i<s1count;i++)
		if(s1r[i]==0)
			s1[i]=tolower(s1[i]);
	for(int i=0;i<s2count;i++)
		if(s2r[i]==0)
			s2[i]=tolower(s2[i]);






	for(int i=0;i<s1count;i++)
		printf("%c",s1[i]);
	printf("\n");
	for(int i=0;i<s2count;i++)
		printf("%c",s2[i]);
	printf("\n");
	for(int i=0;i<21;i++)
	{
		for(int j=0;j<21;j++)
			printf("%2d",blosum[i][j]);
		printf("\n");
	}
	printf("\n");
	for(int i=0;i<s1count+1;i++)
	{
		for(int j=0;j<s2count+1;j++)
			printf("%2d)",G[i][j]);
		printf("\n");
	}
	printf("\n");
	for(int i=0;i<s1count;i++)
		printf("%d",s1r[i]);
	printf("\n");
	for(int i=0;i<s2count;i++)
		printf("%d",s2r[i]);
	printf("\n");


	for(int i=0;i<s1count;i++)
	{
		printf("%c",s1[i]);
		fprintf(wptr,"%c",s1[i]);
	}
	printf("\n");
	fprintf(wptr,"\n\n");
	for(int i=0;i<s2count;i++)
	{
		printf("%c",s2[i]);
		fprintf(wptr,"%c",s2[i]);
	}
	printf("\n");

	fclose(ptr);
	fclose(wptr);
	fclose(blptr);

	system("PAUSE");
}