// 二叉搜索树

#ifndef binary_search_tree_h
#define binary_search_tree_h

#include <ctime>
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

// data struct and algorithm
namespace DSA {
namespace BinarySearchTree {
	// 二分法查找，在有序的数组中，查找target
	// 如果找到target，返回响应的索引index
	// 如果没有target，返回-1
	template<typename T>
	int binarySearch(T arr[], int n, T target)
	{
		// 在[left, right]范围中查找
		int left = 0, right = n-1;
		// 注意这里如果采用(left+right)/2可能会产生溢出
		int mid = left + (right-left)/2;
		while (left <= right) {
			if (target == arr[mid]) {
				return mid;
			} else if (target < arr[mid]) { 
				// [left, mid-1]范围中找
				right = mid-1;
			} else if (target > arr[mid]) {
				// [mid+1, right]范围中找
				left = mid+1;
			}
		}

		return -1;
	}

	// 采用递归的方式查找
	// 在区间[left, right]中查找
	template<typename T>
	int _binarySearch2(T arr[], int left, int right, T target)
	{
		if (left >= right) {
			return -1;
		}

		int mid = left + (right-left)/2;
		if (target == arr[mid]) {
			return mid;
		} else if (target < arr[mid]) {
			// right = mid-1;
			return _binarySearch2(arr, left, mid-1, target);
		} else if (target > arr[mid]) {
			// left = mid+1;
			return _binarySearch2(arr, mid + 1, right, target);
		}
	}

	template<typename T>
	int binarySearch2(T arr[], int n, T target)
	{
		return _binarySearch2(arr, 0, n-1, target);
	}

	void test_for_recursion_effciency()
	{
		int n = 1000000;
		int* a = new int[n];
		for (int i = 0; i < n; i++)
			a[i] = i;

		// 测试非递归二分查找法
		clock_t startTime = clock();

		// 对于我们的待查找数组[0...N)
		// 对[0...N)区间的数值使用二分查找，最终结果应该就是数字本身
		// 对[N...2*N)区间的数值使用二分查找，因为这些数字不在arr中，结果为-1
		for (int i = 0; i < 2 * n; i++) {
			int v = binarySearch(a, n, i);
			if (i < n)
				assert(v == i);
			else
				assert(v == -1);
		}
		clock_t endTime = clock();
		cout << "Binary Search (Without Recursion): " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

		// 测试递归的二分查找法
		startTime = clock();

		for (int i = 0; i < 2 * n; i++) {
			int v = binarySearch2(a, n, i);
			if (i < n)
				assert(v == i);
			else
				assert(v == -1);
		}
		endTime = clock();
		cout << "Binary Search (Recursion): " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

		delete[] a;
	}
}
}

#endif // binary_search_tree_h
