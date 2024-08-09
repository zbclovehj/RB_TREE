//#include "stdafx.h"

#include<iostream>
#include"RB_Tree.h"
#include"RB_Tree.cpp"
#include"RB_Tree_Node.h"
int main() {
	RB_Tree<double>* my_rb_tree = new RB_Tree<double>(1.0);
	for (int i = 2; i < 10; i++)
	{
		double a = i;
		my_rb_tree->Insert_Node(a);
		my_rb_tree->Print(my_rb_tree->Root_Node);

	}
	
	for (int i = 9; i >= 2; i--)
	{
		double a = i;
		int sum = my_rb_tree->Delete_Node(a);
		if (sum == 1) {
			std::cout << "É¾³ý³É¹¦" <<a<< std::endl;
		}
		my_rb_tree->Print(my_rb_tree->Root_Node);
	}
	my_rb_tree->Print(my_rb_tree->Root_Node);
	return 0;
}