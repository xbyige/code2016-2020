//
//  Header.h
//  170516_linked
//
//  Created by 陈鹏 on 2017/5/16.
//  Copyright © 2017年 陈鹏. All rights reserved.
//

#ifndef Header_h
#define Header_h


#endif /* Header_h */

struct node
{
    int x;
    node *next;
    node();
};

node::node()
{
    x=0;
    next=nullptr;
}
