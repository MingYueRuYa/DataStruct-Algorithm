// 二叉搜索树

#ifndef binary_search_tree_h
#define binary_search_tree_h

#include "FileOps.h"
#include "SequenceST.h"

#include <ctime>
#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include <deque>

using std::cout;
using std::endl;
using std::vector;
using std::deque;
using std::string;

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
		while (left <= right) {
			// 注意这里如果采用(left+right)/2可能会产生溢出
			int mid = left + (right-left)/2;
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
		if (left >= right) { return -1; }

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

		return -1;
	}

	template<typename T>
	int binarySearch2(T arr[], int n, T target)
	{
		return _binarySearch2(arr, 0, n-1, target);
	}

	void test_for_recursion_effciency()
	{
		int n = 100000;
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
		}
		clock_t endTime = clock();
		cout << "Binary Search (Without Recursion): " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

		// 测试递归的二分查找法
		startTime = clock();

		for (int i = 0; i < 2 * n; i++) {
			int v = binarySearch2(a, n, i);
		}
		endTime = clock();
		cout << "Binary Search (Recursion): " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

		delete[] a;
	}

	template<typename Key, typename Value>
	class BinarySearchTree {
	private:
		struct Node {
			Key key;
			Value value;
			Node *left;
			Node *right;

			Node(Key key, Value value) {
				this->key = key;
				this->value = value;
				this->left = this->right = nullptr;
			}
		};

		// 向以node为根的二分搜索树中, 插入节点(key, value), 使用递归算法
		// 返回插入新节点后的二分搜索树的根
		Node * _insert(Node *node, Key key, Value value)
		{
			if (nullptr == node) {
				++count;
				node = new Node(key, value);
				return node;
			}

			if (node->key == key) {
				node->value = value;
			} else if (key < node->key) {
				node->left = _insert(node->left, key, value);
			} else if (key > node->key) {
				node->right = _insert(node->right, key, value);
			}

			return node;
		}

		// 查看以node为根的二分搜索树中是否包含键值为key的节点, 使用递归算法
		bool _contain(Node *node, Key key)
		{
			if (nullptr == node) { return false; }

			if (node->key == key) {
				return true;
			} else if (key < node->key) {
				return _contain(node->left, key);
			} else if (key > node->key) {
				return _contain(node->right, key);
			}

			return false;
		}

		Value* _search(Node *node, Key key)
		{
			if (nullptr == node) { return nullptr; }

			if (node->key == key) {
				return &(node->value);
			} else if (key < node->key) {
				return _search(node->left, key);
			} else if (key > node->key) {
				return _search(node->right, key);
			}

			return nullptr;
		}

		void _inOrder(Node *node) 
		{
			if (nullptr == node) { return; }

			cout << node->key << " ";

			_inOrder(node->left);
			_inOrder(node->right);
		}

		void _midOrder(Node *node) {
			if (nullptr == node) { return; }

			_midOrder(node->left);
			cout << node->key << " "; 
			_midOrder(node->right);
		}

		void _postOrder(Node *node) {
			if (nullptr == node) { return; }

			_postOrder(node->left);
			_postOrder(node->right);
			cout << node->key << " "; 
		}

		// 返回二叉树最小的节点
		Node* _miniKey(Node* node) {
			if (nullptr == node->left) {
				return node;
			}

			return _miniKey(node->left);
		}

		// 返回二叉树最大的节点
		Node* _maxKey(Node* node) {
			if (nullptr == node->right) {
				return node;
			}

			return _maxKey(node->right);
		}

		Node *_removeMinKey(Node *node) {
			if (nullptr == node->left) {
				Node *node_right = node->right;
				delete node;
				--count;
				return node_right;
			}

			node->left = _removeMinKey(node->left);
			return node;
		}

		Node *_removeMaxKey(Node *node) {
			if (nullptr == node->right) {
				Node *node_left = node->left;
				delete node;
				--count;
				return node_left;
			}

			node->right = _removeMaxKey(node->right);
			return node;
		}

		int count = 0;
		Node *root = nullptr;

	public:
		BinarySearchTree() {}
		~BinarySearchTree() {
			// 采用层次遍历的方式，释放节点
			destroy(root);
		}

		// 返回二叉搜索树中的元素个数
		int size() {
			return count;
		}

		// 是否为空
		bool isEmpty() {
			return 0 == count;
		}

		void insert(Key key, Value value)
		{
			root = _insert(root, key, value);
		}

		bool contain(Key key)
		{
			return _contain(root, key);
		}

		Value *search(Key key)
		{
			return _search(root, key);
		}

		// 前序遍历
		void inOrder() {
			_inOrder(root);
			cout << endl;
		}

		// 中序遍历
		void midOrder() {
			_midOrder(root);
			cout << endl;
		}

		void postOrder() {
			_postOrder(root);
			cout << endl;
		}

		// 层次遍历
		// 在进行层次遍历的时候，需要借助队列容器
		void levelOrder() {
			deque<Node*> node_queue = {root};
			while (! node_queue.empty()) {
				Node* node = node_queue.front();
				node_queue.pop_front();

				if (nullptr == node) { continue; }
				cout << node->key << " ";
				
				if (nullptr != node->left) {
					node_queue.push_back(node->left);
				}

				if (nullptr != node->right) {
					node_queue.push_back(node->right);
				}
			}
		}

		// 以后序的方式进行释放内存，先是left节点，后是right节点，在父节点
		void destroy(Node *node) {
			if (nullptr == node) { return; }

			destroy(node->left);
			destroy(node->right);

			cout << node->key << " ";

			delete node;
			node = nullptr;
			--count;
		}


		Key* miniKey() {
			if (nullptr == root) { return nullptr; }
			Node* node = _miniKey(root);
			return nullptr == node ? nullptr : &node->key;
		}

		Key* maxKey() {
			if (nullptr == root) { return nullptr; }
			Node *node = _maxKey(root);

			return nullptr == node ? nullptr : &node->key;
		}

		void removeMinKey() {
			root = _removeMinKey(root);
		}

		void removeMaxKey() {
			root = _removeMaxKey(root);
		}
	};

	void test_bst_search()
	{
		string file_name = "../test_files/bible.txt";
		vector<string> words = {};
		if (! FileOps::readFile(file_name, words)) {
			cout << "read bible file error." << endl;
			return;
		}

		cout << "There are totally " << words.size() << " words in " << file_name << endl;
		cout << endl;

		time_t startTime = clock();

		BinarySearchTree<string, int> bst_words = BinarySearchTree<string, int>();
		for(auto &item : words) {
			int *count = bst_words.search(item);
			if (nullptr == count) {
				bst_words.insert(item, 1);
			} else {
				++(*count);
			}
		}

        // 输出圣经中god一词出现的频率
        if(bst_words.contain("god"))
            cout << "'god' : " << *bst_words.search("god") << endl;
        else
            cout << "No word 'god' in " << file_name << endl;

        time_t endTime = clock();

        cout << "BST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
        cout << endl;

		// 测试顺序查找表 SST
		startTime = clock();

		// 统计圣经中所有词的词频
		// 注: 这个词频统计法相对简陋, 没有考虑很多文本处理中的特殊问题
		// 在这里只做性能测试用
		SequenceST<string, int> sst = SequenceST<string, int>();
		for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
			int* res = sst.search(*iter);
			if (res == NULL)
				sst.insert(*iter, 1);
			else
				(*res)++;
		}

		// 输出圣经中god一词出现的频率
		if (sst.contain("god"))
			cout << "'god' : " << *sst.search("god") << endl;
		else
			cout << "No word 'god' in " << file_name << endl;

		endTime = clock();

		cout << "SST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
	}

	void test_bst_traverse()
	{
		BinarySearchTree<int, int> bst = BinarySearchTree<int, int>();

		bst.insert(10, 5);
		bst.insert(5, 5);
		bst.insert(6, 5);
		bst.insert(20, 5);
		bst.insert(8, 5);
		bst.insert(4, 5);

		bst.inOrder();
		bst.midOrder();
		bst.postOrder();
		bst.levelOrder();
		// in order: 10 5 4 6 8 20
		// mid order: 4 5 6 8 10 20
		// post order: 4 8 6 5 20 10
		// level orfer: 10 5 20 4 6 8
	}

	void test_bst_destroy() {
		BinarySearchTree<int, int> bst = BinarySearchTree<int, int>();
		bst.insert(10, 1);
		bst.insert(5, 2);
		bst.insert(6, 3);
		bst.insert(20, 4);
		bst.insert(8, 5);
		bst.insert(4, 6);
	}

	void test_bst_min_max_key() {
		BinarySearchTree<int, int> bst = BinarySearchTree<int, int>();
		bst.insert(10, 1);
		bst.insert(5, 2);
		bst.insert(6, 3);
		bst.insert(20, 4);
		bst.insert(8, 5);
		bst.insert(4, 6);

		int* min_key = bst.miniKey();
		int* max_key = bst.maxKey();

		cout << "bst min key:" << *min_key << endl;
		cout << "bst max key:" << *max_key << endl;
	}

	void test_bst_remove_min_max_key()
	{
		BinarySearchTree<int, int> bst = BinarySearchTree<int, int>();
		bst.insert(10, 1);
		bst.insert(5, 2);
		bst.insert(6, 3);
		bst.insert(20, 4);
		bst.insert(8, 5);
		bst.insert(4, 6);

		bst.levelOrder();
		cout << endl;
		
		bst.removeMinKey();
		bst.removeMaxKey();
	}

}
}

#endif // binary_search_tree_h
