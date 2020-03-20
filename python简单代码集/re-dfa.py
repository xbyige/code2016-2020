from graphviz import Digraph
import re

'''
编写nfa时把程序数据结构想的过于复杂，再加上python使用不熟练，因此后来迟迟没有落笔
直到后来发现数据结构可以简化，想到这一点，后来在输出nfa的时候顺带简化了dfa结构，dfa以及可视化编写只用了两个小时，但这也导致nfa与dfa的数据结构并没有统一
'''
'''
(a*|b*)b(ba)*
(a*|b*)*a*b*
a(a|c)b|b(ab|bc)(ba|c)
((a*)*|(b|a)*)cd*
'''

nfa = []    #存放State 以及 连接线Connection
nfanull_tmp = []
nfanull = []
nfach_tmp = []
nfach = []
nfa_acc = []
dfa = []
m_dfa = []

class dfaState:
    dfanum = 0
    def __init__(self, num, start):
        self.id_num = num
        self.start = start
        self.accepted = False
        self._con = []
        self.represent = []
        self.groupID = 0

class State:
    num = 0
    def __init__(self, num, start, accepted):
        self.id_num = num          #ID号
        self.start = start         #是否为start状态
        self.accepted = accepted   #是否为可accepted状态
        self._con = []             #连接线

class Connection:
    def __init__(self, ch):
        self.ch = ch               #连接字母
        self._to = []              #终点
        self.vis = False

symbol = {'|': 1, '·': 2, '*': 3, '(': -1, ')':-1}

def point_re(re):
    i = 0
    while i < len(re) - 1:
        if re[i]!='(' and re[i]!=')' and re[i]!='*' and re[i]!='|' and re[i]!='·':
            if re[i+1]!=')' and re[i+1]!='*' and re[i+1]!='|':
                re = re[:i+1] + '·' + re[i+1:]
                i = i + 1
        else:
            if re[i] == ')':
                if re[i+1]!='(' and re[i+1]!=')' and re[i+1]!='*' and re[i+1]!='|' and i<len(re)-1:
                    re = re[:i+1] + '·' + re[i+1:]
                    i = i + 1
            elif re[i] == '*':
                if re[i+1]!=')' and re[i+1]!='*' and re[i+1]!='|' and i<len(re)-1:
                    re = re[:i+1]+ '·' + re[i+1:]
                    i = i + 1
        i = i + 1
    return re
        
def suffix_re(re):
    po = []
    postr = ""
    for i in re:
        if i!='(' and i!=')' and i!='*' and i!='|' and i!='·':
            postr = postr + i
        else:
            if len(po)==0:
                po.append(i)
            elif i=='(':
                po.append(i)
            elif i==')':
                while po[len(po)-1]!='(':
                    postr = postr + po[len(po)-1]
                    po.pop(-1)
                po.pop(-1)
            elif i=='*':
                while len(po)!=0 and po[len(po)-1]=='*':
                    postr = postr + po[len(po)-1]
                    po.pop(-1)
                po.append(i)
            elif i=='·':
                while len(po)!=0 and (po[len(po)-1]=='·' or po[len(po)-1]=='*'):
                    postr = postr + po[len(po)-1]
                    po.pop(-1)
                po.append(i)
            elif i=='|':
                while len(po)!=0 and (po[len(po)-1]=='·' or po[len(po)-1]=='*' or po[len(po)-1]=='|'):
                    postr = postr + po[len(po)-1]
                    po.pop(-1)
                po.append(i)

    while len(po)!=0:
        postr = postr + po[len(po)-1]
        po.pop(-1)

    return postr

def NFA_re(re):
    for i in re:
        if i!='*' and i!='|' and i!='·':  #如果i为非运算符
            Nnfa1 = State(State.num, True, False) #创建节点，压入nfa栈中
            State.num = State.num + 1             #num++
            Nnfa2 = State(State.num, False, True)
            State.num = State.num + 1
            Tran = Connection(i)
            Tran._to = Nnfa2
            Nnfa1._con.append(Tran)                     #给Nnfa1和Nnfa2建立联系
            nfa.append(Nnfa1)

        else:   #如果i为运算符
            if i == '*':
                #取出栈内一个nfa进行*操作
                Nnfa = nfa[len(nfa) - 1]
                Nnfa.start = False
                #遍历找到栈内Nnfa的accepted状态
                Nnfa_end = Findend(Nnfa)
                Nnfa_end.accepted = False
                Nnfa1 = State(State.num, True, False)
                State.num = State.num + 1
                Nnfa2 = State(State.num, False, True)
                State.num = State.num + 1
                #创建连接线
                Tran1 = Connection('null')
                Tran1._to = Nnfa
                Nnfa1._con.append(Tran1)
                Tran2 = Connection('null')
                Tran2._to = Nnfa2
                Nnfa1._con.append(Tran2)
                Tran3 = Connection('null')
                Tran3._to = Nnfa2
                Tran4 = Connection('null')
                Tran4._to = Nnfa
                Nnfa_end._con.append(Tran3)
                Nnfa_end._con.append(Tran4)
                nfa.pop(-1)
                nfa.append(Nnfa1)
            elif i == '·':
                #取出两个state，进行连接操作
                Nnfax = nfa[len(nfa) - 2]
                Nnfay = nfa[len(nfa) - 1]
                Nnfax_end = Findend(Nnfax)
                Nnfay.start = False
                Nnfax_end.accepted = False
                Tran = Connection('null')
                Tran._to = Nnfay
                Nnfax_end._con.append(Tran)
                nfa.pop(-1)
                nfa.pop(-1)
                nfa.append(Nnfax)
            elif i == '|':
                #取出两个state，进行或操作，首先取消标记
                Nnfax = nfa[len(nfa) - 2]
                Nnfay = nfa[len(nfa) - 1]
                Nnfax_end = Findend(Nnfax)
                Nnfay_end = Findend(Nnfay)
                Nnfax.start = False
                Nnfay.start = False
                Nnfax_end.accepted = False
                Nnfay_end.accepted = False
                #创建新状态
                Nnfa1 = State(State.num, True, False)
                State.num = State.num + 1
                Nnfa2 = State(State.num, False, True)
                State.num = State.num + 1
                #创建连接线
                Tran1x = Connection('null')
                Tran1y = Connection('null')
                Tranx2 = Connection('null')
                Trany2 = Connection('null')
                Tran1x._to = Nnfax
                Tran1y._to = Nnfay
                Tranx2._to = Nnfa2
                Trany2._to = Nnfa2
                Nnfa1._con.append(Tran1x)
                Nnfa1._con.append(Tran1y)
                Nnfax_end._con.append(Tranx2)
                Nnfay_end._con.append(Trany2)
                #出栈入栈操作
                nfa.pop(-1)
                nfa.pop(-1)
                nfa.append(Nnfa1)
    return
    
def Findend(nfa):
    if nfa.accepted == True:
        return nfa
    i = 0
    while i<= len(nfa._con)-1:
        return Findend(nfa._con[i]._to)
        i = i + 1

#输出nfa，同时为下一步dfa生成做进一步准备
def printf(nfa):
    i = 0
    if nfa.id_num == 5:
        print("yyr", len(nfa._con))
        print(nfa.accepted)
    while i<= len(nfa._con)-1:
        if nfa._con[i].ch == 'null':
            nfanull_tmp.append([nfa.id_num, nfa._con[i]._to.id_num])
            #加入nfanull列表
        else:
            nfach_tmp.append([nfa.id_num, nfa._con[i].ch, nfa._con[i]._to.id_num])
        print(nfa.id_num, nfa._con[i].ch, nfa._con[i]._to.id_num) 
        NFAdot.edge(str(nfa.id_num), str(nfa._con[i]._to.id_num), nfa._con[i].ch)
        if nfa._con[i].vis == False:
            nfa._con[i].vis = True
            printf(nfa._con[i]._to)
            nfa._con[i].vis == False
        i = i + 1

'''
18.11.8
0.找出任意一点为开始的所有e-闭包
1.遍历nfa，找出起点的e-闭包，记作初始dfa
2.查找其他dfa（初始，或其他状态dfa经过输入符号后产生的状态以及e-合并后的状态）
3.压缩dfa
4.图形化

1.nfa结构
id_num： id号
start：是否为nfa的start状态
accepted：是否为nfa的accepted状态
_con：记录连接线

connection：
ch：连接字母
_to：到哪个点

dfa：
id_num
start
accepted
_to
represent：代表点的集合
'''

def DFA_NFA(nfa):
    firstdfa = dfaState(dfaState.dfanum, True)
    tmp = nfanull[nfa.id_num]
    tmp.append(nfa.id_num)
    firstdfa.represent = list(set(tmp))    #构建初始dfa
    flag = False
    for i in firstdfa.represent:
        for j in nfa_acc:
            if i == j:
                flag = True
                break
    firstdfa.accepted = flag
    if flag == True:
        firstdfa.groupID = 1
        
    dfa.append(firstdfa)
    dfaState.dfanum = dfaState.dfanum + 1
    point = 0
    #    根据初始dfa的represent顺序找到DFA M‘
    while point < len(dfa):
        dict = {}
        for i in dfa[point].represent:
        #第一个为6号节点为例，指向6，4，7，那么分别扫描6，4，7号节点的全部_con.ch，构建接下来的dfa
            for j in nfach:
                if i == j[0]:
                    if j[1] in dict:
                        dict[j[1]].append(j[2])
                    else:
                        dict[j[1]] = []
                        dict[j[1]].append(j[2])
                    
        #如果dict内指向的列表不在dfa中则添加进入dfa中
        for i in dict:
            tmp = []
            for kk in dict[i]:
                tmp.append(kk)
                for ll in nfanull[kk]:
                    tmp.append(ll)
            tmp = list(set(tmp))
            
            pos = -1
            for j in range(len(dfa)):
                if dfa[j].represent == tmp:
                    pos = j
                    break
            if pos == -1:
                #添加(i,dict(i))进入dfa
                newdfa = dfaState(dfaState.dfanum, False)
                #represent = dict[i]的全部e-闭包
                
                newdfa.represent = tmp    
                
                flag = False
                for ii in newdfa.represent:
                    for jj in nfa_acc:
                        if ii == jj:
                            flag = True
                            break
                            
                newdfa.accepted = flag
                if flag == True:
                    newdfa.groupID = 1
                dfa[point]._con.append([i, dfaState.dfanum])
                dfa.append(newdfa)
                dfaState.dfanum = dfaState.dfanum + 1
                
            else:
                #[ch = i, next = pos]
                dfa[point]._con.append([i, pos])
            
        point = point + 1
                    
'''
        i = 0
        while i<= len(nfa._con)-1:
            ch = nfa._con[i].ch
            if ch == 'null':
                continue
            minidfa = []
            for i in 
            minidfa.append(pathch(nfa, ch))
            #如果字典没查到 +1 查到 不变
            i = i + 1
'''

def SIMPFY_DFA():
    #如果在同组 而且经过元素也在同组 就不用分割 否则分割
    group = []
    lastgroup = [8]
    n = 1
    while n < 100000:
        group = []
        tmpgid = []
        gcount = -1
        for i in dfa:
            tmp = []
            tmp.append(i.groupID)
            for j in i._con:
                x = j[0]
                y = dfa[j[1]].groupID
                tmp.append([x, y])
            if tmp not in group:
                group.append(tmp)
                gcount = gcount + 1
                tmpgid.append(gcount)
            else:
                for k in range(len(group)):
                    if tmp == group[k]:
                        tmpgid.append(k)
                        break
                    
        for i in range(len(dfa)):
            dfa[i].groupID = tmpgid[i]
        
        if lastgroup == group:
            break
        lastgroup = group
        n = n + 1
      
    print()
    for i in dfa:
        print(i.id_num,i.start,i.accepted,i._con,i.represent,i.groupID)    
    #分组已出，以下是完成合并
    group = []
    for i in dfa:
        if i.groupID not in group:
            m_dfa.append(i)
            group.append(i.groupID)
        else:
            k = i.id_num
            l = i.groupID
            for ii in m_dfa:
                for jj in ii._con:
                    if jj[1] == k:
                        jj[1] = l
            
            for ii in dfa:
                for jj in ii._con:
                    if jj[1] == k:
                        jj[1] = l

if __name__ == '__main__':
    re = input("Please input an RE:")
    re = point_re(re)    #加点
    print(re)
    re = suffix_re(re)   #变后缀表达式
    print(re)
#    re = 'ab|*ab|*·aa·bb·|cc·|*·d|'
    NFA_re(re)           #后缀表达式变NFA
    
    NFAdot = Digraph(comment='NFA')
    for i in range(State.num):
        k = str(i)
        NFAdot.node(k, k)
    printf(nfa[0])
    NFAdot.view()
    NFAdot.render('dfa/NFA.gv', view=True)

    nfanull_tmp.sort(key = lambda s:(s[0],s[1]))
    #去重操作，同时构建nfanull以及nfach，简化数据结构，便于dfa统计
    for i in nfanull_tmp:
        if i not in nfanull:
            nfanull.append(i)
            
    k = 0
    nnn = []
    for i in range(State.num):
        tmp = []
        while k < len(nfanull) and nfanull[k][0] == i:
            tmp.append(nfanull[k][1])
            k = k + 1
        nnn.append(tmp)
    
    nfanull = nnn
    print(nfanull)
    
    #查找每个state的e-闭包
    nnn = []
    for i in range(State.num):
        j = 0
        tmp = nfanull[i]
        while j < len(tmp):
            for k in nfanull[tmp[j]]:
                
                flag = False
                for kk in tmp:
                    if kk == k:
                        flag = True
                        break
                if flag == False:
                    tmp.append(k)
                    
            j = j + 1
        tmp = list(set(tmp))
        nnn.append(tmp)
    
    nfanull = nnn
    print(nfanull)
    
    nfach_tmp.sort(key = lambda s:(s[0],s[2]))
       
    for i in nfach_tmp:
        if i not in nfach:
            nfach.append(i)
    print(nfach)
    
    for i in range(State.num):
        nfa_acc.append(i)
        
    for i in range(State.num):
        if len(nfanull[i]) > 0:
            nfa_acc.remove(i)
            
    for i in range(len(nfach)):
        nfa_acc.remove(nfach[i][0])
    print("nfa_acc =", nfa_acc)
    
    DFA_NFA(nfa[0])      #NFA变DFA
    
    print()
    print("len DFA M* =", len(dfa))
    for i in dfa:
        print(i.id_num,i.start,i.accepted,i._con,i.represent,i.groupID)
        
    DFAdot = Digraph(comment='DFA')
    for i in range(len(dfa)):
        s = ""
        for j in dfa[i].represent:
            s = s + str(j) + " "
        s.rstrip()
        DFAdot.node(str(i), s)

    for i in dfa:
        for j in i._con:
            DFAdot.edge(str(i.id_num), str(j[1]), j[0])
    DFAdot.view()
    DFAdot.render('dfa/DFA.gv', view=True)
        
    
    SIMPFY_DFA()         #简化DFA
    print()
    for i in m_dfa:
        print(i.id_num,i.start,i.accepted,i._con,i.represent,i.groupID) 
        
    MDFAdot = Digraph(comment='M_DFA')
    for i in range(len(m_dfa)):
        s = ""
        for j in m_dfa[i].represent:
            s = s + str(j) + " "
        s.rstrip()
        MDFAdot.node(str(m_dfa[i].id_num), s)

    for i in m_dfa:
        for j in i._con:
            MDFAdot.edge(str(i.id_num), str(j[1]), j[0])
    MDFAdot.view()
    MDFAdot.render('dfa/M_DFA.gv', view=True)