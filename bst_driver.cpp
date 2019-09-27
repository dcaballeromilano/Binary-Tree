#include "bst.h"

using namespace std;

int main()
{

	cout << "Test1: default constructor\n";
	bst myTree;

	cout << "Testing print_tree\n";
	myTree.print_tree();
	cout << "End Test1\n";

	cout << endl;
	cout << "==========================================" << endl;
	cout << "Test2:insert\n";
	myTree.insert("New-county", 234658);
	myTree.print_tree();
	cout << "End Test2\n";
	cout << "==========================================" << endl;

	cout << endl;
	cout << "==========================================" << endl;
	cout << "Test3: county_ranges\n";
	myTree.county_ranges("bbbb", "k");
	cout << "End Test3\n";
	cout << "==========================================" << endl;

	cout << endl;
	cout << "==========================================" << endl;
	cout << "Test4: del_name\n";
	myTree.del_name("Miami-Dade");
	myTree.print_tree();
	cout << "End Test4\n";
	cout << "==========================================" << endl;

	cout << endl;
	cout << "==========================================" << endl;
	cout << "Test5: sorted_info\n";
	myTree.sorted_info();
	cout << "End Test5\n";

	return 0;
}