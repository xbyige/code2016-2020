//
//  main.cpp
//  170509_binarytree
//
//  Created by 陈鹏 on 2017/5/9.
//  Copyright © 2017年 陈鹏. All rights reserved.
//

#include <iostream>
#include "tree.h"
using std::cin;
using std::cout;
using std::string;

int main(int argc, const char * argv[]) {
    tree tr;
    tr.preinbuild();    //根据前序中序遍历建树
    tr.postorder();     //输出后续遍历结果
    return 0;
}
