//
//  main.cpp
//  170516_kmp
//
//  Created by 陈鹏 on 2017/5/16.
//  Copyright © 2017年 陈鹏. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int num=0;

void kmpnext(string s,int *next,int *nextval){
    int len=s.length();
    int i=0,k=-1;
    next[0]=-1;
    nextval[0]=-1;
    while(i<len-1){
        if(k==-1 || s[i]==s[k]){
            i++,k++;
            next[i]=k;
            if(s[i]==s[next[i]]){
                nextval[i]=nextval[next[i]];
            }else{
                nextval[i]=next[i];
            }
        }else{
            k=next[k];
        }
    }
    for(int i=0;i<len;i++){
        printf("%d %d\n",next[i],nextval[i]);
    }
}

int kmp(string s1,string s2,int *next){
    int len1=s1.length();
    int len2=s2.length();
    int i=0,k=0;
    while(i<len1 && k<len2){
        if(k==-1){
            i++,k++;
        }
        if(s1[i]==s2[k]){
            i++,k++;
        }else{
            k=next[k];
        }
        num++;
    }
    if(k!=len2)return -1;
    return i-k;
}

int main(){
    string s1,s2;
    int next[7687];
    int nextval[7687];
    cin>>s1;
    cin>>s2;
    kmpnext(s2,next,nextval);
    num=0;
    cout<<kmp(s1,s2,nextval)<<endl;
    cout<<num<<endl;
    num=0;
    cout<<kmp(s1,s2,next)<<endl;
    cout<<num;
    return 0;
}
