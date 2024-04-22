#include "mytree1.h"

int main()
{
	setlocale(LC_ALL, "");
	/*tree<int> t1{5, 2, 1 , 5, 6}; // использована tree(std::initializer_list<value_type> il_)
	cout << "Дерево t1:" << endl;
	t1.printLevelOrder();


	tree<int> t2(t1); // использована tree(const tree_t& _tree)
	cout << "Дерево t2:" << endl;
	t2.printLevelOrder();


	tree<int> t3(std::move(t1)); // использована tree(tree_t&& _tree).
	if (t1.empty()) { // проверка на пустоту
		cout << "В дереве t1 больше нет элементов. Они перемещены в дерево t3" << endl;
	}
	cout << "Дерево t3:" << endl;
	t3.printLevelOrder();


	std::vector<int> v{ 5,6,1,4,3,2,6,8 };
	tree<int> t4{ v.begin(), v.end() }; // использована tree(InputIt first, InputIt last)
	cout << "Дерево t4: "<< endl;
	t4.printLevelOrder();


	tree<int> t5 = std::move(t3); // использован tree_t& operator=(tree_t&& tree_) оператор перемещения
	if (t3.empty()) { // проверка на пустоту
		cout << "В дереве t3 больше нет элементов. Они перемещены в дерево t5" << endl;
	}
	cout << "Дерево t5:" << endl;
	t5.printLevelOrder();


	tree<int> t6 = t5; // использован tree_t& operator=(const tree_t& tree_) оператор копирования   
	cout << "Дерево t6:" << endl;
	t6.printLevelOrder();
	cout << "В дереве t6 " << t6.size() << " узлов" << endl << endl << endl; // количество узлов в дереве


	tree<int> t7 = { 1,2,3,4,1,10,20 }; // использован tree_t& operator=(std::initializer_list<value_type> il_) оператор копирования через initializer list
	cout << "Дерево t7:" << endl;
	t7.printLevelOrder();


	t4.~tree(); // использован деструктор
	cout << "На дереве t4 был использован деструктор" << endl;
	if (t4.empty()) {
		cout << "В дереве t4 нет элементов" << endl << endl;
	}


	t5.clear(); // использована очистка
	cout << "На дереве t5 была использована функция очистки" << endl;
	if (t5.empty()) {
		cout << "В дереве t5 нет элементов" << endl << endl << endl;
	}


	// удаление элемента по указателю
	int del_val = 4;
	tree<int>::pointer_type del_pos = t7.find(del_val);
	if (del_pos != nullptr) {
		t7.erase(del_pos);
		cout << "Элемент " << del_val << " успешно удален из дерева t7" << endl << endl;
	}
	else {
		cout << "Элемент " << del_val << " не найден в дереве t7" << endl << endl;
	}

	cout << "Дерево t7:" << endl;
	t7.printLevelOrder();


	// удаление элемента по значению
	int del_key = 20;
	size_t deleted = t7.erase(del_key);
	if (deleted > 0) {
		cout << "Элемент " << del_key << " удален из дерева t7" << endl << endl;
	}
	else {
		cout << "Элемент " << del_key << " не найден в дереве t7" << endl << endl;
	}

	cout << "Дерево t7:" << endl;
	t7.printLevelOrder();


	// удаление элемента по значению (move semantics)
	del_key = 10;
	deleted = t7.erase(move(del_key));
	if (deleted > 0) {
		cout << "Элемент " << del_key << " удален из дерева t7" << endl << endl;
	}
	else {
		cout << "Элемент " << del_key << " не найден в дереве t7" << endl << endl;
	}

	cout << "Дерево t7:" << endl;
	t7.printLevelOrder();

	// вставка с помощью insertion_result insert(const value_type& value_)
	int nums[] = { 5, 3, 7, 2, 4, 6, 8 };
	for (int num : nums) {
		tree<int>::insertion_result res = t1.insert(num);
	}
	cout << "В дерево t1 были добавлены элементы" << endl << endl;

	cout << "Дерево t1:" << endl;
	t1.printLevelOrder();


	// вставка с помощью insertion_result insert(value_type&& value_)
	for (int num : nums) {
		tree<int>::insertion_result res = t3.insert(move(num));
	}
	cout << "В дерево t3 были добавлены элементы" << endl << endl;

	cout << "Дерево t3:" << endl;
	t3.printLevelOrder();

	// поиск элемента в дереве
	cout << "Ищем элемент в дереве t7 с помощью обыной функции" << endl;
	t7 = { 1,2,3,4,1,10,20 };
	int find_key = 4;
	tree<int>::pointer_type found_node = t7.find(find_key);
	if (found_node != nullptr) {
		cout << "Элемент " << *found_node << " найден в дереве" << endl;
	}
	else {
		cout << "Элемент " << find_key << " не найден в дереве" << endl;
	}
	cout << endl;


	// константный поиск элемента в дереве
	cout << "Ищем элемент в дереве t7 с помощью константной функции" << endl;
	const tree<int>& const_t7 = t7;
	found_node = const_t7.find(find_key);
	if (found_node != nullptr) {
		cout << "Элемент " << *found_node << " найден в дереве" << endl;
	}
	else {
		cout << "Элемент " << find_key << " не найден в дереве" << endl;
	}
	cout << endl << endl << endl;


	cout << "Создадим дерево t8 из элементов 4,2,6,1,5,6,7" << endl << endl;
	tree<int> t8{ 4,2,6,1,5,6,7 };


	cout << "Вывод дерева t8 в префиксной форме:" << endl;
	t8.preOrder();
	cout << endl << endl;

	cout << "Вывод дерева t8 в инфиксной форме:" << endl;
	t8.inOrder();
	cout << endl << endl;

	cout << "Вывод дерева t8 в постфиксной форме:" << endl;
	t8.postOrder();
	cout << endl << endl;

	cout << "Вывод дерева t8 по уровням:" << endl;
	t8.printLevelOrder();


	cout << "Добавим в дерево t8 новые элементы 2 и 3 при помощи insertion_result emplace(Args&&... args)" << endl;
	t8.emplace(2);
	t8.emplace(3);


	cout << "Дерево t8 после добавления:" << endl;
	t8.printLevelOrder();
	*/
	return 0;
}