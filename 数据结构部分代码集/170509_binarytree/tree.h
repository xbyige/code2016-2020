//
//  tree.h
//  170509_binarytree
//
//  Created by 陈鹏 on 2017/5/9.
//  Copyright © 2017年 陈鹏. All rights reserved.
//

#ifndef tree_h
#define tree_h


#endif /* tree_h */

#include <string>
#include <vector>

class tree
{
    public:
        tree();
//        ~tree();
        bool isempty();
        void preinbuild();              //建树预操作
        void preinbuild(int k,int prel,int prer,int inl,int inr);   //建树
        void preorder(int p=0);         //先序遍历,初始化下标为0
        void inorder(int p=0);          //中序遍历
        void postorder(int p=0);        //后续遍历

    private:
//        std::vector<char> tr;         //vector对char数组赋值失败原因不明
        char tr[8989];
        std::string prestr,instr;
        int count;
};

tree::tree()
{
    count=0;
    for(int i=0;i<=8988;i++) tr[i]=0;   //初始化tr数组
}

bool tree::isempty()
{
    return !count;
}

void tree::preinbuild()
{
    using std::cin;
    using std::cout;
    cout<<"请输入先序遍历序列:";
    cin>>prestr;
    cout<<"请输入后序遍历序列:";
    cin>>instr;
    char ch=prestr[0];
    int inpos=instr.find(ch);
    int inl=0,inr=prestr.length()-1;
    int prepos=inpos,prer=inr;
    tr[0]=ch;
    preinbuild(1,1,prepos,inl,inpos-1);
    preinbuild(2,prepos+1,prer,inpos+1,inr);
}

void tree::preinbuild(int k,int prel,int prer,int inl,int inr)
{
    char ch=prestr[prel];
    tr[k]=ch;
    if(prel>=prer || inl>=inr) return;
    int inpos=instr.find(ch);
    if(inpos-1>=inl) preinbuild(2*k+1,prel+1,prel+inpos-inl,inl,inpos-1);
    if(inr>=inpos+1) preinbuild(2*k+2,prel+inpos-inl+1,prer,inpos+1,inr);   //参数分别为数组下标,先序的左右下标,中序的左右下标
}

void tree::preorder(int p)
{
    if(isalpha(tr[p]) || isdigit(tr[p]))
    {
        std::cout<<tr[p];
        preorder(2*p+1);
        preorder(2*p+2);        //如果是字符则说明该树有内容,可以继续遍历
    }
    else return;
}

void tree::inorder(int p)
{
    if(isalpha(tr[p]) || isdigit(tr[p]))
    {
        inorder(2*p+1);
        std::cout<<tr[p];
        inorder(2*p+2);
    }
    else return;
}

void tree::postorder(int p)
{
    if(isalpha(tr[p]) || isdigit(tr[p]))
    {
        postorder(2*p+1);
        postorder(2*p+2);
        std::cout<<tr[p];
    }
    else return;
}
