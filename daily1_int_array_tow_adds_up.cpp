/*
 * This is your coding interview problem for today.
 *
 * This problem was recently asked by Google.
 *
 * Given a list of numbers and a number k, return whether any two numbers from the list add up to k.
 *
 * For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.
 *
 * */
#include <vector>
#include <set>
#include <cassert>

using namespace std;


bool adds_up(vector<int> v, int k)
{
	set<int> s;
	for (int i: v)
	{
		s.insert(i);
		if (s.find(k - i) != s.end())
		{
			return (true);
		}
	}
	return (false);
}


int main()
{
	assert(adds_up((vector<int>){10, 15, 3, 7}, 17));
	assert(!adds_up((vector<int>){}, 17));
}
