//
//  mystack.h
//  170516_linkedstack
//
//  Created by 陈鹏 on 2017/5/16.
//  Copyright © 2017年 陈鹏. All rights reserved.
//

#ifndef mystack_h
#define mystack_h


#endif /* mystack_h */

#include "node.h"

class mystack: public node
{
    public:
        mystack();
        int top();
        void pop();
        void push(int x);
        bool empty();
        int size();
    
    private:
        node* head;
        int count;
};

mystack::mystack()
{
    count=0;
    head=new node;
}

int mystack::top()
{
    return head->next->x;
}

void mystack::pop()
{
    if(!empty())
    {
        node *p=head->next;
        head->next=p->next;
        delete []p;
        count--;
    }
}

void mystack::push(int x)
{
    node *p=new node;
    p->next=head->next;
    head->next=p;
    p->x=x;
    count++;
}

bool mystack::empty()
{
    return head->next;
}

int mystack::size()
{
    return count;
}
