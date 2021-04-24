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

// ð�������㷨
// �����Ƚϣ����������Сֵ���ͶԻ�
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

// ˼·��ÿ��ѭ�������ҵ�һ����Сֵ���ڲ��뵽���ʵ�λ����
template <typename T>
void SelectionSort(T arr[], int size)
{
	if (0 == size)  { return;  }

    int min_index = 0;
	for (int i = 0; i < size; ++i) {
        min_index = i;
        // ��[i, size)�������ҵ���Сֵ
        for (int j = i + 1; j < size; ++j) {
            if (arr[min_index] > arr[j]) { 
                min_index = j;
            } // for j
        } // for i

        std::swap(arr[i], arr[min_index]);
	}
}

// �����鿴Ϊ�������֣�һ�������ź���ģ�һ������δ����ġ�
// ��δ����Ĳ��֣�һ���������ź���Ĳ��ֽ��бȽϣ������С����Ի��������ֱ�ӽ���
// insert ��������ƣ��������ֵ����һ����Χ���Ҵ�С���ڷֲ��Ĳ��Ǻ������ʱ��
// �ڽ��������������insert�����Ч�ʷǳ���
template <typename T>
void InsertSort(T arr[], int size)
{
    // Ĭ�ϵ�һ��Ԫ�����ź����

    // ��һ�棺�㷨
    /*
    for (int i = 1; i < size; ++i) {
        for (int j = i; j > 0 && arr[j] < arr[j-1]; --j) {
            std::swap(arr[j], arr[j-1]);
        }
    }
    */

    // �ڶ��棺�Ż��㷨���Ż���˼·���Ǽ���ֵ�ý��������ø��Ʋ�����
    // �����������Ż���ʱ��Ч�ʾͱ�select sort�죬ͬʱinsert sort������ǰ��ֹѭ��
	for (int i = 1; i < size; ++i) {
        T insert_value = arr[i];
        // j ����insert_valueӦ�ò����λ��
        int j = i;
        for (; j > 0 && arr[j-1] > insert_value ; --j) {
            // std::swap(arr[j], arr[j-1]);
            // �ú����ֵ����ǰ���ֵ���ϵض��
            arr[j] = arr[j-1];
        }
        // ���շ��صľ���Ӧ�ò�insert_valueӦ����Ҫ�����λ��
        arr[j] = insert_value;
	}
}

// ���䣺[left, right]
template <typename T>
void InsertSort(T arr[], int left, int right)
{
    for (int i = left+1; i <= right; ++i) {
        T insert_value = arr[i];
        int j = i;
        // 1.j ����>= left����Ϊj-1���ܻᳬ������λ��
        // 2.arr[j-1]����Ϊarr[j]����insert_vlaue�Լ�����Ҫ�ٺ��Լ��Ƚ�
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
    // 0��ʾȫ��
    if (0 != printnums) {
        temp_print_size = printnums;
    } else if (printnums < 0) {
        // С��0��ʾ�Ӻ���ǰ��ӡ
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

// ����������飬�����Ϊ[left, right)
// ����������ظ����õ�ʱ�����ɵ������������һ���ġ�
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

// ���ظ����õ������������������Ҫ�������������������������
int *GenerateRandomArray2(size_t size, int left, int right)
{
    assert(left <= right);

    int *arr = new int[size];

    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % (right - left + 1) + left;
    }

    return arr;
}

// �ж������Ƿ��������
template <typename T>
bool IsSorted(T arr[], size_t size)
{
    for (int i = 0; i < size - 1; ++i) {
        if (arr[i] > arr[i + 1]) { return false; }
    }

    return true;
}

// copyһ�����鵽����һ��������
int *CopyArr(int *source, size_t size)
{
    int *dest = new int[size];

    // ʹ��C++��copy�㷨
    for (int i = 0; i < size; ++i) {
        dest[i] = source[i];
    }

    return dest;
}

// ����һ���������������
// swap_times���������������̶�
// swap_times = 0 ������������
// swap_timesԽ�󣬷��ص�����Խ����
int *GenerateNearlyOrderArray(size_t size, int swap_times)
{
    // 1.������һ�����������
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
        // ��Ҫ�����������
        // 1.left ����Ѿ�������
        // 2.right ����Ѿ�������
        // 3.new_arr[left_bak-left] > arr[middle_bak-left]
        // 4.new_arr[left_bak-left] < arr[middle_bak-left]

        // notice:
        // 1.�ڴ����ʱ��Ҫ���������1,2,3,4��˳����д���
        // 2.�ڽ������ݱȽϵģ�����ʹ��ԭ����arr���бȽϣ���Ϊ�ڴ��������arr��ֵ�Ǳ仯��.

        T *new_arr = new T[right - left+1];
        for (int i = 0; i <= right - left; ++i) {
            new_arr[i] = arr[left+i];
        }

         int left_bak   = left;
         //[left, middle] Ϊ��߲���
         //[middle+1, right] Ϊ�ұ߲���
         // ����������Ҫ+1
         int middle_bak = middle + 1;
         for (int k = left; k <= right; ++k) {
               // left ����Ѿ�������
               if (left_bak > middle) {
                   arr[k] = new_arr[middle_bak-left];
                   ++middle_bak;
               } else if (middle_bak > right) {
                   // right ����Ѿ�������
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
        // �Ż���1��������Բ���insert�㷨�����Ż�
        if (right-left <= 15) {
            InsertSort(arr, left, right);
            return;
        }

        int middle = (right-left) / 2 + left;
        // [0, middle]
        _MergeSort(arr, left, middle);
        _MergeSort(arr, middle+1, right);
        // _Merge(arr, left, middle, right);
        // �Ż���2���������������ľͲ���Ҫ������
        // ���arr[middle] < arr[middle+1]�Ͳ���Ҫ�������ˡ�
        if (arr[middle] > arr[middle+1]) {
            _Merge(arr, left, middle, right);
        }
    }

    template <typename T>
    void _MergeSortBottomUp(T arr[], size_t left, size_t right)
    {
        // sort_num��ʾleft, right��sort_num������Ҫ�ϲ�
        for (int sort_num = 1; sort_num <= right; sort_num += sort_num) {
            // 0, 1 -> 2, 3 -> 4, 5��Ҫindex��Ҫ����sort_num+sort_num��ƫ��
            for (int index = 0; index + sort_num <= right; index += sort_num+sort_num) {
                // ע�������ı߽�����
                // left = index, middle = index+sort_num-1, right = middle+sort_num 
                // ע������Ϊʲô��Ҫ-1,��Ϊ��middle��������0��ʼ�����ܴ�1��ʼ
                // �����1��ʼ���ͻ���Ϊ[0,1]������������������ġ�
                _Merge(arr, index, index+sort_num-1, std::min<T>(index+sort_num+sort_num-1, right));
            }  // for index
        } // for sort_num
    }
}

// �Զ����µı�����ʽ�����ַ�ʽֻ֧��array������ʵ�����
template <typename T>
void MergeSort(T arr[], int size)
{
    MergeSortHelper::_MergeSort(arr, 0, size-1);
}

// �Ե����ϵķ�ʽ������֧��������û��ʹ������������������
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
    // 1.�Ż����������һ��ֵ
    std::swap(arr[left], arr[rand()%(right-left+1)+left]);

	// left_bakʼ��ָ��С�ڵ���pivot������
    int left_bak = left;
    T value = arr[left];
    for (int i = left + 1; i <= right; ++i) {
        if (arr[i] < value) {
            ++left_bak;
            std::swap(arr[i], arr[left_bak]);
        }
    }
    // ���ܲ��������Ľ�����value�Ǹ���ʱֵ��������Ҫ���ǽ���left��left_bakλ���ϵ�ֵ
    // std::swap(value, arr[left_bak]);
    std::swap(arr[left], arr[left_bak]);

    return left_bak;
}

// 2·�����㷨
// ����˼�룺
// 1.���ǵ�һ��λ�õ�����Ϊ��׼��
// 2.���ǰ����������2�����֣�һ����<arr[0]���֣�һ����>arr[0]����
// 3.left(���ϵ���ѵȥѰ��)��ʾ��ߵĵ�һ������arr[0], right(���ϵ���ѵȥѰ��)��ʾ�ұߵ�һ��С��arr[0]
// 4.��󽻻�λ�õ�ֵ
template <typename T>
int _paritial2(T arr[], int left, int right)
{
    // 1.�Ż����������һ��ֵ
    std::swap(arr[left], arr[rand()%(right-left+1)+left]);

	T pivot_value	= arr[left];
	int left_bak	= left+1;
	int right_bak	= right;

	//[left,left_bak) <= pivot_value
	//(right_bak, right] >= pivot_value
	while (true) {
		// ע�����ﲻʹ��arr[left_bak]<=pivot_value��arr[right_bak]>=pivot_value
		// ���Ǽ���������������[0, 1, 1, 1, 1, 1, 1, 1, 1]
		// ����������ڵķ�ʽ����ô�ͻ᷵���м������
		// �����������>=�ķ�ʽ���ͻ᷵�ص����ڶ�����������������������Ĳ�ƽ�⣬����Ч�ʽ���
		while (left_bak <= right && arr[left_bak] < pivot_value) ++left_bak;
		while (right_bak >= left+1 && arr[right_bak] > pivot_value) --right_bak;

		if (left_bak > right_bak) { break; }

		std::swap (arr[left_bak], arr[right_bak]);
		++left_bak;
		--right_bak;
	}

	// right_bakʼ��ָ��<pivot������
	std::swap (arr[right_bak], arr[left]);

    return right_bak;
}

// 1.ע�����ַ�ʽ��quick sort����������ȫ���������£����ӶȾͻ��˻�ΪO(n^2)
// ÿ�ζ���ȡ������ĵ�һ��Ԫ����Ϊ��׼����������ȫ����������
// ÿ�ηֳ����������飬����left��ֻ��һ��Ԫ�أ�right����ʣ�µ�Ԫ��
// ͬʱ��Ҫע���������������£��������̫������stack over flow
// 2.��ȡ�������ȡ�����е�һ��ֵ��Ϊ��׼���Ͳ������1����˵���������
template <typename T>
void _QuickSort(T arr[], int left, int right)
{
    // if (left > right) { return; }
    // 1.��ȡ��merge sortͬ���ķ�ʽ
    if (right - left <= 25) {
        InsertSort<T>(arr, left, right);
        return;
    }

    // ��������Ҫ�ҳ�ÿ�ηָ�֮���������Ԫ�صĵ�ַ
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
    // 1.��ȡ��merge sortͬ���ķ�ʽ
    if (right - left <= 15) {
        InsertSort<T>(arr, left, right);
        return;
    }

    // ��������Ҫ�ҳ�ÿ�ηָ�֮���������Ԫ�صĵ�ַ
    int index = _paritial2(arr, left, right);

    // [left, index-1]
    _QuickSort2(arr, left, index-1);
    // [index+1, right]
    _QuickSort2(arr, index+1, right);
}

// 3·quick sort
// 3·����ĺ��ľ��ǣ������鿴��3������[left, lt-1] > value, [lt,gt] == value, [gt+1, right] < value
template <typename T>
void _QuickSort3(T arr[], int left, int right)
{
    // 1.��ȡ��merge sortͬ���ķ�ʽ
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
    // ����ʱ������
    srand(time(nullptr));

	// ��һ��quick sort
    QuickSortHelper::_QuickSort(arr, 0, size-1);
}

// �ڶ���2·quick sort
template <typename T>
void QuickSort2(T arr[], int size)
{
    // ����ʱ������
    srand(time(nullptr));

    QuickSortHelper::_QuickSort2(arr, 0, size-1);
}

// ������3·quick sort
template <typename T>
void QuickSort3(T arr[], int size)
{
    // ����ʱ������
    srand(time(nullptr));

    QuickSortHelper::_QuickSort3(arr, 0, size-1);
}

}

#endif // _sorthelper_
