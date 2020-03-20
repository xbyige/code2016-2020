//
//  my_linked_queue.h
//  my_linked_queue
//
//  Created by 陈鹏 on 2017/4/17.
//  Copyright © 2017年 陈鹏. All rights reserved.
//

#include "node.h"

#ifndef my_linked_queue_h
#define my_linked_queue_h


#endif /* my_linked_queue_h */

class my_linked_queue: public node
{
    public:
        my_linked_queue();          //模仿STL
//        ~my_linked_queue();
        void init();                //初始化
        void pop();                 //弹出顶部
        void push(int x);           //加入
        int front();                //队列前端
        int back();                 //队列后端
        bool empty();               //判空
        int size();                 //输出长度
        void destroy();             //销毁
    
    private:
        node *tail_,*back_;
        int count;
};

my_linked_queue::my_linked_queue()
{
    count=0;
    tail_=new node;
    back_=tail_;
}

void my_linked_queue::init()
{
    destroy();
    my_linked_queue();
}

void my_linked_queue::destroy()
{
    node *p=tail_;
    node *q=p->next;
    while(!p->next)
    {
        delete []p;
        p=q;
        if(q) q=q->next;
    }
    delete []p;
}

void my_linked_queue::pop()
{
    node *p=tail_->next;
    node *q=p->next;
    tail_->next=q;
    delete[] p;
    count--;
}

void my_linked_queue::push(int x)
{
    node *current_=new node;
    back_->next=current_;
    current_->x=x;
    current_->next=nullptr;
    back_=current_;
    count++;
}

int my_linked_queue::front()
{
    return tail_->next->x;
}

int my_linked_queue::back()
{
    return back_->x;
}

bool my_linked_queue::empty()
{
    return count!=0;
}

int my_linked_queue::size()
{
    return count;
}
