//
//  main.cpp
//  170410_myqueue
//
//  Created by 陈鹏 on 2017/4/10.
//  Copyright © 2017年 陈鹏. All rights reserved.
//

#include <iostream>
#include <queue>
#include "myqueue.h"
using namespace std;

int main(int argc, const char * argv[]) {
    myqueue<unsigned long long> c;
//    queue<int> c;
    unsigned long long n,i,a,b;
    cin>>n;
    c.enqueue(0);
    c.enqueue(1);
    c.enqueue(0);
    cout<<"1"<<endl;
    for(i=2;i<=n;i++)
    {
        a=c.gethead();
        c.dequeue();
        b=c.gethead();
        for(;;)
        {
            cout<<a+b<<" ";
            c.enqueue(a+b);

            if(b==0) break;
            c.dequeue();
            a=b;
            b=c.gethead();
        }
        c.enqueue(0);
        cout<<endl;
    }
    return 0;
}
