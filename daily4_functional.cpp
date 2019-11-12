/*
 * This is your coding interview problem for today.
 * This problem was asked by Jane Street.
 *
 * cons(a, b) constructs a pair, and car(pair) and cdr(pair) returns the first and last element of that pair. For example, car(cons(3, 4)) returns 3, and cdr(cons(3, 4)) returns 4.
 *
 * Given this implementation of cons:
 *
 * def cons(a, b):
 *     def pair(f):
 *         return f(a, b)
 *     return pair
 * Implement car and cdr.
 *
 * We will be sending the so
 * */
#include <iostream>
#include <functional>

using namespace std;

function<int(function<int(int, int)>)> cons(int a, int b)
{
	return [a, b](
		const function<int(int, int)>& fun
	){
		return fun(a, b);
	};
}

int car(const function<int(function<int(int, int)>)>& pair)
{
	return pair([&](int a, int _){
		return a;
	});
}
int cdr(const function<int(function<int(int, int)>)>& pair)
{
	return pair([&](int _, int b){
		return b;
	});
}

int main()
{
	cout << "car(cons(1, 2)): " << car(cons(-12, 22)) << "\n";
	cout << "cdr(cons(1, 2)): " << cdr(cons(-12, 22)) << "\n";
	return 0;
}
