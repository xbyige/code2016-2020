//
//  main.cpp
//  170510_poland
//
//  Created by 陈鹏 on 2017/5/10.
//  Copyright © 2017年 陈鹏. All rights reserved.
//

#include <iostream>
#include <stack>
#include <string>
using namespace std;

int ope(int a,int b,int o)      //计算二元运算
{
    switch(o)
    {
        case -1:    return a+b;
        case -2:    return a-b;
        case -3:    return a*b;
        case -4:    return a/b;
        default:    return -1;
    }
}

int ex(char ch)                 //设置符号在栈内的标志
{
    int w;
    if(ch=='+') w=-1;
    if(ch=='-') w=-2;
    if(ch=='*') w=-3;
    if(ch=='/') w=-4;
    return w;
}

char eex(int t)                 //反向设置
{
    char w;
    if(t==-1) w='+';
    if(t==-2) w='-';
    if(t==-3) w='*';
    if(t==-4) w='/';
    return w;
}

bool isoperator(char ch)        //判断ch是否为运算符号
{
    switch(ch)
    {
        case '+':
        case'-':
        case'*':
        case'/':
            return true;
        default:
            return false;
    }
}

int prior(char ch)              //设置优先级
{
    switch(ch)
    {
        case '(':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return -1;
    }
}

int main(int argc, const char * argv[])
{
    stack<int> eva;
    stack<char> p;
    stack<int> e;
    string s;
    int t=0,f=0;
    char ch;
    cout<<"请输入要进行运算的表达式:";
    cin>>s;
    for(int i=0;i<s.length();i++)
    {
        ch=s[i];
        if(ch>='0' && ch<='9')
        {
            f=1;                            //f为t是否可以入栈的标志
            t=t*10+ch-'0';
        }
        else
        {
            if(f==1) eva.push(t);
            t=0;f=0;
            if(ch=='(')                     //左括号直接入符号栈
            {
                p.push(ch);
            }
            else if(ch==')')                //右括号则是把从右括号到左括号中间符号全部入栈
            {
                while(p.top()!='(')
                {
                    eva.push(ex(p.top()));
                    p.pop();
                }
                p.pop();
            }
            else if(isoperator(ch))
            {
                while(!p.empty() && prior(ch)<=prior(p.top()))      //如果ch优先级不大于符号栈栈顶则弹出符号栈内容到表达式栈循环
                {
                    eva.push(ex(p.top()));
                    p.pop();
                }
                p.push(ch);
            }
        }
    }
    if(f==1) eva.push(t);               //如果最后有数则入栈
    while(!p.empty())
    {
        if(p.top()!='(' && p.top()!=')') eva.push(ex(p.top()));       //入栈其他在比符号栈的符号
        p.pop();
    }
    while(!eva.empty())
    {
        e.push(eva.top());              //颠倒栈
        eva.pop();
    }
/*    while(!e.empty())
    {
        t=e.top();
        if(t>=0)
        {
            cout<<t<<" ";
        }
        else
        {
            cout<<eex(t)<<" ";
        }
        e.pop();
    }*/
    while(!e.empty())
    {
        if(e.top()>=0)
        {
            eva.push(e.top());
        }
        else
        {
            int t1=eva.top();
            eva.pop();
            int t2=eva.top();
            eva.pop();
            eva.push(ope(t2,t1,e.top()));   //计算
        }
        e.pop();
    }
    cout<<eva.top();
    return 0;
}


//while(cin)
