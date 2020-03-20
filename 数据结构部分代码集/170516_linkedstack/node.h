//
//  node.h
//  170516_linkedstack
//
//  Created by 陈鹏 on 2017/5/16.
//  Copyright © 2017年 陈鹏. All rights reserved.
//

#ifndef node_h
#define node_h


#endif /* node_h */

struct node
{
    node();
    node *next;
    int x;
};

node::node()
{
    next=nullptr;
    x=0;
}
