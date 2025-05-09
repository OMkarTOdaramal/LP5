#include<iostream>
#include<omp.h>
#include<cstring>
using namespace std;

void merge(int *a, int low, int mid, int high) {
    int *temp = new int[high - low + 1];
    int i = low, j = mid + 1, k = 0;

    while (i <= mid && j <= high) {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];
    while (j <= high)
        temp[k++] = a[j++];

    for (int i = low, k = 0; i <= high; ++i, ++k)
        a[i] = temp[k];

    delete[] temp;
}

void merge_sort_sequential(int *a, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        merge_sort_sequential(a, low, mid);
        merge_sort_sequential(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

void merge_sort_parallel(int *a, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            merge_sort_parallel(a, low, mid);

            #pragma omp section
            merge_sort_parallel(a, mid + 1, high);
        }

        merge(a, low, mid, high);
    }
}

int main() {
    int *original, *seq, *par, n;

    cout << "\nEnter total number of elements: ";
    cin >> n;

    original = new int[n];
    seq = new int[n];
    par = new int[n];

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
        cin >> original[i];

    // Copy for both versions
    memcpy(seq, original, n * sizeof(int));
    memcpy(par, original, n * sizeof(int));

    double start, end;

    // Sequential Merge Sort
    start = omp_get_wtime();
    merge_sort_sequential(seq, 0, n - 1);
    end = omp_get_wtime();
    cout << "\nSequential Sorted Array: ";
    for (int i = 0; i < n; i++) cout << seq[i] << " ";
    cout << "\nTime taken by Sequential Merge Sort: " << end - start << " seconds\n";

    // Parallel Merge Sort
    start = omp_get_wtime();
    merge_sort_parallel(par, 0, n - 1);
    end = omp_get_wtime();
    cout << "\nParallel Sorted Array: ";
    for (int i = 0; i < n; i++) cout << par[i] << " ";
    cout << "\nTime taken by Parallel Merge Sort: " << end - start << " seconds\n";

    delete[] original;
    delete[] seq;
    delete[] par;

    return 0;
}
