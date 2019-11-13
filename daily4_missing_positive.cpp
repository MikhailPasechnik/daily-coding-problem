/*
 * This is your coding interview problem for today.
 *
 * This problem was asked by Stripe.
 *
 * Given an array of integers, find the first missing positive integer in linear time and constant space.
 * In other words, find the lowest positive integer that does not exist in the array.
 * The array can contain duplicates and negative numbers as well.
 *
 * For example, the input [3, 4, -1, 1] should give 2. The input [1, 2, 0] should give 3.
 *
 * */
#include <vector>
#include <cassert>

using namespace std;

int missing_positive(vector<int> v)
{
	int 	r = 1;
	int 	len = v.size();
	/*
	 * [3,  4, -1, 1]
	 * [-1, 4,  3, 1]
	 *   #		^
	 * [-1, 4,  3, 1]
	 *      #
	 * [  , 4,  3, 1]
	 * 			#
	 * [  ,  ,  3, 1]
	 * 			   #
	 *
	 * [ 1,  ,  3,  ]
	 * 		!
	 * */
	for (int i = 0; i < len; ++i)
	{
		int n = v[i];
		while (n > 0 && n <= len && n != i + 1)
		{
			int tmp = v[n - 1];
			v[n - 1] = n;
			v[i] = tmp;
			n = tmp;
		}
	}
	int j;
	for (j = 0; j < len; ++j)
	{
		int n = v[j];
		if (n != j + 1)
		{
			r = j + 1;
			break ;
		}
	}
	return j == len ? len + 1 : r;
}

int main()
{
	assert(missing_positive((vector<int>){3, 4, -1, 1}) == 2);
	assert(missing_positive((vector<int>){1, 2, 3, 4}) == 5);
	assert(missing_positive((vector<int>){}) == 1);
	assert(missing_positive((vector<int>){-1, 0}) == 1);
	return 0;
}
