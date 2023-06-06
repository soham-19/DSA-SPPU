import java.util.Scanner;
public class Asg01 {
	public static void main(String args[]) {
		
		Scanner sc = new Scanner(System.in);
		int choice = 0;
		System.out.print("Enter size of array : ");
		int n = sc.nextInt();
		int[] arr = new int[n];

		for (int i = 0; i < n; i++) {
			System.out.print("arr[" + i + "] = ");
			arr[i] = sc.nextInt();
		}
		System.out.print("Input/Unsorted Array is : ");
		printArr(arr, 0, n);
		System.out.println("\n");
		
		System.out.println();
		System.out.println("   * S O R T I N G * ");
		System.out.println("1-Heap Sort");
		System.out.println("2-Shell Sort");
		choice = sc.nextInt();


		if (choice == 1)
			heapSort(arr);
		else
			shellSort(arr);

		System.out.print("\nOutput/Sorted Array is : ");
		printArr(arr, 0, n);
		System.out.println("\n");
		sc.close();
	}

	public static void printArr(int[] arr, int s, int e) {
		for (int i = s; i < e; i++)
			System.out.print(arr[i] + " ");
	}

	public static void heapSort(int[] arr) {
		int n = arr.length;
		System.out.println("Building a max-heap from given array ...\n");
		for (int i = n / 2; i >= 0; i--)
			heapify(arr, i, n);

		System.out.print("Built max-heap is : ");
		printArr(arr, 0, n);
		System.out.println("\n");

		for (int i = n - 1, pass = 1; i > 0; i--, pass++) {
			// delete and replace
			int temp = arr[i];
			arr[i] = arr[0];
			arr[0] = temp;

			heapify(arr, 0, i);
			// display-passwise
			System.out.print("Pass " + pass + ":\tUnsorted ");
			printArr(arr, 0, n - pass);
			System.out.print("| ");
			printArr(arr, n - pass, n);
			System.out.println("Sorted");
		}
	}

	public static void heapify(int[] arr, int i, int n) {

		int left = 2 * i + 1,right = 2 * i + 2,maxIdx = i; 

		if (left < n && arr[left] > arr[maxIdx])
			maxIdx = left;
		if (right < n && arr[right] > arr[maxIdx])
			maxIdx = right;

		if (i != maxIdx) {
			int temp = arr[i];
			arr[i] = arr[maxIdx];
			arr[maxIdx] = temp;

			heapify(arr, maxIdx, n);
		}
	}

	public static void shellSort(int arr[]) {
		int pass = 1;
		for (int gap = arr.length / 2; gap != 0; gap /= 2) {
			for (int i = gap; i < arr.length; i++) {
				int temp = arr[i];
				int j = i;
				while (j >= gap && arr[j - gap] > temp) {
					arr[j] = arr[j - gap];
					j = j - gap;
				}
				arr[j] = temp;
				System.out.print("Pass " + pass++ + " : ");
				printArr(arr, 0, arr.length);
				System.out.println();
			}
		}
	}
}