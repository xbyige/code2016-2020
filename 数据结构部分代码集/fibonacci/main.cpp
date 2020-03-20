//
//  main.cpp
//  fibonacci
//
//  Created by 陈鹏 on 2017/4/10.
//  Copyright © 2017年 陈鹏. All rights reserved.
//

#include <iostream>
#include <stack>
using namespace std;

int main(int argc, const char * argv[]) {
/*    unsigned long long a[10000];
    a[0]=0;a[1]=1;
    for(int i=2;i<=60;i++) a[i]=a[i-1]+a[i-2];
//    for(int i=0;i<=60;i++) cout<<a[i]<<"  ";
    int m,k;cin>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>k;
        cout<<a[k]<<endl;
    }
    return 0;*/
    int n,tmp;
    cin>>n;
    stack<int> fib;             //STL stack,可套用自己写的模板
    unsigned long long sum=0;
    fib.push(n);
    while(!fib.empty())         //结束条件,栈空
    {
        if(fib.top()<=1)
        {
            sum+=fib.top();
            fib.pop();          //若栈顶为0或1,栈顶加到sum并出队
        }
        else
        {
            tmp=fib.top();
            fib.pop();
            fib.push(tmp-1);
            fib.push(tmp-2);    //若栈顶不为0或1,栈顶被替换
        }
    }
    cout<<sum;
}
