// Nathanael Fixx
// 15 Jan 2018

// some interactive and non-interactive testes to test BinarySearchTree

#include <iostream>
#include <sstream>
#include <vector>
// climits needed under linux, not needed under MacOS
#include <climits>
#include <string>

#include "binarysearchtree.h"
#include "binarynode.h"

using namespace std;

int total_visit_count = 0;

int errors = 0;
int oks = 0;
int totaloks = 33;

void itemDisplay(string& anItem) {
	cout << anItem << " ";
	total_visit_count++;
}

void intDisplay(int& anItem) {
	cout << anItem << " ";
}


template <typename T>
string isOK(const T& got, const T& expected) {
	string str;
	str.append(to_string(oks + errors + 1));
	str.append("/");
	str.append(to_string(totaloks));
	str.append(" ");
	if (got == expected) {
		oks++;
		return str + "OK: ";
	}
	else {
		cout << "    Got " << got << " expected " << expected << endl;
		errors++;
		return str + "ERR: ";
	}
}

void test_01() {
	cout << "\n\n* Testing: 1. Constructors: Empty, 1 parameter and Copy Constructor" << endl;
	BinarySearchTree<string> b1;
	BinarySearchTree<string> b2;
	BinarySearchTree<string> b3;
	cout << isOK(b1 == b2 && (!(b1 != b2)), true) << "== for empty trees" << endl;
	b1.add("c");
	b2.add("c");
	b3.add("b");
	cout << isOK(b1 == b2 && (!(b1 != b2)), true) << "== for 1-node trees b1, b2" << endl;
	cout << isOK(b1 != b3 && (!(b1 == b3)), true) << "== for 1-node trees b1, b3" << endl;
	b1.add("a"); b1.add("f"); b1.add("g"); b1.add("x");
	b2.add("a"); b2.add("f"); b2.add("g"); b2.add("x");
	cout << isOK(b1 == b2 && (!(b1 != b2)), true) << "== for 5-node trees b1, b2" << endl;
	BinarySearchTree<string> b4(b3);
	cout << isOK(b3 == b4 && (!(b3 != b4)), true) << "copy constructor for 1-node trees b3, b4" << endl;
	BinarySearchTree<string> b5(b1);
	cout << isOK(b1 == b5 && (!(b5 != b1)), true) << "copy constructor for 5-node trees b1, b5" << endl;
	BinarySearchTree<string> b7("b");
	cout << isOK(b3 == b7 && (!(b3 != b7)), true) << "1-param constructor for 1-node trees b3, b7" << endl;
}

void test_02() {
	cout << "\n\n* Testing: 2. Destructor, clear" << endl;
	BinarySearchTree<string> b1;
	b1.add("10");
	b1.clear();
	cout << isOK(b1.getNumberOfNodes(), 0) << "0-node tree b1 after add/clear" << endl;
	b1.add("c"); b1.add("p"); b1.add("q"); b1.add("b");
	cout << isOK(b1.getNumberOfNodes(), 4) << "4-node tree b1" << endl;
	b1.clear();
	cout << isOK(b1.getNumberOfNodes(), 0) << "0-node tree b1 after clear" << endl;
	cout << isOK(b1.isEmpty(), true) << "0-node tree b1 after clear is empty" << endl;
	BinarySearchTree<string> b2;
	cout << isOK(b2.getNumberOfNodes(), 0) << "0-node tree b2" << endl;
	b2.clear();
	cout << isOK(b2.getNumberOfNodes(), 0) << "0-node tree b2 after clear" << endl;
	cout << isOK(b2.isEmpty(), true) << "0-node tree b2 after clear is empty" << endl;
}

void test_03() {
	cout << "\n\n* Testing: 3. isEmpty, getHeight, numberOfNodes, contains" << endl;
	BinarySearchTree<string> b1;
	cout << isOK(b1.getHeight(), 0) << "0-node tree b1 has height 0" << endl;
	b1.add("b");
	cout << isOK(b1.getHeight(), 1) << "1-node tree b1 has height 1" << endl;
	b1.add("p");
	cout << isOK(b1.getHeight(), 2) << "2-node tree b1 has height 2" << endl;
	b1.add("q");
	cout << isOK(b1.getHeight(), 3) << "3-node tree b1 has height 3" << endl;
	b1.add("r");
	cout << isOK(b1.getHeight(), 4) << "4-node tree b1 has height 4" << endl;
	b1.add("c");
	cout << isOK(b1.getHeight(), 4) << "5-node tree b1 has height 4" << endl;
	b1.add("a");
	cout << isOK(b1.getHeight(), 4) << "6-node tree b1 has height 4" << endl;
	b1.add("d");
	cout << isOK(b1.getHeight(), 4) << "7-node tree b1 has height 4" << endl;
	cout << isOK(b1.contains("x"), false) << "7-node tree b1 does not have x" << endl;
	cout << isOK(b1.contains("p"), true) << "7-node tree b1 does have p" << endl;
	cout << isOK(b1.contains("r"), true) << "7-node tree b1 does have r" << endl;
	b1.add("d");
	cout << isOK(b1.getNumberOfNodes(), 7) << "7-node tree after adding duplicate still 7" << endl;
	b1.add("e");
	b1.add("f");
	b1.add("g");
	cout << isOK(b1.contains("d"), true) << "10-node tree b1 does have d" << endl;
	cout << isOK(b1.contains("e"), true) << "10-node tree b1 does have e" << endl;
	cout << isOK(b1.contains("f"), true) << "10-node tree b1 does have f" << endl;
	cout << isOK(b1.contains("g"), true) << "10-node tree b1 does have g" << endl;
}
void test_04() {
	cout << "\n\n* Testing: 4. operator==, operator!=" << endl;
	cout << "Already tested" << endl;
}
void test_05() {
	cout << "\n\n* Testing: 5. add" << endl;
	cout << "Already tested" << endl;
}
void test_06() {
	cout << "\n\n* Testing: 6. inorderTraverse" << endl;
	BinarySearchTree<string> b1;
	b1.add("c"); b1.add("p"); b1.add("q"); b1.add("r");
	b1.add("e"); b1.add("b"); b1.add("d"); b1.add("f");
	total_visit_count = 0;
	cout << "* Visual inspection" << endl;
	b1.inorderTraverse(itemDisplay);
	cout << isOK(total_visit_count, 8) << "8-node tree b1, each node got visited" << endl;
}

void test_07() {
	cout << "\n\n* Testing: 7. rebalance" << endl;
	BinarySearchTree<string> b1;
	b1.add("c"); b1.add("p"); b1.add("q"); b1.add("r");
	b1.add("e"); b1.add("b"); b1.add("d");
	cout << "* Visual inspection" << endl;
	b1.rebalance();
	cout << isOK(b1.getHeight(), 3) << "7-node tree b1 has height 3" << endl;
	b1.displaySideways();
	b1.clear();
	b1.add("c"); b1.add("p"); b1.add("q"); b1.add("r");
	b1.add("e"); b1.add("b"); b1.add("d"); b1.add("f");
	b1.rebalance();
	cout << isOK(b1.getHeight(), 4) << "8-node tree b1 has height 4" << endl;
	cout << "* Visual inspection" << endl;
	b1.displaySideways();

}
void test_08() {
	cout << "\n\n* Testing: 8. readTree" << endl;
	BinarySearchTree<string> b1;
	BinarySearchTree<string> b2;
	string arr[7]{ "a", "b", "c", "d", "e", "f", "g" };
	string arr2[8]{ "a", "b", "c", "d", "e", "f", "g", "h" };
	string arr3[9]{ "a", "b", "c", "d", "e", "f", "g", "h", "i" };
	string arr4[10]{ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" };
	string arr5[11]{ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k" };
	string arr6[12]{ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l" };
	string arr7[15]{ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o" };
	b1.readTree(arr, 7);
	cout << "* Visual inspection 7" << endl;
	b1.displaySideways();
	b2.readTree(arr2, 8);
	cout << "* Visual inspection 8" << endl;
	b2.displaySideways();
	b1.readTree(arr3, 9);
	cout << "* Visual inspection 9" << endl;
	b1.displaySideways();
	b2.readTree(arr4, 10);
	cout << "* Visual inspection 10" << endl;
	b2.displaySideways();
	b1.clear();
	b1.readTree(arr5, 11);
	cout << "* Visual inspection 11" << endl;
	b1.displaySideways();
	b2.readTree(arr6, 12);
	cout << "* Visual inspection 12" << endl;
	b2.displaySideways();
	b2.readTree(arr7, 15);
	cout << "* Visual inspection 15" << endl;
	b2.displaySideways();
	cout << "Done with test_08" << endl;
}

void test_09() {
	cout << "\n\n* Testing: 9. memory leaks" << endl;
	cout << "Will leave that to valgrind" << endl;
}
void test_10() {
	cout << "\n\n* Testing: 10. efficiency and complexity" << endl;
	cout << "Will leave that to grader" << endl;
}
void test_11() {
	cout << "\n\n* Testing: 11. comments.txt - tested on CSS Linux Labs" << endl;
	cout << "Hope it is there" << endl;
}
void test_12() {
	cout << "\n\n* Testing: 12. Coding style + ass2.zip constructed properly" << endl;
	cout << "Test and fix comments from cpplint and cppcheck when possible" << endl;
	cout << "Lines should be <= 80 characters long" << endl;
	cout << "*** NO LINES MORE THAN 80 CHARACTERS *** " << endl;
	cout << "Lines should be <= 80 characters long" << endl;
}

int main() {
	cout << "A total of " << totaloks << " tests " << endl;
	test_01();
	test_02();
	test_03();
	test_04();
	test_05();
	test_06();
	test_07();
	test_08();
	test_09();
	test_10();
	test_11();
	test_12();
	cout << "Total number of ERRs: " << errors << "/" << totaloks << endl;
	return 0;
}
