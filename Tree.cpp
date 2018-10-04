#include <iostream>

using namespace std;

struct node {
	int value;
	struct node* left;
	struct node* right;
};

struct node* root = NULL;

void insert_integer(struct node** tree, int value){
	node* a;
	a = new node;
	a->value = value;


}
void print_tree(struct node* tree);
void terminate_tree(struct node* tree);

int main() {
	node* a;
	a = new node;
	a->value=

	int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	insert_integer(a, arr);

	return 0;
}


@Marco