/*
Read the marks obtained by students of second year in an online examination of particular subject. 
Find out maximum and minimum marks obtained in that subject Use heap data structure Analyze the algorithm
*/

#include<iostream>
using namespace std;

class Heap{
	int n;
	int * arr;
	public:
	
	void setHeap(){
		cout << "Enter number of students : ";
		cin >> n;
		arr = new int[n];
		
		cout << "Enter marks : \n";
		for(int i=0; i<n; i++){
			cout << "Student " << i+1 << " : ";
			cin >> arr[i];
		}
		cout << "  Marks stored successfully.\n";
		cout << "Sorting the given marks...\n";
		char ch;	cin >> ch;
		
		sort();
	}
	
	void sort(){
		
		cout << " Building heap ...\n";
		
		for(int i=n/2; i>=0; i--){
			heapify(i,n);
		}
		
		cout << " MinHeap built successfully\n";
		
		for(int i = n-1; i>0; i--){
			int temp = arr[0];
			arr[0] = arr[i];
			arr[i] = temp;
			heapify(0,i);
		}
		cout << "  Data Sorted successfully\n";
	}
	
	void heapify(int i, int n){
		int left = 2*i+1;
		int right = 2*i+2;
		int maxIdx = i;
		
		if(left<n && arr[left] > arr[maxIdx])
			maxIdx = left;
		
		if(right<n && arr[right] > arr[maxIdx])
			maxIdx = right;
		
		if(maxIdx != i){
			int temp = arr[maxIdx];
			arr[maxIdx] = arr[i];
			arr[i] = temp;
			
			heapify(maxIdx,n);
		}
	}
	
	void min(){
		cout << "  Minimum score = " << arr[0] << endl;
	}
	void max(){
		cout << "  Maximum score = " << arr[n-1] << endl;
	}
	void bestScores(){
		cout << "How many ranks do you want to display : ";
		int m;	cin >> m;
		
		for(int i=n-1,rank=1; i>=0 && rank<=m; rank++,i--)
			cout << "    Rank " << rank << " : " << arr[i] << endl;
		cout << "  These are the " << m << " best scores.\n";
	}
	void leastScores(){
		cout << "How many ranks do you want to display : ";
		int m;	cin >> m;
		
		for(int i=0,rank=1; i>=0 && rank<=m; rank++,i++)
			cout << "    Rank " << n-rank+1 << " : " << arr[i] << endl;
		cout << "  These are the " << m << " lowest scores.\n";
	}
};
int main(){
	int ch;
	Heap heap;
	
	while(true){
		cout << "\n\n     * H E A P *\n"
			 << "  1-set the marks\n"
			 << "  2-find minimum marks\n"
			 << "  3-find maximum marks\n"
			 << "  4 - find top scores\n"
			 << "  5 - find least scores\n\n"
			 << "  Enter your choice : ";
		cin >> ch;
		
		switch(ch){
			case 0:
				cout << "  T E R M I N A T I N G\n";
				return 0;
			case 1:
				heap.setHeap();
				heap.sort();
				break;
			case 2:
				heap.min();
				break;
			case 3:
				heap.max();
				break;
			case 4:
				heap.bestScores();
				break;
			case 5:
				heap.leastScores();
				break;
			default:
				cout << "  Invalid choice!!\n";				
		}
	}
}