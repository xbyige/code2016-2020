//floyd

#include <bits/stdc++.h>
using namespace std;

int main()
{
	int a[101][101];
	int n,m,d,i,j,k,x,y;
	cout<<"请输入节点数和边数："; 
	cin>>n>>m;
	for(i=1;i<=100;i++)
	{
		for(j=1;j<=100;j++) a[i][j]=INT_MAX;
	}
	for(i=1;i<=100;i++) a[i][i]=0;
	for(i=1;i<=m;i++)
	{
		cin>>x>>y>>d;
		a[x][y]=d; 
	}
	for(k=1;k<=n;k++)
 		for(i=1;i<=n;i++)   
     		for(j=1;j<=n;j++)   
  				if(a[i][j]<a[i][k]+a[k][j])   
      				a[i][j]=a[i][k]+a[k][j];
    for(i=1;i<=n;i++)
    {
    	for(j=1;j<=n;j++)
    	{
    		cout<<a[i][j]<<" ";
    	}
    	cout<<endl;
    } 
	return 0;
}
