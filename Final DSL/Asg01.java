import java.util.Scanner;

public class Asg01 {
    
    public static void heapSort(int[] arr) {

        int n = arr.length;
        // buid a max heap
        System.out.println("Building a max-heap...");
        for (int i = n / 2; i >= 0; i--) {
            heapify(arr, i, n);
        }

        System.out.println("Built max-heap is : ");
        printArr(arr, 0, n);
        System.out.println();
        
        for (int i = n - 1, pass = 1; i > 0; i--) {
            
            //swap
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            
            heapify(arr, 0, i);

            //display 
            System.out.print("Pass " + pass + ":\t");
            System.out.print("\tUnsorted : ");
            printArr(arr,0,n-pass);
            System.out.print(" |  ");
            printArr(arr, n-pass, n);
            System.out.print("  Sorted\n\n");
            pass++;
        }
    }
    
    public static void heapify(int[] arr, int i, int n) {
        
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int maxIdx = i;

        if(left<n && arr[left] > arr[maxIdx])
            maxIdx = left;

        if(right < n && arr[right] > arr[maxIdx])
            maxIdx = right;

        // swap jar garaj asel tar ch
        if (maxIdx != i) {
            int temp = arr[i];
            arr[i] = arr[maxIdx];
            arr[maxIdx] = temp;
            heapify(arr, maxIdx, n);
        }
    }

    public static void printArr(int[] arr, int s, int e) {    
        for (int i = s; i < e ; i++) {
            System.out.print(arr[i] + " ");
        }
    }
    
    public static void main(String args[]) {

        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the array size : ");
        int n = sc.nextInt();

        int[] arr = new int[n];

        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }

        System.out.print("Input Unsorted Array : ");
        printArr(arr, 0, n);
        System.out.println();
        
        heapSort(arr);
        
        System.out.print("\nOutput Sorted Array : ");
        printArr(arr, 0, n);
        System.out.println();

        sc.close();
    }


}
