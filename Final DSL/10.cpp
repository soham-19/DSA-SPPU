#include<iostream>
using namespace std;

class Heap{
	
	private:
	int* arr;
	int n;
	bool isSorted;
	
	void heapify(int i, int n){
		
		int left = 2*i+1;
		int right = 2*i+2;
		int maxIndex = i;
		
		if(left < n && arr[left]>arr[maxIndex])
			maxIndex = left;
		
		if(right < n && arr[right]>arr[maxIndex])
			maxIndex = right;
		
		if(i!=maxIndex){
			int temp = arr[i];
			arr[i] = arr[maxIndex];
			arr[maxIndex] = temp;
			
			heapify(maxIndex,n);
		}
	}
		
	public:
	
	Heap(int n){
		this->n = n;
		arr = new int[n];
		for(int i=0;i<n;i++) {
			cout << " ->  ";
			cin >> arr[i];
		}
		isSorted = false;
	}
	
	
	void sort(){
		
		for(int i=n/2;i>=0;i--)
			heapify(i,n);
		
		for(int i=n-1;i>0;i--){
			
			int temp = arr[i];
			arr[i] = arr[0];
			arr[0] = temp;
			
			heapify(0,i);
		}
		isSorted = true;
	}
	
	void min(){
		if(!isSorted){
			cout << "Data is not sorted yet.\n";
			return;
		}
		cout << "Minimum score : " << arr[0] <<endl;
	}
	void max(){
		if(!isSorted){
			cout << "Data is not sorted yet.\n";
			return;
		}
		cout << "Maximum score : " << arr[n-1] <<endl;
	}	
	
	void topScores(int m){
		if(!isSorted){
			cout << "Data is not sorted yet.\n";
			return;
		}
		for(int i=n-1,rank=1;i>=0&&rank<=m;i--,rank++){
			cout << "Rank " << rank << " : " << arr[i] << endl;
		}
	}
	
	void bottomScores(int m){
		if(!isSorted){
			cout << "Data is not sorted yet.\n";
			return;
		}
		for(int i=0,rank=1;i<n&&rank<=m;i++,rank++){
			cout << "Lowest " << rank << " : " << arr[i] << endl;
		}		
	}
};

int main(){
	
	Heap heap(6);
	
	heap.min();
	heap.sort();
	
	heap.min();
	heap.max();
	heap.topScores(3);
	heap.bottomScores(3);
}