#include "bst.h"

/* 
bst();

Opens file and reads through contents, testing for spaces on each line as some counties
have a space between their names 
*/
bst::bst()
{
	ifstream in;
	ifstream in2;
	string county;
	string county2;
	double population;
	string s;
	int scount = 0;
	in.open("county_data.txt"); //file instance used for initial iteration
	in2.open("county_data.txt"); //This is in case the county name contains more than one word

	root = 0; //initialize root as 0

	if (in.is_open() && in2.is_open())
	{ 

		while (!in.eof()) 
		{

			while (getline(in, s))
			{
				//iterates through each line, counts the number
				//of spaces on each line and stores in var scount
				for (int i = 0; i < s.length(); i++)
				{
					if (s[i] == ' ') {
						scount++;
					}
				}
				//reads in second instance of file to variables
				//according to 1 word or 2 word county name
				//and calls insert
				if (scount == 1) //if 1 space found, means county name is one word
				{
					in2 >> county >> population;
					insert(county, population);
				}
				if (scount == 2) //if 2, county name is two words. 
				{
					in2 >> county >> county2 >> population;
					county = county + " " + county2;
					insert(county, population);
				}
				
				scount = 0;		//reset space count
			}

		}
	}
	else 
	{
		cout << "No file found." << endl;
	}
	in.close();
	in2.close();
}


/*
empty();

Returns true if empty, false if not
*/
bool bst::empty()
{
	return (root == 0);
}

/*
insert(const string & item, const double & population);

Calls overloaded insert function, passing string and double variables
*/
void bst::insert(const string & item, const double & population)
{
	insert(root, item, population);
}

/*
insert(treenode * & loc_ptr, string item, double population);

If the treenode is empty, adds new item to treenode, assigning variables county_name and population and initializing
rchild and lchild. Recursively adds items and sorts alphabetically based on county name
*/
void bst::insert(treenode * & loc_ptr, string item, double population)
{
	transform(item.begin(), item.end(), item.begin(), tolower);

	if (loc_ptr == 0)
	{
		loc_ptr = new treenode;
		loc_ptr->lchild = loc_ptr->rchild = 0;
		loc_ptr->county_name = item;
		loc_ptr->population_size = population;
	}
	else if (loc_ptr->county_name>item)
		insert(loc_ptr->lchild, item, population);
	else if (loc_ptr->county_name<item)
		insert(loc_ptr->rchild, item, population);
	else
		cout << "the item is already in the tree\n";
}


/*
search_tree(string item);

Calls search_tree function, passing root and string and returns the result of that function
*/
treenode * bst::search_tree(string item)
{
	return search_tree(root, item);
}

/*
search_tree(treenode * loc_ptr, string item);

Searches for location of the county_name, recursively iterating through the bst
*/
treenode * bst::search_tree(treenode * loc_ptr, string item)
{
	transform(item.begin(), item.end(), item.begin(), tolower);

	if (loc_ptr != 0)
	{
		if (loc_ptr->county_name == item)
			return loc_ptr;
		else if (loc_ptr->county_name>item)
			return search_tree(loc_ptr->lchild, item);
		else
			return search_tree(loc_ptr->rchild, item);
	}
	else
		return loc_ptr;
}

/*
del_name(string item);

Calls overloaded del_name funtion, passing root and the string item, to search for the item and delete if found
*/
void bst::del_name(string item)
{
	del_name(root, item);
}

/*
del_name(treenode * & loc_ptr, string item);

Takes pointer to a treenode and a string. It iterates through string until item is found by 
recursively calling function. Once item is found in tree, deletes instances of rchild and lchild,
then finally deletes instance of item in tree
*/
void bst::del_name(treenode * & loc_ptr, string item)
{
	transform(item.begin(), item.end(), item.begin(), tolower);

	if (loc_ptr == 0)
		cout << "item not in tree\n";

	else if (loc_ptr->county_name > item)
		del_name(loc_ptr->lchild, item);

	else if (loc_ptr->county_name < item)
		del_name(loc_ptr->rchild, item);

	else
	{
		treenode * ptr;

		if (loc_ptr->lchild == 0)
		{
			ptr = loc_ptr->rchild;
			delete loc_ptr;
			loc_ptr = ptr;
		}
		else if (loc_ptr->rchild == 0)
		{
			ptr = loc_ptr->lchild;
			delete loc_ptr;
			loc_ptr = ptr;
		}
		else
		{
			ptr = inorder_succ(loc_ptr);
			loc_ptr->county_name = ptr->county_name;
			del_name(loc_ptr->rchild, ptr->county_name);
		}
	}

}

/*
county_ranges(string min_name, string max_name);

Calls overloaded function county_ranges, passing treenode root and range strings
*/
void bst::county_ranges(string min_name, string max_name)
{
	transform(min_name.begin(), min_name.end(), min_name.begin(), tolower);
	transform(max_name.begin(), max_name.end(), max_name.begin(), tolower);

	county_ranges(root, min_name, max_name);

}

/*
county_ranges(treenode * loc_ptr, string min_name, string max_name);

Function runs loop, recursively passing lchild and rchild and printing 
county_name to output if it falls in the range, inclusive of max and min range parameters
*/
void bst::county_ranges(treenode * loc_ptr, string min_name, string max_name) 
{
	if (loc_ptr != 0)
	{
		county_ranges(loc_ptr->lchild, min_name, max_name);
		if (loc_ptr->county_name >= min_name && loc_ptr->county_name <= max_name) 
		{
			cout << loc_ptr->county_name << endl;
		}
		county_ranges(loc_ptr->rchild, min_name, max_name);
	}
}

/*
inorder_succ(treenode * loc_ptr);

Declares new treenode p, assigns to rchild and tests for lchild. 
If lchild exists, assigns pp to lchild and returns p
*/
treenode * bst::inorder_succ(treenode * loc_ptr)
{
	treenode *p = loc_ptr->rchild;

	while (p->lchild != 0)
	{
		p = p->lchild;
	}
	return p;
}


/*
print_tree();

Calls overloaded print_tree function to print contents of tree to output
*/
void bst::print_tree()
{
	print_tree(root);
}

/*
~bst();

Calls del_name function for each item in current bst until empty
*/
bst::~bst()
{
	while (root != 0)
	{
		del_name(root->county_name);
	}
}

/*
print_tree(treenode * loc_ptr);

Sets precision of cout to 10 to print doubles greater than 6 digits. Prints to output county_name
and population_size if loc_ptr is not empty, recursively passing lchild and rchild for output
*/
void bst::print_tree(treenode * loc_ptr)
{
	cout.precision(10);

	if (loc_ptr != 0)
	{
		print_tree(loc_ptr->lchild);
		cout << loc_ptr->county_name << "  " << loc_ptr->population_size << "\n";
		print_tree(loc_ptr->rchild);
	}

}

/*
sorted_info(ofstream & out, treenode * loc_ptr);

Prints contents to a file, recursively passing each lchild and rchild 
*/
void bst::sorted_info(ofstream & out, treenode * loc_ptr)
{

	if (out.is_open()) {
		if (loc_ptr != 0)
		{
			sorted_info(out, loc_ptr->lchild);
			out << loc_ptr->county_name << "  " << loc_ptr->population_size << "\n";
			sorted_info(out, loc_ptr->rchild);
		}
	}

}

/*
sorted_info();

Creates new file, calls overloaded function sorted_info to print to file, 
and closes function. Important to open and close file from this function to prevent errors in file output
*/
void bst::sorted_info()
{
	ofstream out;
	out.open("county_info.txt");
	out.precision(10);

	sorted_info(out, root);

	out.close();
}
