/**
\file   structs.h
\brief  Функторы для определения порядка.
\author Подколзин Павел
\date   30.04.2014
*/


#ifndef STRUCTS_H
#define STRUCTS_H

// Функтор, определяющий отношение меджу объектами.
// Выполняет "меньше чем" операции (operator<) на основе своих аргументов.
template<class Type = void>
struct SLess
{
	bool operator()(const Type& left, const Type& right) const
	{
		return (left < right);
	}
};

// Функтор, определяющий отношение меджу объектами.
// Выполняет "больше чем" операции (operator>) на основе своих аргументов.
template<class Type = void>
struct SGreater
{
	bool operator()(const Type& left, const Type& right) const
	{
		return (left > right);
	}
};

#endif // STRUCTS_H