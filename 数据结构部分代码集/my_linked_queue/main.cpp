//
//  main.cpp
//  my_linked_queue
//
//  Created by 陈鹏 on 2017/4/17.
//  Copyright © 2017年 陈鹏. All rights reserved.
//

#include <iostream>
#include "my_linked_queue.h"
using namespace std;

int main(int argc, const char * argv[]) {
    my_linked_queue c;
    //    queue<int> c;
    int n,i,a,b;
    cin>>n;
    c.push(0);
    c.push(1);
    c.push(0);
    cout<<"1"<<endl;
    for(i=2;i<=n;i++)
    {
        a=c.front();
        c.pop();
        b=c.front();
        for(;;)
        {
            cout<<a+b<<" ";
            c.push(a+b);
            
            if(b==0) break;
            c.pop();
            a=b;
            b=c.front();
        }
        c.push(0);
        cout<<endl;
    }

    return 0;
}
