using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 科学计算器
{
    public partial class Form1 : Form
    {
        string calstr,vstr,ans;
        string[] temp = new string[1000];
        int calp=0, vp=0,tmpnum=0,calflag=0,cal0=0,v0=0;

        public class S
        {
            int kind;  //相当于优先级 
            double num;  // 
            char p;
            public S()
            {
                kind = 0;
                num = 0;
                p = (char)1;
            }
            public void kindgai(int i)
            {
                kind = (short)i;
            }
            public void numgai(double i)
            {
                num = i;
            }
            public void chgai(char c)
            {
                p = c;
            }
            public int getkind()
            {
                return kind;
            }
            public double getnum()
            {
                return num;
            }
            public char getp()
            {
                return p;
            }
        };

        void calc(string ev)
        {
            S[] s1=new S[100];
            S[] s2 = new S[100];    //设置两个栈，1为数字栈，2为临时符号栈，逆序波兰式存到s1
            for(int i=0;i<100;i++)
            {
                s1[i] = new S();
                s2[i] = new S();
            }
            int len;
            len = ev.Length; 
            char[] eva = ev.ToCharArray();  //行读入，按字符手动操作 
            char ch; int p1 = 0, p2 = 0, kind1 = -1,ks=0,ws=0;  //p1为s1的栈顶坐标，p2为s2的栈顶坐标，n为临时存放的数，kind为临时存放的ch对应的符号类型 
            for (int i = 0; i < len; i++)
            {
                ch = eva[i];
                if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch=='^')
                {
                    if (ws != 0)
                    {
                        string sss = ev.Substring(ks, ws).ToString();
                        double ddd = Convert.ToDouble(sss);
                        p1 = p1 + 1;
                        s1[p1].kindgai(5);
                        s1[p1].numgai(ddd);               //遇到符号时首先判断n是否为0，若不为0则把n入栈后清零，在这里把数的优先级设为5 

                        ks = ks + ws+1;
                        ws = 0;
                    }
                    else { ks = ks + 1; }
                    if (ch == '+' || ch == '-') kind1 = 1;
                    if (ch == '*' || ch == '/') kind1 = 2;  //手动设定优先级 
                    if (ch == '^') kind1 = 3;
                    if (p2 == 0)
                    {
                        p2 = p2 + 1;
                        s2[p2].kindgai(kind1);
                        s2[p2].chgai(ch);
                        continue;                   //若符号栈为空，则强制把符号入栈 
                    }
                    if (ch == '(')
                    {
                        p2 = p2 + 1;
                        s2[p2].kindgai(4);
                        s2[p2].chgai(ch);   //若ch为左括号，则强制压入s2栈 
                    }
                    else if (ch == ')')
                    {
                        while (s2[p2].getp() != '(')
                        {
                            p1 = p1 + 1;
                            s1[p1].kindgai(s2[p2].getkind());
                            s1[p1].numgai(s2[p2].getnum());
                            s1[p1].chgai(s2[p2].getp());
                            s2[p2].kindgai(0); s2[p2].numgai(-1); s2[p2].chgai((char)0);  //若ch为右括号，则把从上一个左括号开始到这个右括号的全部符号压入s1中，同时清理s2栈 
                            p2 = p2 - 1;
                        }
                        s2[p2].kindgai(0);
                        s2[p2].chgai((char)0);
                        p2 = p2 - 1;
                    }
                    else if (s2[p2].getp() == '(')
                    {
                        p2 = p2 + 1;
                        s2[p2].kindgai(kind1);           //若栈顶为左括号，则强制压ch入s2栈 
                        s2[p2].chgai(ch);
                    }
                    else if (kind1 < s2[p2].getkind())
                    {
                        if (s2[p2].getp() != '(')
                        {
                            while (kind1 <= s2[p2].getkind() && s2[p2].getp() != '(' && p2 != 0)
                            {
                                p1 = p1 + 1;
                                s1[p1].kindgai(s2[p2].getkind());
                                s1[p1].numgai(s2[p2].getnum());
                                s1[p1].chgai(s2[p2].getp());
                                s2[p2].kindgai(0); s2[p2].numgai(-1); s2[p2].chgai((char)0);  //若ch符号优先级小于栈顶符号优先级且栈顶不为左括号则把s2中的符号压入s1中，并重复此操作，直到ch优先级大于s2的栈顶优先级 
                                p2 = p2 - 1;
                            }
                            p2 = p2 + 1;
                            s2[p2].kindgai(kind1);                            //最后把ch压入s2 
                            s2[p2].chgai(ch);
                        }
                    }
                    else
                    {
                        p2 = p2 + 1;
                        s2[p2].kindgai(kind1);                                //若没有达到以上条件，则把ch压入s2 
                        s2[p2].chgai(ch);
                    }
                }
                if ((ch >= '0' && ch <= '9') || (ch=='.'))
                {
           //         n = n * 10;
           //         n = n + ch - 48;                                           //如果ch为数字则暂时存入n中
                    ws++;
           //         MessageBox.Show("ws="+ws.ToString()+" ks="+ks.ToString());
                }
                if (i == len - 1)
                {
                    if (ws != 0)
                    {
                        p1 = p1 + 1;
                        string sss = ev.Substring(ks, ws).ToString();
                        double ddd = Convert.ToDouble(sss);
                        s1[p1].kindgai(5);                                   //对于最后一次操作要进行特殊处理，先放数字再把s2的全部内容压入s1中 
                        s1[p1].numgai(ddd);
                        s1[p1].chgai((char)0);
                    }
                    while (p2 != 0)
                    {
                        p1 = p1 + 1;
                        s1[p1].kindgai(s2[p2].getkind());
                        s1[p1].numgai(s2[p2].getnum());
                        s1[p1].chgai(s2[p2].getp());
                        p2 = p2 - 1;
                    }
                }
            }

          /*string sc="";
            for (int i = 1; i <= p1; i++)
            {
                if (s1[i].getkind() == 5) sc+=s1[i].getnum().ToString(); else sc+=s1[i].getp().ToString();  //输出逆序波兰式 
            }*/

            double[] s3 = new double[100];
            int p = 1;
            s3[1] = s1[1].getnum();
            for (int i = 2; i <= p1; i++)
            {
                if (s1[i].getkind() == 5)
                {
                    p = p + 1;
                    s3[p] = s1[i].getnum();
                }
                else
                {
                    if (s1[i].getp() == '+') s3[p - 1] = s3[p - 1] + s3[p];
                    if (s1[i].getp() == '-') s3[p - 1] = s3[p - 1] - s3[p];
                    if (s1[i].getp() == '*') s3[p - 1] = s3[p - 1] * s3[p];             //引入s3栈，计算逆序波兰式的值 
                    if (s1[i].getp() == '/') s3[p - 1] = s3[p - 1] / s3[p];
                    if (s1[i].getp() == '^') s3[p - 1] = System.Math.Pow(s3[p - 1], s3[p]);
                    s3[p] = 0;
                    p = p - 1;
                }
            }
            string ss=s3[1].ToString();
            ans = ss;
            calflag = 1;
            textBox1.Text = vstr+"="+ans;
            return;
        }
    
        void numadd(string tmpstr)
        {
    //        if (!(cal0 == 1 && tmpstr=="0" && calstr.Substring(calstr.Length)=="0"))
      //      {
                calstr = cstradd(tmpstr);
      //      }
      //      if (!(v0 == 1 && tmpstr=="0" && vstr.Substring(vstr.Length)=="0"))
      //      {
                vstr = vstradd(tmpstr);
      //      }
            if(vstr=="")
            {
                textBox1.Text = "0";
            }
            else textBox1.Text = vstr;
        }

        void opeadd(string tmpstr)
        {
            if (calstr.Length == 0 && (tmpstr == "+" || tmpstr == "*" || tmpstr == "/")) return;
            if(calstr.Length==0 && tmpstr=="-")
            {
                calstr = cstradd(tmpstr);
                vstr = vstradd(tmpstr);
                cal0 = 0;
                v0 = 0;
                calp = calstr.Length;
                vp = vstr.Length;
                textBox1.Text = vstr;
                return;
            }
            if (tmpstr=="(" || tmpstr==")" ||(calstr[calstr.Length - 1] >= '0' && calstr[calstr.Length - 1] <= '9') || calstr[calstr.Length - 1] == '(' || calstr[calstr.Length - 1] == ')')
            {
                calstr = cstradd(tmpstr);
                vstr = vstradd(tmpstr);
            }
            cal0 = 0;
            v0 = 0;
            calp = calstr.Length;
            vp = vstr.Length;
            textBox1.Text = vstr;
        }
        string cstradd(string str1)
        {
            string tmpstr=calstr+str1;
            if (str1 != "0") cal0 = 1;
            return tmpstr;
        }
        string vstradd(string str1)
        {
            string tmpstr = vstr + str1;
            if (str1 != "0") v0 = 1;
            return tmpstr;
        }

        private void Form1_KeyPress(object sender, KeyPressEventArgs e)
        {
            switch (e.KeyChar)
            {
                case '0':
                    numadd("0"); break;
                case '1':
                    numadd("1"); break;
                case '2':
                    numadd("2"); break;
                case '3':
                    numadd("3"); break;
                case '4':
                    numadd("4"); break;
                case '5':
                    numadd("5"); break;
                case '6':
                    numadd("6"); break;
                case '7':
                    numadd("7"); break;
                case '8':
                    numadd("8"); break;
                case '9':
                    numadd("9"); break;
                case '+':
                    opeadd("+"); break;
                case '-':
                    opeadd("-"); break;
                case '*':
                    opeadd("*"); break;
                case '/':
                    opeadd("/"); break;
                case '(':
                    opeadd("("); break;
                case ')':
                    opeadd(")"); break;
                case (char)13:
                    calc(calstr); break;
                case '.':
                    numadd("."); break;
                case '^':
                    opeadd("^"); break;

            }
        }

        private void button23_Click(object sender, EventArgs e)
        {
            numadd("5");
        }

        private void button22_Click(object sender, EventArgs e)
        {
            numadd("4");
        }

        private void button17_Click(object sender, EventArgs e)
        {
            numadd("7");
        }

        private void button18_Click(object sender, EventArgs e)
        {
            numadd("8");
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button19_Click(object sender, EventArgs e)
        {
            numadd("9");
        }

        private void button27_Click(object sender, EventArgs e)
        {
            numadd("1");
        }

        private void button28_Click(object sender, EventArgs e)
        {
            numadd("2");
        }

        private void button30_Click(object sender, EventArgs e)
        {
            opeadd("+");
        }

        private void button25_Click(object sender, EventArgs e)
        {
            opeadd("-");
        }

        private void button20_Click(object sender, EventArgs e)
        {
            opeadd("*");
        }

        private void button31_Click(object sender, EventArgs e)
        {
            opeadd("(");
        }

        private void button32_Click(object sender, EventArgs e)
        {
            opeadd(")");
        }

        private void button13_Click(object sender, EventArgs e)
        {
            calstr = "";
            vstr = "";
            calp = 0; vp = 0; cal0 = 0; v0 = 0;
            textBox1.Text = "0";
        }

        private void button12_Click(object sender, EventArgs e)
        {
            calstr = calstr.Substring(0, calp);
            vstr = vstr.Substring(0, vp);
            cal0 = 0;v0 = 0;
            textBox1.Text = vstr;
            if (vstr == "") textBox1.Text = "0";
        }

        private void button21_Click(object sender, EventArgs e)
        {
            calstr = calstr + System.Math.E.ToString();
            vstr = vstr + System.Math.E.ToString();
            textBox1.Text = vstr;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button26_Click(object sender, EventArgs e)
        {
            if(ans!="")
            {
                tmpnum++;
                temp[tmpnum] = ans;
                comboBox2.Items.Add(ans);
            }
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button14_Click(object sender, EventArgs e)
        {
            calstr = calstr + comboBox2.Text;
            vstr = vstr + comboBox2.Text;
            textBox1.Text = vstr;
        }

        private void button16_Click(object sender, EventArgs e)
        {
            calstr = calstr + System.Math.PI.ToString();
            vstr = vstr + System.Math.PI.ToString();
            textBox1.Text = vstr;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string tmp = "";
            tmp = calstr.Substring(calp);
            double ddd = Convert.ToDouble(tmp);
            ddd = ddd * ddd;
            tmp = ddd.ToString();
            calstr = calstr.Substring(0, calp);
            vstr = vstr.Substring(0, vp);
            calstr = calstr + ddd;
            vstr = vstr + ddd;
            textBox1.Text = vstr;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            /*     string tmp = "",tmp1="";
                 tmp = calstr.Substring(calp);
                 double ddd = Convert.ToDouble(tmp),ddd1;

                 tmp = ddd.ToString();
                 calstr = calstr.Substring(0, calp);
                 vstr = vstr.Substring(0, vp);
                 calstr = calstr + ddd;
                 vstr = vstr + ddd;
                 textBox1.Text = vstr;*/
            opeadd("^");
        }

        private void button6_Click(object sender, EventArgs e)
        {
            string tmp = "";
            tmp = calstr.Substring(calp);
            double ddd = Convert.ToDouble(tmp);
            ddd = System.Math.Pow(ddd, 0.5);
            tmp = ddd.ToString();
            calstr = calstr.Substring(0, calp);
            vstr = vstr.Substring(0, vp);
            calstr = calstr + ddd;
            vstr = vstr + ddd;
            textBox1.Text = vstr;
        }

        private void button8_Click(object sender, EventArgs e)
        {
            string tmp = "";
            tmp = calstr.Substring(calp);
            double ddd = Convert.ToDouble(tmp);
            ddd = System.Math.Pow(10,ddd);
            tmp = ddd.ToString();
            calstr = calstr.Substring(0, calp);
            vstr = vstr.Substring(0, vp);
            calstr = calstr + ddd;
            vstr = vstr + ddd;
            textBox1.Text = vstr;
        }

        private void button9_Click(object sender, EventArgs e)
        {
            string tmp = "";
            tmp = calstr.Substring(calp);
            double ddd = Convert.ToDouble(tmp);
            ddd = System.Math.Log10(ddd);
            tmp = ddd.ToString();
            calstr = calstr.Substring(0, calp);
            vstr = vstr.Substring(0, vp);
            calstr = calstr + ddd;
            vstr = vstr + ddd;
            textBox1.Text = vstr;
        }

        private void button10_Click(object sender, EventArgs e)
        {
            string tmp = "";
            tmp = calstr.Substring(calp);
            double ddd = Convert.ToDouble(tmp);
            ddd = System.Math.Log(ddd);
            tmp = ddd.ToString();
            calstr = calstr.Substring(0, calp);
            vstr = vstr.Substring(0, vp);
            calstr = calstr + ddd;
            vstr = vstr + ddd;
            textBox1.Text = vstr;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string tmp = "";
            tmp = calstr.Substring(calp);
            double ddd = Convert.ToDouble(tmp);
            ddd = System.Math.Sin(ddd);
            tmp = ddd.ToString();
            calstr = calstr.Substring(0, calp);
            vstr = vstr.Substring(0, vp);
            calstr = calstr + ddd;
            vstr = vstr + ddd;
            textBox1.Text = vstr;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            string tmp = "";
            tmp = calstr.Substring(calp);
            double ddd = Convert.ToDouble(tmp);
            ddd = System.Math.Cos(ddd);
            tmp = ddd.ToString();
            calstr = calstr.Substring(0, calp);
            vstr = vstr.Substring(0, vp);
            calstr = calstr + ddd;
            vstr = vstr + ddd;
            textBox1.Text = vstr;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            string tmp = "";
            tmp = calstr.Substring(calp);
            double ddd = Convert.ToDouble(tmp);
            ddd = System.Math.Tan(ddd);
            tmp = ddd.ToString();
            calstr = calstr.Substring(0, calp);
            vstr = vstr.Substring(0, vp);
            calstr = calstr + ddd;
            vstr = vstr + ddd;
            textBox1.Text = vstr;
        }

        private void button7_Click(object sender, EventArgs e)
        {
            string tmp = "";
            tmp = calstr.Substring(calp);
            double ddd = Convert.ToDouble(tmp);
            ddd = System.Math.Exp(ddd);
            tmp = ddd.ToString();
            calstr = calstr.Substring(0, calp);
            vstr = vstr.Substring(0, vp);
            calstr = calstr + ddd;
            vstr = vstr + ddd;
            textBox1.Text = vstr;
        }

        private void button34_Click(object sender, EventArgs e)
        {
            numadd(".");
        }

        private void button15_Click(object sender, EventArgs e)
        {
            opeadd("/");
        }

        private void button35_Click(object sender, EventArgs e)
        {
            calc(calstr);
        }

        private void D0_Click(object sender, EventArgs e)
        {
            numadd("0");
        }

        private void button29_Click(object sender, EventArgs e)
        {
            numadd("3");
        }

        public Form1()
        {
            InitializeComponent();
            calstr = "";
            vstr = "";
            calp = 0;
            vp = 0;
            textBox1.Text = "0";
        }

        private void button24_Click(object sender, EventArgs e)
        {
            numadd("6");
        }
    }
}
