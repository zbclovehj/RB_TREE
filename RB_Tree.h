#ifndef RB_TREE_H
#define RB_TREE_H
//#pragma once
#include "RB_Tree_Node.h"
#include "RB_Tree_Node.cpp"
template <class T>
class RB_Tree
{
public:
	RB_Tree(T Root_Data);
	~RB_Tree();
	void Destroy(RB_Tree_Node<T>* node);
	void Left_Rotate(RB_Tree_Node<T>* current_Node);
	void Right_Rotate(RB_Tree_Node<T>* current_Node);
	void Insert_Node(T insert_data);
	int Delete_Node(T delete_data);
	void Fix_Tree(RB_Tree_Node<T>* current_Node);
	void erase_Node(RB_Tree_Node<T>* Node_del);
	void Fix_Tree_Delete(RB_Tree_Node<T>* current_Node, RB_Tree_Node<T>* father_Node);
	RB_Tree_Node<T>* Find_Node(T search_data);
	RB_Tree_Node<T>* Find_Successor_Node(RB_Tree_Node<T>* current_Node);
	void Print(RB_Tree_Node<T>* node);
	
	RB_Tree_Node<T>* Root_Node;
};

#endif