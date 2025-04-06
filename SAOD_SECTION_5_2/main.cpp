#include <iostream>
#include <string>
#include <regex>

using namespace std;

int VERTEX_COUNT;

struct Tree {
	int data;
	Tree* left;
	Tree* right;
} *TREE;

struct Stack{
	int vertex_level;
	Tree* vertex;
	Stack* next;
} *stack;

static void initStack(Tree *tree) {
	stack = new Stack;
	stack->vertex = tree;
	stack->vertex_level = -1;
	stack->next = NULL;
}

static bool isEmpty(){
	return ((stack->vertex_level) < 0);
}

static Tree* push(Tree* vertex, int n) {
	Tree* temp;
	int leftVertexCount, rightVertexCount;

	if (n == 0) return NULL;
	leftVertexCount = n / 2;
	rightVertexCount = n - leftVertexCount - 1;
	temp = new Tree;
	temp->data = rand() % 100;
	temp->left = push(temp->left, leftVertexCount);
	temp->right = push(temp->right, rightVertexCount);
	vertex = temp;
	return vertex;
}

static void printForward(Tree* current, int level) {
	if (current != NULL) {
		string str;
		for (int i = 0; i < level; i++) str += "	";
		
		cout << " " << str << current->data << endl;
		printForward(current->left, level+1);
		printForward(current->right, level+1);
	}
}

static void printNoRecursiya() {
	initStack(TREE);

	Tree* current = TREE;
	bool finish = false;
	int level = 0;

	while (!finish) {
		while (current != NULL){
			Stack* newStack = new Stack;
			newStack->vertex = current;
			newStack->vertex_level = level;
			newStack->next = stack;
			stack = newStack;
			current = current->left;
			level++;
		}
		if (isEmpty()) finish = true;
		else {
			level = stack->vertex_level;
			current = stack->vertex;
			string str = "";
			for (int i = 0; i < level; i++) str += "	";
			cout << str << current->data << endl;
			Stack* temp = stack;
			stack = stack->next;
			delete temp;
			current = current->right;
			level++;
		}
	}
}

static void printSymetric(Tree* current, int level) {
	if (current != NULL) {
		printSymetric(current->left, level + 1);
		string str;
		for (int i = 0; i < level; i++) cout << "	";
		cout << str << current->data << endl;
		printSymetric(current->right, level + 1);
	}
}

static void printBackSymetric(Tree* current, int level) {
	if (current != NULL) {
		printBackSymetric(current->right, level + 1);
		string str;
		for (int i = 0; i < level; i++) cout << "	";
		cout << str << current->data << endl;
		printBackSymetric(current->left, level + 1);
	}
}

static void deleteTree(Tree* current) {
	if (current != NULL) {
		deleteTree(current->left);
		deleteTree(current->right);
		delete current;
	}
}

static int validIntegerInput(string message) {
	string input;
	regex valid("-?[1-9][0-9]*");
	do {
		cout << message;
		getline(cin, input);
	} while (!regex_match(input, valid));
	return stoi(input);
}


int main() {
	setlocale(LC_ALL, "Russian");

	srand(time(0));
	VERTEX_COUNT = validIntegerInput("Введите количество вершин дерева: ");
	while (VERTEX_COUNT > 0) {
		cout << endl << "---------------------------------------------------------------" << endl;
		TREE = push(TREE, VERTEX_COUNT);
		cout << "Дерево создано" << endl;

		cout << endl << "Дерево в прямом порядке:" << endl;
		printForward(TREE, 0);

		cout << endl << "Дерево в симметричном порядке:" << endl;
		printSymetric(TREE, 0);

		cout << endl << "Дерево в симметричном порядке без рекрсии:" << endl;
		printNoRecursiya();

		cout << endl << "Дерево в обратном симметричном порядке:" << endl;
		printBackSymetric(TREE, 0);

		deleteTree(TREE);
		cout << endl << "Дерево удалено" << endl;

		VERTEX_COUNT = validIntegerInput("Введите количество вершин дерева: ");
	}
}

