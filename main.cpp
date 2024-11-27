#include <iostream>
#include <vector>
#include <chrono>
#include <random>

class SortingComparison {
public:
    // insrtion sort
    void insertionSort(std::vector<int>& arr) {
        // MY CODE

        for (int p = 1; p < arr.size(); p++)
        {
            int tmp = std::move(arr[p]);

            int j; 
            for (j = p; j > 0 && tmp < arr[j - 1]; --j)
                arr[j] = std::move(arr[j - 1]);
            arr[j] = std::move(tmp);
        }

    }

    // quick sort
    void quickSort(std::vector<int>& arr, int left, int right) 
    {
        // TODO
        if (left + 10 <= right)
        {
            const int& pivot = median3(arr, left, right);

            //begin aprtitioning
            int i = left, j = right - 1;
            for (; ;)
            {
                while (arr[++i] < pivot) {}
                while (pivot < arr[--j]) {}
                if (i < j)
                    std::swap(arr[i], arr[j]);
                else
                    break;
            }

            std::swap(arr[i], arr[right - 1]);

            quickSort(arr, left, i - 1);
            quickSort(arr, i + 1, right);
        }
        else
            insertionSort(arr);
    }

    // merge sort
    void mergeSort(std::vector<int>& arr, int left, int right) {
        //MY CODE
        std::vector<int> temp_a(arr.size());
        //call to private
        mergeSorthelp(arr, temp_a, 0, arr.size() - 1);
    }

    // generate random integers
    std::vector<int> generateRandomArray(int size) {
        std::vector<int> arr(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 100000);
        for (int& x : arr) {
            x = dist(gen);
        }
        return arr;
    }

    // test sorted
    bool isSorted(const std::vector<int>& arr) {
        for (size_t i = 1; i < arr.size(); ++i) {
            if (arr[i] < arr[i - 1]) {
                return false;
            }
        }
        return true;
    }

    // comparison run time for three sorting algorithms
    void compareSortingAlgorithms() {
        std::vector<int> sizes = {1000, 10000, 100000}; // data scales
        for (int size : sizes) {
            std::vector<int> arr = generateRandomArray(size);
            
            std::cout << "Data size: " << size << "\n";

            // test insertion sort
            std::vector<int> arr_copy = arr;
            auto start = std::chrono::high_resolution_clock::now();
            insertionSort(arr_copy);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            std::cout << "Insertion Sort: " << elapsed.count() << " seconds\n";
            std::cout << "Sorted: " << (isSorted(arr_copy) ? "Yes" : "No") << "\n";


            // test quick sort
            arr_copy = arr;
            start = std::chrono::high_resolution_clock::now();
            quickSort(arr_copy, 0, arr_copy.size() - 1);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            std::cout << "Quick Sort: " << elapsed.count() << " seconds\n";
            std::cout << "Sorted: " << (isSorted(arr_copy) ? "Yes" : "No") << "\n";


            // test merge sort
            arr_copy = arr;
            start = std::chrono::high_resolution_clock::now();
            mergeSort(arr_copy, 0, arr_copy.size() - 1);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            std::cout << "Merge Sort: " << elapsed.count() << " seconds\n";
            std::cout << "Sorted: " << (isSorted(arr_copy) ? "Yes" : "No") << "\n\n";
        }
    }

private:
    // Some internal helper functions

    void mergeSorthelp(std::vector<int>& arr, std::vector<int>& temp_a, int left, int right)
    {
        if (left < right)
        {
            int center = (left + right) / 2;
            mergeSorthelp(arr, temp_a, left, center);
            mergeSorthelp(arr, temp_a, center + 1, right);
            merge( arr, temp_a, left, center + 1, right );
        }
    }

    void merge(std::vector<int>& arr, std::vector<int>& temp_a,
        int leftPos, int rightPos, int rightEnd)
    {
        int leftEnd = rightPos - 1;
        int tempPos = leftPos;
        int numElements = rightEnd - leftPos + 1;

        while (leftPos <= leftEnd && rightPos <= rightEnd)
            if (arr[leftPos] <= arr[rightPos])
                temp_a[tempPos++] = std::move(arr[leftPos++]);
            else
                temp_a[tempPos++] = std::move(arr[rightPos++]);

        while (leftPos <= leftEnd)  //Copy rest of first half
            temp_a[tempPos++] = std::move(arr[leftPos++]);

        while (rightPos <= rightEnd)    //Copy rest of right half
            temp_a[tempPos++] = std::move(arr[rightPos++]);

        //Copy temp_a back
        for (int i = 0; i < numElements; ++i, --rightEnd)
            arr[rightEnd] = std::move(temp_a[rightEnd]);
    }

    const int& median3(std::vector<int>& a, int left, int right)
    {
        int center = (left + right) / 2;

        if (a[center] < a[left])
            std::swap(a[left], a[center]);
        if (a[right] < a[left])
            std::swap(a[left], a[right]);
        if (a[right] < a[center])
            std::swap(a[center], a[right]);

        std::swap(a[center], a[right - 1]);
        return a[right - 1];
    }
};

int main() {
    SortingComparison sorter;
    sorter.compareSortingAlgorithms();
    return 0;
}
