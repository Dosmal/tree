#include "../mytree1.h"
#include "gtest/gtest.h"

TEST(TestCaseName, TestName) {
	bool test1 = 0;
	tree<int> t1{ 5, 2, 1 , 5, 6 }; // использована tree(std::initializer_list<value_type> il_)
	EXPECT_EQ(t1.printLevelOrder(), 1);
	EXPECT_EQ(t1.preOrder(), 1);
	EXPECT_EQ(t1.inOrder(), 1);
	EXPECT_EQ(t1.postOrder(), 1);


	tree<int> t2(t1); // использована tree(const tree_t& _tree)
	EXPECT_EQ(t1.size(), t2.size());


	tree<int> t3(std::move(t1)); // использована tree(tree_t&& _tree).
	EXPECT_EQ(t1.empty(), 1);
	EXPECT_EQ(t3.size(), t2.size());


	std::vector<int> v{ 5,6,1,4,3,2,6,8 };
	tree<int> t4{ v.begin(), v.end() }; // использована tree(InputIt first, InputIt last)
	EXPECT_EQ(t4.empty(), 0);


	tree<int> t5 = std::move(t3); // использован tree_t& operator=(tree_t&& tree_) оператор перемещения
	EXPECT_EQ(t3.empty(), 1);
	EXPECT_EQ(t5.size(), t2.size());


	tree<int> t6 = t5; // использован tree_t& operator=(const tree_t& tree_) оператор копирования   
	int size6 = t6.size();
	EXPECT_EQ(t6.size(), t5.size());


	tree<int> t7 = { 1,2,3,4,1,10,20 };
	EXPECT_EQ(t7.empty(), 0);


	t4.~tree();
	EXPECT_EQ(t4.empty(), 1);


	t5.clear();
	EXPECT_EQ(t5.empty(), 1);


	int del_val = 4;
	tree<int>::pointer_type del_pos = t7.find(del_val);
	if (del_pos != nullptr) {
		if (t7.erase(del_pos) != nullptr)
			test1 = 1;
	}
	EXPECT_EQ(test1, 1);
	test1 = 0;


	int del_key = 20;
	size_t deleted = t7.erase(del_key);
	EXPECT_EQ(deleted, 1);


	del_key = 10;
	deleted = t7.erase(move(del_key));
	EXPECT_EQ(deleted, 1);


	int nums[] = { 5, 3, 7, 2, 4, 6, 8 };
	for (int num : nums) {
		tree<int>::insertion_result res = t1.insert(num);
	}
	EXPECT_EQ(t1.empty(), 0);


	for (int num : nums) {
		tree<int>::insertion_result res = t3.insert(move(num));
	}
	EXPECT_EQ(t3.empty(), 0);


	t7 = { 1,2,3,4,1,10,20 };
	int find_key = 4;
	tree<int>::pointer_type found_node = t7.find(find_key);
	if (found_node != nullptr)
		test1 = 1;
	EXPECT_EQ(test1, 1);
	test1 = 0;


	const tree<int>& const_t7 = t7;
	found_node = const_t7.find(find_key);
	if (found_node != nullptr)
		test1 = 1;
	EXPECT_EQ(test1, 1);
	test1 = 0;


	tree<int> t8{ 4,2,6,1,5,6,7 };
	if (t8.emplace(3) != nullptr)
		test1 = 1;
	EXPECT_EQ(test1, 1);
	test1 = 0;
}
