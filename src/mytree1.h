#include <iostream>
#include <vector> // ����� ������ ��� ������� ������������� tree(InputIt first, InputIt last)
using namespace std;

template <typename T>
struct tnode { // ��������� ����
	T field;
	struct tnode* left;
	struct tnode* right;
};


template<typename _Ty, typename node = tnode<_Ty>>
class tree
{
public:
	// ��� �����, ����� ������ ������ :)
	using value_type = _Ty;
	using tree_t = tree<value_type, node>;
	using reference_type = value_type&;
	using pointer_type = value_type*;
	// ���� ���������� �������. � ����� ������ ��� ��������� �� ����� ��������� ����. ����� �������� �� bool ��� reference_type
	using insertion_result = pointer_type;


	// ������������
	tree(std::initializer_list<value_type> il_) { // ��������� ��������� ������ ����� ������ ������������� tree<int>  t {1, 2, 3, 4, 5};
		for (const auto& val : il_) {
			insert(val);
		}
	};


	tree(tree_t&& _tree) { // (move semantics) ��������� ������ ����������� �������� ������ ������ � ������, ��� ���� ������ ���������� ����� (��������� ������ ����������)
		root = std::move(_tree.root);
		_tree.root = nullptr;
		nodesCount = _tree.nodesCount;
		_tree.nodesCount = 0;
	};


	tree(const tree_t& _tree) { // ����������� ���������� ������ � ������ (��������� ������ ����������)
		root = nullptr;
		copy(_tree.root, root);
		nodesCount = _tree.nodesCount;
	};


	tree() : root(nullptr), nodesCount(0) {}; // ��� �������� ����� ������


	template<class InputIt>
	tree(InputIt first, InputIt last) { // ������������ ������ �� ���������. ��������: std::vector<int> v {1,2,3,4}; tree<int> t {v.begin(), v.end()};
		while (first != last) {
			insert(*first);
			++first;
		}
	}


	~tree() { // ����� ����������, ����� ������� ��� ���� ������, ����� ������ ����� ��������
		clear();
	};



	// ��������� ����������� � �����������
	tree_t& operator=(tree_t&& tree_) { // �������� ����������� (move semantics)
		if (this != &tree_) {
			clear();
			root = tree_.root;
			tree_.root = nullptr;
			nodesCount = tree_.nodesCount;
			tree_.nodesCount = 0;
		}
		return *this;
	}


	tree_t& operator=(const tree_t& tree_) { // �������� �����������   
		if (this != &tree_) {
			clear(root);
			copy(tree_.root, root);
			nodesCount = tree_.nodesCount;
		}
		return *this;
	};


	tree_t& operator=(std::initializer_list<value_type> il_) { // �������� ����������� ����� initializer list
		clear();
		for (const auto& val : il_) {
			insert(val);
		}
		nodesCount = il_.size();
		return *this;
	}


	bool   empty() { // ��������, ��� ������ ������
		return root == nullptr;
	}


	bool empty() const { // ����������� ������ �������� �� �������
		return root == nullptr;
	}


	size_t size() { // ���������� ���������� ����� � ������
		return nodesCount;
	}


	size_t size() const { // ����������� ������, ������������ ���������� ����� � ������
		return nodesCount;
	}


	void   clear() { // ������� ������
		clearDo(root);
		root = nullptr;
	}



	// ������ �������
	insertion_result insert(const value_type& value_) { // ��������� �������.
		return insertDo(root, value_);
	}


	insertion_result insert(value_type&& value_) { // ��������� ������� (move semantics)
		return insertDo(root, std::move(value_));
	}



	// ������ ������
	pointer_type  find(const value_type& value_) { // ����� �������� � ������
		return findDo(value_);
	}


	pointer_type find(const value_type& value_) const { // ����������� ����� �������� � ������
		return findDo(value_);
	}


	// ��������� �������������� ������� ���� �� ����� ������� (move semantics)
	template<typename... Args>
	insertion_result emplace(Args&&... args) {
		return insertDo(root, value_type(std::forward<Args>(args)...));
	}


	// ������ ��������
	pointer_type erase(pointer_type pos) { // �������� �� ���������
		return eraseDo(root, pos);
	}


	size_t erase(const value_type& key_) { // �������� �� ��������
		return eraseByKey(root, key_);
	}


	size_t erase(value_type&& key_) {
		return eraseByKey(root, std::move(key_)); // �������� �� �������� (move semantics)
	}


	// ������ ������
	bool preOrder() { // ����� ������ � ���������� ����� (������ - ���� - �����)
		preOrder(root);
		cout << endl;
		return 1;
	}

	bool inOrder() { // ����� ������ � ��������� ����� (���� - ������ - �����)
		inOrder(root);
		cout << endl;
		return 1;
	}

	bool postOrder() { // ����� ������ � ����������� ����� (���� - ����� - ������)
		postOrder(root);
		cout << endl;
		return 1;
	}

	bool printLevelOrder() { // ����� ������ �� ������� 
		int max_level = nodesCount;
		for (int i = 1; i <= max_level; i++) {
			printLevelOrder(root, i);
			cout << endl;
		}
		return 1;
	}


private:
	node* root = nullptr; // ���������� ������ 
	size_t nodesCount;


	void copy(node* src, node*& cur) { // ����������� ������
		if (src == nullptr) {
			cur = nullptr;
			return;
		}

		cur = new node{ src->field, nullptr, nullptr };
		copy(src->left, cur->left);
		copy(src->right, cur->right);
	}


	void clearDo(node* curr) { // �������
		if (curr != nullptr) {
			clearDo(curr->left);
			clearDo(curr->right);
			delete curr;
			nodesCount = 0;
		}
	}


	insertion_result insertDo(node*& curr, const value_type& value_) { // ������� 
		if (curr == nullptr) {
			curr = new node{ value_, nullptr, nullptr };
			nodesCount++;
			return &(curr->field);
		}
		if (value_ < curr->field) {
			return insertDo(curr->left, value_);
		}
		else {
			return insertDo(curr->right, value_);
		}
	}


	insertion_result insertDo(node*& curr, value_type&& value_) { // ������� rvalue
		if (curr == nullptr) {
			curr = new node{ std::move(value_), nullptr, nullptr };
			nodesCount++;
			return &(curr->field);
		}
		if (value_ < curr->field) {
			return insertDo(curr->left, std::move(value_));
		}
		else {
			return insertDo(curr->right, std::move(value_));
		}
	}


	pointer_type findDo(const value_type& value_) const { // �����
		node* current = root;
		while (current != nullptr) {
			if (value_ == current->field) {
				return &(current->field);
			}
			else if (value_ < current->field) {
				current = current->left;
			}
			else {
				current = current->right;
			}
		}
		return nullptr;
	}


	pointer_type eraseDo(node*& curr, pointer_type pos) { // �������� �� ���������
		if (curr == nullptr) {
			return nullptr;
		}
		if (curr->field == *pos) {
			pointer_type result = &(curr->field);
			if (curr->left == nullptr) {
				node* temp = curr->right;
				delete curr;
				curr = temp;
			}
			else if (curr->right == nullptr) {
				node* temp = curr->left;
				delete curr;
				curr = temp;
			}
			else {
				node* temp = findMin(curr->right);
				curr->field = temp->field;
				eraseDo(curr->right, &(temp->field));
			}
			nodesCount--;
			return result;
		}
		else if (*pos < curr->field) {
			return eraseDo(curr->left, pos);
		}
		else {
			return eraseDo(curr->right, pos);
		}
	}


	size_t eraseByKey(node*& curr, const value_type& key_) {
		if (curr == nullptr) {
			return 0;
		}
		size_t nodesDeleted = 0;
		if (curr->field == key_) {
			nodesDeleted = 1;
			if (curr->left == nullptr) {
				node* temp = curr->right;
				delete curr;
				curr = temp;
			}
			else if (curr->right == nullptr) {
				node* temp = curr->left;
				delete curr;
				curr = temp;
			}
			else {
				node* temp = findMin(curr->right);
				curr->field = temp->field;
				nodesDeleted += eraseByKey(curr->right, temp->field);
			}
			// ��������� ���������� ����� � ������ ����� ��������
			nodesCount -= nodesDeleted;
		}
		else if (key_ < curr->field) {
			nodesDeleted = eraseByKey(curr->left, key_);
		}
		else {
			nodesDeleted = eraseByKey(curr->right, key_);
		}
		return nodesDeleted;
	}


	node* findMin(node* curr) { // ��������������� ������ ��� ��������
		while (curr->left != nullptr) {
			curr = curr->left;
		}
		return curr;
	}


	void inOrder(node* curr) { // ����� ������
		if (curr == nullptr) {
			return;
		}
		inOrder(curr->left);
		cout << curr->field << " ";
		inOrder(curr->right);
	}


	void preOrder(node* curr) { // ����� �������
		if (curr == nullptr) {
			return;
		}
		cout << curr->field << " ";
		preOrder(curr->left);
		preOrder(curr->right);
	}


	void postOrder(node* curr) { // ����� ��������
		if (curr == nullptr) {
			return;
		}
		postOrder(curr->left);
		postOrder(curr->right);
		cout << curr->field << " ";
	}


	void printLevelOrder(node* curr, int level) { // ����� ������
		if (curr == nullptr) {
			return;
		}
		if (level == 1) {
			cout << curr->field << " ";
		}
		else if (level > 1) {
			printLevelOrder(curr->left, level - 1);
			printLevelOrder(curr->right, level - 1);
		}
	}
};