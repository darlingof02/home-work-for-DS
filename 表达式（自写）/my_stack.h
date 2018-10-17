//
// Created by 彭轶壮 on 2018/10/13.
//

#ifndef UNTITLED1_MY_STACK_H
#define UNTITLED1_MY_STACK_H

#endif //UNTITLED1_MY_STACK_H
#include<iostream>
#include<string>
#include<cstdio>
#include<algorithm>
#define MAXSIZE 1005
using namespace std;


template<class Type>
class my_stack
{
private:
    Type *elements;
    int top;
    int MaxSize;
public:
    my_stack(int size);
    my_stack();
    ~my_stack(){delete []elements;}
    bool isEmpty();
    bool isFull();
    int pop(Type &x);
    int push(Type &x);
    Type Top();
};

template <class Type>
my_stack<Type>::my_stack() {
    elements = new Type[MAXSIZE];
    top = -1;
    MaxSize = MAXSIZE;
}

template <class Type>
my_stack<Type>::my_stack(int size) {
    elements = new Type[size];
    top = -1;
    MaxSize = size;
}
template <class Type>
bool my_stack<Type>::isFull() {
    return top == MaxSize;
}

template <class Type>
int my_stack<Type>::push(Type &x) {
    if(!isFull()) {
        elements[++top] = x;
        return 1;
    }
    else return 0;
}

template <class Type>
bool my_stack<Type>::isEmpty() {
    return top==-1;
}

template<class Type>
Type my_stack<Type>::Top() {
    return elements[top];
}

template <class Type>
int my_stack<Type>::pop(Type &x) {
    if(!isEmpty())
    {
        x = elements[top--];
        return 1;
    }
    else return 0;
}