#pragma once

#include "sorthelper.h"

void compare_insert_select()
{
    int size = 20000;
    int range_arr[2] = {0, 3};

//     int *select_arr = SortHelper::GenerateRandomArray(size, range_arr[0], range_arr[1]);
//     int *insert_arr = SortHelper::CopyArr(select_arr, size);
// 
//     SortHelper::TestSort(L"insert sort", insert_arr, size, SortHelper::InsertSort);
//     SortHelper::TestSort(L"select sort", select_arr, size, SortHelper::SelectionSort);

     int *select_arr = SortHelper::GenerateNearlyOrderArray(size, 300);
     int *insert_arr = SortHelper::CopyArr(select_arr, size);
     SortHelper::TestSort(L"insert sort", insert_arr, size, SortHelper::InsertSort);
     SortHelper::TestSort(L"select sort", select_arr, size, SortHelper::SelectionSort);

    delete[] select_arr;
    delete[] insert_arr;
}

void compare_bubble_select()
{
     int size = 20000;
     int range_arr[2] = {0, 1000};
 
     int *bubble_arr = SortHelper::GenerateRandomArray(size, range_arr[0], range_arr[1]);
     int *select_arr = SortHelper::CopyArr(bubble_arr, size);
 
     SortHelper::TestSort(L"bubble sort", bubble_arr, size, SortHelper::BubbleSort);
     SortHelper::TestSort(L"select sort", select_arr, size, SortHelper::SelectionSort);
     delete[] select_arr;
     delete[] bubble_arr;
}

void test_merge_sort()
{
    size_t size = 100000;
    int range[] = {0, 1000};
    int *arr        = SortHelper::GenerateRandomArray(size, range[0], range[1]);
    int *arr2       = SortHelper::CopyArr(arr, size);

    SortHelper::TestSort(L"Merge Sort", arr, size, SortHelper::MergeSort);
    SortHelper::TestSort(L"Insert Sort", arr2, size, SortHelper::InsertSort);
    
    delete[] arr;
    delete[] arr2;
}

void test_merge_bottom_up_sort()
{
    size_t size = 100000;
    int range[] = {0, 1000};
    int *arr        = SortHelper::GenerateRandomArray(size, range[0], range[1]);
    int *arr2       = SortHelper::CopyArr(arr, size);

    SortHelper::TestSort(L"Merge Bottom Up Sort", arr, size, SortHelper::MergeSortBottomUp);
    SortHelper::TestSort(L"Insert Sort", arr2, size, SortHelper::InsertSort);
    
    delete[] arr;
    delete[] arr2;
}

void test_quick_sort()
{
    size_t size = 100000;
    int range[] = {0, 1000};
    int *arr    = SortHelper::GenerateRandomArray(size, range[0], range[1]);
    int *arr2	= SortHelper::CopyArr (arr, size);
	
	// ���Ե������������
    SortHelper::TestSort (L"Merge Bottom Up Sort", arr, size, SortHelper::MergeSortBottomUp);
    SortHelper::TestSort(L"Quick Sort", arr2, size, SortHelper::QuickSort);
    
    delete[] arr;
    delete[] arr2;

    cout << "test generate order array " << endl;

	// ������������£��������̫��ֱ�������stack over flow
	// ������������
    size	= 10000;
    arr		= SortHelper::GenerateNearlyOrderArray(size, 0);
	arr2	= SortHelper::CopyArr(arr, size);

    SortHelper::TestSort (L"Merge Bottom Up Sort", arr, size, SortHelper::MergeSortBottomUp);
    SortHelper::TestSort(L"Quick Sort", arr2, size, SortHelper::QuickSort);

    delete[] arr;
    delete[] arr2;
}

// ����2·quick sort
void test_quick_sort2()
{
    size_t size = 1000000;
    int range[] = {0, 1000};
	// ���Դ��������ظ�������
    int *arr    = SortHelper::GenerateRandomArray(size, range[0], 10);
    int *arr2	= SortHelper::CopyArr (arr, size);

    SortHelper::TestSort (L"Quick Sort", arr, size, SortHelper::QuickSort);
    SortHelper::TestSort(L"Quick Sort2", arr2, size, SortHelper::QuickSort2);

    delete[] arr;
    delete[] arr2;
}

// ����3·quick sort
void test_quick_sort3()
{
    size_t size = 1000000;
    int range[] = {0, 1000};
	// ���Դ��������ظ�������
    int *arr    = SortHelper::GenerateRandomArray(size, range[0], 10);
    int *arr2	= SortHelper::CopyArr (arr, size);
    int *arr3	= SortHelper::CopyArr (arr, size);

    // SortHelper::TestSort (L"Quick Sort", arr, size, SortHelper::QuickSort);
    SortHelper::TestSort(L"Quick Sort2", arr2, size, SortHelper::QuickSort2);
    SortHelper::TestSort(L"Quick Sort3", arr3, size, SortHelper::QuickSort3);

    delete[] arr;
    delete[] arr2;
    delete[] arr3;
}
