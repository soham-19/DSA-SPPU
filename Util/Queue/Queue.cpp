#include<iostream>
using namespace std;

class QueueNode{

    int data;
    QueueNode *next;

    public:
    QueueNode(int x){
        this->data = x;
        this->next = NULL;
    }

    friend class Queue;
};

class Queue{

    QueueNode *front, *rear;

    public:
    Queue(){
        front = rear = NULL;
    }

    bool isEmpty(){
        return front == NULL;
    }

    void add(int x){

        QueueNode *node = new QueueNode(x);

        if(isEmpty()){
            front = rear = node;
            return;
        }

        rear->next = node;
        rear = node;
    }

    void remove(){
        if(isEmpty()){
            cout << "QueueEmptyException\n";
            return;
        }

        if(front == rear){

            QueueNode *temp = front;
            front = rear = NULL;
            delete temp;
        }
        else{
            QueueNode *temp = front;
            front = front->next;
            delete temp;
        }
    }

    int peekFront(){
        if(isEmpty()){
            cout << "QueueEmptyException\n";
            return -1;
        }
        return front->data;
    }

    int peekRear(){
        if(isEmpty()){
            cout << "QueueEmptyException\n";
            return -1;
        }
        return rear->data;
    }
};