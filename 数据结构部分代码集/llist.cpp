//c++ class简单应用 部分采用vector容器
//输入输出文件同一个，只存数值 采用c++流输入与保存 提示行输出

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

const int maxnum = 20001;

class linearlist
{
    public:
        linearlist();
        ~linearlist();
        bool check(int pos) const;  //检查pos是否合法
        void add(int x);            //线性表末位添加数
        void add0(int x);
        int get(int pos) const;     //获得该位置数值
        void ins(int pos, int x);   //pos后插入数值x
        void del(int pos);          //删除指定位置数值
        void delsp(int x);          //删除全部指定数值
        void set(int pos, int x);   //把指定位置数值修改为x
        void search(int x) const;   //查找某数
        void print() const;         //输出线性表
        int size() const;           //返回线性表大小
        void showmenu() const;      //输出菜单
        bool try0(int n);
        void setsize(int n);
    
    private:
        vector <int> list;          //使用vector容器模拟变长操作
        int total;
        int n;
};

linearlist::linearlist()
{
    total=0;
}

linearlist::~linearlist()           //析构函数,类周期结束前进行文件保存
{
    char c;
    cout<<"是否保存记录,保存请输入y"<<endl;
    cin>>c;
    if(c=='y')
    {
        ofstream output;
        output.open("/Users/CP/Desktop/135246/170308/170308/1.txt");
        for(int i=1;i<=size();i++)
            output<<list[i]<<" ";
        cout<<"记录已保存,供下次使用";
        output.close();
    }
    else cout<<"记录不保存";
    cout<<endl<<"程序退出";
}

void linearlist::setsize(int n)
{
    list.resize(n);
    total=n;
}

int linearlist::get(int pos) const
{
    if(check(pos)) return list[pos];
    return -1;
}

bool linearlist::check(int pos) const
{
    if(pos>total || pos<1)
    {
        cout<<"操作失败!"<<endl;
        return false;
    }
    cout<<"操作成功!"<<endl;
    return true;
}

void linearlist::add(int x)
{
    if(total==maxnum)
    {
        cout<<"队列已满,操作失败!"<<endl;
        return;
    }
    total++;
    list.resize(total+1);
    list[total]=x;
    cout<<"操作成功!"<<endl;
}

void linearlist::add0(int x)
{
    if(total==maxnum)
    {
        cout<<"队列已满!"<<endl;
        return;
    }
    total++;
    list.resize(total+1);
    list[total]=x;
}

void linearlist::set(int pos, int x)
{
    if(check(pos))
        list[pos]=x;
}

void linearlist::ins(int pos, int x)
{
    if(check(pos))
    {
        list.resize(total+2);
        for(int i=total;i>pos;i--) list[i+1]=list[i];
        list[pos]=x;
        total++;
    }
}

void linearlist::del(int pos)
{
    if(check(pos))
    {
        for(int i=pos+1;i<=total;i++) list[i-1]=list[i];
        list[total]=0;
        total--;
    }
}

void linearlist::delsp(int x)
{
    int i,j=0;
    for(i=1;i<=total;i++)
    {
        if(list[i]!=x)
        {
            j++;
            list[j]=list[i];
        }
    }
    for(i=j+1;i<=total;i++) list[i]=0;
    total=j;
    if(i==j) cout<<"没有找到要删除的数!";
    if(i!=j) cout<<"删除成功!";
    cout<<endl;
}

void linearlist::search(int x) const
{
    cout<<"要查找的数在以下位置：";
    for(int i=1;i<=total;i++)
    {
        if(list[i]==x) cout<<i<<" ,";
    }
    cout<<endl;
}

void linearlist::print() const
{
    cout<<"线性表中共有"<<total<<"个数， 分别是: ";
    for(int i=1;i<=total;i++) cout<<list[i]<<" ";
    cout<<endl;
}

int linearlist::size() const
{
    return total;
}

void linearlist::showmenu() const
{
    cout<<"1:添加一个数到末位 2:删除指定位置的数 20:删除线性表中指定数 3:插入到指定位置之后一个数 4:获得指定位置的数 5:设置指定位置的数 6:输出线性表 7:排序 8:查找指定数 9:显示帮助 0:退出程序"<<endl;
}

bool linearlist::try0(int n)
{
    int x,pos;
    switch(n)
    {
        case 0:
        {
            return false;
        }
        case 1:
        {
            cout<<"请输入要添加的数x:";
            cin>>x;
            add(x);
            break;
        }
        case 2:
        {
            cout<<"请输入要删除的指定位置pos:";
            cin>>pos;
            del(pos);
            break;
        }
        case 3:
        {
            cout<<"请先后输入要插入的位置pos和要插入的数x:";
            cin>>pos>>x;
            ins(pos,x);
            break;
        }
        case 4:
        {
            cout<<"请输入您要获得的数的指定位置:";
            cin>>pos;
            cout<<"您要获得的数是:"<<get(pos)<<endl;
            break;
        }
        case 5:
        {
            cout<<"请先后输入要设置的位置pos和要插入的数x:";
            cin>>pos>>x;
            set(pos,x);
            break;
        }
        case 6:
        {
            print();
            break;
        }
        case 7:
        {
            sort(list.begin()+1,list.end());
            cout<<"排序成功!"<<endl;
            break;
        }
        case 8:
        {
            cout<<"请输入要查找的数x:";
            cin>>x;
            search(x);
            break;
        }
        case 9:
        {
            showmenu();
            break;
        }
        case 20:
        {
            cout<<"请输入要删除的指定的数x:";
            cin>>x;
            delsp(x);
            break;
        }
        default:
        {
            cout<<"指令错误!"<<endl;
        }
        
    }
    return true;
}

void input(linearlist &ll)
{
    int k;
    ifstream input;
    input.open("/Users/CP/Desktop/135246/170308/170308/1.txt");
    while(input>>k) ll.add0(k);
    input.close();
}

void run()                                          //主函数
{
    int n,i=0;
    linearlist ll;
    input(ll);
    cout<<"线性表构造完成,请输入您要进行的操作:"<<endl;
    ll.showmenu();
    while(i<=1000)
    {
        cin>>n;
        if(!ll.try0(n)) return;
        i++;
        if(i%6==0) ll.showmenu();
    }
    cout<<"操作已执行1000次，程序自动退出";
}

void jiaoji(linearlist A,linearlist B)              //集合求交集
{
    int k=0;
    for(int i=1;i<=A.size();i++)
    {
        for(int j=1;j<=B.size();j++)
        {
            if(A.get(i)==B.get(j))
            {
                k++;
                A.set(k,A.get(i));
                break;
            }
        }
    }
    A.setsize(k);
}

void bingji(linearlist A,linearlist B)              //集合求并集
{
    int k=0;
    A.setsize(A.size()+B.size());
    for(int i=1;i<=A.size();i++)
    {
        for(int j=1;j<=B.size();j++)
        {
            if(A.get(i)==B.get(j))
            {
                break;
            }
            k++;
            A.set(k,A.get(i));
        }
    }
}

int main()
{
    run();
    return 0;
}
