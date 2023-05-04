import java.util.Scanner;

public class Sorting {

	public static void shellSort(int arr[]) {
	
		for(int gap = arr.length/2; gap != 0; gap /= 2) {
		
			for(int i = gap; i < arr.length; i++) {
			
				int temp = arr[i];
				
				int j = i;
				
				while(j >= gap && arr[j-gap] > temp) {
					
					arr[j] = arr[j-gap];
					
					j = j - gap;
				}
				
				arr[j] = temp;
			}
			printArr(arr);
		}
	}
	
	
	public static int[] getArr() {
	
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter size : " );
		
		int n = sc.nextInt();
		
		int arr[] = new int[n];
		
		for(int i=0; i<arr.length; i++) {
			System.out.print("--> " + (i+1) + "th element : ");
			arr[i] = sc.nextInt();
		}
		
		sc.close();
		
		return arr;	
	}
	
	public static void printArr(int arr[]) {
	
		System.out.print("Array is : ");
		
		for(int i=0; i<arr.length; i++) {
			System.out.print(arr[i] + " ");
		}
		System.out.println();		
	}
	
	public static void main(String args[]) {

		int arr[] = getArr();
		
		printArr(arr);
		
		shellSort(arr);

		
		printArr(arr);		
		
	}
	
}
