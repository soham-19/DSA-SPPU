import java.util.Scanner;

public class Heap{
	
	public static void printArr(int[] arr, int s, int e){
		
		for(int i=s;i<e;i++){
			System.out.print(arr[i]+" ");
		}
	}
	
	public static void heapify(int[] arr, int i, int n){
		
		int left = 2*i+1;
		int right = 2*i+2;
		int maxIndex = i;
		
		if(left <n && arr[left]>arr[maxIndex])
			maxIndex = left;
		
		if(right < n && arr[right] > arr[maxIndex])
			maxIndex = right;
		
		if(maxIndex != i){
			
			int temp = arr[i];
			arr[i] = arr[maxIndex];
			arr[maxIndex] = temp;
			
			heapify(arr,maxIndex,n);
		}
	}
	
	public static void heapSort(int[] arr) {
		
		int n = arr.length;
		// build a max heap.
		System.out.println("Building a max-heap");
		for(int i=n/2;i>=0;i--){
			heapify(arr,i,n);
		}
		
		System.out.println("Max-heap built successfully.\n");
		System.out.print("Max-heap is : ");
		printArr(arr,0,n);
		System.out.println();
		
		for(int i=n-1, pass=1; i>0;i--,pass++) {
			
			//swap
			int temp = arr[0];
			arr[0] = arr[i];
			arr[i] = temp;
			
			heapify(arr,0,i);
			
			System.out.println("Pass " + pass+" : ");
			System.out.print("Unsorted : \t");
			printArr(arr,0,n-pass);
			System.out.print(" |  ");
			printArr(arr,n-pass,n);
			System.out.println("  Sorted");
			System.out.println();
		}
		
	}
	
	public static void main(String args[]){
		
		Scanner sc = new Scanner(System.in);
		
		int n = sc.nextInt();
		int arr[] = new int[n];
		
		for(int i=0;i<n;i++){
			arr[i] = sc.nextInt();
		}
		
		System.out.print("Input Array is : ");
		printArr(arr,0,n);
		System.out.println();
		
		heapSort(arr);
		
		sc.close();
	}
	
}