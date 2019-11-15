/*
 * This is your coding interview problem for today.
 *
 * This problem was asked by Facebook.
 *
 * Given the mapping a = 1, b = 2, ... z = 26, and an encoded message,
 * count the number of ways it can be decoded.
 *
 * For example, the message '111' would give 3,
 * since it could be decoded as 'aaa', 'ka', and 'ak'.
 *
 * You can assume that the messages are decodable.
 * For example, '001' is not allowed.
 *
 * */

#include <cassert>
#include <vector>

using namespace std;

int count_decode_ways(vector<int> msg)
{
	// Leaf node hit, count it
	if (msg.empty()) return 1;

	/*
	 * Descend tree accumulating leaf count
	 *		(x, y)
	 *	  /      \  < Only if x*10 + y < 26
	 *	(x)      ()
	 *	|
	 * ()
	 *
	 * */
	int r = 0;

	r += count_decode_ways(vector<int>(msg.begin() + 1, msg.end()));

	if (msg.size() > 1 && msg[0] * 10 + msg[1] <= 26)
		r += count_decode_ways(vector<int>(msg.begin() + 2, msg.end()));

	return r;
}

int main()
{
	/*
	 * 				(1, 1, 1)
	 * 				/		\
	 * 			(1, 1)	   (1)
	 * 			/    \       \
	 * 		 (1)	  ()     ()
	 *       /		  ^	     ^
	 *     ()
	 *     ^
	 * */
	 assert(count_decode_ways((vector<int>){1,1,1}) == 3);
	/*
	 * 				(2, 2, 7)
	 * 				/
	 * 			(2, 7)
	 * 			/    \
	 * 		 (7)	  ()
	 *       /		  ^
	 *     ()
	 *     ^
	 * */
	assert(count_decode_ways((vector<int>){2,2,7}) == 2);
	/*
	 * 				(2, 7, 2)
	 * 				/
	 * 			(7, 2)
	 * 			/
	 * 		 (2)
	 *       /
	 *     ()
	 *     ^
	 * */
	assert(count_decode_ways((vector<int>){2,7,2}) == 1);
	/*
	 * 				(2, 7, 2, 9, 1)
	 * 				/
	 * 		(7, 2, 9, 1)
	 * 			/
	 * 	   (2, 9, 1)
	 *       /
	 *   (9, 1)
	 *    (1)
	 *    ()
	 *    ^
	 * */
	assert(count_decode_ways((vector<int>){2,7,2,9,1}) == 1);
	/*
	 * 				(2, 7, 2, 6, 1)
	 * 				/
	 * 		(7, 2, 9, 1)
	 * 			/
	 * 	   (2, 6, 1)
	 *       /  \
	 *   (6, 1) (1)
	 *    (1)   ()
	 *    ()    ^
	 *    ^
	 * */
	assert(count_decode_ways((vector<int>){2,7,2,6,1}) == 2);
	return 0;
}
