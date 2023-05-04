/*
  Implement the Heap/Shell sort algorithm implemented in Java demonstrating heap/shell data structure with modularity of programming language
 */

import java.util.*;

public class Asg01 {

    public static void printArr(int arr[]) {
        System.out.print("Array is : [");
        for (int i = 0; i < arr.length; i++) {
            if (i != arr.length - 1)
                System.out.print(arr[i] + " ");
            else
                System.out.print((arr[i]) + "]\n");
        }
    }

    public static void shellSort(int arr[]) {

        for (int gap = arr.length / 2; gap != 0; gap /= 2) {

            for (int i = gap; i < arr.length; i++) {

                int temp = arr[i];

                int j = i;

                while (j >= gap && arr[j - gap] > temp) {

                    arr[j] = arr[j - gap];

                    j = j - gap;
                }

                arr[j] = temp;
            }
            printArr(arr);
        }
    }

    public static void heapify(int arr[], int i, int n) {

        printArr(arr);
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int maxIdx = i;

        if (left < n && arr[maxIdx] < arr[left])
            maxIdx = left;

        if (right < n && arr[maxIdx] < arr[right])
            maxIdx = right;

        if (maxIdx != i) {

            int temp = arr[i];
            arr[i] = arr[maxIdx];
            arr[maxIdx] = temp;

            heapify(arr, maxIdx, n);
        }
    }

    public static void heapSort(int arr[]) {

        int n = arr.length;

        // step1 : build heap
        for (int i = n / 2; i >= 0; i--) {
            heapify(arr, i, n);
        }

        // step2 : push largest at end
        for (int i = n - 1; i > 0; i--) {

            // swap
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            // heapify
            printArr(arr);
            heapify(arr, 0, i);
        }
    }

    public static void main(String args[]) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the size of array : ");
        final int size = sc.nextInt();

        int arr[] = new int[size];

        System.out.println("Enter array elements ");
        for (int i = 0; i < arr.length; i++)
            arr[i] = sc.nextInt();

        System.out.println("Enter the array elements.");
        printArr(arr);

        System.out.println("1-Perform Shell Sort");
        System.out.println("2-Perform Heap Sort");
        System.out.print("Enter your choice : ");

        if (sc.nextInt() == 1)
            shellSort(arr);
        else
            heapSort(arr);

        sc.close();
    }

}