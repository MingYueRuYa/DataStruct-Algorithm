#pragma once

#include "sorthelper.h"

//1.如何找到数组的一共有多少逆序对
// 逆序对可以衡量一个数组的有序程度，如果逆序对越多表示这个数组越混乱
// 使用归并排序的思路
//2.如何找到一个数组中第k位的数值是多少
namespace homework
{
	long long _Merge(int arr[], int left, int middle, int right)
	{
		int* aux = new int[right-left+1];

		for (int i = 0; i < right - left + 1; ++i) {
			aux[i] = arr[left + i];
		}

		int left_bak	= left;
		int middle_bak	= middle+1;
		long long num	= 0;

		for (int k = left; k <= right; ++k) {
			// left已经比较完了
			if (left_bak > middle) {
				arr[k] = aux[middle_bak-left];
				++middle_bak;
			} else if (middle_bak > right) {
				arr[k] = aux[left_bak-left];
				++left_bak;
			} else if (aux[left_bak-left] < aux[middle_bak-left]) {
				arr[k] = aux[left_bak-left];
				++left_bak;
			} else {
				// right < left
				arr[k] = aux[middle_bak-left];
				++middle_bak;
				// 因为aux[middle_bak] < aux[left_bak]，所以还剩下的middle-left_bak+1都是
				// 逆序对
				num += (middle-left_bak+1);
			}
		}

		delete[] aux;
		aux = nullptr;

		return num;
	}

	long long _MergeSort(int arr[], int left, int right)
	{
		if (left >= right) { return 0; }

		int middle = (right - left) / 2 + left;
		long long num1 = _MergeSort(arr, left, middle);
		long long num2 = _MergeSort(arr, middle+1, right);

		return num1 + num2 + _Merge(arr, left, middle, right);
	}


	long long MergeSort(int arr[], size_t size)
	{
		return _MergeSort(arr, 0, size-1);
	}

	void test_arr_chaos()
	{
		size_t size= 10000;
		// 测试随机数组
		int *new_arr = SortHelper::GenerateRandomArray(size, 0, 10);

		cout << "number: " << homework::MergeSort(new_arr, size) << endl;

		delete[] new_arr;
		new_arr = nullptr;

		// 测试有序数组，逆序对应该是0
		new_arr = SortHelper::GenerateNearlyOrderArray(size, 0);
		cout << "number: " << homework::MergeSort(new_arr, size) << endl;
		// "number:0"

		delete[] new_arr;
		new_arr = nullptr;
	}

	int _partition(int *arr, int left, int right)
	{
		// 可以优化
		int value = arr[left];

		int left_bak	= left+1;
		int right_bak	= right;
		while(true) {
			while (left_bak <= right && arr[left_bak] < value) { ++left_bak; }
			while (left+1 <= right_bak && arr[right_bak] > value) { --right_bak; }

			if (left_bak > right_bak) { break; }

			std::swap(arr[left_bak], arr[right_bak]);
			++left_bak;
			--right_bak;
		}
		
		std::swap(arr[left], arr[right_bak]);

		return right_bak;
	}

	//[left, right]
	int QuickSort(int *arr, int findpos, int left, int right)
	{
		// 为什么这里需要发挥arr[left];
		// if (left == right) { return arr[left]; }
		if (left > right) { return 0; }

		int pos = _partition(arr, left, right);
	
		if (pos == findpos) { return arr[pos]; }

		if (findpos > pos) {
			// 去找上半部分
			return QuickSort(arr, findpos, pos+1, right);
		} else {
			// 去找下半部分
			return QuickSort(arr, findpos, left, pos-1);
		}

	}

	//2.找到数组中第k个位置的元素
	int FindKPosValue(int *arr, size_t pos, size_t size)
	{
		assert(pos >= 0 && pos <= size-1);

		return QuickSort(arr, pos, 0, size-1);
	}

	void test_find_k_pos_value(int pos)
	{
		int size = 10;
		srand(time(nullptr));
		for (int i = 0; i < 10; ++i) {
			int *arr = SortHelper::GenerateRandomArray2(size, 0, 10);

			int value = FindKPosValue(arr, pos, size);

			SortHelper::PrintArray(arr, size);

			std::cout << "find "<< pos <<" pos:" << value << std::endl;

			delete[] arr;
		}
	}

}


