
#include"RB_Tree.h"
#include<iostream>
#include <iomanip>

using namespace std;
template<class T>
RB_Tree<T>::RB_Tree(T Root_Data) :Root_Node(NULL) {
	if (Root_Node == NULL) {
		Root_Node = new RB_Tree_Node<T>(Root_Data);
		//将根节点颜色设置为0
		Root_Node->color_tag = 0;

		std::cout << "创建红黑树" << std::endl;
	}
}

template<class T>
RB_Tree<T>::~RB_Tree()
{
	//Destroy(Root_Node);
	std::cout << "摧毁红黑树" << std::endl;
}
template <class T>
void RB_Tree<T>::Destroy(RB_Tree_Node<T>* node)
{
	if (node)
	{
		Destroy(node->Left_child);
		Destroy(node->Right_child);
		delete node;
		node = NULL;
	}
}

template<class T>
void RB_Tree<T>::Left_Rotate(RB_Tree_Node<T>* current_Node)
{
	RB_Tree_Node<T>* Right_child = current_Node->Right_child;
	RB_Tree_Node<T>* Father_Node = current_Node->Father_Node;
	current_Node->Right_child = Right_child->Left_child;
	Right_child->Father_Node = Father_Node;
	if (Right_child->Left_child) {
		Right_child->Left_child->Father_Node = current_Node;
	}
	if (Father_Node == NULL) {
		Root_Node = Right_child;
	}
	else if (current_Node == Father_Node->Left_child) {
		Father_Node->Left_child = Right_child;
	}
	else if (current_Node = Father_Node->Right_child) {
		Father_Node->Right_child = Right_child;
	}
	Right_child->Left_child = current_Node;
	current_Node->Father_Node = Right_child;
}

template<class T>
void RB_Tree<T>::Right_Rotate(RB_Tree_Node<T>* current_Node)
{
	RB_Tree_Node<T>* Father_Node = current_Node->Father_Node;
	RB_Tree_Node<T>* Left_child = current_Node->Left_child;
	current_Node->Left_child = Left_child->Right_child;
	Left_child->Father_Node = Father_Node;
	if (Left_child->Right_child) {
		Left_child->Right_child->Father_Node = current_Node;
	}
	if (Father_Node == NULL) {
		Root_Node = Left_child;
	}
	else if (Father_Node->Left_child == current_Node) {
		Father_Node->Left_child = Left_child;
	}
	else if (Father_Node->Right_child == current_Node) {
		Father_Node->Right_child = Left_child;
	}
	current_Node->Father_Node = Left_child;
	Left_child->Right_child = current_Node;
}
/************************************************************************/
/* 函数功能：向红黑树中插入一个节点           左小右大                           */
// 入口参数：插入的数据
// 返回值：无
/************************************************************************/
template<class T>
void RB_Tree<T>::Insert_Node(T insert_data)
{
	//每次插入从根节点开始寻找插入位置
	RB_Tree_Node<T>* temp_Node = Root_Node;
	while (temp_Node != NULL)
	{
		if (insert_data > temp_Node->data) {
			//插入右节点
			if (temp_Node->Right_child == NULL) {
				temp_Node->Right_child = new RB_Tree_Node<T>(insert_data);
				temp_Node->Right_child->Father_Node = temp_Node;
				temp_Node->Right_child->color_tag = 1;
				std::cout << "插入右节点数据"<<insert_data << std::endl;
				if (temp_Node->color_tag == 1) {
					Fix_Tree(temp_Node->Right_child);
				}
				break;
			}
			else {
				temp_Node = temp_Node->Right_child;
			}

		}
		else {
			if (temp_Node->Left_child == NULL) 
			{
				temp_Node->Left_child = new RB_Tree_Node<T>(insert_data);
				temp_Node->Left_child->Father_Node = temp_Node;
				temp_Node->Left_child->color_tag = 1;
				std::cout << "插入左节点数据" << insert_data << std::endl;
				if (temp_Node->color_tag == 1) {
					Fix_Tree(temp_Node->Left_child);
				}
				break;
			}
			else {
				temp_Node = temp_Node->Left_child;
			}
		}
		
	}
}
/************************************************************************/
/* 函数功能：从红黑树中搜寻要删除的数据节点                             */
// 入口参数：删除的数据
// 返回值：1表示删除成功 -1表示删除失败
/************************************************************************/
template<class T>
int RB_Tree<T>::Delete_Node(T delete_data)
{
	RB_Tree_Node<T>* temp_Node = Root_Node;
	while (temp_Node->data != delete_data && temp_Node != NULL) {
		if (temp_Node->data < delete_data) 
		{
			temp_Node = temp_Node->Right_child;
		}
		else
		{
			temp_Node = temp_Node->Left_child;
		}
	}
	//找到了要删除的数据
	if (temp_Node != NULL) {
		int color_tag = temp_Node->color_tag;
		//如果当前节点没有孩子 则直接删除
		RB_Tree_Node<T>* child = NULL;
		RB_Tree_Node<T>* parent = NULL;
		if (temp_Node->Left_child == NULL && temp_Node->Right_child == NULL)
		{
			if (temp_Node == Root_Node) {
				RB_Tree<T>::~RB_Tree();
			}
			parent = temp_Node->Father_Node;
			
			
		} //左子树为空,右子树不为空 
		else if (temp_Node->Left_child == NULL && temp_Node->Right_child != NULL)
		{
			child = temp_Node->Right_child;
			parent = temp_Node->Father_Node;
			if (child)
				child->Father_Node = parent;
			
				if (temp_Node != Root_Node)
				{//要删除的节点不是根节点
					if (temp_Node == temp_Node->Father_Node->Left_child)
					{

						temp_Node->Father_Node->Left_child = temp_Node->Right_child;
						temp_Node->Right_child->Father_Node = temp_Node->Father_Node;

					}
					else if (temp_Node == temp_Node->Father_Node->Right_child)
					{

						temp_Node->Father_Node->Right_child = temp_Node->Right_child;
						temp_Node->Right_child->Father_Node = temp_Node->Father_Node;

					}
				}
				else {//要删除的节点为根节点
					Root_Node = temp_Node->Right_child;
					temp_Node->Right_child->Father_Node = NULL;
				}
				
		}//左子树不为空,右子树为空
		else if (temp_Node->Left_child != NULL && temp_Node->Right_child == NULL) {
			
			child = temp_Node->Left_child;
			parent = temp_Node->Father_Node;
			if (child)
				child->Father_Node = parent;
			if (temp_Node != Root_Node) {
				if (temp_Node->Father_Node->Left_child == temp_Node) 
				{

					temp_Node->Father_Node->Left_child = temp_Node->Left_child;
					temp_Node->Left_child->Father_Node = temp_Node->Father_Node;

				} 
				else if (temp_Node == temp_Node->Father_Node->Right_child)
				{

					temp_Node->Father_Node->Right_child = temp_Node->Left_child;
					temp_Node->Left_child->Father_Node = temp_Node->Father_Node;

				}
			}
			else {
				Root_Node = temp_Node->Left_child;
				temp_Node->Left_child->Father_Node = NULL;
			}
		}
		else if (temp_Node->Left_child != NULL && temp_Node->Right_child != NULL)
			//左右子树都不为空 当左右子树都不为空时其实删除的是后继节点，然后将值替换即可
		{
			//寻找继承节点 其实删除的是后继节点，故此在这种情况下需不需要调整其实是看后继节点的颜色
			RB_Tree_Node<T>* Successor_Node = temp_Node->Right_child;
			while (Successor_Node->Left_child) {
				Successor_Node = Successor_Node->Left_child;
			}
			color_tag = Successor_Node->color_tag;
			if (temp_Node->Father_Node) {
				if (temp_Node->Father_Node->Left_child == temp_Node) {
					temp_Node->Father_Node->Left_child = Successor_Node;
				}
				else if (temp_Node->Father_Node->Right_child == temp_Node) {
					temp_Node->Father_Node->Right_child = Successor_Node;
				}
			}
			else {
				Root_Node = Successor_Node;//如果没有父节点表示要删掉的是个根节点
			}
				RB_Tree_Node<T>* successor_child = Successor_Node->Right_child;
				RB_Tree_Node<T>* succssor_father = Successor_Node->Father_Node;
				//如果后继节点刚好是要删去节点的孩子，则直接连接即可，不用管后继节点的右子树
				if (succssor_father == temp_Node) {
					succssor_father = Successor_Node;
				}
				else {
					if (successor_child)
						successor_child->Father_Node = succssor_father;
					succssor_father->Left_child = successor_child;
					Successor_Node->Right_child = temp_Node->Right_child;

				}
				Successor_Node->Father_Node = temp_Node->Father_Node;
				Successor_Node->color_tag = temp_Node->color_tag;
				Successor_Node->Left_child = temp_Node->Left_child;
				temp_Node->Left_child->Father_Node = Successor_Node;
				child = successor_child;
				parent = succssor_father;
			
		}
		erase_Node(temp_Node);
		if (color_tag == 0) {//红色则不需要
			//如果删除的节点为黑色  则需调整红黑树
			{
				Fix_Tree_Delete(child, parent);
			}
		}

	}
	else {
		return -1;
	}
	return 1;
}

template<class T>
void RB_Tree<T>::Fix_Tree(RB_Tree_Node<T>* current_Node)
{
	RB_Tree_Node<T>* temp_current_Node = current_Node;
	//叔叔节点，用于判断如何旋转
	while (true) {
		if (temp_current_Node->Father_Node == NULL) {
			break;
		}
		if (temp_current_Node->Father_Node->color_tag != 1) {
			break;
		}
		RB_Tree_Node<T>* father_Node = temp_current_Node->Father_Node;
		RB_Tree_Node<T>* grandfather_Node = father_Node->Father_Node;
		if (grandfather_Node) {//如果爷爷节点存在
			//在爷爷节点的左子树
			if (father_Node == grandfather_Node->Left_child) //
			{
				RB_Tree_Node<T>* uncle_Node =  grandfather_Node->Right_child;
				if (uncle_Node) {//叔叔节点存在时
					//叔叔节点为红色时
					if (uncle_Node->color_tag == 1) {
						uncle_Node->color_tag = 0;
						father_Node->color_tag = 0;
						grandfather_Node->color_tag = 1;
						temp_current_Node = grandfather_Node;//将爷爷节点变成了红色 所以需要向上回溯
					}//叔叔节点为黑色时，需要旋转调整颜色，并且分两种情况当前节点为父节点的左右孩子
					else if (temp_current_Node == father_Node->Right_child) {
						temp_current_Node = temp_current_Node->Father_Node;
						Left_Rotate(temp_current_Node);//先左旋转，后右旋转
					} 
					else if (temp_current_Node == father_Node->Left_child)
					{  //当右旋转时直接要变颜色了
						father_Node->color_tag = 0;
						grandfather_Node->color_tag = 1;
						Right_Rotate(grandfather_Node);
					}
				}
				else {//没有叔叔节点时 直接判断当前节点 左右节点
					if (temp_current_Node == father_Node->Right_child) {
						temp_current_Node = temp_current_Node->Father_Node;
						Left_Rotate(temp_current_Node);
					}
					else if (temp_current_Node == father_Node->Left_child) {
						grandfather_Node->color_tag = 1;
						father_Node->color_tag = 0;
						Right_Rotate(grandfather_Node);
					}
				}
			}//在爷爷节点的右子树当中
			else if (grandfather_Node->Right_child == father_Node) {
				RB_Tree_Node<T>* uncle_Node = grandfather_Node->Left_child;
				if (uncle_Node)
				{
					if (uncle_Node->color_tag == 1) {
						grandfather_Node->color_tag = 1;
						uncle_Node->color_tag = 0;
						father_Node->color_tag = 0;
						temp_current_Node = grandfather_Node;
					}
					else if (temp_current_Node == father_Node->Left_child) {
						temp_current_Node = temp_current_Node->Father_Node;
						Right_Rotate(temp_current_Node);
					}
					else if (temp_current_Node == father_Node->Right_child) {
						father_Node->color_tag = 0;
						grandfather_Node->color_tag = 1;
						Left_Rotate(grandfather_Node);
					}
				}
				else {
					if (temp_current_Node == father_Node->Left_child) {
						temp_current_Node = temp_current_Node->Father_Node;
						Right_Rotate(temp_current_Node);
					}
					else if (temp_current_Node == father_Node->Right_child) {
						father_Node->color_tag = 0;
						grandfather_Node->color_tag = 1;
						Left_Rotate(grandfather_Node);
					}
				}
			}
		}
	}
	Root_Node->color_tag = 0;
}

template<class T>
void RB_Tree<T>::erase_Node(RB_Tree_Node<T>* Node_del)
{
	if (Node_del->Father_Node) {
	
		if (Node_del->Father_Node->Left_child==Node_del)
			Node_del->Father_Node->Left_child = NULL;
		else if(Node_del->Father_Node->Right_child == Node_del)
			Node_del->Father_Node->Right_child = NULL;
	}
	Node_del->color_tag = NULL;
	Node_del->Father_Node = NULL;
	Node_del->Left_child = NULL;
	Node_del->Right_child = NULL;
	Node_del->data = NULL;
	delete Node_del;
}

template<class T>
void RB_Tree<T>::Fix_Tree_Delete(RB_Tree_Node<T>* current_Node, RB_Tree_Node<T>* father_Node) {

	while ((!current_Node || current_Node->color_tag == 0) && current_Node != Root_Node) {
		if (father_Node->Left_child == current_Node) {
			//左边
			RB_Tree_Node<T>* brother  = father_Node->Right_child;
			// x的兄弟节点w是红色的x是平衡的，但因为节点B的左子树被删去了一个黑色节点，导致节点B的左子树黑高少了1，所以节点B是不平衡的。此时， ha==hb==hr-1， hr==hd==he==hf。
			//可以对节点B进行一次左旋，然后修改节点B和节点D的颜色，转变成情况2、3、4进行处理（上图转换后，x仍为A节点，B节点仍是不平衡的）
			if (brother->color_tag == 1) {
				brother->color_tag = 0;
				father_Node->color_tag = 1;
				Left_Rotate(father_Node);
				brother = father_Node->Right_child;
			}
			//2) x的兄弟节点w是黑色的，并且w的两个子节点都是黑色的
			if ((!brother->Left_child || brother->Left_child->color_tag == 0) &&
				(!brother->Right_child || brother->Right_child->color_tag == 0)) {
				brother->color_tag = 1;
				current_Node = father_Node;
				father_Node = current_Node->Father_Node;
			}
			else {
				//3) x的兄弟节点w是黑色的，而且w的左孩子是红色的，w的右孩子是黑色的
				if (!brother->Right_child || brother->Right_child->color_tag == 0) {
					brother->Left_child->color_tag = 0;
					brother->color_tag = 1;
					Right_Rotate(brother);
					brother = father_Node->Right_child;
				}
				//4) x的兄弟节点w是黑色的，并且w的右孩子是红色的
				brother->color_tag = father_Node->color_tag;
				father_Node->color_tag = 0;
				brother->Right_child->color_tag = 0;
				Left_Rotate(father_Node);
				current_Node = Root_Node;
				break;
			}
		}
		else {
			RB_Tree_Node<T>* brother = father_Node->Left_child;
			if (brother->color_tag == 1) {
				brother->color_tag = 0;
				father_Node->color_tag = 1;
				Right_Rotate(father_Node);
				brother = father_Node->Left_child;
			}
			if ((!brother->Left_child || brother->Left_child->color_tag == 0) &&
				(!brother->Right_child || brother->Right_child->color_tag == 0)) {
				brother->color_tag = 1;
				current_Node = father_Node;
				father_Node = current_Node->Father_Node;
			}
			else {
				if (!brother->Left_child || brother->Left_child->color_tag == 0) {
					brother->Right_child->color_tag = 0;
					brother->color_tag = 1;
					Right_Rotate(brother);
					brother = father_Node->Left_child;
				}
				brother->color_tag = father_Node->color_tag;
				father_Node->color_tag = 0;
				brother->Left_child->color_tag = 0;
				Right_Rotate(father_Node);
				current_Node = Root_Node;
				break;
			}
		}
	}
	if (current_Node) {
		current_Node->color_tag = 0;
	}
}

template<class T>
RB_Tree_Node<T>* RB_Tree<T>::Find_Node(T search_data)
{
	RB_Tree_Node<T>* temp_Node = Root_Node;

	while (temp_Node) {
		if (temp_Node->data < search_data) {
			temp_Node = temp_Node->Right_child;
		}
		else if (temp_Node->data > search_data) {
			temp_Node = temp_Node->Left_child;
		}
		else {
			return temp_Node;
		}
	}
	return nullptr;
}

template<class T>
RB_Tree_Node<T>* RB_Tree<T>::Find_Successor_Node(RB_Tree_Node<T>* current_Node)
{
	RB_Tree_Node<T>* temp_Node = current_Node->Right_child;
	while (temp_Node->Left_child!=NULL) {
		temp_Node = temp_Node->Left_child;
	}
	return temp_Node;
}
template <class T>
void RB_Tree<T>::Print(RB_Tree_Node<T>* node)
{
	if (node)
	{
		if (!node->Father_Node)
		{
			cout << setw(3) << node->data << "(B) is root" << endl;
		}
		else
		{
			cout << setw(3) << node->data << (node->color_tag == 1 ? "(R)" : "(B)") << " is " 
				<< setw(3) << node->Father_Node->data << "'s " << setw(12) << (node->data < node->Father_Node->data ? "left child" : "right child") << endl;
		}
		Print(node->Left_child);
		Print(node->Right_child);
	}
}