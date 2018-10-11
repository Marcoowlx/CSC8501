#include <iostream>

using namespace std;

struct node {
	int value;
	struct node* left;
	struct node* right;
};

struct node* root = NULL;

class tree {
public:
	tree(node* tree);
	~tree();
	void insert_interger(node **tree, int value);
	void print_tree(node *tree);
	int search_tree(node *tree, int value);
	void terminate_tree(struct node *tree);

};

tree::tree(node * tree) {
	tree = new node;  //分配空间
	tree->left = 0;
	tree->right = 0;
}

tree::~tree() {

}



//如果该树为空，在根节点插入
//如果插入的数小于根节点，插入左子树
//如果插入的数大于根节点，插入右子树
void tree::insert_interger(node **tree, int value) {
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
void tree::print_tree(node* tree) {
	if (tree != NULL) {
		print_tree(tree->left);
		cout << tree->value << endl;
		print_tree(tree->right);
	}
}


//查找
int tree::search_tree(node* tree, int value) {
	if (tree == NULL) {
		return 0;
	}
	else {
		if (tree->value == value) {
			return 1;
		}
		else if(tree->value>value){
			return search_tree(tree->left, value);
		}
		else if (tree->value < value) {
			return search_tree(tree->right, value);
		}
		else {
			return 0;
		}
	}
}






//销毁树
void tree::terminate_tree(struct node* tree) {
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
	int s;
	int j;
	cout << "Input a value to search:" << endl;
	cin >> s;
	tree t(root);
	t.insert_interger(&root, 1);
	t.insert_interger(&root, 4);
	t.insert_interger(&root, 2);
	t.insert_interger(&root, 3);
	j=t.search_tree(root, s);
	if (s == 1) {
		cout << "The tree has [ " <<s<<" ] "<< endl;
	}
	else {
		cout << "The tree dont has [ "<<s<<" ] " << endl;
	}
	t.print_tree(root);
	t.terminate_tree(root);
	system("pause");

	return 0;
}