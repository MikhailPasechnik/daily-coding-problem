/*
 * This is your coding interview problem for today.
 *
 * This problem was asked by Google.
 *
 * An XOR linked list is a more memory efficient doubly linked list.
 * Instead of each node holding next and prev fields, it holds a field named both,
 * which is an XOR of the next node and the previous node.
 * Implement an XOR linked list; it has an add(element) which adds the element to the end,
 * and a get(index) which returns the node at index.
 *
 * If using a language that has no pointers (such as Python),
 * you can assume you have access to get_pointer and
 * dereference_pointer functions that converts between nodes and memory addresses.
 * */
#include <iostream>
#include <cassert>
using namespace std;

class Node {
public:
	uintptr_t diff;
	int data;

	explicit Node(int data){
		this->data = data;
		this->diff = (uintptr_t) nullptr;
	};

	void setNext(Node *prev, Node *next)
	{
		this->diff = (uintptr_t)prev ^ (uintptr_t)next;
	}

	Node *next(Node *prev){
		return (Node *)(uintptr_t)((uintptr_t)prev ^ diff);
	}
	Node *prev(Node *next){
		return (Node *)(uintptr_t)((uintptr_t)next ^ diff);
	}
};

string bits(uintptr_t p)
{
	string b;
	uint64_t m = 1;
	for (unsigned int i = 0; i < 4; ++i)
	{
		if (!(i % 4))
			b.insert(0, " ");
		b.insert(0, m << i & p ? "1" : "0");
	}
	return (b);
}

int main()
{
	auto r = new Node(0);
	auto n1 = new Node(1);
	r->setNext(nullptr, n1);
	auto n2 = new Node(2);
	n1->setNext(r, n2);
	auto n3 = new Node(3);
	n2->setNext(n1, n3);
	auto n4 = new Node(4);
	n3->setNext(n2, n4);
	n4->setNext(n3, nullptr);

	cout <<
		"           a: " << bits(0b101u) << endl <<
		"           b: " << bits(0b001u) << endl <<
	    "         a^b: " << bits(0b101u ^ 0b001u) << endl <<
	    "(a^b)^a == b: " << bits(0b100u ^ 0b101u) << endl <<
		"(a^b)^b == a: " << bits(0b100u ^ 0b001u) << endl <<
	"";

	Node *previous = nullptr;
	Node *tmp = previous;
	Node *node = r;
	int i = node->data;

	// Traverse forward
	while (node) {
		assert(node->data == i);
		cout << node->data;
		tmp = node;
		node = node->next(previous);
		cout << (node ? " -> " : "\n");
		previous = tmp;
		i++;
	};

	// Traverse back
	previous = nullptr;
	tmp = previous;
	node = n4;
	i = node->data;
	while (node) {
		assert(node->data == i);
		cout << node->data;
		tmp = node;
		node = node->prev(previous);
		cout << (node ? " <- " : "\n");
		previous = tmp;
		i--;
	};
	return 0;
}
