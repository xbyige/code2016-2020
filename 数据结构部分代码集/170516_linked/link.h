//
//  link.h
//  170516_linked
//
//  Created by 陈鹏 on 2017/5/16.
//  Copyright © 2017年 陈鹏. All rights reserved.
//

#ifndef link_h
#define link_h


#endif /* link_h */

#include "Header.h"

class linked : public node
{
    public:
        linked();
        void pop();
        int top();
        void push(int x);
        bool empty();
        int size();
    
    private:
        node *head;
        int count;
};

linked::linked()
{
    head=new node;
    count=0;
}

int linked::size()
{
    return count;
}

bool linked::empty()
{
    return head->next;
}

void linked::pop()
{
    if(!empty())
    {
        node *p=head->next;
        head->next=p->next;
        delete []p;
        count--;
    }
    else std::cerr<<"链表已空";
}

int linked::top()
{
    if(!empty())
    {
        return head->next->x;
    }
    std::cerr<<"链表已空";
    return -1;
}

void linked::push(int x)
{
    node *p=new node;
    p->next=head->next;
    p->x=x;
    count++;
}
