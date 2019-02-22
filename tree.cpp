#include <string>
using namespace std;
struct node {
	char *txt; 
	int len;
	int tok;
	struct node* parent;
};

struct node* add_child(struct node *parent, const char *txt, int len, int tok) {
	int j = 0;
	if (parent == 0) {
		struct node *children = (struct node*)malloc(sizeof(struct node));
		children->txt = txt;
		children->len = len;
		children->tok = tok;
		children->parent = parent;
		for (int i = 0; i<100; i++) {
			children->children[i] = 0;
		}
		return children;

	}
	else {
		while (parent->children[j] != 0 && j<100) {
			j++;
		}
		struct node *children = (struct node*)malloc(sizeof(struct node));
		parent->children[j] = children;
		children->txt = txt;
		children->len = len;
		children->tok = tok;
		children->parent = parent;
		children->childparent = j;
		parent->numc = j;
		for (int i = 0; i<100; i++) {
			children->children[i] = 0;
		}
		return children;
	}
}
struct node* add_child2(struct node *parent, struct node *child) {
	int j = 0;
	while (parent->children[j] != 0 && j<100) {
		j++;
	}
	struct node *children = (struct node*)malloc(sizeof(struct node));
	parent->children[j] = children;
	children->txt = child->txt;
	children->len = child->len;
	children->tok = child->tok;
	children->parent = parent;
	children->childparent = j;
	parent->numc = j;
	for (int i = 0; i<100; i++) {
		children->children[i] = 0;
	}
	return children;
}


struct node* add_sibling(struct node *ptr, const char *txt, int len, int tok) {
	struct node* p = ptr->parent;
	return add_child(p, txt, len, tok);
}

void del_sub_tree(struct node *tree) {
	int x = 0;
	struct node *par;
	x = tree->childparent;
	par = tree->parent;
	for (int i = 0; i<100; i++) {
		if (tree->children[i] != 0) {
			del_sub_tree(tree->children[i]);
		}
	}
	free(tree);
	for (int j = x; j<100; j++) {
		if (par->children[j] != 0) {
			par->children[j] = par->children[j + 1];
			if (par->children[j] != 0) {
				par->children[j]->childparent = j;
			}
		}
	}
}

//void printnode(struct node*n){
//	printf("%s\n",n->txt);
//}

void traverse_depth_first(void(*fun)(struct node*), struct node* root) {
	int x;
	int i = 0;
	fun(root);
	x = root->numc;
	while (root->children[i] != 0 && i<x + 1) {
		traverse_depth_first(fun, root->children[i]);
		i++;
	}
}

void traverse_breadth_first(void(*fun)(struct node*), struct node* root) {
	struct node* queue[100];
	queue[0] = root;
	int fui = 0;
	int lui = 0;
	while (fui <= lui) {
		fun(queue[fui]);
		int i = 0;
		while (queue[fui]->children[i] != 0) {
			queue[++lui] = queue[fui]->children[i];
			i++;
		}
		fui++;
	}
}

//int main(){
//	struct node*F=add_child(0, "F", 1, 2);
//	struct node*B=add_child(F, "B", 1, 2);
//	struct node*C=add_sibling(B, "C", 1, 2);
//	struct node*E=add_child(B, "E", 1, 2);
//	struct node*X=add_child(C, "x", 1, 2);
//
//	traverse_depth_first(printnode, F);
//}

