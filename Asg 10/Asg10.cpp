/*
Read the marks obtained by students of second year in an online examination of particular subject. Find out maximum and minimum marks obtained in that subject Use heap data structure Analyze the algorithm
*/

#include<iostream>
using namespace std;

class MinHeap{
    public:
        int *heap;
        int size;
        int capacity;

        MinHeap(int capacity){
            this->capacity = capacity;
            heap = new int[capacity];
            for (int i = 0; i < capacity;i++){
                heap[i] = 0;
            }
                size = 0;
        }

        ~MinHeap(){
            delete[] heap;
        }

        void add(int data){

            if(size==capacity){
                cout << "MinHeap is Full.\n";
            }

            heap[size] = data;
            int current = size;
            int parent = (current - 1) / 2;

            while(heap[current] < heap[parent]){
                
                int temp = heap[current];
                heap[current] = heap[parent];
                heap[parent] = temp;

                current = parent;
                parent = (current - 1) / 2;
            }
            size++;
        }

        int peek() {
            if (size == 0) {
                cout << "MinHeap is empty. Cannot peek element." << endl;
                return -1;
            }
            return heap[0];
        }

};

class MaxHeap{
    public:
        int *heap;
        int size;
        int capacity;

        MaxHeap(int capacity){
            this->capacity = capacity;
            heap = new int[capacity];
            for (int i = 0; i < capacity;i++){
                heap[i] = 0;
            }
                size = 0;
        }

        ~MaxHeap(){
            delete[] heap;
        }

        void add(int data){

            if(size==capacity){
                cout << "MaxHeap is Full.";
            }

            heap[size] = data;
            int current = size;
            int parent = (current - 1) / 2;

            while(heap[current] > heap[parent]){
                
                int temp = heap[current];
                heap[current] = heap[parent];
                heap[parent] = temp;

                current = parent;
                parent = (current - 1) / 2;
            }
            size++;
        }

        int peek() {
            if (size == 0) {
                cout << "MaxHeap is empty. Cannot peek element." << endl;
                return -1;
            }
            return heap[0];
        }

};


int main() {

    MinHeap min(3);
    MaxHeap max(3);

    int arr[] = {3, 4, 1, 2, 9, 7,11};

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]);i++){
        min.add(arr[i]);
        max.add(arr[i]);
    }

    cout << endl;
    cout << "Min Ele : " << min.peek() << endl;
    cout << "Max ELe : " << max.peek() << endl;

    return 0;
}