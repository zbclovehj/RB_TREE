#include "RB_Tree_Node.h"
#include<iostream>
template <class T>
RB_Tree_Node<T>::RB_Tree_Node(T data_in) :data(data_in), color_tag(0), Left_child(NULL), Right_child(NULL), Father_Node(NULL) {
	data = data_in;
	//每次创建一个节点颜色默认为红色
	color_tag = 1;
}
template<class T>
RB_Tree_Node<T>::~RB_Tree_Node(void) {
	std::cout << "删除了一个节点" << std::endl;
}