#include<iostream>
#include<stdlib.h>
#include<omp.h>

using namespace std;

void bubble_sequential(int *, int);
void bubble_parallel(int *, int);
void swap(int &, int &);

void bubble_sequential(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void bubble_parallel(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        int first = i % 2;
        #pragma omp parallel for shared(a, first)
        for (int j = first; j < n - 1; j += 2)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int *original, *seq, *par, n;

    cout << "\nEnter total number of elements: ";
    cin >> n;

    original = new int[n];
    seq = new int[n];
    par = new int[n];

    cout << "\nEnter elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> original[i];
    }

    // Copy original array to both versions
    for (int i = 0; i < n; i++)
    {
        seq[i] = original[i];
        par[i] = original[i];
    }

    double start, end;

    // Time Sequential
    start = omp_get_wtime();
    bubble_sequential(seq, n);
    end = omp_get_wtime();
    cout << "\nSequential Sorted array: ";
    for (int i = 0; i < n; i++) cout << seq[i] << " ";
    cout << "\nTime taken by Sequential Bubble Sort: " << end - start << " seconds\n";

    // Time Parallel
    start = omp_get_wtime();
    bubble_parallel(par, n);
    end = omp_get_wtime();
    cout << "\nParallel Sorted array: ";
    for (int i = 0; i < n; i++) cout << par[i] << " ";
    cout << "\nTime taken by Parallel Bubble Sort: " << end - start << " seconds\n";

    delete[] original;
    delete[] seq;
    delete[] par;

    return 0;
}
