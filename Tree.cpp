#include <iostream>

using namespace std;

struct node {
	int value;
	struct node* left;
	struct node* right;
};

struct node* root = NULL;


//如果该树为空，在根节点插入
//如果插入的数小于根节点，插入左子树
//如果插入的数大于根节点，插入右子树
void insert_interger(node **tree, int value) {
	//**tree=&root
	//*tree=root


	//判断是否为空
	if (*tree == NULL) {
		*tree = new node;  //分配空间
		(*tree)->left = 0;
		(*tree)->right = 0;
		(*tree)->value = value;

	}

	//递归写入右子树
	else if ((*tree)->value < value) {
		insert_interger(&((*tree)->right), value);

	}
	//递归写入左子树
	else if ((*tree)->value > value) {
		insert_interger(&((*tree)->left), value);

	}


}

//中序遍历
void print_tree(node *tree) {
	if (tree != NULL) {
		print_tree(tree->left);
		cout << tree->value << endl;
		print_tree(tree->right);
	}
}


//销毁树
void terminate_tree(struct node* tree) {
	if (tree == NULL)
		return;

	if (tree->left != NULL)
		return terminate_tree(tree->left);
	if (tree->right != NULL)
		return terminate_tree(tree->right);
	delete tree;
	tree = NULL;
	cout << "Tree terminate" << endl;
}

int main() {

	insert_interger(&root, 2);
	insert_interger(&root, 4);
	insert_interger(&root, 1);
	insert_interger(&root, 3);
	print_tree(root);
	terminate_tree(root);
	system("pause");

	return 0;
}