/*
 * This is your coding interview problem for today.
 *
 * This problem was asked by Uber.
 *
 * Given an array of integers, return a new array such that each element at index i of the new array is the product of all the numbers in the original array except the one at i.
 *
 * For example, if our input was [1, 2, 3, 4, 5], the expected output would be [120, 60, 40, 30, 24]. If our input was [3, 2, 1], the expected output would be [2, 3, 6].
 *
 * Follow-up: what if you can't use division?
 * */
#include <vector>

using namespace std;

vector<int> prod_array(vector<int> &v)
{
	auto result = vector<int>(v.size());
	auto a = vector<int>(v.size());
	auto b = vector<int>(v.size());

	size_t size = v.size();
	if (!size)
		return (v);

	a[0] = 1;
	b[size - 1] = 1;

	/*		[2, 3, 4]
	 *
	 * 	    [1, 2, 6]
	 * 		 1, 2, 3
	 * 			1  2
	 * 			   1
	 *
	 *	    [12,4, 1]
	 *		 3	4  1
	 *		 4	1
	 *		 1
	 *		[12 8 6]
	 *
	 *		 3	4  1
	 *		 4	1  2
	 *		 1  2  3
	 *
	 * */

	for (size_t i = 1; i < size; ++i)
		a[i] = v[i - 1] * a[i - 1];
		// 1:0	   2  	     1
		// 2:1	   3  	     2

	for (size_t i = size - 1; i > 0; --i)
		b[i - 1] = v[i] * b[i];
		// 1:0	   4  	     1
		// 0:1	   3  	     4

	for (int j = 0; j < size; ++j)
		result[j] = a[j] * b[j];

	return result;
}

int main()
{
	vector<int> v2 = {1, 2, 3};
	prod_array(v2);
	return 0;
}
