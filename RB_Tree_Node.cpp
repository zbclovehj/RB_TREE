#include "RB_Tree_Node.h"
#include<iostream>
template <class T>
RB_Tree_Node<T>::RB_Tree_Node(T data_in) :data(data_in), color_tag(0), Left_child(NULL), Right_child(NULL), Father_Node(NULL) {
	data = data_in;
	//ÿ�δ���һ���ڵ���ɫĬ��Ϊ��ɫ
	color_tag = 1;
}
template<class T>
RB_Tree_Node<T>::~RB_Tree_Node(void) {
	std::cout << "ɾ����һ���ڵ�" << std::endl;
}