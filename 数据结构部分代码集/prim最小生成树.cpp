//prim zuixiaoshengchengshu
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int x1[101],y1[101],v1[101],a[101][101],vis[101],dvis[101],p,dp;
	int n,m,i,j,k,e,f,x,y,min,ans=0;
	cout<<"请输入节点数和边数：";
	cin>>n>>m;
	for(i=1;i<=100;i++)
	{
		for(j=1;j<=100;j++) a[i][j]=INT_MAX;
	}
	for(i=1;i<=m;i++)
	{
		cin>>x>>y>>k;
		a[x][y]=k; 
	}
	for(i=1;i<=100;i++)
	{
		vis[i]=0;
		dvis[i]=1;
	}
	vis[1]=1;
	p=1;
	for(x=1;x<n;x++)
	{
		min=INT_MAX;
		for(j=1;j<=p;j++)
		{
			f=1;
			for(k=1;k<=p;k++)
			{
				if(vis[j]==k)
				{
					f=0;
					break;
				}
			}
			if(f && min>a[vis[x]][j]])
			{
				min=a[vis[x]][j];
				e=k;
			}
		}
		p++;vis[p]=k;
		ans=ans+min;
	}
	cout<<ans;
	return 0;
}
