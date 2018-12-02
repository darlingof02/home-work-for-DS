//
// Created by 彭轶壮 on 2018-11-30.
//

#ifndef HUFFMANTREE_MYSELF_HUFFMANTREE_H
#define HUFFMANTREE_MYSELF_HUFFMANTREE_H

#include <iostream>
#include <limits>
#include <fstream>
#include <stack>
#include <string>

using namespace std;

class HuffmanNode
{
public:
    char info;
    int parent, lChild, rChild;
    int wei;
    string code;
    HuffmanNode()
    {
        parent = lChild = rChild = -1;
    }
    HuffmanNode (const char &ch, const int &weight)
    {
        info  = ch;
        wei = weight;
        lChild = rChild = parent = -1;
    }
//    friend void operator=(HuffmanNode a, HuffmanNode b);
    ~HuffmanNode(){;}
};

//void HuffmanNode::operator=(HuffmanNode a, HuffmanNode b) {
//    a.code = b.code;
//    a.parent = b.parent;
//    a.rChild = b.rChild;
//    a.lChild = b.lChild;
//    a.wei = b.wei;
//    a.info = b.info;
//}

class HuffmanTree
{
public:
    void Run(const char *inFilename, const char *outFilename, const char *outFilename2);
    HuffmanTree();
    ~HuffmanTree();
private:
    HuffmanNode *tree;
    int maxSize;
    int curSize;
    string encrypt, decrypt, File;
    void Insert(const char &ch, const int &weight);
    void CreateTree();
    void Encode();
    void Decode();
    void Print();
    int FindPos(char info);
    bool IsFind(string s);
    char FindElem(string A);
};

void HuffmanTree::Run(const char *inFilename, const char *outFilename, const char *outFilename2) {
    ifstream inFile(inFilename, ios::in);
    if (!inFile)
    {
        cerr<<"打开失败"<<endl;
    }

    char ch;
    int pos;
    inFile>>ch;
    while (inFile && !inFile.eof()) {
        File += ch;
        pos = FindPos(ch);
        if (pos != -1)
            tree[pos].wei++;
        else
            Insert(ch, 1);
        inFile>>ch;
    }

    CreateTree();
    Encode();
    Decode();
    Print();

    ofstream outFile1(outFilename);
    if (!outFile1)
    {
        cerr<<"写入文件1打开失败"<<endl;
    }
    else {
        outFile1<<decrypt<<endl;
    }

    ofstream outFile2(outFilename2);
    if (!outFile2)
    {
        cerr<<"写入文件2打开失败"<<endl;
    }
    else {
        outFile2<<encrypt<<endl;
    }
}

HuffmanTree ::HuffmanTree() {
    curSize = 0;
    maxSize = 100;
    tree = new HuffmanNode[maxSize];
}

HuffmanTree ::~HuffmanTree() {
    delete []tree;
}

void HuffmanTree ::Insert(const char &ch, const int &weight) {
    tree[curSize].info = ch;
    tree[curSize].wei = weight;
    tree[curSize].code = "";
    curSize ++;
}

void HuffmanTree ::CreateTree() {
    int w1, w2;
    int i = curSize;
    int k;
    int lNode=-1, rNode=-1;
    while (i<2*curSize-1)
    {
        k = 0;
        w1 = w2 = numeric_limits<int>::max();
        while (k < i)             //查询最小和次小的数
        {
            if (tree[k].parent == -1)
            {
                if (tree[k].wei < w1)
                {
                    w2 = w1;
                    w1 = tree[k].wei;
                    rNode =  lNode;
                    lNode = k;
                }
                else if (tree[k].wei < w2)
                {
                    w2 = tree[k].wei;
                    rNode = k;
                }
            }
            k++;
        }
        tree[i].wei = tree[lNode].wei + tree[rNode].wei;
        tree[i].lChild = lNode;
        tree[i].rChild = rNode;
        tree[lNode].parent = tree[rNode].parent = i;
        i++;
    }
}

void HuffmanTree::Encode()
{
    int k=-1;
    int Vis[100] = {0};
    for (int i = 0; i < 2*curSize-1; ++i) {
        if (tree[i].parent == -1) {
            k = i;
            break;
        }
    }
    if (k==-1) {
        cout<<"Huffman树错误"<<endl;
        return;
    }

    stack<HuffmanNode> s1;
    s1.push(tree[k]);
    Vis[k] = true;
    while (!s1.empty())
    {
        HuffmanNode x = s1.top();
        int l = x.lChild;
        int r = x.rChild;
        if(Vis[r] && Vis[l]) s1.pop();
        if (l!=-1 && !Vis[l])
        {
            Vis[l] = 1;
            tree[l].code = x.code + "0";
            s1.push(tree[l]);
        }
        else if (r!=-1 && !Vis[r])
        {
            Vis[r] = 1;
            tree[r].code = x.code + "1";
            s1.push(tree[r]);
        }
    }
    int l = File.length();
    for (int j = 0; j < l; ++j) {
        int t = FindPos(File[j]);
        if (t == -1)
        {
            cerr<<"没有查到树上的字符内容"<<endl;
        }
        encrypt += tree[t].code;
    }
}

int HuffmanTree::FindPos(char ch)
{
    for (int i = 0; i < curSize*2-1; ++i) {
        if (tree[i].info == ch)
            return i;
    }
    return -1;
}

void HuffmanTree::Print() {
    for (int i = 0; i < 2*curSize-1; ++i) {
        cout<<i<<" "<<tree[i].info<<'('<<tree[i].code<<')'<<"  "<<tree[i].wei<<
        "  "<<tree[i].lChild<<":"<<tree[i].rChild<<"  "<<tree[i].parent<<endl;
    }
    cout<<"原文为"<<File<<endl;
    cout<<"编码为"<<encrypt<<endl;
    cout<<"译码为"<<decrypt<<endl;
}

void HuffmanTree::Decode() {
    string test;
    int l = encrypt.length();
    for (int i = 0; i < l; ++i) {
        test += encrypt[i];
        if (IsFind(test))
        {
            decrypt += FindElem(test);
            test = "";
        }

    }
}

bool HuffmanTree::IsFind(string s) {
    for (int i = 0; i < curSize; ++i) {
        if (tree[i].code == s)
        {
            return true;
        }
    }
    return false;
}

char HuffmanTree::FindElem(string A) {
    if (IsFind(A))
    {
        for (int i = 0; i < curSize; ++i) {
            if (A == tree[i].code) {
                return tree[i].info;
            }
        }
    }
}
#endif //HUFFMANTREE_MYSELF_HUFFMANTREE_H
