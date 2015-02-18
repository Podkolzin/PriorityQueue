/**
\file   Main.cpp
\brief  Очередь с приоритетами.
\author Подколзин Павел
\date   30.04.2014
*/

#include "binary_heap.h"
#include "binomial_heap.h"
#include "timer.h"
#include "structs.h"

#include <iostream>
#include <queue>


using namespace std;

int main()
{
	CBinaryPriorityQueue<int> binary(10);
	CBinomialPriorityQueue<int> binomial;
	priority_queue<int> prio;

	cout << "Process of the programm: to add and to remove 5000 items, "
		"to add 10000 items, to remove 9500 items, to add and to remove 5000 items, "
		"to remove 500. Top 10 elements. Max-Heap." << endl << endl;
	cout << "The time of working:" << endl;
	cout << "The pqueue on my binary heap = " << timer(binary) << " sec." << endl << endl << endl;
	cout << "The pqueue on my binomial heap = " << timer(binomial) << " sec." << endl << endl << endl;
	cout << "The pqueue on a STL priority queue = " << timer(prio) << " sec." << endl << endl << endl;

	return 0;
}