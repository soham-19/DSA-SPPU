#include<iostream>
using namespace std;
#define M 25

class Heap{

    int n;
    int *arr;

    void printArr(){
        for (int i = 0; i < n;i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    void heapify(int i,int n) {

        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int maxIdx = i;

        if(left<n&&arr[left]>arr[maxIdx])
            maxIdx = left;

        if(right<n&&arr[right]>arr[maxIdx])
            maxIdx = right;

        // swap if needed
        if(i!=maxIdx) {
            int temp = arr[i];
            arr[i] = arr[maxIdx];
            arr[maxIdx] = temp;
            heapify(maxIdx, n);
        }
    }

    public:

    Heap(int N){
        n = N;
        arr = new int[n];
        for (int i = 0; i < n;i++){
            cout << "->";
            cin >> arr[i];
        }
    }

    void sort(){

        // build heap;
        for (int i = n / 2; i >= 0;i--)
            heapify(i,n);

        for (int i = n - 1; i > 0;i--){

            //swap
            int temp = arr[i];
            arr[i] = arr[0];
            arr[0] = temp;
            heapify(0, i);
        }
    }

    void max(){
        cout << "Max Score = " << arr[n - 1] << endl;
    }
    void min(){
        cout << "Min Score = " << arr[0] << endl;
    }
    void toppers(int m) {
        if(m>n)
            return;
        for (int i = n - 1, rank = 1; rank!=m+1;i--,rank++){
            cout << "Rank " << rank << " : " << arr[i] << endl;
        }
    }
};

int main(){

    int n;
    cout << "Size : ";
    cin >> n;

    Heap heap(n);
    heap.sort();
    heap.max();
    heap.min();
    heap.toppers(3);
}