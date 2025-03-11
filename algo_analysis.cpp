#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to perform Insertion Sort
// Insertion Sort works by iteratively building a sorted portion of the array
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    // Start from the second element (index 1) and move forward
    for (int i = 1; i < n; i++) {
        int key = arr[i];  // The element to be placed in the sorted portion
        int j = i - 1;     // Start comparing with the previous element

        // Move elements of arr[0..i-1], that are greater than key, to one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;  // Place the key at its correct position
    }
}

// Helper function for Merge Sort to merge two subarrays
// arr[p..q] and arr[q+1..r] are merged into a sorted array
void merge(vector<int>& arr, int p, int q, int r) {
    int n1 = q - p + 1;  // Size of the first subarray
    int n2 = r - q;      // Size of the second subarray
    vector<int> L(n1), R(n2);  // Temporary arrays to hold the subarrays

    // Copy data into temporary arrays
    for (int i = 0; i < n1; i++) L[i] = arr[p + i];
    for (int i = 0; i < n2; i++) R[i] = arr[q + 1 + i];

    int i = 0, j = 0, k = p;
    // Merge the two subarrays back into the original array
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    // Copy the remaining elements, if any
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Recursive function for Merge Sort
// It divides the array into two halves and sorts each half
void mergeSort(vector<int>& arr, int p, int r) {
    if (p < r) {
        int q = p + (r - p) / 2;  // Find the middle point
        mergeSort(arr, p, q);      // Recursively sort the first half
        mergeSort(arr, q + 1, r);  // Recursively sort the second half
        merge(arr, p, q, r);       // Merge the two sorted halves
    }
}

// Helper function for Heap Sort to maintain the heap property
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;        // Initialize largest as root
    int left = 2 * i + 1;   // Left child index
    int right = 2 * i + 2;  // Right child index

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest]) largest = left;

    // If right child is larger than largest
    if (right < n && arr[right] > arr[largest]) largest = right;

    // If largest is not root, swap it with the largest and recursively heapify the affected sub-tree
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Function to perform Heap Sort
// First, build a max heap and then extract elements one by one
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Build a max heap
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);

    // One by one extract elements from the heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);    // Move current root to the end
        heapify(arr, i, 0);       // Call max-heapify on the reduced heap
    }
}

// Helper function for Quick Sort to partition the array
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // Pivot element
    int i = low - 1;        // Index of smaller element

    // Loop through the array and rearrange elements such that smaller elements are on the left of pivot
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) swap(arr[++i], arr[j]);
    }
    swap(arr[i + 1], arr[high]);  // Place the pivot element at the correct position
    return i + 1;                  // Return the pivot index
}

// Recursive function for Quick Sort
// It partitions the array and sorts each subarray recursively
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // Partition the array
        quickSort(arr, low, pi - 1);         // Sort the left subarray
        quickSort(arr, pi + 1, high);        // Sort the right subarray
    }
}

// Function to generate a random array of a given size
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    // Fill the array with random integers between 0 and 9999
    for (int& num : arr) num = rand() % 10000;
    return arr;
}

// Function to measure and display the execution time of sorting algorithms that take only a vector argument
void measureExecutionTime(void (*sortFunction)(vector<int>&), vector<int> arr, const string& sortName) {
    auto start = high_resolution_clock::now();   // Start the clock
    sortFunction(arr);                           // Call the sorting function
    auto end = high_resolution_clock::now();     // End the clock
    auto duration = duration_cast<milliseconds>(end - start);  // Calculate the time taken
    cout << sortName << " took " << duration.count() << " ms\n";  // Display the time taken
}

// Function to measure and display the execution time of sorting algorithms that require indices
void measureExecutionTime(void (*sortFunction)(vector<int>&, int, int), vector<int> arr, const string& sortName) {
    auto start = high_resolution_clock::now();   // Start the clock
    sortFunction(arr, 0, arr.size() - 1);         // Call the sorting function
    auto end = high_resolution_clock::now();     // End the clock
    auto duration = duration_cast<milliseconds>(end - start);  // Calculate the time taken
    cout << sortName << " took " << duration.count() << " ms\n";  // Display the time taken
}

int main() {
    srand(time(0));  // Seed the random number generator

    // Array of different sizes to test the sorting algorithms
    vector<int> sizes = {50, 100, 500, 1000, 5000, 10000, 20000, 50000, 100000};

    // Loop through each array size and test all sorting algorithms
    for (int size : sizes) {
        cout << "\nSorting " << size << " elements:\n";
        vector<int> arr = generateRandomArray(size);  // Generate a random array of the current size

        // Measure and print the execution time for each sorting algorithm
        measureExecutionTime(insertionSort, arr, "Insertion Sort");
        measureExecutionTime(heapSort, arr, "Heap Sort");
        measureExecutionTime(mergeSort, arr, "Merge Sort");
        measureExecutionTime(quickSort, arr, "Quick Sort");
    }
    return 0;
}
