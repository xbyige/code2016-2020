//
//  tree.h
//  170509_linkedtree
//
//  Created by 陈鹏 on 2017/5/9.
//  Copyright © 2017年 陈鹏. All rights reserved.
//

#ifndef tree_h
#define tree_h


#endif /* tree_h */

#include <iostream>
#include "node.h"

class tree: public node
{
    public:
        tree();
//        ~tree();
        bool isempty();
        void build(int n);
        void build(node*, int n);       //随意建树
        void preorder();
        void preorder(node*);           //重载函数,分别代表第一次以及以后的遍历情况
        void inorder();
        void inorder(node*);
        void postorder();
        void postorder(node*);
    
    private:
        node *root;
        int count;
};

tree::tree()
{
    root=new node;
    count=0;
}

bool tree::isempty()
{
    return !count;
}

void tree::build(int n)
{
    root->x=++count;
    build(root,n-1);
}

void tree::build(node *p,int n)
{
    if(n==0) return;
    node *left=new node;
    left->x=++count;
    node *right=new node;
    right->x=++count;
    p->l=left;
    p->r=right;
    build(left,n-1);
    build(right,n-1);
}

void tree::preorder()
{
    if(isempty())
    {
        std::cout<<"树空"<<std::endl;
        return;
    }
    preorder(root);
}

void tree::preorder(node *p)
{
    if(p==nullptr) return;
    std::cout<<p->x<<" ";
    preorder(p->l);
    preorder(p->r);
}

void tree::inorder()
{
    if(isempty())
    {
        std::cout<<"树空"<<std::endl;
        return;
    }
    preorder(root);
}

void tree::inorder(node *p)
{
    if(p==nullptr) return;
    inorder(p->l);
    std::cout<<p->x<<" ";
    inorder(p->r);
}

void tree::postorder()
{
    if(isempty())
    {
        std::cout<<"树空"<<std::endl;
        return;
    }
    postorder(root);
}

void tree::postorder(node *p)
{
    if(p==nullptr) return;
    inorder(p->l);
    inorder(p->r);
    std::cout<<p->x<<" ";
}
