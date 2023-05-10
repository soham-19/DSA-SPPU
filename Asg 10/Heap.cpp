#include <iostream>

using namespace std;

class Heap {
public:
    int* heap;
    int size;
    int capacity;

public:
    Heap(int capacity) {
        this->capacity = capacity;
        heap = new int[capacity];
        size = 0;
    }

    ~Heap() {
        delete[] heap;
    }

    void add(int data) {
        if (size == capacity) {
            cout << "Heap is full. Cannot add element." << endl;
            return;
        }

        heap[size] = data;
        int current = size;
        int parent = (current - 1) / 2;

        while (current > 0 && heap[current] < heap[parent]) {
            // Swap child and parent
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
            cout << "Heap is empty. Cannot peek element." << endl;
            return -1;
        }

        return heap[0];
    }

    void heapify(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int minIdx = i;

        if (left < size && heap[minIdx] > heap[left])
            minIdx = left;

        if (right < size && heap[minIdx] > heap[right])
            minIdx = right;

        if (minIdx != i) {
            int temp = heap[i];
            heap[i] = heap[minIdx];
            heap[minIdx] = temp;

            heapify(minIdx);
        }
    }

    int remove() {
        if (size == 0) {
            cout << "Heap is empty. Cannot remove element." << endl;
            return -1;
        }

        int data = heap[0];
        heap[0] = heap[size - 1];
        size--;

        heapify(0);

        return data;
    }

    bool isEmpty() {
        return size == 0;
    }
};

int main() {
    Heap h(10);

    h.add(3);
    h.add(4);
    h.add(10);
    h.add(5);
    cout << "Min : " << h.peek()<<endl;
    // while (h.size!=1) {
    //     h.remove();
    // }
    cout << "Max : " << h.heap[h.size-1]<< endl;

    return 0;
}
