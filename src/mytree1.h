#include <iostream>
#include <vector> // нужна только для примера использования tree(InputIt first, InputIt last)
using namespace std;

template <typename T>
struct tnode { // структура нода
	T field;
	struct tnode* left;
	struct tnode* right;
};


template<typename _Ty, typename node = tnode<_Ty>>
class tree
{
public:
	// Это нужно, чтобы писать меньше :)
	using value_type = _Ty;
	using tree_t = tree<value_type, node>;
	using reference_type = value_type&;
	using pointer_type = value_type*;
	// Пара определяет вставки. В нашем случае это указатель но вновь созданный узел. Можно заменить на bool или reference_type
	using insertion_result = pointer_type;


	// Конструкторы
	tree(std::initializer_list<value_type> il_) { // Позволяет построить дерево через список инициализации tree<int>  t {1, 2, 3, 4, 5};
		for (const auto& val : il_) {
			insert(val);
		}
	};


	tree(tree_t&& _tree) { // (move semantics) позволяет быстро переместить значения одного дерева в другое, при этом первое становится путым (принимает дерево аргументом)
		root = std::move(_tree.root);
		_tree.root = nullptr;
		nodesCount = _tree.nodesCount;
		_tree.nodesCount = 0;
	};


	tree(const tree_t& _tree) { // копирование целикового дерева в другое (принимает дерево аргументом)
		root = nullptr;
		copy(_tree.root, root);
		nodesCount = _tree.nodesCount;
	};


	tree() : root(nullptr), nodesCount(0) {}; // для нулевого корня дерева


	template<class InputIt>
	tree(InputIt first, InputIt last) { // Конструирует объект из диапазона. Например: std::vector<int> v {1,2,3,4}; tree<int> t {v.begin(), v.end()};
		while (first != last) {
			insert(*first);
			++first;
		}
	}


	~tree() { // Нужен деструктор, чтобы удалить все узлы дерева, когда объект будет разрушен
		clear();
	};



	// операторы копирования и перемещения
	tree_t& operator=(tree_t&& tree_) { // Оператор перемещения (move semantics)
		if (this != &tree_) {
			clear();
			root = tree_.root;
			tree_.root = nullptr;
			nodesCount = tree_.nodesCount;
			tree_.nodesCount = 0;
		}
		return *this;
	}


	tree_t& operator=(const tree_t& tree_) { // Оператор копирования   
		if (this != &tree_) {
			clear(root);
			copy(tree_.root, root);
			nodesCount = tree_.nodesCount;
		}
		return *this;
	};


	tree_t& operator=(std::initializer_list<value_type> il_) { // Оператор копирования через initializer list
		clear();
		for (const auto& val : il_) {
			insert(val);
		}
		nodesCount = il_.size();
		return *this;
	}


	bool   empty() { // Проверка, что дерево пустое
		return root == nullptr;
	}


	bool empty() const { // Константная версия проверки на пустоту
		return root == nullptr;
	}


	size_t size() { // Возвращает количество узлов в дереве
		return nodesCount;
	}


	size_t size() const { // Константная версия, возвращающая количество узлов в дереве
		return nodesCount;
	}


	void   clear() { // Очищает дерево
		clearDo(root);
		root = nullptr;
	}



	// методы вставки
	insertion_result insert(const value_type& value_) { // выполняет вставку.
		return insertDo(root, value_);
	}


	insertion_result insert(value_type&& value_) { // выполняет вставку (move semantics)
		return insertDo(root, std::move(value_));
	}



	// методы поиска
	pointer_type  find(const value_type& value_) { // поиск элемента в дереве
		return findDo(value_);
	}


	pointer_type find(const value_type& value_) const { // константный поиск элемента в дереве
		return findDo(value_);
	}


	// Позволяет конструировать элемент прям на месте вставки (move semantics)
	template<typename... Args>
	insertion_result emplace(Args&&... args) {
		return insertDo(root, value_type(std::forward<Args>(args)...));
	}


	// методы удаления
	pointer_type erase(pointer_type pos) { // удаление по указателю
		return eraseDo(root, pos);
	}


	size_t erase(const value_type& key_) { // удаление по значению
		return eraseByKey(root, key_);
	}


	size_t erase(value_type&& key_) {
		return eraseByKey(root, std::move(key_)); // удаление по значению (move semantics)
	}


	// методы вывода
	bool preOrder() { // вывод дерева в префиксной форме (корень - лево - право)
		preOrder(root);
		cout << endl;
		return 1;
	}

	bool inOrder() { // вывод дерева в инфиксной форме (лево - корень - право)
		inOrder(root);
		cout << endl;
		return 1;
	}

	bool postOrder() { // вывод дерева в постфиксной форме (лево - право - корень)
		postOrder(root);
		cout << endl;
		return 1;
	}

	bool printLevelOrder() { // вывод дерева по уровням 
		int max_level = nodesCount;
		for (int i = 1; i <= max_level; i++) {
			printLevelOrder(root, i);
			cout << endl;
		}
		return 1;
	}


private:
	node* root = nullptr; // обозначает корень 
	size_t nodesCount;


	void copy(node* src, node*& cur) { // копирование дерева
		if (src == nullptr) {
			cur = nullptr;
			return;
		}

		cur = new node{ src->field, nullptr, nullptr };
		copy(src->left, cur->left);
		copy(src->right, cur->right);
	}


	void clearDo(node* curr) { // очищает
		if (curr != nullptr) {
			clearDo(curr->left);
			clearDo(curr->right);
			delete curr;
			nodesCount = 0;
		}
	}


	insertion_result insertDo(node*& curr, const value_type& value_) { // вставка 
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


	insertion_result insertDo(node*& curr, value_type&& value_) { // вставка rvalue
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


	pointer_type findDo(const value_type& value_) const { // поиск
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


	pointer_type eraseDo(node*& curr, pointer_type pos) { // удаление по указателю
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
			// Уменьшаем количество узлов в дереве после удаления
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


	node* findMin(node* curr) { // вспомогательная фунция для удаления
		while (curr->left != nullptr) {
			curr = curr->left;
		}
		return curr;
	}


	void inOrder(node* curr) { // вывод инфикс
		if (curr == nullptr) {
			return;
		}
		inOrder(curr->left);
		cout << curr->field << " ";
		inOrder(curr->right);
	}


	void preOrder(node* curr) { // вывод префикс
		if (curr == nullptr) {
			return;
		}
		cout << curr->field << " ";
		preOrder(curr->left);
		preOrder(curr->right);
	}


	void postOrder(node* curr) { // вывод постфикс
		if (curr == nullptr) {
			return;
		}
		postOrder(curr->left);
		postOrder(curr->right);
		cout << curr->field << " ";
	}


	void printLevelOrder(node* curr, int level) { // вывод уровни
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