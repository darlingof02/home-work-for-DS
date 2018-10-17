#include "my_stack.h"

class bds
{
private:
    string A;
public:
    bds(string a);
    void valuate();
    ~bds(){};
    friend double calulate(double x, double y, char c);
    friend bool isop(char c);
    friend int priority(char c);
    friend void compute(my_stack<double> &num, my_stack<char> &op);
};


bds::bds(string a) {
    A = a;
}

double calulate(double x, double y, char c)
{
    switch (c)
    {
        case '+':
            return x+y;
        case '-':
            return x-y;
        case '/':
            return x/y;
        case '*':
            return x*y;
    }
}

void compute(my_stack<double> &num, my_stack<char> &op)
{
    double x, y;
    char c1;
    num.pop(x);
    num.pop(y);
    op.pop(c1);
    double result = calulate(y, x, c1);
    num.push(result);
}

bool isop(char c)
{
    return (c=='+'||c=='-'||c=='/'||c=='*'||c=='('||c==')');
}

int priority(char c)
{
    int num=-10;
    switch (c)
    {
        case '+':
        case '-':
            num=1;
            break;
        case '*':
        case '/':
            num=2;
            break;
        case '(':
        case ')':
            num=0;
        default:
            num=-1;
    }
    return num;
}

void bds::valuate() {
    my_stack<double> num;
    my_stack<char> op;
    string str1;
    str1.clear();
    char c = '#';
    op.push(c);
    for(int i=0; i<A.length()-1; i++)
    {
        if(A[i] == '(')
        {
            op.push(A[i]);
        }
        else if(A[i] == ')')
        {
            while(op.Top() != '(')
            {
                double x, y;
                char c1;
                num.pop(x);
                num.pop(y);
                op.pop(c1);
                double result = calulate(y, x, c1);
                num.push(result);
            }
            char rub;
            op.pop(rub);
        }
        else if(isop(A[i]))
        {
            if(priority(A[i]) > priority(op.Top()))
            {
                op.push(A[i]);
            }
            else
            {
                while(priority(op.Top()) >= priority(A[i]))
                {
                    double x, y;
                    char c1;
                    num.pop(x);
                    num.pop(y);
                    op.pop(c1);
                    double result = calulate(y, x, c1);
                    num.push(result);
                }
                op.push(A[i]);
            }
        }
        else
        {
            str1 += A[i];
            if(i<A.length()-1 && (isop(A[i+1])||A[i+1] == '='))
            {
                double x = atof(str1.c_str());
                num.push(x);
                str1.clear();
            }
        }
    }
    while(op.Top() != '#')
    {
        double x, y;
        num.pop(x);
        num.pop(y);
        char c;
        op.pop(c);
        double result = calulate(y,x,c);
        num.push(result);
    }
    cout<<"结果为:"<<num.Top()<<endl;
}

int main()
{
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    string strp;
    cout<<"请输入一个表达式（不含负数，小数）:";
    cin>>strp;
    bds a(strp);
    a.valuate();
    return 0;
}