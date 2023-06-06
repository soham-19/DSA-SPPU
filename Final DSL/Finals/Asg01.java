package Finals;
import java.util.Scanner;

public class Asg01{
	public static void main(String args[]){
		
		Scanner sc = new Scanner(System.in);
		
		System.out.print("Enter array size : ");
		int n = sc.nextInt();
		
		int[] arr = new int[n];
		
		for(int i=0; i<n; i++){
			System.out.print("Enter array["+i+"]  ");
			arr[i] = sc.nextInt();
		}
		System.out.println("Array stored successfully");
		
        while (true) {
            System.out.println("	* S O R T I N G *\n  1-heap sort\n  2-shell sort\n\nEnter your choice :");
            int ch = sc.nextInt();

            if (ch == 0) {
                System.out.println("	T E R M I N A T I N G\n");
                sc.close();
                return;
            } else if (ch == 1) {
                System.out.print("Input array is ");
                printArr(arr);
                heapSort(arr);
                System.out.print("\nOutput array is ");
                printArr(arr);
            } else if (ch == 2) {
                System.out.print("Input array is ");
                printArr(arr);
                shellSort(arr);
                System.out.print("\nOutput array is ");
                printArr(arr);
            } else {
                System.out.println("Invalid Operation Chosen!");
            }
        }
	}
	
	public static void printArr(int[] arr){
		for(int i=0; i<arr.length; i++)
			System.out.print(arr[i] + " ");
		System.out.println();
	}
	
	public static void heapSort(int[] arr){
		int n = arr.length;
		System.out.println("Building max-heap");
		for(int i=n/2;i>=0; i--){
			heapify(arr,i,n);
		}
		System.out.println("Max-Heap constructed successfully\n");
		int pass = 1;
		for(int i=n-1;i>0;i--){
			int temp = arr[i];
			arr[i] = arr[0];
			arr[0] = temp;
			heapify(arr,0,i);
			System.out.print("Pass " + pass++ + " : ");
			printArr(arr);
		}
	}
	
	public static void heapify(int[] arr, int i, int n){
		int left = 2*i+1;
		int right = 2*i+2;
		int maxIdx = i;
		
		if(left<n && arr[maxIdx]<arr[left])
			maxIdx = left;
		if(right<n && arr[maxIdx]<arr[right])
			maxIdx = right;
		
		if(maxIdx != i){
			int temp = arr[i];
			arr[i] = arr[maxIdx];
			arr[maxIdx] = temp;
			heapify(arr,maxIdx,n);
		}
	}
	
	public static void shellSort(int[] arr){
		int n = arr.length;
		int pass = 1;
		for(int gap = n/2; gap != 0; gap/=2){
			for(int i=gap; i<n; i++){
				int j=i;
				int temp = arr[i];
				while(j>=gap && arr[j-gap]>temp){
					arr[j] =arr[j-gap];
					j = j-gap;
				}
				arr[j] = temp;
				System.out.print("Pass " + pass++ + " : ");
				printArr(arr);
			}
		}
	}
	
}