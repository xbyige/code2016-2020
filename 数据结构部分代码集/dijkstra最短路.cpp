//dijkstra zuiduanlu
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int a[101][101],vis[101]={0},q[1001]={0},count=1,dis[101];
	int n,m,i,j,k,x,y;
	cout<<"请输入节点数和边数：";
	cin>>n>>m;
	for(i=1;i<=100;i++)
	{
		for(j=1;j<=100;j++) a[i][j]=-1;
	}
	for(i=1;i<=m;i++)
	{
		cin>>x>>y>>k;
		a[x][y]=k; 
	}
	dis[1]=0;
	for(i=2;i<=100;i++) dis[i]=INT_MAX;
	vis[1]=1;q[1]=1;
	for(i=1;i<=count;)
	{
		for(j=1;j<=n;j++)
		{
			if(a[q[i]][j]!=-1)
			{
				if(dis[q[i]]+a[q[i]][j]<dis[j])
				{
					dis[j]=dis[q[i]]+a[q[i]][j];
					if(vis[j]==0)
					{
						count++;
						q[count]=j;
						vis[j]=1;
					}
				}
			}
		}
		vis[q[i]]=0;i++;
	}
	for(i=1;i<=n;i++) cout<<dis[i]<<" "; 
}
