#include <iostream>
#include "dbl_lk_list.h"
#include <string>
#include <fstream>
using namespace std;


//帮助菜单，获取功能页面
void help()
{
    cout << "@:获取当前行数" << endl;
    cout << "R:读取文本文档到缓冲区中，缓冲区内容将丢失" <<endl;
    cout << "W:将缓冲区中文件写入文本文件" <<endl;
    cout << "I:插入一行，行号指向该行" <<endl;
    cout << "D:删除当前行，行号指向下一行" <<endl;
    cout << "F:从开始查找字符串" <<endl;
    cout << "C:替换字符串" <<endl;
    cout << "Q:退出编辑器" <<endl;
    cout << "N:移动到下一行" <<endl;
    cout << "P:移动到上一行" <<endl;
    cout << "B:移动到首行" <<endl;
    cout << "E:移动到行末" <<endl;
    cout << "G:移动到指定行" <<endl;
    cout << "V:显示缓冲区内容" <<endl;
}

//将小写字母转换成大写，以便用户操作
char ToUpper(char c)
{
    if (c>='a' && c<='z')
    {
        return c-('a'-'A');
    }
    else return c;
}

//编辑器的构造
class texteditor{
private:
    DblLinkList<string> textBuffer; //暂时保存的编辑内容，保存在链表各节点
    int curLineNo; //通过改变此值，实现当前行变换
    DblLinkList<string> textUndoBuffer;
    int curUndoLineNo;
    ifstream inFile;   //输入文件指针
    ofstream outFile;  //输出文件指针
    int line;  //记录总行数

    void ReadFile();   //将目标文件中内容读入缓存区
    void WriteFile();  //将缓存区中内容写入目标文件
    void GetLine(int &curL, int &TotalL);  //获取当前行数
    void InsertLine(int pos, string s1);   //将一行内容插入缓存区
    void ShowText();  //将缓存区内容显示出来；
    void DeleteLine(int pos);  //删除选定行
    void FindText();  //查找文本中对应内容
    void ChangeLine();  //将文本中对应内容替换
public:
    texteditor(string infName, string outfName); //编辑器初始化
    void Run();  //编辑器运行
};

//用文件名配合文件指针打开文件，
// 其中ios::in 表示只读操作
// ios::out 表示只写操作
// 给出文件打开失败提示
// 将当前行和总行数置为0 完成初始化
texteditor::texteditor(string infName, string outfName) {
    inFile.open(infName, ios::in);
    if (inFile.is_open()) {}
    else cout << "读入文件打开失败" << endl;
    outFile.open(outfName, ios::out);
    if (outFile.is_open()){}
    else cout << "写入文件打开失败" << endl;
    curLineNo = 0;
    curUndoLineNo = 0;
}


//运行函数，
// 给出功能提示栏，
// 读入用户输入操作，
// 使用switch case 跳转至相应功能
// 值得注意的是当case中定义变量时，
// 应用{}包围，否则将报错
void texteditor::Run() {
    char Command;
    cout << "@:获取当前行数" << endl;
    cout << "R:读取文本文档到缓冲区中，缓冲区内容将丢失" <<endl;
    cout << "W:将缓冲区中文件写入文本文件" <<endl;
    cout << "I:插入一行，行号指向该行" <<endl;
    cout << "D:删除当前行，行号指向下一行" <<endl;
    cout << "F:从开始查找字符串" <<endl;
    cout << "C:替换字符串" <<endl;
    cout << "Q:退出编辑器" <<endl;
    cout << "N:移动到下一行" <<endl;
    cout << "P:移动到上一行" <<endl;
    cout << "B:移动到首行" <<endl;
    cout << "E:移动到行末" <<endl;
    cout << "G:移动到指定行" <<endl;
    cout << "V:显示缓冲区内容" <<endl;
    while (1)
    {
        cout << "请输入要执行的操作" <<endl;
        cin >> Command;
        Command = ToUpper(Command);
        int flag = 1;
        switch (Command)
        {
            //获取行数
            case '@':
            {
                int CurL, TotalL;
                GetLine(CurL, TotalL);
                cout <<"当前总共"<<TotalL<<"行"<<endl;
                cout <<"目前在第"<<CurL<<"行"<<endl;
                break;
            }
            //读入文件
            case 'R':
                ReadFile();
                break;
            //写入文件
            case 'W':
                WriteFile();
                break;
            //插入内容
            case 'I':
                {
                int pos;
                string s1;
                cout << "请输入想插入的位置" << endl;
                cin >> pos;
                getchar();
                cout << "请输入想插入的内容" << endl;
                getline(cin, s1);
                InsertLine(pos, s1);
                break;
                }
            //显示内容
            case 'V':
                ShowText();
                break;
            //删除行
            case 'D':
            {
                int pos;
                cout << "请输入要删除的行" <<endl;
                cin >> pos;
                DeleteLine(pos);
                break;
            }
            //替换内容
            case 'C':
                ChangeLine();
                break;
            //退出编辑
            case 'Q':
                flag = 0;
                inFile.close();
                outFile.close();
                break;
            //获取菜单
            case 'H':
                help();
                break;
            //查找内容
            case 'F':
                FindText();
                break;
            //使用curLineNo加减实现行号变换
            //向上移动行
            case 'N':
                curLineNo ++;
                curLineNo = min(line, curLineNo);
                cout << "当前在第" <<curLineNo<<"行"<<endl;
                break;
            //向下移动行
            case 'P':
                curLineNo --;
                curLineNo = max(1, curLineNo);
                cout << "当前在第" <<curLineNo<<"行"<<endl;
                break;
            //行数置为1
            case 'B':
                curLineNo = 1;
                cout << "回归首行" <<endl;
                break;
            //行数置为末行
            case 'E':
                curLineNo = line;
                cout << "已到行末" <<endl;
                break;
            //改变当前行
            case 'G':
            {
                int mov;
                cout << "请输入想要跳转到的行" <<endl;
                cin >> mov;
                if (mov>line || mov<1)
                {
                    cout << "当前不存在该行" <<endl;
                }
                else {
                    curLineNo = mov;
                }
                break;
            }
            //提示错误信息
            default:
                cout <<"输入错误，按H获得功能页面"<<endl;
        }
        if (!flag) break;
    }
}

//
//getline(char *, string &e)获得文件某行内容，
// 同时将其插入缓存区，
// 当前行加一，总行数加一
// 循环操作实现读入文本，
void texteditor::ReadFile() {
    string text;
    line = curLineNo = 0;
    while(getline(inFile, text))
    {
        textBuffer.Insert(line+1, text);
        line ++;
        curLineNo ++;
    }
}

//遍历链表
//将缓存区内容逐行读入string,
//逐行写入文件
void texteditor::WriteFile() {
    string text;
    DblNode<string> *p = textBuffer.GiveHead();
    p = p->next;
    for (int i = 0; i <textBuffer.Length() ; ++i) {
        outFile<<p->data<<endl;
        p = p->next;
    }
}

//获取当前行数
void texteditor::GetLine(int &CurL, int &TotalL) {
    CurL = curLineNo;
    TotalL = line;
}

//用链表中Insert将内容插入缓存区
//当前行置为插入位置
//总行数加一
void texteditor::InsertLine(int pos, string s1) {
    if (pos > line + 1) {
        cout<<"插入失败"<<endl;
        return;
    }
    else {
        textBuffer.Insert(pos, s1);
        line ++;
        curLineNo = pos;
    }
}

//使用双向链表中Print函数打印全部元素
void texteditor::ShowText() {
    textBuffer.PrintList();
}

//使用链表中Delete函数删除某行
//总行数减一
void texteditor::DeleteLine(int pos) {
    string  s1;
    textBuffer.Delete(pos, s1);
    line --;
}

//先判断用户开始查找的位置，
// 再在编辑器中遍历行，使用getline(int pos,string &e)
// 读入每行内容，
// 再使用string类中find函数，
// 用npos判断是否找到，否则返回找到的位置
void texteditor::FindText() {
    char answer;
    bool initialResponse = true;
    do {
        if (initialResponse)
        {
            cout << "从第1行开始F(irst)或从当前行开始C(urrent):" << endl;
        }
        else
        {
            cout << "用f或c作答:" << endl;
        }
        cin >> answer;
        getchar();
        answer = ToUpper(answer);
        initialResponse = false;
    } while (answer != 'F' && answer != 'C');
    if (answer == 'F') curLineNo = 1;


    size_t index, flag = 0;
    cout << "输入被查找的字符串" << endl;
    string S, P;
    getline(cin, P);
    for (; curLineNo <= line; ++curLineNo)
    {
        textBuffer.GetElem(curLineNo, S);
        index = S.find(P);
        if (index == string::npos) continue;
        else {
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        cout <<"已找到字符串"<<endl;
        cout <<"在第"<<curLineNo<<"行"<<"第"<<index+1<<"个字符"<<endl;
        cout <<S<<endl;
    }
    else
    {
        cout <<"没有找到"<<endl;
    }
}


//首先判断用户选择开始替换的位置，
// 再使用和查找一样的方式找到要替换的行数和位置，
// 然后使用string类中replace函数替换内容，
// 将所得string放在新的string变量中，
// 最后使用双向链表中SetElem重置该节点数据值为新string
void texteditor::ChangeLine() {
    char answer;
    bool initialResponse = true;
    do
    {
        if (initialResponse)
        {
            cout << "替换当前行C(urrent)或替换所有行A(ll):"<<endl;
        }
        else
        {
            cout <<"用c或a回答:";
        }

        cin>>answer;
        getchar();
        answer = ToUpper(answer);
        initialResponse = false;
    } while (answer != 'C' && answer != 'A');


    cout <<"输入要被替换的指定文本串"<<endl;
    string P, S;
    getline(cin, S);
    cout<<S<<endl;
    cout <<"输入新文本串"<<endl;
    getline(cin, P);
    cout<<P<<endl;
    for (int row = 1; row <= line; ++row) {
        if (answer == 'C' && row != curLineNo)
        {
            continue;
        }

        string strRow;
        int l = S.length();
        textBuffer.GetElem(row, strRow);
        size_t index = strRow.find(S);
        if (index!=string::npos)
        {
            string newline = strRow.replace(index, l, P);
            cout<<newline<<endl;
            textBuffer.SetElem(row, newline);
        }
    }
}

//测试代码
int main()
{
    string inFileName, outFileName;
    cout << "请输入想要打开的文件名" <<endl;
    cin >> inFileName;
    cout << "请输入想要写入的文件名" <<endl;
    cin >> outFileName;
    texteditor article1(inFileName, outFileName);
    article1.Run();
//    string s1 = "i'm not good";
//    string s2 = "Not";
//    string s3 = "not";
//    int index = s1.find(s3);
//    cout<<index<<endl;
//    s1.replace(index, s3.length(), s2);
//    cout<<s1;
    return 0;
}