#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;
using namespace std :: chrono;

ifstream fin("tests.in");

const int RUN = 32;
vector<long long> x;
vector<long long> output;
vector<long long> right_array;
vector<long long> left_array;


void generate_array(long long n, long long Max, vector<long long> &x)
{
    mt19937 gen(time(NULL));
    uniform_int_distribution<long long> random(0, Max);

    long long i;
    for(i = 0; i < n; ++i)
        x[i] = random(gen);
}

bool test_sort(long long n, vector<long long> &x)
{
    long long i;

    for(i = 0; i < n - 1; ++i)
        if(x[i+1] < x[i])
            return false;

    return true;
}

/// ================= RADIX SORT =================

long long getMax(long long n, vector<long long> &x)
{
    long long i, mx = x[0];
    for(i = 1; i < n; ++i)
        if(x[i] > mx)
            mx = x[i];
    return mx;
}

void CountSort_base10(long long n, long long exp, vector<long long> &x)
{
    output = vector<long long>(n);

    long long i, cnt[10] = {};

    for(i = 0; i < n; ++i)
        cnt[(x[i] / exp) % 10]++;

    for(i = 1; i < 10; ++i)
        cnt[i] += cnt[i-1];

    for(i = n-1; i >= 0; --i)
    {
        output[cnt[(x[i] / exp) % 10] - 1] = x[i];
        cnt[(x[i] / exp) % 10]--;

    }

    x = output;
}

void RadixSort_base10(long long n, vector<long long> &x)
{
    long long exp, Max = getMax(n, x);

    for(exp = 1; Max / exp > 0; exp *= 10)
        CountSort_base10(n, exp, x);
}

void CountSort_base2power(long long n, long long exp, long long power, vector<long long> &x)
{
    output = vector<long long>(n);

    long long i, cnt[power] = {};

    for(i = 0; i < n; ++i)
        cnt[(x[i] / exp) % power] ++;

    for(i = 1; i <= power; ++i)
        cnt[i] += cnt[i-1];

    for(i = n-1; i >= 0; --i)
    {
        output[cnt[(x[i] / exp) % power] - 1] = x[i];
        cnt[(x[i] / exp) % power] --;
    }

    x = output;
}

void RadixSort_base2power(long long n, long long power, vector<long long> &x)
{
    long long exp, Max = getMax(n, x);

    for(exp = 1; Max / exp > 0; exp *= power)
        CountSort_base2power(n,exp,power,x);
}

/// ================= END OF RADIX SORT =================


/// ================= MERGE SORT =================

void Merge(long long left, long long mid, long long right, vector<long long> &x)
{
    long long i, j, size_left, size_right;

    size_left = mid - left + 1;
    size_right = right - mid;

    left_array = vector<long long>(size_left);
    right_array = vector<long long>(size_right);

    for(i = 0; i < size_left; ++i)
        left_array[i] = x[left + i];

    for(i = 0; i < size_right; ++i)
        right_array[i] = x[mid + i + 1];

    long long index_merged = left;

    i = j = 0;

    while(i < size_left && j < size_right)
    {
        if(left_array[i] <= right_array[j])
        {
            x[index_merged] = left_array[i];
            i++;
        }
        else
        {
            x[index_merged] = right_array[j];
            j++;
        }

        index_merged++;
    }

    while(i < size_left)
    {
        x[index_merged] = left_array[i];
        i++;
        index_merged++;
    }

    while(j <size_right)
    {
        x[index_merged] = right_array[j];
        j++;
        index_merged++;
    }
}

void Merge_Sort(long long left, long long right, vector<long long> &x)
{
    if(left >= right)
        return;

    long long mid = left + (right - left) / 2;
    Merge_Sort(left, mid, x);
    Merge_Sort(mid + 1, right, x);
    Merge(left, mid, right, x);
}

/// ================= END OF MERGE SORT =================


/// ================= SHELL SORT =================

void ShellSort(long long n, vector<long long> &x)
{
    long long interval, i, j, temp;

    for(interval = n / 2; interval > 0; interval /= 2)
    {
        for(i = interval; i < n; ++i)
        {
            temp = x[i];

            for(j = i; j >= interval && x[j-interval] > temp; j -= interval)
                x[j] = x[j-interval];

            x[j] = temp;
        }
    }
}

void ShellSort_Knuth(long long n, vector<long long> &x)
{
    long long i, j, temp, increment;

    increment = 1;

    while(increment <= (n - 1) / 9)
        increment = 3 * increment + 1;

    while(increment >= 1)
    {
        for(i = increment; i < n; ++i)
        {
            temp = x[i];

            for(j = i - increment; j >= 0 && temp < x[j]; j -= increment)
                x[j + increment] = x[j];

            x[j + increment] = temp;
        }

        increment /= 3;
    }
}

/// ================= END OF SHELL SORT =================


/// =================  REGULAR QUICK SORT =================

void Swap(long long *e1, long long *e2)
{
    long long aux;
    aux = *e1;
    *e1 = *e2;
    *e2 = aux;
}

long long partition_pivot_last(long long low, long long high, vector<long long> &x)
{
    long long pivot = x[high], i = low -1;
    long long j;

    for(j = low; j < high; ++j)
        if(x[j] < pivot)
        {
            i++;
            Swap(&x[i], &x[j]);
        }

    Swap(&x[i + 1], &x[high]);

    return (i + 1);

}

void regular_quick_sort(long long low, long long high, vector<long long> &x)
{
    if(low < high)
    {
        long long pi = partition_pivot_last(low, high, x);
        regular_quick_sort(low, pi - 1, x);
        regular_quick_sort(pi + 1, high, x);
    }
}

/// ================= END OF  REGULAR QUICK SORT =================


/// ================= PIVOT FIST QUICK SORT =================

long long partition_pivot_first(long long low, long long high, vector<long long> &x)
{
    long long pivot = x[low], i =low + 1;
    long long j;

    for(j = low + 1; j <= high; ++j)
    {
        if(x[j] < pivot)
        {
            if(j != i)
                Swap(&x[i], &x[j]);

            i++;
        }
    }

    Swap(&x[i - 1], &x[low]);

    return (i - 1);
}

void quickSort_pivot_first(long long low, long long high, vector<long long> &x)
{
    if(low < high)
    {
        long long pi = partition_pivot_first(low, high, x);
        quickSort_pivot_first(low, pi - 1, x);
        quickSort_pivot_first(pi + 1, high, x);
    }
}
/// ================= END OF PIVOT FIRST QUICK SORT =================


/// ================= RANDOM PIVOT QUICK SORT =================

long long partition_pivot_random(long long low, long long high, vector<long long> &x)
{
    long long pivot;

    pivot = (rand() % (high - low + 1)) + low;
    Swap(&x[pivot], &x[high]);

    return partition_pivot_last(low, high, x);
}

void quickSort_pivot_random(long long low, long long high, vector<long long> &x)
{
    if(low < high)
    {
        long long pi = partition_pivot_random(low, high, x);
        quickSort_pivot_random(low, pi - 1, x);
        quickSort_pivot_random(pi + 1, high, x);
    }
}

/// ================= END OF RANDOM PIVOT QUICK SORT =================


/// ================= MEDIAN OF 3 QUICK SORT =================

long long partition_pivot_med_of_3(long long low, long long high, vector<long long> &x)
{
    long long pivot, mid, i, j;

    mid = (low + high) / 2;

    if(x[mid] < x[low])
        Swap(&x[mid], &x[low]);

    if(x[high] < x[low])
        Swap(&x[high], &x[low]);

    if(x[high] < x[mid])
        Swap(&x[high], &x[mid]);

    Swap(&x[mid], &x[high - 1]);
    pivot = x[high - 1];

    return partition_pivot_last(low, high, x);

}

void quickSort_med_of_3(long long low, long long high, vector<long long> &x)
{
    if(low < high)
    {
        long long pi = partition_pivot_med_of_3(low, high, x);
        quickSort_med_of_3(low, pi - 1, x);
        quickSort_med_of_3(pi + 1, high, x);
    }
}

/// ================= END OF MEDIAN OF 3 QUICK SORT =================


/// ================= TIMSORT =================

void insertionSort(long long left, long long right, vector<long long> &x)
{
    long long i, temp, j;

    for (i = left + 1; i <= right; ++i)
    {
        temp = x[i];
        j = i - 1;
        while (j >= left && x[j] > temp)
        {
            x[j+1] = x[j];
            j--;
        }
        x[j + 1] = temp;
    }
}

void timSort(long long n, vector<long long> &x)
{
    long long i, left, mid, right;

    for (i = 0; i < n; i += RUN)
        insertionSort(i, min((i + RUN - 1), (n-1)), x);

    for (i = RUN; i < n; i = 2*i)
    {
        for (left = 0; left < n; left += 2 * i)
        {
            mid = left + i - 1;
            right = min((left + 2 * i - 1),(n-1));

              if(mid < right)
                Merge(left, mid, right, x);
        }
    }
}

/// ================= END OF TIMSORT SORT =================


long long get_time(int sort_index, long long n, long long valMax, vector<long long> x)
{
    if(sort_index == 0)
    {
        auto start = high_resolution_clock::now();
        sort(x.begin(), x.end());
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);
        return duration.count();
    }
    else if(sort_index == 1)
    {
        auto start = high_resolution_clock::now();
        RadixSort_base10(n, x);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);
        return duration.count();
    }
    else if(sort_index == 2 )
    {
        auto start = high_resolution_clock::now();
        RadixSort_base2power(n, 2, x);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);
        return duration.count();
    }
    else if(sort_index == 3)
    {
        auto start = high_resolution_clock::now();
        RadixSort_base2power(n, 256, x);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);
        return duration.count();
    }
    else if(sort_index == 4)
    {
        auto start = high_resolution_clock::now();
        ShellSort(n, x);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);
        return duration.count();
    }
    else if(sort_index == 5)
    {
        auto start = high_resolution_clock::now();
        ShellSort_Knuth(n, x);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);
        return duration.count();
    }
    else if(sort_index == 6)
    {
        auto start = high_resolution_clock::now();
        Merge_Sort(0, n - 1, x);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);
        return duration.count();
    }
    else if(sort_index == 7)
    {
        auto start = high_resolution_clock::now();
        regular_quick_sort(0, n - 1, x);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);
        return duration.count();
    }
    else if(sort_index == 8)
    {
        auto start = high_resolution_clock::now();
        quickSort_pivot_first(0, n - 1, x);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);
        return duration.count();
    }
    else if(sort_index == 9)
    {
        auto start = high_resolution_clock::now();
        quickSort_pivot_random(0, n - 1, x);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);
        return duration.count();
    }
    else if(sort_index == 10)
    {
        auto start = high_resolution_clock::now();
        quickSort_med_of_3(0, n - 1, x);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);
        return duration.count();
    }
    else if(sort_index == 11)
    {
        auto start = high_resolution_clock::now();
        timSort(n, x);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);
        return duration.count();
    }
}

void graph1(long long Min, long long Max, long long step, long long valMax)
{
    ofstream fout("graph1.csv");
    fout<<"N, STL sort, Radix sort base 10, Radix sort base 2, Radix sort base 2^16, Shell sort, Shell sort Knuth's increments, Merge sort, Quick sort simple, Quick sort pivot = first, Quick sort pivot = random, Quick sort median of 3, TimSort \n";
    for(long long n = Min; n <= Max; n += step)
    {
        fout<<n;
        vector<long long> copy_x2(n);
        generate_array(n, valMax, copy_x2);
        for(int index = 0; index <= 11 ; ++index)
            fout<<","<<get_time(index, n, valMax, copy_x2);
        fout<<"\n";
    }

    fout.close();

}

void graph2(long long Min, long long Max, long long n)
{
    ofstream fout("graph2.csv");
    fout<<"valMax, STL sort, Radix sort base 10, Radix sort base 2, Radix sort base 2^16, Shell sort, Shell sort Knuth's increments, Merge sort, Quick sort simple, Quick sort pivot = first, Quick sort pivot = random, Quick sort median of 3, TimSort \n";
    for(long long valMax = Min; valMax <= Max; valMax *= 1000)
    {
        fout<<valMax;
        vector<long long> copy_x2(n);
        generate_array(n, valMax, copy_x2);
        for(int index = 0; index <= 11; ++index)
            fout<<","<<get_time(index, n, valMax, copy_x2);
        fout<<"\n";
    }
}

int main()
{
     /*long long n, valMax;
     int test;

     fin>>test; ///nr de teste

     for(int i = 1; i <= test; ++i)
     {
         fin>>n>>valMax;
         cout<<"Test "<<i<<": n = "<<n<<" maxim = "<<valMax<<"\n \n";

         x = vector<long long>(n);
         vector <long long> copy_of_x(n);

         generate_array(n, valMax, x);
         copy_of_x = x;

         auto start = high_resolution_clock::now();
         sort(copy_of_x.begin(), copy_of_x.end());
         auto stop = high_resolution_clock::now();

         auto duration = duration_cast<milliseconds>(stop - start);
         cout<<"STL sort: "<<duration.count()<<" ms \n";

         ///***********RADIX SORT BASE 10*************

         copy_of_x = x;

         start = high_resolution_clock::now();
         RadixSort_base10(n, copy_of_x);
         stop = high_resolution_clock::now();

         if(test_sort(n, copy_of_x))
         {
             duration = duration_cast<milliseconds>(stop - start);
             cout<<"Radix sort base 10: "<<duration.count()<<" ms \n";
         }
         else
             cout<<"Radix sort base 10: FAILED \n";

         ///*******************************************

         ///***********RADIX SORT BASE 2***************

         copy_of_x = x;

         start = high_resolution_clock::now();
         RadixSort_base2power(n, 2, copy_of_x);
         stop = high_resolution_clock::now();

         if(test_sort(n, copy_of_x))
         {
             auto duration = duration_cast<milliseconds>(stop - start);
             cout<<"Radix sort base 2: "<<duration.count()<<" ms \n";
         }
         else
             cout<<"Radix sort base 2: FAILED \n";


         ///******************************************

         ///***********RADIX SORT BASE 2^16***********

         copy_of_x = x;

         start = high_resolution_clock::now();
         RadixSort_base2power(n, 256, copy_of_x);
         stop = high_resolution_clock::now();

         if(test_sort(n, copy_of_x))
         {
             auto duration = duration_cast<milliseconds>(stop - start);
             cout<<"Radix sort base 2^16: "<<duration.count()<<" ms \n";
         }
         else
             cout<<"Radix sort base 2^16: FAILED \n";

         ///************************************

         ///************MERGE SORT**************

         copy_of_x = x;

         start = high_resolution_clock::now();
         Merge_Sort(0, n - 1, copy_of_x);
         stop = high_resolution_clock::now();

         if(test_sort(n, copy_of_x))
         {
             duration = duration_cast<milliseconds>(stop - start);
             cout<<"Merge sort: "<<duration.count()<<" ms \n";
         }
         else
             cout<<"Merge sort: FAILED \n";


         ///************************************

         ///***********SHELL SORT***************

         copy_of_x = x;

         start = high_resolution_clock::now();
         ShellSort(n, copy_of_x);
         stop = high_resolution_clock::now();

         if(test_sort(n, copy_of_x))
         {
             auto duration = duration_cast<milliseconds>(stop - start);
             cout<<"Shell sort: "<<duration.count()<<" ms \n";
         }
         else
             cout<<"Shell sort: FAILED \n";
         ///************************************

         ///***********SHELL SORT KNUTH'S INCREMENTS************

         copy_of_x = x;

         start = high_resolution_clock::now();
         ShellSort_Knuth(n, copy_of_x);
         stop = high_resolution_clock::now();

         if(test_sort(n, copy_of_x))
         {
             auto duration = duration_cast<milliseconds>(stop - start);
             cout<<"Shell sort Knuth's increments: "<<duration.count()<<" ms \n";
         }
         else
             cout<<"Shell sort Knuth's increments: FAILED \n";


         ///************************************

         ///***********REGULAR QUICK SORT***************

         copy_of_x = x;

         start = high_resolution_clock::now();
         regular_quick_sort(0, n-1, copy_of_x);
         stop = high_resolution_clock::now();

         if(test_sort(n, copy_of_x))
         {
             auto duration = duration_cast<milliseconds>(stop - start);
             cout<<"Quick sort: "<<duration.count()<<" ms \n";
         }
         else
             cout<<"Quick sort: FAILED \n";

         ///************************************

         ///***********QUICK SORT: PIVOT = FIRST ELEMENT*******

         copy_of_x = x;

         start = high_resolution_clock::now();
         quickSort_pivot_first(0, n-1, copy_of_x);
         stop = high_resolution_clock::now();

         if(test_sort(n, copy_of_x))
         {
             auto duration = duration_cast<milliseconds>(stop - start);
             cout<<"Quick sort: pivot = first element: "<<duration.count()<<" ms \n";
         }
         else
             cout<<"Quick sort: pivot = first element: FAILED \n";


         ///************************************

         ///***********QUICK SORT: PIVOT RANDOM***************

         copy_of_x = x;

         start = high_resolution_clock::now();
         quickSort_pivot_random(0, n-1, copy_of_x);
         stop = high_resolution_clock::now();

         if(test_sort(n, copy_of_x))
         {
             auto duration = duration_cast<milliseconds>(stop - start);
             cout<<"Quick sort: pivot random: "<<duration.count()<<" ms \n";
         }
         else
             cout<<"Quick sort: pivot random: FAILED \n";
         ///************************************

         ///***********QUICK SORT MEDIAN OF 3***************

         copy_of_x = x;

         start = high_resolution_clock::now();
         quickSort_med_of_3(0, n-1, copy_of_x);
         stop = high_resolution_clock::now();

         if(test_sort(n, copy_of_x))
         {
             auto duration = duration_cast<milliseconds>(stop - start);
             cout<<"Quick sort median of 3: "<<duration.count()<<" ms \n";
         }
         else
             cout<<"Quick sort median of 3: FAILED \n";


         ///************************************

         ///***********TIMSORT***************

         copy_of_x = x;

         start = high_resolution_clock::now();
         timSort(n, copy_of_x);
         stop = high_resolution_clock::now();

         if(test_sort(n, copy_of_x))
         {
             auto duration = duration_cast<milliseconds>(stop - start);
             cout<<"TimSort sort: "<<duration.count()<<" ms \n";
         }
         else
             cout<<"TimSort: FAILED \n";

         cout<<"\n \n";

     }
*/
    graph1(1000, 1000000000, 1000, 10000);
    cout<<"done";

    graph2(1000, 1000000000, 100000);
    cout<<"done";

    return 0;
}
