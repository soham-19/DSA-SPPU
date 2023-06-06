#include<iostream>
using namespace std;

class Heap{

    private:
    int n;
    int *arr;
    bool isSorted;

    void heapify(int i, int n) {

        int left = 2 * i + 1, right = 2 * i + 2, maxIdx = i;

        if(left<n&&arr[left] >arr[maxIdx])
            maxIdx = left;
        
        if(right <n && arr[right]>arr[maxIdx])
            maxIdx = right;

        if(i!=maxIdx){
            swap(arr[maxIdx], arr[i]);
            heapify(maxIdx, n);
        }
    }

    public:

    Heap(int n){
        this->n = n;
        isSorted = false;
        arr = new int[n];
        for (int i = 0; i < n;i++){
            cout << "array[" << i << "] = ";
            cin >> arr[i];
        }
    }

    void sort(){

        // build a max heap
        for (int i = n / 2; i >= 0;i--)
            heapify(i, n);

        for (int i = n - 1; i > 0;i--){

            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            heapify(0, i);
        }
        isSorted = true;
    }

    void min(){
        if(isSorted){
            cout << "Min : " << arr[0] <<endl<<endl;
        } else {
            cout << "Data is unsorted yet.\n";
        }
    }
    void max(){
        if(isSorted){
            cout << "Max : " << arr[n-1]<<endl<<endl;
        } else {
            cout << "Data is unsorted yet.\n";
        }

    }

    void topScores(int m){
        if(isSorted){
            for (int i = n - 1, rank = 1; rank <= m && i >= 0;rank++,i--){
                cout << "Rank " << i << " : " << arr[i] << endl;
            }
        } else {
            cout << "Data is unsorted yet.\n";
        }
    }
    void bottomScores(int m){
        if(isSorted){
            for (int i = 0, rank = 1; rank <= m && i <n ;rank++,i++){
                cout << "Least " << i << " : " << arr[i] << endl;
            }
                cout << endl;
        } else {
            cout << "Data is unsorted yet.\n";
        }
    }
};

int main(){

    Heap heap(6);

    heap.sort();
    heap.max();
    heap.min();
    heap.topScores(4);
    heap.bottomScores(4);
}