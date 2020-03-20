//
//  main.cpp
//  170509_linkedtree
//
//  Created by 陈鹏 on 2017/5/9.
//  Copyright © 2017年 陈鹏. All rights reserved.
//

#include "tree.h"
#include <iostream>
using std::cin;
using std::cout;

int main(int argc, const char * argv[]) {
    tree tr;
    tr.build(4);
    tr.preorder();
    return 0;
}
