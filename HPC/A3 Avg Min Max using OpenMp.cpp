#include <iostream>
#include <omp.h>
#include <climits>
using namespace std;

// Sequential computation of min, max, sum, and average
void compute_sequential(int* arr, int n) {
    int min_val = INT_MAX;
    int max_val = INT_MIN;
    long long sum = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
        sum += arr[i];
    }

    double avg = static_cast<double>(sum) / n;

    cout << "\n--- Sequential Output ---\n";
    cout << "Minimum: " << min_val << endl;
    cout << "Maximum: " << max_val << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;
}

// Parallel computation using OpenMP reduction
void compute_parallel(int* arr, int n) {
    int min_val = INT_MAX;
    int max_val = INT_MIN;
    long long sum = 0;

    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum)
    for (int i = 0; i < n; ++i) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
        sum += arr[i];
    }

    double avg = static_cast<double>(sum) / n;

    cout << "\n--- Parallel Output ---\n";
    cout << "Minimum: " << min_val << endl;
    cout << "Maximum: " << max_val << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int* arr = new int[n];
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    double start, end;

    // Sequential execution with timing
    start = omp_get_wtime();
    compute_sequential(arr, n);
    end = omp_get_wtime();
    cout << "Time taken by Sequential Computation: " << end - start << " seconds\n";

    // Parallel execution with timing
    start = omp_get_wtime();
    compute_parallel(arr, n);
    end = omp_get_wtime();
    cout << "Time taken by Parallel Computation: " << end - start << " seconds\n";

    delete[] arr;
    return 0;
}
