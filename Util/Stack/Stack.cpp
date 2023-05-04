#include<iostream>
#include<climits>
using namespace std;

class StackNode{

    int data;
    StackNode *next;

    public:
    StackNode(int x){
        this->data = x;
        this->next = NULL;
    }
    friend class Stack;
};

class Stack{

    StackNode *top;

    public:

    Stack(){
        top = NULL;
    }

    void push(int x){
        StackNode *node = new StackNode(x);
        node->next = top;
        top = node;
    }

    void pop(){

        if(top == NULL){
            cout << "StackEmptyException\n";
            return;
        }

        StackNode *temp = top;

        top = top->next;

        delete temp;
    }

    int peek(){
        if(isEmpty())
            return INT_MIN;

        return top->data;
    }

    bool isEmpty(){
        return top == NULL;
    }



};