/*
 * This is your coding interview problem for today.
 *
 * This problem was asked by Airbnb.
 *
 * Given a list of integers,
 * write a function that returns the largest sum of non-adjacent numbers.
 * Numbers can be 0 or negative.
 *
 * For example, [2, 4, 6, 2, 5] should return 13,
 * since we pick 2, 6, and 5.
 * [5, 1, 1, 5] should return 10, since we pick 5 and 5.
 *
 * */
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;


int largest_sum(vector<int> v)
{
	if (v.size() == 2)
		return max(0, max(v[0], v[1]));
	else if (v.size() == 1)
		return max(0, v[0]);
	else if (v.empty())
		return (0);

	int a = max(0, v[0]);
	int b = max(a, v[1]);

	for (int i = 2; i < v.size(); ++i)
	{
		int t = b;
		b = max(v[i] + a, b);
		a = t;
	}
	return (b);
}

int main()
{
	assert(largest_sum(vector<int>({5, 1, 1, 5})) == 10);
	assert(largest_sum(vector<int>({2, 4, 6, 2, 5})) == 13);
	return (0);
}
