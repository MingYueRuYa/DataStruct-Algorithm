#ifndef _sorthelper_
#define _sorthelper_

#include <ctime>
#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>

using std::min;
using std::cout;
using std::endl;
using std::wstring;
using std::swap;

namespace SortHelper{

    enum SortType {
        S_Unknow,
        S_Select,
        S_End
    };

// 冒泡排序算法
// 两两比较，如果遇到较小值，就对换
template <typename T>
void BubbleSort(T arr[], int size)
{
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[i] > arr[j]) {
                std::swap(arr[i], arr[j]);
            } // if (arr[i] > arr[j])
        } // for j
    } // for i
}

// 思路：每次循环都是找到一个最小值，在插入到合适的位置中
template <typename T>
void SelectionSort(T arr[], int size)
{
	if (0 == size)  { return;  }

    int min_index = 0;
	for (int i = 0; i < size; ++i) {
        min_index = i;
        // 在[i, size)区间内找到最小值
        for (int j = i + 1; j < size; ++j) {
            if (arr[min_index] > arr[j]) { 
                min_index = j;
            } // for j
        } // for i

        std::swap(arr[i], arr[min_index]);
	}
}

// 将数组看为两个部分，一部分是排好序的，一部分是未排序的。
// 将未排序的部分，一个个的与排好序的部分进行比较，如果是小于则对换，否则就直接结束
// insert 排序的优势：在排序的值，在一定范围内且大小存在分布的不是很随机的时候
// 在近乎有序的条件，insert排序的效率非常高
template <typename T>
void InsertSort(T arr[], int size)
{
    // 默认第一个元素是排好序的

    // 第一版：算法
    /*
    for (int i = 1; i < size; ++i) {
        for (int j = i; j > 0 && arr[j] < arr[j-1]; --j) {
            std::swap(arr[j], arr[j-1]);
        }
    }
    */

    // 第二版：优化算法，优化的思路就是减少值得交换，采用复制操作。
    // 经过这样的优化，时间效率就比select sort快，同时insert sort可以提前终止循环
	for (int i = 1; i < size; ++i) {
        T insert_value = arr[i];
        // j 保留insert_value应该插入的位置
        int j = i;
        for (; j > 0 && arr[j-1] > insert_value ; --j) {
            // std::swap(arr[j], arr[j-1]);
            // 让后面的值，把前面的值不断地额覆盖
            arr[j] = arr[j-1];
        }
        // 最终返回的就是应该插insert_value应该需要插入的位置
        arr[j] = insert_value;
	}
}

// 区间：[left, right]
template <typename T>
void InsertSort(T arr[], int left, int right)
{
    for (int i = left+1; i <= right; ++i) {
        T insert_value = arr[i];
        int j = i;
        // 1.j 不能>= left，因为j-1可能会超出索引位置
        // 2.arr[j-1]是因为arr[j]就是insert_vlaue自己不需要再和自己比较
        for (; j > left && arr[j-1] > insert_value; --j) {
                arr[j] = arr[j-1];
        }
        arr[j] = insert_value;
    }
}

template<typename T>
void PrintArray(T arr, int size)
{
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template<typename T>
void PrintArray(T arr, int size, int printnums)
{
    int temp_print_size = size;
    // 0表示全部
    if (0 != printnums) {
        temp_print_size = printnums;
    } else if (printnums < 0) {
        // 小于0表示从后往前打印
        temp_print_size = printnums;
    }

    if (printnums >= 0) { 
		for (int i = 0; i < temp_print_size; ++i) {
			cout << arr[i] << " ";
		}
    } else {
		for (int i = temp_print_size; temp_print_size == 0; ++temp_print_size) {
			cout << arr[--size] << " ";
		}
    }

    cout << endl;
}

// 随机生成数组，随机数为[left, right)
// 这个函数在重复调用的时候，生成的随机数可能是一样的。
int *GenerateRandomArray(size_t size, int left, int right)
{
    assert(left <= right);

    int *arr = new int[size];

    srand(time(nullptr));

    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % (right - left + 1) + left;
    }

    return arr;
}

// 可重复调用的生成随机数，但是需要调用者主动设置随机数的种子
int *GenerateRandomArray2(size_t size, int left, int right)
{
    assert(left <= right);

    int *arr = new int[size];

    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % (right - left + 1) + left;
    }

    return arr;
}

// 判断数组是否是有序的
template <typename T>
bool IsSorted(T arr[], size_t size)
{
    for (int i = 0; i < size - 1; ++i) {
        if (arr[i] > arr[i + 1]) { return false; }
    }

    return true;
}

// copy一个数组到另外一个数组中
int *CopyArr(int *source, size_t size)
{
    int *dest = new int[size];

    // 使用C++的copy算法
    for (int i = 0; i < size; ++i) {
        dest[i] = source[i];
    }

    return dest;
}

// 生成一个近乎有序的数组
// swap_times定义了数组的无序程度
// swap_times = 0 数组就是有序的
// swap_times越大，返回的数组越无序
int *GenerateNearlyOrderArray(size_t size, int swap_times)
{
    // 1.先生成一个有序的数组
    int *arr = new int[size];

    for (int i = 0; i < size; ++i) {
        arr[i] = i;
    }

    srand(time(nullptr));

    for (int i = 0; i < swap_times; ++i) {
        int pos_x = rand() % size;
        int pos_y = rand() % size;
        std::swap(arr[pos_x], arr[pos_y]);
    }

    return arr;
}

void TestSort(const wstring &sortName, int sortArr[], int size, void(*sortFun)(int arr[], int size))
{
    clock_t start_time = clock();

    sortFun(sortArr, size);

    clock_t end_time = clock();

    std::wcout << sortName.c_str() << L" : " 
         << static_cast<double>(end_time - start_time)/ CLOCKS_PER_SEC 
         << L" s" << endl;

    assert(IsSorted(sortArr, size));
}

namespace MergeSortHelper
{
    template <typename T>
    void _Merge(T arr[], size_t left, size_t middle, size_t right)
    {
        // 需要处理四种情况
        // 1.left 这边已经处理完
        // 2.right 这边已经处理完
        // 3.new_arr[left_bak-left] > arr[middle_bak-left]
        // 4.new_arr[left_bak-left] < arr[middle_bak-left]

        // notice:
        // 1.在处理的时候，要按照上面的1,2,3,4的顺序进行处理
        // 2.在进行数据比较的，不能使用原来的arr进行比较，因为在处理过程中arr的值是变化的.

        T *new_arr = new T[right - left+1];
        for (int i = 0; i <= right - left; ++i) {
            new_arr[i] = arr[left+i];
        }

         int left_bak   = left;
         //[left, middle] 为左边部分
         //[middle+1, right] 为右边部分
         // 所以这里需要+1
         int middle_bak = middle + 1;
         for (int k = left; k <= right; ++k) {
               // left 这边已经处理完
               if (left_bak > middle) {
                   arr[k] = new_arr[middle_bak-left];
                   ++middle_bak;
               } else if (middle_bak > right) {
                   // right 这边已经处理完
                   arr[k] = new_arr[left_bak-left];
                   ++left_bak;
               } else if (new_arr[left_bak-left] < new_arr[middle_bak-left]) {  
                   // left < right
                   arr[k] = new_arr[left_bak-left];
                   ++left_bak;
               } else {
                   // right < left
                   arr[k] = new_arr[middle_bak-left];
                   ++middle_bak;
               } // if left_bak > middle

         } // for left_bak

         delete[] new_arr;
    }

    template <typename T>
    void _MergeSort(T arr[], size_t left, size_t right)
    {
        // if (left >= right) { return; }
        // 优化点1：这里可以采用insert算法进行优化
        if (right-left <= 15) {
            InsertSort(arr, left, right);
            return;
        }

        int middle = (right-left) / 2 + left;
        // [0, middle]
        _MergeSort(arr, left, middle);
        _MergeSort(arr, middle+1, right);
        // _Merge(arr, left, middle, right);
        // 优化点2：如果数组是有序的就不需要在排序
        // 如果arr[middle] < arr[middle+1]就不需要在排序了。
        if (arr[middle] > arr[middle+1]) {
            _Merge(arr, left, middle, right);
        }
    }

    template <typename T>
    void _MergeSortBottomUp(T arr[], size_t left, size_t right)
    {
        // sort_num表示left, right有sort_num个数需要合并
        for (int sort_num = 1; sort_num <= right; sort_num += sort_num) {
            // 0, 1 -> 2, 3 -> 4, 5需要index需要加上sort_num+sort_num的偏移
            for (int index = 0; index + sort_num <= right; index += sort_num+sort_num) {
                // 注意索引的边界问题
                // left = index, middle = index+sort_num-1, right = middle+sort_num 
                // 注意这里为什么需要-1,是为了middle的索引从0开始，不能从1开始
                // 如果从1开始，就会认为[0,1]这个区间的序列是有序的。
                _Merge(arr, index, index+sort_num-1, std::min<T>(index+sort_num+sort_num-1, right));
            }  // for index
        } // for sort_num
    }
}

// 自顶向下的遍历方式，这种方式只支持array随机访问的特性
template <typename T>
void MergeSort(T arr[], int size)
{
    MergeSortHelper::_MergeSort(arr, 0, size-1);
}

// 自底向上的方式，可以支持链表，它没有使用数组的随机访问特性
template <typename T>
void MergeSortBottomUp(T arr[], int size)
{
    // [0, size-1]
    MergeSortHelper::_MergeSortBottomUp(arr, 0, size-1);
}

namespace QuickSortHelper
{

template <typename T>
int _paritial(T arr[], int left, int right)
{
    // 1.优化点随机交换一个值
    std::swap(arr[left], arr[rand()%(right-left+1)+left]);

	// left_bak始终指向小于等于pivot的索引
    int left_bak = left;
    T value = arr[left];
    for (int i = left + 1; i <= right; ++i) {
        if (arr[i] < value) {
            ++left_bak;
            std::swap(arr[i], arr[left_bak]);
        }
    }
    // 不能采用这样的交换，value是个临时值。我们需要的是交换left，left_bak位置上的值
    // std::swap(value, arr[left_bak]);
    std::swap(arr[left], arr[left_bak]);

    return left_bak;
}

// 2路排序算法
// 核心思想：
// 1.还是第一个位置的数组为基准。
// 2.还是把数组想象成2个部分，一个是<arr[0]部分，一个是>arr[0]部分
// 3.left(不断的轮训去寻找)表示左边的第一个大于arr[0], right(不断的轮训去寻找)表示右边第一个小于arr[0]
// 4.最后交换位置的值
template <typename T>
int _paritial2(T arr[], int left, int right)
{
    // 1.优化点随机交换一个值
    std::swap(arr[left], arr[rand()%(right-left+1)+left]);

	T pivot_value	= arr[left];
	int left_bak	= left+1;
	int right_bak	= right;

	//[left,left_bak) <= pivot_value
	//(right_bak, right] >= pivot_value
	while (true) {
		// 注意这里不使用arr[left_bak]<=pivot_value和arr[right_bak]>=pivot_value
		// 考虑极端情况如果数组是[0, 1, 1, 1, 1, 1, 1, 1, 1]
		// 如果采用现在的方式，那么就会返回中间的索引
		// 但是如果采用>=的方式，就会返回倒数第二个的索引，这样会造成树的不平衡，导致效率降低
		while (left_bak <= right && arr[left_bak] < pivot_value) ++left_bak;
		while (right_bak >= left+1 && arr[right_bak] > pivot_value) --right_bak;

		if (left_bak > right_bak) { break; }

		std::swap (arr[left_bak], arr[right_bak]);
		++left_bak;
		--right_bak;
	}

	// right_bak始终指向<pivot的索引
	std::swap (arr[right_bak], arr[left]);

    return right_bak;
}

// 1.注意这种方式的quick sort在数组是完全有序的情况下，复杂度就会退化为O(n^2)
// 每次都是取出数组的第一个元素作为基准，在数组完全有序的情况下
// 每次分出的两组数组，都是left都只有一个元素，right就是剩下的元素
// 同时需要注意在以有序的情况下，如果数量太大会造成stack over flow
// 2.采取了随机获取数组中的一个值作为基准，就不会造成1中所说的那种情况
template <typename T>
void _QuickSort(T arr[], int left, int right)
{
    // if (left > right) { return; }
    // 1.采取和merge sort同样的方式
    if (right - left <= 25) {
        InsertSort<T>(arr, left, right);
        return;
    }

    // 这里是需要找出每次分割之后数组的首元素的地址
    int index = _paritial(arr, left, right);

    // [left, index-1]
    _QuickSort(arr, left, index-1);
    // [index+1, right]
    _QuickSort(arr, index+1, right);
}

template <typename T>
void _QuickSort2(T arr[], int left, int right)
{
    // if (left > right) { return; }
    // 1.采取和merge sort同样的方式
    if (right - left <= 15) {
        InsertSort<T>(arr, left, right);
        return;
    }

    // 这里是需要找出每次分割之后数组的首元素的地址
    int index = _paritial2(arr, left, right);

    // [left, index-1]
    _QuickSort2(arr, left, index-1);
    // [index+1, right]
    _QuickSort2(arr, index+1, right);
}

// 3路quick sort
// 3路排序的核心就是：将数组看成3个部分[left, lt-1] > value, [lt,gt] == value, [gt+1, right] < value
template <typename T>
void _QuickSort3(T arr[], int left, int right)
{
    // 1.采取和merge sort同样的方式
    if (right - left <= 15) {
        InsertSort<T>(arr, left, right);
        return;
    }
	
	std::swap(arr[left], arr[rand () % (right - left + 1) + left]);

	// [left, lt) < value, [lt, gt) == value, [gt, right] > value
	int lt	= left;
	int gt	= right+1;
	int i	= left+1;
	T value = arr[left];
	while (i < gt) {
		if (arr[i] < value) {
			std::swap(arr[i], arr[lt+1]);
			++i;
			++lt;
		} else if (arr[i] > value) {
			std::swap(arr[i], arr[gt-1]);
			--gt;
		} else {
			i++;
		}
	}

	std::swap (arr[left], arr[lt]);

    // [left, lt-1]
    _QuickSort3(arr, left, lt-1);
    // [gt, right]
    _QuickSort3(arr, gt, right);
}

}

template <typename T>
void QuickSort(T arr[], int size)
{
    // 设置时间种子
    srand(time(nullptr));

	// 第一种quick sort
    QuickSortHelper::_QuickSort(arr, 0, size-1);
}

// 第二种2路quick sort
template <typename T>
void QuickSort2(T arr[], int size)
{
    // 设置时间种子
    srand(time(nullptr));

    QuickSortHelper::_QuickSort2(arr, 0, size-1);
}

// 第三种3路quick sort
template <typename T>
void QuickSort3(T arr[], int size)
{
    // 设置时间种子
    srand(time(nullptr));

    QuickSortHelper::_QuickSort3(arr, 0, size-1);
}

}

#endif // _sorthelper_
