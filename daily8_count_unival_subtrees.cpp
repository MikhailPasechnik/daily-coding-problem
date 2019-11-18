/*
 * This is your coding interview problem for today.
 *
 * This problem was asked by Google.
 *
 * A unival tree (which stands for "universal value")
 * is a tree where all nodes under it have the same value.
 *
 * Given the root to a binary tree, count the number of unival subtrees.
 *
 * For example, the following tree has 5 unival subtrees:
 *
 *     0
 *   /  \
 *  1    0
 *      / \
 *     1   0
 *    / \
 *   1   1
 *  /
 * 0
 * */

#include <cassert>
#include <iostream>

using namespace std;

class Node
{
public:
	bool val;
	Node *left;
	Node *right;
	Node(bool val, Node *left, Node *right)
	{
		this->val = val;
		this->left = left;
		this->right = right;
	};

	int count_unival() {
		auto u = Node::unival(this);
		return u.second;
	}
	~Node()
	{
		delete left;
		delete right;
	}

private:
	static pair<bool, int> unival(Node *n)
	{
		if (n == nullptr)
			return pair(true, 0);

		auto lUnival = unival(n->left);
		auto rUnival = unival(n->right);

		int count = lUnival.second + rUnival.second;

		if (lUnival.first && rUnival.first)
		{
			// Left or right is unival but value differs
			if (n->left && n->left->val != n->val)
				return pair(false, count);
			if (n->right && n->right->val != n->val)
				return pair(false, count);

			/*
			 * Handel's cases where n is leaf node
			 * or left and right is unival with same value
			 *
			 * */
			return pair(true, count + 1);
		}
		return pair(false, count);
	}
};

int main()
{
	auto root = Node(
		false,
		new Node(true,
			nullptr, nullptr),
		new Node(false,
			new Node(true,
				new Node(true, new Node(false, nullptr, nullptr), nullptr),
				new Node(true, nullptr, nullptr)),
			new Node(false, nullptr, nullptr)
		)
	);
	/*
	 *     0
	 *   /  \
	 *  1 <  0
	 *      / \
	 *     1   0 <
	 *    / \
	 *   1   1 <
	 *  /
	 * 0 <
	 *
	 * */
	assert(root.count_unival() == 4);
	auto root2 = Node(
		false,
		new Node(true,
			nullptr, nullptr),
		new Node(false,
			new Node(true,
				new Node(true, nullptr, nullptr),
				new Node(true, nullptr, nullptr)),
			new Node(false, nullptr, nullptr)
		)
	);
	/*
	 *     0
	 *   /  \
	 *  1 <  0
	 *      / \
	 *     1 < 0 <
	 *    / \
	 *   1 < 1 <
	 *
	 * */
	assert(root2.count_unival() == 5);
}
