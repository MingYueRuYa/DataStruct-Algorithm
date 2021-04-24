#ifndef heap_h
#define heap_h

#include "sorthelper.h"

#include <ctime>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

//2021-2-6 10:59:39

/*

                                               98
                        /                                              \
                       97                                              97
            /                      \                        /                      \
           88                      92                      96                      96
      /          \            /          \            /          \            /          \
     82          83          65          90          56          58          43          91
   /    \      /    \      /    \      /    \      /    \      /    \      /    \      /    \
  79    79    69    72    41    53    39    72    23    41    11    15    27    40    51    58
 / \   / \   / \   / \   / \   / \   / \   / \   / \   / \   / \   / \   / \   / \   / \   / \
24 25 15 66 47 23 57  5 25 26 36 52 32 38 16 65 2  10 37
*/

// data struct and algorithm
namespace DSA
{
    namespace Heap {
		// �󶥶��еĵ�һ��λ�ÿճ���������
		// [0, 6, 5, 4, 3, 2, 2, 1]
		template<typename Item>	
		class MaxHeap
		{
		public:
			// ���캯������ʼ�����������
			MaxHeap(int capacity) {
				data = new Item[capacity+1];
				this->count = 0;
				this->capacity = capacity;
			}

			MaxHeap(Item item[], int size) {
				data = new Item[size+1];
				this->count = size;
				this->capacity = size;

				for (int i = 0; i < size; ++i) {
					data[i + 1] = item[i];
				}

				for (int parent_node = count / 2; parent_node >= 1; --parent_node) {
					shiftDown(parent_node);
				}

			}

			~MaxHeap() {
				delete[] data;
				data = nullptr;
			}

			// ���ض��е����ж��ٸ�Ԫ��
			int size() {
				return this->count; 
			}

			// �ж϶����Ƿ�Ϊ��
			int empty() { return 0 == this->count; }

			// ����Ԫ��
			void insert(Item newdata) {
				assert(count+1 <= capacity);
				data[count + 1] = newdata;

				shiftUp(count+1);
				count++;
			}

			// ����һ��Ԫ��
			Item extractItem() {
				assert(count > 0);

				Item ret = data[1];
				std::swap(data[count], data[1]);
				count--;
				shiftDown(1);

				return ret;
			}

			// ��ȡ��������Ԫ��
			Item maxItem() {
				return data[1];
			}

		private:
			void shiftUp(int pos) {
				// 1.���ϵ��ҳ����ڵ㣬�븸�ڵ�Ա�
				// ����ȸ��ڵ�󣬾��븸�ڵ㽻���������˳�
				// ע���ٽ��������pos > 1
				while(pos > 1 && data[pos/2] < data[pos]) {
					std::swap(data[pos/2], data[pos]);
					pos /= 2;
				}
			}

			void shiftDown(int pos) {
				// ��������Ϊ1��ʼ���������������Ƚ��бȽ�
				// �����������бȽ���֮���ں͸��ڵ���бȽϣ�����ȸ��ڵ�󣬾ͽ��жԵ���
				// ���С�����˳��Ƚ�
				// ע��������ٽ�������2*pos == count����Ϊ���һ���ĸ��ڵ����û���Һ���
				while (2*pos <= count) {
					// left node
					int child_node = pos * 2;
					// child_node +1 --> right node
					// �Ƚ������ӽڵ�˭��˭С
					if (child_node+1 <= count && 
						data[child_node] < data[child_node+1]) {
						++child_node;
					}
					
					// �����ӽڵ��ں͸��ڵ�Ƚ�
					// ������ڵ��ֱ�ӷ��أ�����ϴ���ӽڵ�ͺ͸��ڵ�Ի�
					if (data[pos] > data[child_node]) { break; }

					std::swap(data[pos], data[child_node]);

					// �ߵ���һ�ڵ�
					pos = child_node;
				}
			}

		public:
			// ����״��ӡ�����ѽṹ
			void testPrint(){

				// ���ǵ�testPrintֻ�ܴ�ӡ100��Ԫ�����ڵĶѵ���״��Ϣ
				if( size() >= 100 ){
					cout<<"This print function can only work for less than 100 int";
					return;
				}

				// ���ǵ�testPrintֻ�ܴ���������Ϣ
				if( typeid(Item) != typeid(int) ){
					cout <<"This print function can only work for int item";
					return;
				}

				cout<<"The max heap size is: "<<size()<<endl;
				cout<<"Data in the max heap: ";
				for( int i = 1 ; i <= size() ; i ++ ){
					// ���ǵ�testPrintҪ����е�����������[0, 100)�ķ�Χ��
					assert( data[i] >= 0 && data[i] < 100 );
					cout<<data[i]<<" ";
				}
				cout<<endl;
				cout<<endl;

				int n = size();
				int max_level = 0;
				int number_per_level = 1;
				while( n > 0 ) {
					max_level += 1;
					n -= number_per_level;
					number_per_level *= 2;
				}

				int max_level_number = int(pow(2, max_level-1));
				int cur_tree_max_level_number = max_level_number;
				int index = 1;
				for( int level = 0 ; level < max_level ; level ++ ){
					string line1 = string(max_level_number*3-1, ' ');

					int cur_level_number = min(count-int(pow(2,level))+1,int(pow(2,level)));
					bool isLeft = true;
					for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index ++ , index_cur_level ++ ){
						putNumberInLine( data[index] , line1 , index_cur_level , cur_tree_max_level_number*3-1 , isLeft );
						isLeft = !isLeft;
					}
					cout<<line1<<endl;

					if( level == max_level - 1 )
						break;

					string line2 = string(max_level_number*3-1, ' ');
					for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index_cur_level ++ )
						putBranchInLine( line2 , index_cur_level , cur_tree_max_level_number*3-1 );
					cout<<line2<<endl;

					cur_tree_max_level_number /= 2;
				}
			}

		private:
			void putNumberInLine( int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft){

				int sub_tree_width = (cur_tree_width - 1) / 2;
				int offset = index_cur_level * (cur_tree_width+1) + sub_tree_width;
				assert(offset + 1 < line.size());
				if( num >= 10 ) {
					line[offset + 0] = '0' + num / 10;
					line[offset + 1] = '0' + num % 10;
				}
				else{
					if( isLeft)
						line[offset + 0] = '0' + num;
					else
						line[offset + 1] = '0' + num;
				}
			}

			void putBranchInLine( string &line, int index_cur_level, int cur_tree_width){

				int sub_tree_width = (cur_tree_width - 1) / 2;
				int sub_sub_tree_width = (sub_tree_width - 1) / 2;
				int offset_left = index_cur_level * (cur_tree_width+1) + sub_sub_tree_width;
				assert( offset_left + 1 < line.size() );
				int offset_right = index_cur_level * (cur_tree_width+1) + sub_tree_width + 1 + sub_sub_tree_width;
				assert( offset_right < line.size() );

				line[offset_left + 1] = '/';
				line[offset_right + 0] = '\\';
			}
		private:
			Item* data;
			int count;
			int capacity;

		};

		template<typename Item>	
		class IndexMaxHeap
		{
		public:
			// ���캯������ʼ�����������
			IndexMaxHeap(int capacity) {
				data = new Item[capacity+1];
				indexes = new int[capacity+1];
				data[0] = 0;
				indexes[0] = 0;
				this->count = 0;
				this->capacity = capacity;
			}

			/*
			IndexMaxHeap(Item item[], int size) {
				data = new Item[size+1];
				indexes = new int[capacity+1];
				data[0] = 0;
				indexes[0] = 0;
				this->count = size;
				this->capacity = size;

				for (int i = 0; i < size; ++i) {
					data[i + 1] = item[i];
					indexes[i + 1] = i;
				}

				for (int parent_node = count / 2; parent_node >= 1; --parent_node) {
					shiftDown(parent_node);
				}
			}
			*/
			~IndexMaxHeap() {
				delete[] data;
				data = nullptr;

				delete[] indexes;
				indexes = nullptr;
			}

			// ���ض��е����ж��ٸ�Ԫ��
			int size() {
				return this->count; 
			}

			// �ж϶����Ƿ�Ϊ��
			int empty() { return 0 == this->count; }

			// ����Ԫ��
			// ���û���˵�����µ�Ԫ�أ�Ԫ��������0��ʼ
			void insert(int data_index, Item newdata) {
				assert(count+1 <= capacity);
				data_index += 1;
				count++;
				indexes[count] = data_index;
				data[data_index] = newdata;

				shiftUp(count);
			}

			// ����һ��Ԫ�أ��޸Ļ�������ֵ
			Item extractItem() {
				assert(count > 0);

				Item ret = data[indexes[1]];
				std::swap(data[indexes[count]], data[indexes[1]]);
				count--;
				shiftDown(1);

				return ret;
			}

			// ȡ���Ѷ����Ԫ�ص�����
			int getMaxHeapIndex() {
				int max_index = indexes[1] - 1;

				std::swap(data[indexes[count]], data[indexes[1]]);
				count--;
				shiftDown(1);

				return max_index;
			}

			// ��ȡ��������Ԫ��
			Item maxItem() {
				return data[indexes[1]];
			}

			int getMaxIndex() {
				return indexes[1] - 1;
			}

			Item getItem(int data_index) {
				return data[indexes[data_index + 1]];
			}

			// �û���������0��ʼ�ģ�������ʵ���Ǵ�1��ʼ
			// ����data_index += 1;
			void change(int data_index, Item new_data) {
				assert(data_index+1 <= count);
				
				data_index += 1;

				// ע��indexes��˳��������������ڴ��˳��
				// ʵ����indexes���汣�����data�����ݵ�����
				data[indexes[data_index]] = new_data;
				shiftUp(data_index);
				shiftDown(data_index);

				//1.�ҵ�����ʵ�ʶ�Ӧ������λ��
				/*
				int actual_index = 0;
				data_index += 1;
				int i = 0;
				for (i = 1; i <= count; ++i) {
					if (indexes[i] == data_index) {
						break;
					}
				} // for i

				if (0 == i) { 
					assert(false);
					return; 
				}

				data[i] = new_data;
				shiftUp(i);
				shiftDown(i);
				*/
			}

		public:
			// ����״��ӡ�����ѽṹ
			void testPrint(){

				// ���ǵ�testPrintֻ�ܴ�ӡ100��Ԫ�����ڵĶѵ���״��Ϣ
				if( size() >= 100 ){
					cout<<"This print function can only work for less than 100 int";
					return;
				}

				// ���ǵ�testPrintֻ�ܴ���������Ϣ
				if( typeid(Item) != typeid(int) ){
					cout <<"This print function can only work for int item";
					return;
				}

				cout<<"The max heap size is: "<<size()<<endl;
				cout<<"Data in the max heap: ";
				for( int i = 1 ; i <= size() ; i ++ ){
					// ���ǵ�testPrintҪ����е�����������[0, 100)�ķ�Χ��
					assert( data[indexes[i]] >= 0 && data[indexes[i]] < 100 );
					cout<<data[indexes[i]]<<" ";
				}
				cout<<endl;
				cout<<endl;

				int n = size();
				int max_level = 0;
				int number_per_level = 1;
				while( n > 0 ) {
					max_level += 1;
					n -= number_per_level;
					number_per_level *= 2;
				}

				int max_level_number = int(pow(2, max_level-1));
				int cur_tree_max_level_number = max_level_number;
				int data_index = 1;
				for( int level = 0 ; level < max_level ; level ++ ){
					string line1 = string(max_level_number*3-1, ' ');

					int cur_level_number = min(count-int(pow(2,level))+1,int(pow(2,level)));
					bool isLeft = true;
					for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; data_index ++ , index_cur_level ++ ){
						putNumberInLine( data[indexes[data_index]] , line1 , index_cur_level , cur_tree_max_level_number*3-1 , isLeft );
						isLeft = !isLeft;
					}
					cout<<line1<<endl;

					if( level == max_level - 1 )
						break;

					string line2 = string(max_level_number*3-1, ' ');
					for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index_cur_level ++ )
						putBranchInLine( line2 , index_cur_level , cur_tree_max_level_number*3-1 );
					cout<<line2<<endl;

					cur_tree_max_level_number /= 2;
				}
			}

		private:
			void putNumberInLine( int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft){

				int sub_tree_width = (cur_tree_width - 1) / 2;
				int offset = index_cur_level * (cur_tree_width+1) + sub_tree_width;
				assert(offset + 1 < line.size());
				if( num >= 10 ) {
					line[offset + 0] = '0' + num / 10;
					line[offset + 1] = '0' + num % 10;
				}
				else{
					if( isLeft)
						line[offset + 0] = '0' + num;
					else
						line[offset + 1] = '0' + num;
				}
			}

			void putBranchInLine( string &line, int index_cur_level, int cur_tree_width){

				int sub_tree_width = (cur_tree_width - 1) / 2;
				int sub_sub_tree_width = (sub_tree_width - 1) / 2;
				int offset_left = index_cur_level * (cur_tree_width+1) + sub_sub_tree_width;
				assert( offset_left + 1 < line.size() );
				int offset_right = index_cur_level * (cur_tree_width+1) + sub_tree_width + 1 + sub_sub_tree_width;
				assert( offset_right < line.size() );

				line[offset_left + 1] = '/';
				line[offset_right + 0] = '\\';
			}

		private:
			// ��������, ����֮��ıȽϸ���data�Ĵ�С���бȽ�, ��ʵ�ʲ�����������
			void shiftUp(int pos) {
				// 1.���ϵ��ҳ����ڵ㣬�븸�ڵ�Ա�
				// ����ȸ��ڵ�󣬾��븸�ڵ㽻���������˳�
				// ע���ٽ��������pos > 1
				while(pos > 1 && data[indexes[pos/2]] < data[indexes[pos]]) {
					std::swap(indexes[pos/2], indexes[pos]);
					pos /= 2;
				}
			}

			void shiftDown(int pos) {
				// ��������Ϊ1��ʼ���������������Ƚ��бȽ�
				// �����������бȽ���֮���ں͸��ڵ���бȽϣ�����ȸ��ڵ�󣬾ͽ��жԵ���
				// ���С�����˳��Ƚ�
				// ע��������ٽ�������2*pos == count����Ϊ���һ���ĸ��ڵ����û���Һ���
				while (2*pos <= count) {
					// left node
					int child_node = pos * 2;
					// child_node +1 --> right node
					// �Ƚ������ӽڵ�˭��˭С
					if (child_node+1 <= count && 
						data[indexes[child_node]] < data[indexes[child_node+1]]) {
						++child_node;
					}
					
					// �����ӽڵ��ں͸��ڵ�Ƚ�
					// ������ڵ��ֱ�ӷ��أ�����ϴ���ӽڵ�ͺ͸��ڵ�Ի�
					if (data[indexes[pos]] > data[indexes[child_node]]) { break; }

					std::swap(indexes[pos], indexes[child_node]);

					// �ߵ���һ�ڵ�
					pos = child_node;
				}
			}

		public:
			void PrintIndexData() {
				std::cout << "index ";
				for (int i = 0; i < count+1; ++i) {
					cout << indexes[i] << " ";
				}
				cout << endl;

				std::cout << "data ";
				for (int i = 0; i < count+1; ++i) {
					cout << data[i] << " ";
				}
				cout << endl;
			}

		private:
			Item* data = nullptr;
			int* indexes = nullptr;
			int count = 0;
			int capacity = 0;

		};

		void test_heap() {
			MaxHeap<int> max_heap = MaxHeap<int>(100);
			srand(time(nullptr));

			for (int i = 0; i < 50; ++i) {
				max_heap.insert(rand()%100);
			}

			max_heap.testPrint();
			cout << endl;

			while (! max_heap.empty()) {
				cout << max_heap.extractItem() << " ";
			}
			cout << endl;

			int size = 50;
			int range[] = { 0, 50 };
			int *arr = SortHelper::GenerateRandomArray(size, range[0], range[1]);

			MaxHeap<int> max_heap2 = MaxHeap<int>(arr, size);
			max_heap2.testPrint();
			cout << endl;

			delete[] arr;
		}

		void test_index_max_heap() {
			IndexMaxHeap<int> index_max_heap = IndexMaxHeap<int>(100);
			srand(time(nullptr));

			int value = 0;
			for (int i = 0; i < 10; ++i) {
				value = rand() % 10;
				index_max_heap.insert(i, value);
				cout << value << " ";
			}
			cout << endl;
			index_max_heap.testPrint();

			int data = index_max_heap.getItem(0);
			cout << "get item 0 position data:" << data << endl;

			cout << endl;
			index_max_heap.testPrint();

			data = index_max_heap.extractItem();
			cout << "get item max:" << data << endl;
			index_max_heap.testPrint();

			// int data_index = index_max_heap.getMaxHeapIndex();
			// cout << "get max index:" << data_index << endl;
			// index_max_heap.testPrint();

			// IndexMaxHeap<int> index_max_heap2 = IndexMaxHeap<int>(100);
			// for (int i = 1; i < 6; ++i) {
				// index_max_heap2.insert(i-1, i*10);
				// cout << value << " ";
			// }
			// cout << endl;
			// index_max_heap2.testPrint();


			while (1) {
				int change_value = 0, change_position = 0;
				cout << "input change position:";
				std::cin >> change_position;

				cout << "input change value:";
				std::cin >> change_value;

				cout << "input change value:" << change_value << endl;
				cout << "input change postion:" << change_position << endl;

				index_max_heap.change(change_position, change_value);
				cout << "change 5 position value is 30:" << endl;
				index_max_heap.testPrint();
			}

			// print result:
			// 4 9 8 2 4 1 3 5 4 7
			// The max heap size is: 10
			// Data in the max heap: 9 7 8 4 5 1 3 2 4 4
			// 
			//            9
			//       /          \
			//      7            8
			//    /    \      /    \
			//   4      5    1      3
			//  / \   / \   / \   / \
			// 2   4 4
			// get item 0 position data:9
			// 
			// The max heap size is: 10
			// Data in the max heap: 9 7 8 4 5 1 3 2 4 4
			// 
			//            9
			//       /          \
			//      7            8
			//    /    \      /    \
			//   4      5    1      3
			//  / \   / \   / \   / \
			// 2   4 4
			// get item max:9
			// The max heap size is: 9
			// Data in the max heap: 8 7 4 4 5 1 3 2 4
			// 
			//            8
			//       /          \
			//      7            4
			//    /    \      /    \
			//   4      5    1      3
			//  / \   / \   / \   / \
			// 2   4
			// get max index:2
			// The max heap size is: 8
			// Data in the max heap: 7 5 4 4 4 1 3 2
			// 
			//            7
			//       /          \
			//      5            4
			//    /    \      /    \
			//   4      4    1      3
			//  / \   / \   / \   / \
			// 2
			// change 1 position value is 30:
			// The max heap size is: 8
			// Data in the max heap: 30 5 7 4 4 1 3 2
			// 
			//            30
			//       /          \
			//      5            7
			//    /    \      /    \
			//   4      4    1      3
			//  / \   / \   / \   / \
			// 2

//			max_heap.testPrint();
//			cout << endl;
//
//			while (! max_heap.empty()) {
//				cout << max_heap.extractItem() << " ";
//			}
//			cout << endl;
//
//			int size = 50;
//			int range[] = { 0, 50 };
//			int *arr = SortHelper::GenerateRandomArray(size, range[0], range[1]);
//
//			MaxHeap<int> max_heap2 = MaxHeap<int>(arr, size);
//			max_heap2.testPrint();
//			cout << endl;
//
//			delete[] arr;
		}

		template<typename T>
		void heapSort1(T arr[], int size) {
			MaxHeap<T> max_heap = MaxHeap<T>(size);

			for (int i = 0; i < size; ++i) {
				max_heap.insert(arr[i]);
			}

			for (int i = size - 1; i >= 0; --i) {
				arr[i] = max_heap.extractItem();
			}
		}

		template<typename T>
		void heapSort2(T arr[], int size) {
			MaxHeap<T> max_heap = MaxHeap<T>(arr, size);

			for (int i = size - 1; i >= 0; --i) {
				arr[i] = max_heap.extractItem();
			}
		}

		void test_heap_sort() {
			int n = 1000000;

			// ����1 һ���Բ���
			cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;
			int *arr1 = SortHelper::GenerateRandomArray(n,0,10);
			int *arr2 = SortHelper::CopyArr(arr1, n);
			int *arr3 = SortHelper::CopyArr(arr1, n);
			int *arr4 = SortHelper::CopyArr(arr1, n);
			int *arr5 = SortHelper::CopyArr(arr1, n);
			int *arr6 = SortHelper::CopyArr(arr1, n);

			SortHelper::TestSort(L"Merge Sort", arr1, n, SortHelper::MergeSort);
			SortHelper::TestSort(L"Quick Sort", arr2, n, SortHelper::QuickSort);
			SortHelper::TestSort(L"Quick Sort 2 Ways", arr3, n, SortHelper::QuickSort2);
			SortHelper::TestSort(L"Quick Sort 3 Ways", arr4, n, SortHelper::QuickSort3);
			SortHelper::TestSort(L"Heap Sort 1", arr5, n, heapSort1);
			SortHelper::TestSort(L"Heap Sort 2", arr6, n, heapSort2);

			delete[] arr1;
			delete[] arr2;
			delete[] arr3;
			delete[] arr4;
			delete[] arr5;
			delete[] arr6;

			cout<<endl;


			// ����2 ���Խ������������
			int swapTimes = 100;
			cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;
			arr1 = SortHelper::GenerateRandomArray(n,0,10);
			arr2 = SortHelper::CopyArr(arr1, n);
			arr3 = SortHelper::CopyArr(arr1, n);
			arr4 = SortHelper::CopyArr(arr1, n);
			arr5 = SortHelper::CopyArr(arr1, n);
			arr6 = SortHelper::CopyArr(arr1, n);

			SortHelper::TestSort(L"Merge Sort", arr1, n, SortHelper::MergeSort);
			SortHelper::TestSort(L"Quick Sort", arr2, n, SortHelper::QuickSort);
			SortHelper::TestSort(L"Quick Sort 2 Ways", arr3, n, SortHelper::QuickSort2);
			SortHelper::TestSort(L"Quick Sort 3 Ways", arr4, n, SortHelper::QuickSort3);
			SortHelper::TestSort(L"Heap Sort 1", arr5, n, heapSort1);
			SortHelper::TestSort(L"Heap Sort 2", arr6, n, heapSort2);

			delete[] arr1;
			delete[] arr2;
			delete[] arr3;
			delete[] arr4;
			delete[] arr5;
			delete[] arr6;

			cout<<endl;

			// ����3 ���Դ��ڰ���������ͬԪ�ص�����
			cout<<"Test for random array, size = "<<n<<", random range [0,10]"<<endl;
			arr1 = SortHelper::GenerateRandomArray(n,0,10);
			arr2 = SortHelper::CopyArr(arr1, n);
			arr3 = SortHelper::CopyArr(arr1, n);
			arr4 = SortHelper::CopyArr(arr1, n);
			arr5 = SortHelper::CopyArr(arr1, n);
			arr6 = SortHelper::CopyArr(arr1, n);

			SortHelper::TestSort(L"Merge Sort", arr1, n, SortHelper::MergeSort);
			// ���������, ��ͨ��QuickSort�˻�ΪO(n^2)���㷨, ��������
			//SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
			SortHelper::TestSort(L"Quick Sort 2 Ways", arr3, n, SortHelper::QuickSort2);
			SortHelper::TestSort(L"Quick Sort 3 Ways", arr4, n, SortHelper::QuickSort3);
			SortHelper::TestSort(L"Heap Sort 1", arr5, n, heapSort1);
			SortHelper::TestSort(L"Heap Sort 2", arr6, n, heapSort2);

			delete[] arr1;
			delete[] arr2;
			delete[] arr3;
			delete[] arr4;
			delete[] arr5;
			delete[] arr6;

			// Test for random array, size = 1000000, random range [0, 1000000]
			// Merge Sort : 0.395 s
			// Quick Sort : 134.312 s
			// Quick Sort 2 Ways : 1.008 s
			// Quick Sort 3 Ways : 0.348 s
			// Heap Sort 1 : 2.786 s
			// Heap Sort 2 : 2.708 s
 
			// Test for nearly ordered array, size = 1000000, swap time = 100
			// Merge Sort : 0.21 s
			// Quick Sort : 135.385 s
			// Quick Sort 2 Ways : 1.007 s
			// Quick Sort 3 Ways : 0.316 s
			// Heap Sort 1 : 2.845 s
			// Heap Sort 2 : 2.78 s
 
			// Test for random array, size = 1000000, random range [0,10]
			// Merge Sort : 0.21 s
			// Quick Sort 2 Ways : 1.009 s
			// Quick Sort 3 Ways : 0.444 s
			// Heap Sort 1 : 2.826 s
			// Heap Sort 2 : 2.749 s
		}
	}

}

#endif // heap_h
