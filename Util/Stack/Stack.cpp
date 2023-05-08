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

int main(){

    Stack s;

    int x;
    int ch;
    while(true){

        cout << "1-push()\n2-pop()\n3-peek()\n4-isEmpty()\n\n";
        cout << " ? ";
        cin >> ch;

        switch(ch){

            case 1:
                cout << "-> ";
                cin >> x;
                s.push(x);
                break;
            case 2:
                cout << "Before pop() : " << s.peek() << endl;
                s.pop();
                if(!s.isEmpty())
                cout << "After pop() : " << s.peek() << endl;
                else{
                cout << "StackEmpty\n";
                }
                break;
            case 3:
                cout << "[top] : " << s.peek()<<endl;
                break;
            case 4:
                cout << "s.isEmpty() : "<<
                (s.isEmpty() ? "true\n" : "false\n");
                break;
            default:
                exit(0);
        }
    }
}
