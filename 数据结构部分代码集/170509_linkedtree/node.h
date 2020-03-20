//
//  node.h
//  170509_linkedtree
//
//  Created by 陈鹏 on 2017/5/9.
//  Copyright © 2017年 陈鹏. All rights reserved.
//

#ifndef node_h
#define node_h


#endif /* node_h */

struct node
{
    int x;
    node *l,*r;
    node() {x=0;l=nullptr;r=nullptr;}
//    node operator +(const node &n);
};

/*node node::operator +(const node &n)
{
    node sum;
    sum.x=x+n.x;
    return sum;
}*/
