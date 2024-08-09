
#include"RB_Tree.h"
#include<iostream>
#include <iomanip>

using namespace std;
template<class T>
RB_Tree<T>::RB_Tree(T Root_Data) :Root_Node(NULL) {
	if (Root_Node == NULL) {
		Root_Node = new RB_Tree_Node<T>(Root_Data);
		//�����ڵ���ɫ����Ϊ0
		Root_Node->color_tag = 0;

		std::cout << "���������" << std::endl;
	}
}

template<class T>
RB_Tree<T>::~RB_Tree()
{
	//Destroy(Root_Node);
	std::cout << "�ݻٺ����" << std::endl;
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
/* �������ܣ��������в���һ���ڵ�           ��С�Ҵ�                           */
// ��ڲ��������������
// ����ֵ����
/************************************************************************/
template<class T>
void RB_Tree<T>::Insert_Node(T insert_data)
{
	//ÿ�β���Ӹ��ڵ㿪ʼѰ�Ҳ���λ��
	RB_Tree_Node<T>* temp_Node = Root_Node;
	while (temp_Node != NULL)
	{
		if (insert_data > temp_Node->data) {
			//�����ҽڵ�
			if (temp_Node->Right_child == NULL) {
				temp_Node->Right_child = new RB_Tree_Node<T>(insert_data);
				temp_Node->Right_child->Father_Node = temp_Node;
				temp_Node->Right_child->color_tag = 1;
				std::cout << "�����ҽڵ�����"<<insert_data << std::endl;
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
				std::cout << "������ڵ�����" << insert_data << std::endl;
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
/* �������ܣ��Ӻ��������ѰҪɾ�������ݽڵ�                             */
// ��ڲ�����ɾ��������
// ����ֵ��1��ʾɾ���ɹ� -1��ʾɾ��ʧ��
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
	//�ҵ���Ҫɾ��������
	if (temp_Node != NULL) {
		int color_tag = temp_Node->color_tag;
		//�����ǰ�ڵ�û�к��� ��ֱ��ɾ��
		RB_Tree_Node<T>* child = NULL;
		RB_Tree_Node<T>* parent = NULL;
		if (temp_Node->Left_child == NULL && temp_Node->Right_child == NULL)
		{
			if (temp_Node == Root_Node) {
				RB_Tree<T>::~RB_Tree();
			}
			parent = temp_Node->Father_Node;
			
			
		} //������Ϊ��,��������Ϊ�� 
		else if (temp_Node->Left_child == NULL && temp_Node->Right_child != NULL)
		{
			child = temp_Node->Right_child;
			parent = temp_Node->Father_Node;
			if (child)
				child->Father_Node = parent;
			
				if (temp_Node != Root_Node)
				{//Ҫɾ���Ľڵ㲻�Ǹ��ڵ�
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
				else {//Ҫɾ���Ľڵ�Ϊ���ڵ�
					Root_Node = temp_Node->Right_child;
					temp_Node->Right_child->Father_Node = NULL;
				}
				
		}//��������Ϊ��,������Ϊ��
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
			//������������Ϊ�� ��������������Ϊ��ʱ��ʵɾ�����Ǻ�̽ڵ㣬Ȼ��ֵ�滻����
		{
			//Ѱ�Ҽ̳нڵ� ��ʵɾ�����Ǻ�̽ڵ㣬�ʴ�������������費��Ҫ������ʵ�ǿ���̽ڵ����ɫ
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
				Root_Node = Successor_Node;//���û�и��ڵ��ʾҪɾ�����Ǹ����ڵ�
			}
				RB_Tree_Node<T>* successor_child = Successor_Node->Right_child;
				RB_Tree_Node<T>* succssor_father = Successor_Node->Father_Node;
				//�����̽ڵ�պ���Ҫɾȥ�ڵ�ĺ��ӣ���ֱ�����Ӽ��ɣ����ùܺ�̽ڵ��������
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
		if (color_tag == 0) {//��ɫ����Ҫ
			//���ɾ���Ľڵ�Ϊ��ɫ  ������������
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
	//����ڵ㣬�����ж������ת
	while (true) {
		if (temp_current_Node->Father_Node == NULL) {
			break;
		}
		if (temp_current_Node->Father_Node->color_tag != 1) {
			break;
		}
		RB_Tree_Node<T>* father_Node = temp_current_Node->Father_Node;
		RB_Tree_Node<T>* grandfather_Node = father_Node->Father_Node;
		if (grandfather_Node) {//���үү�ڵ����
			//��үү�ڵ��������
			if (father_Node == grandfather_Node->Left_child) //
			{
				RB_Tree_Node<T>* uncle_Node =  grandfather_Node->Right_child;
				if (uncle_Node) {//����ڵ����ʱ
					//����ڵ�Ϊ��ɫʱ
					if (uncle_Node->color_tag == 1) {
						uncle_Node->color_tag = 0;
						father_Node->color_tag = 0;
						grandfather_Node->color_tag = 1;
						temp_current_Node = grandfather_Node;//��үү�ڵ����˺�ɫ ������Ҫ���ϻ���
					}//����ڵ�Ϊ��ɫʱ����Ҫ��ת������ɫ�����ҷ����������ǰ�ڵ�Ϊ���ڵ�����Һ���
					else if (temp_current_Node == father_Node->Right_child) {
						temp_current_Node = temp_current_Node->Father_Node;
						Left_Rotate(temp_current_Node);//������ת��������ת
					} 
					else if (temp_current_Node == father_Node->Left_child)
					{  //������תʱֱ��Ҫ����ɫ��
						father_Node->color_tag = 0;
						grandfather_Node->color_tag = 1;
						Right_Rotate(grandfather_Node);
					}
				}
				else {//û������ڵ�ʱ ֱ���жϵ�ǰ�ڵ� ���ҽڵ�
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
			}//��үү�ڵ������������
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
			//���
			RB_Tree_Node<T>* brother  = father_Node->Right_child;
			// x���ֵܽڵ�w�Ǻ�ɫ��x��ƽ��ģ�����Ϊ�ڵ�B����������ɾȥ��һ����ɫ�ڵ㣬���½ڵ�B���������ڸ�����1�����Խڵ�B�ǲ�ƽ��ġ���ʱ�� ha==hb==hr-1�� hr==hd==he==hf��
			//���ԶԽڵ�B����һ��������Ȼ���޸Ľڵ�B�ͽڵ�D����ɫ��ת������2��3��4���д�����ͼת����x��ΪA�ڵ㣬B�ڵ����ǲ�ƽ��ģ�
			if (brother->color_tag == 1) {
				brother->color_tag = 0;
				father_Node->color_tag = 1;
				Left_Rotate(father_Node);
				brother = father_Node->Right_child;
			}
			//2) x���ֵܽڵ�w�Ǻ�ɫ�ģ�����w�������ӽڵ㶼�Ǻ�ɫ��
			if ((!brother->Left_child || brother->Left_child->color_tag == 0) &&
				(!brother->Right_child || brother->Right_child->color_tag == 0)) {
				brother->color_tag = 1;
				current_Node = father_Node;
				father_Node = current_Node->Father_Node;
			}
			else {
				//3) x���ֵܽڵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ�ģ�w���Һ����Ǻ�ɫ��
				if (!brother->Right_child || brother->Right_child->color_tag == 0) {
					brother->Left_child->color_tag = 0;
					brother->color_tag = 1;
					Right_Rotate(brother);
					brother = father_Node->Right_child;
				}
				//4) x���ֵܽڵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ��
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