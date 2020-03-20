//krustal最小生成树
#include <bits/stdc++.h>
using namespace std; 

typedef struct
{
	int x,y,v;
}node;

int main()
{
	int i,j,k,p,a,b,ans,m,n,x,y,v,vis[101]={0};
	node map[101],t;
	cin>>n>>m;
	for(i=1;i<=m;i++)
	{
		cin>>x>>y>>v;
		map[i].x=x;
		map[i].y=y;
		map[i].v=v;
	}
	for(i=1;i<m;i++)
	{
		for(j=i+1;j<=m;j++)
		{
			if(map[i].v>map[j].v)
			{
				t=map[i];
				map[i]=map[j];
				map[j]=t;
			}
		}
	}
	p=0;
	for(i=1;i<=m;i++)
	{
		a=map[i].x;
		b=map[i].y;
		k=0;
		for(j=1;j<=p;j++)
		{
			if(a==vis[j]) k++;
			if(b==vis[j]) k+=2;
		}
		if(k<3)
		{
			if(k==0)
			{
				p++;
				vis[p]=a;
				p++;
				vis[p]=b;
			}
			if(k==1)
			{
				p++;
				vis[p]=b;
			}
			if(k==2)
			{
				p++;
				vis[p]=a;
			}
			ans+=map[i].v;
		}
	} 
	cout<<ans;
	return 0;
} 
