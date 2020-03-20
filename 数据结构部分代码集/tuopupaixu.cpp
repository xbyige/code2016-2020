//Õÿ∆À≈≈–Ú 

#include <bits/stdc++.h>
using namespace std;

typedef struct
{
	int x,y,v;
}node;

int main()
{
	int i,j,k,n,m;
	node map[101],t;
	int in[101]={0},ans[101]={0},vis[101]={0};
	cin>>n>>m;
	for(i=1;i<=m;i++)
	{
		cin>>map[i].x>>map[i].y>>map[i].v;
		in[map[i].y]++;
	}
	for(i=1;i<m;i++)
	{
		for(j=i+1;j<=m;j++)
		{
			if(map[i].x>map[j].x || (map[i].x==map[j].x && map[i].y>map[j].y))
			{
				t=map[i];map[i]=map[j];map[j]=t;
			}
		}
	}
	for(i=1;i<=n;i++) cout<<in[i]<<" ";
	cout<<endl; 
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
//			cout<<in[j]<<" "<<ans[j]<<endl;
			if(in[j]==0 && vis[j]==0) break;
		}
		cout<<j<<endl;
		vis[j]=1;
		ans[i]=j;
		for(k=1;k<=m;k++)
			if(map[k].x==j) in[map[k].y]--;
	}
	return 0;
}
