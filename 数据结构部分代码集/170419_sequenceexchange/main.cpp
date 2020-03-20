//
//  main.cpp
//  170419_sequenceexchange
//
//  Created by 陈鹏 on 2017/4/19.
//  Copyright © 2017年 陈鹏. All rights reserved.
//

#include <iostream>
using namespace std;

const int maxrange = 101;

template<typename elemtype>
struct sequence
{
    elemtype x,y,n;
};

int main(int argc, const char * argv[])
{
    int x,y,m,n,count,total[101]={0},ans[maxrange][maxrange]={0};
    sequence<int> *a= new sequence<int>[maxrange];
    sequence<int> *b= new sequence<int>[maxrange];
    cin>>m;
    for(int i=1;i<=m;i++)           //预处理
    {
        cin>>x>>y>>n;
        a[count].x=x;
        a[count].y=y;
        a[count].n=n;
        count++;
        total[y]++;
    }
    for(int i=1;i<=100;i++) total[i]=total[i-1]+total[i];
    for(int i=0;i<m;i++)            //矩阵转置
    {
        b[total[a[i].y-1]].x=a[i].y;
        b[total[a[i].y-1]].y=a[i].x;
        b[total[a[i].y-1]].n=a[i].n;
        total[a[i].y-1]++;
    }
    for(int i=0;i<m;i++)
    {
        cout<<b[i].x<<" "<<b[i].y<<" "<<b[i].n<<endl;
    }
    
    for(int i=0;i<m;i++)            //矩阵乘法
    {
        for(int j=0;j<m;j++)
        {
            ans[a[i].x][b[j].y]+=a[i].n*b[i].n;
            ans[a[i].y][b[j].x]+=a[i].n*b[i].n;
        }
    }
    for(int i=0;i<10;i++)           //打印乘法后二维矩阵(邻接矩阵)
    {
        for(int j=0;j<10;j++)
        {
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
