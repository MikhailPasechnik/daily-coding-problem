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
#include <string>

using namespace std;

int _count_decode_ways(string msg)
{
	// Leaf node hit, count it
	if (msg.empty()) return 1;

	int r = 0;
	int x, y;

	// Check that meg can be decoded
	// first in range [1..9]
	if ((x = msg[0] - 48) < 1 || x > 9)
		return 0;
	// second if exists and in range [1..9]
	if (msg.size() > 1 && ((y = msg[1] - 48) < 1  || y > 9))
		return 0;

	/*
	 * Descend tree accumulating leaf count
	 *		(x, y)
	 *	  /      \  < Only if x*10 + y < 26
	 *	(x)      ()
	 *	|
	 * ()
	 * */
	r += _count_decode_ways(string(msg.begin() + 1, msg.end()));
	if (msg.size() > 1)
	{
		if (x * 10 + y <= 26)
			r += _count_decode_ways(string(msg.begin() + 2, msg.end()));
	}
	return r;
}

int count_decode_ways(const string& msg)
{
	return msg.empty() ? 0: _count_decode_ways(msg);
}

int main()
{
	// Test messages is not decodable
	assert(count_decode_ways("") == 0);
	assert(count_decode_ways("0") == 0);
	assert(count_decode_ways("6x") == 0);
	assert(count_decode_ways(" 2") == 0);

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
	 assert(count_decode_ways("111") == 3);

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
	assert(count_decode_ways("227") == 2);

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
	assert(count_decode_ways("272") == 1);

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
	assert(count_decode_ways("27291") == 1);

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
	assert(count_decode_ways("27261") == 2);

	return 0;
}
