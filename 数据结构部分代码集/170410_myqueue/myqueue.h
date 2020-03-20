//
//  myqueue.h
//  170410_myqueue
//
//  Created by 陈鹏 on 2017/4/10.
//  Copyright © 2017年 陈鹏. All rights reserved.
//

#ifndef myqueue_h
#define myqueue_h


#endif /* myqueue_h */

enum error_code{success=1,underflow=0,overflow=0,failed=0};

const int queuesize = 200;

template <typename elemtype>
class myqueue
{
    public:
        myqueue();
        ~myqueue();
        bool empty();               //判空
        bool full();                //判满
        int length();               //长度
        error_code enqueue(elemtype);   //入队
        error_code dequeue();           //出队
        elemtype gethead();             //头
    
    private:
        elemtype *data;
        int front,rear;
        int count;
};

template<typename elemtype>
myqueue<elemtype>::myqueue()
{
    data=new elemtype[queuesize];
    front=1;
    rear=0;
    count=0;
}

template<typename elemtype>
myqueue<elemtype>::~myqueue()
{
    delete []data;
}

template<typename elemtype>
bool myqueue<elemtype>::empty()
{
    return !count;
}

template<typename elemtype>
bool myqueue<elemtype>::full()
{
    return count==queuesize;
}

template<typename elemtype>
int myqueue<elemtype>::length()
{
    return count;
}

template<typename elemtype>
error_code myqueue<elemtype>::enqueue(elemtype n)
{
    if(full()) {std::cout<<"sb";return overflow;}
    rear=(rear+1)%queuesize;
    data[rear]=n;
    count++;
    return success;
}

template<typename elemtype>
error_code myqueue<elemtype>::dequeue()
{
    if(empty()) return underflow;
    front=(front+1)%queuesize;
    count--;
    return success;
}

template<typename elemtype>
elemtype myqueue<elemtype>::gethead()
{
    return data[front];
}
