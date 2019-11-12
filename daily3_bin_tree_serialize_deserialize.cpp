/* This problem was asked by Google.
 *
 * Given the root to a binary tree, implement serialize(root), which serializes the tree into a string, and deserialize(s), which deserializes the string back into the tree.
 *
 * For example, given the following Node class
 *
 * class Node:
 *     def __init__(self, val, left=None, right=None):
 *         self.val = val
 *         self.left = left
 *         self.right = right
 * The following test should pass:
 *
 * node = Node('root', Node('left', Node('left.left')), Node('right'))
 * assert deserialize(serialize(node)).left.left.val == 'left.left'
 * */
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

class Node
{
public:
	explicit Node()
	{
		this->right = this->left = nullptr;
		this->data = "";
	}

	explicit Node(string data)
	{
		setData(data);
		this->left = nullptr;
		this->right = nullptr;
	}

	Node(string data, Node *right, Node *left)
	{
		setData(data);
		this->left = left;
		this->right = right;
	}

	void setData(string &str)
	{
		if (str.find('|') != string::npos)
			throw invalid_argument(" '|' in node data! '|' used as delimiter for serialization");
		if (str.find('*') != string::npos)
			throw invalid_argument(" '*' in node data! '*' used to indicate NULL for left and right nodes during serialization");
		this->data = move(str);
	}

	void print()
	{
		this->_print(this, 0);
	}

	~Node()
	{
		delete this->right;
		delete this->left;
	}

	Node *left;
	Node *right;
	string data;
private:
	void _print(Node *n, int level)
	{
		for (int _ = 0; _ < level; ++_)
			cout << " ";
		cout << " <" << n->data << ">\n";
		if (n->right)
			this->_print(n->right, level + 1);
		if (n->left)
			this->_print(n->left, level + 1);

	}
};

Node *_deserialize(vector<string>::iterator *it, vector<string>::iterator end)
{
	if (*it == end)
		return (nullptr);
	if (**it == "*")
	{
		*it = next(*it);
		return (nullptr);
	}
	auto n = new Node(**it);
	*it = next(*it);

	n->right = _deserialize(it, end);
	n->left = _deserialize(it, end);

	return n;
}

void serialize(Node *node, stringstream *st)
{
	*st << node->data << '|';
	if (node->right)
		serialize(node->right, st);
	else
		*st << '*' << '|';
	if (node->left)
		serialize(node->left, st);
	else
		*st << '*' << '|';
}

Node *deserialize(const string& data)
{
	stringstream st(data);
	vector<string> split;
	string part;


	while (getline(st, part, '|'))
		split.push_back(part);
	auto begin = split.begin();
	return _deserialize(&begin, split.end());
}

int main()
{
	Node *root;
	try
	{
		root = new Node(
				"root",
				new Node("r",
						 new Node("r.r",
								  new Node("r.r.r"), nullptr
						 ),
						 new Node("r.l")),
				new Node("l",
						 new Node("l.r"), new Node("l.l"))
		);
	} catch (std::exception &e)
	{
		cout << e.what();
		exit(1);
	}
	cout << "input tree:\n";
	root->print();

	stringstream st;
	serialize(root, &st);

	cout << "\nserialized tree:\n";
	cout << st.str();

	auto serialized = deserialize(st.str());
	cout << "\ndeserialized tree:\n";
	serialized->print();
	return 0;
}
