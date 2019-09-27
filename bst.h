#pragma once
//////////////////////////////////////////////////////////////////////////////////////////// 
/*Name: Daniel Caballero   Z# : 23439643
Course : Date Structures and Algorithm Analysis(COP3530)
Professor : Dr.Lofton Bullard
Due Date : 08 / 01 / 2018  Due Time : 11 : 59pm
Total Points : 25
Assignment 9 : bts program
*/////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <fstream> 
#include <algorithm> 
#include <iostream>

using namespace std;

class treenode
{
public:
	string county_name;
	double population_size;
	treenode *lchild, *rchild; //left and right children pointers
};

class bst
{

public:
	bst(); //store the data file (ìcounty_data.txtî) into initial bst
	~bst(); //de-allocates dynamic memory allocate for tree
	bool empty(); // checks to see if the tree is empty
	void insert(const string & item, const double & population);//inserts a county record into bst based on county_name
	void insert(treenode * &, string item, double population);  
	void del_name(string item); //deletes a county record based on county name
	void del_name(treenode * & loc_ptr, string item);
	treenode * search_tree(treenode *, string item); //returns pointer to node with county_name
	treenode * search_tree(string item); 
	treenode * inorder_succ(treenode *); //return pointer to inorder successor (based on county name.)
	void county_ranges(string min_name, string max_name); //prints all county names to the screen between min_name and max_name, inclusive
	void county_ranges(treenode * loc_ptr, string min_name, string max_name); //prints all county names to the screen between min_name and max_name, inclusive
	void print_tree(); //prints each county record to the screen sorted by county name
	void print_tree(treenode *);
	void sorted_info();//prints each county record to a file called ìcounty_info.txtî sorted by county //nameî.
	void sorted_info(ofstream & out, treenode * loc_ptr);

private:
	treenode * root;

};