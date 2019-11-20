/*
 * This problem was asked by Twitter.
 *
 * Implement an autocomplete system.
 * That is, given a query string s and a set of all possible query strings,
 * return all strings in the set that have s as a prefix.
 *
 * For example, given the query string de and the set of strings [dog, deer, deal],
 * return [deer, deal].
 *
 * Hint: Try preprocessing the dictionary into a more efficient data structure to speed up queries.
 *
 * */

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cassert>
#include <unordered_map>

using namespace std;


class Node
{
public:
	Node()
	{
		this->value = string();
		this->children = unordered_map<char, Node*>();
	}
	~Node()
	{
		for (auto c: children)
			delete c.second;
	}

	void construct(const set<string>& data)
	{
		for (const auto& w: data)
			this->insert(w);
	}

	void insert(const string& word)
	{
		_insert(word, 0);
	}

	set<string> descendants()
	{
		set<string> d;
		this->_autocomplete(d);
		return d;
	}
	void print()
	{
		Node::_print(this, 0);
	}
	set<string> autocomplete(const string &query)
	{
		Node *node = this;
		for (int i = 0; i < query.size(); ++i)
		{
			auto child = node->children.find(query[i]);
			if (child != node->children.end())
			{
				if (i == query.size() - 1)
					return child->second->descendants();
				node = child->second;
			}
			else
				break;
		}
		return {};
	}
private:
	string value;
	unordered_map<char, Node*> children;

	void _autocomplete(set<string> &d)
	{
		if (!this->value.empty())
			d.insert(this->value);
		for (auto c: children)
			c.second->_autocomplete(d);
	}

	void _insert(const string& word, size_t at)
	{

		if (at <= word.size() - 1)
		{
			auto child = children.find(word[at]);
			if (child != children.end())
				child->second->_insert(word, at + 1);
			else
			{
				children.insert(pair(word[at], new Node()));
				children[word[at]]->_insert(word, at + 1);
			}
		}
		else
			this->value = word;
	}
	static void _print(Node *n, int level)
	{
		for (int _ = 0; _ < level; ++_)
			cout << " ";
		cout << " [" << n->value << "]: ";
		for (auto c: n->children)
			cout << " '" << c.first << "' ";
		cout <<  endl;
		for (auto c: n->children)
			Node::_print(c.second, level + 1);
	}
};

set<string> autocomplete(const string& query, const set<string>& data)
{
	/*
	 * Construct tree where structure represents 'path' to the word:
	 * Given data ["hola", "ho", "hi"] tree will be
	 * 			     		ROOT
	 * 			 ____________|
	 * 		 ___h_____
	 * 		|        |
	 * 		o:'ho'   i:'hi'
	 * 	   |
	 * 	   l
	 * 	   |
	 * 	   a:'hola'
	 *
	 * And by iterating query characters, we can traverse tree to find node
	 * from where we can return every descendent node with data.
	 * */
	auto root = Node();
	root.construct(data);
	cout << "Query: " << query << endl << "Tree: " << endl;
	root.print();
	return root.autocomplete(query);
}

int main()
{
	assert(autocomplete("de", {"dog", "dogs", "deer", "deal"}) == set<string>({"deer", "deal"}));
	assert(autocomplete("dog", {"dog", "dogs", "deer", "deal"}) == set<string>({"dog", "dogs"}));
	assert(autocomplete("dog", {}) == set<string>({}));
	return 0;
}
