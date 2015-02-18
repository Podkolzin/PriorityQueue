/**
\file   timer.h
\brief  Шаблон, вычисляющий время работы программы.
\author Подколзин Павел
\date   30.04.2014
*/


#ifndef TIMER_H
#define TIMER_H

#include <ctime>

template<class PQueue>
double timer(PQueue &priorityqueue)
{
	clock_t start;
	clock_t finish;
	double timer(0.0);
	const int i(0);

	int arr[10] = { 40, 310, 8, 400000, 5, 10, 40, 100, 750, 0 };

	// Начальное время
	start = clock();

	// Добавление и удаление элементов из стека
	for (int j(0); j < 5000; ++j)
	{
		if ((j % 2) == 0)
		{
			priorityqueue.push(j);
		}
		else
		{
			priorityqueue.pop();
		}
	}
	for (int j(0); j < 10000; ++j)
	{
		priorityqueue.push(j);
	}
	for (int j(0); j < 9500; ++j)
	{
		priorityqueue.pop();
	}
	for (int j(0); j < 5000; ++j)
	{
		if ((j % 2) == 0)
		{
			priorityqueue.push(j);
		}
		else
		{
			priorityqueue.pop();
		}
	}
	for (int j(0); j < 500; ++j)
	{
		priorityqueue.pop();
	}

	for (int i(0); i < 10; ++i)
	{
		priorityqueue.push(arr[i]);
	}

	while (!priorityqueue.empty())
	{
		cout << priorityqueue.top() << '\t';
		priorityqueue.pop();
	}

	cout << endl;

	// Конечное время
	finish = clock();

	// Вычисление времени работы программы
	timer = static_cast<double> (finish - start) / CLOCKS_PER_SEC;

	return timer;
}

#endif