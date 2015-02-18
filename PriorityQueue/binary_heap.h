/**
\file   binary_heap.h
\brief  Реализация очереди с приоритетами с помощью бинарной кучи.
\author Подколзин Павел
\date   24.04.2014
*/

#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <cassert>

typedef enum{ MAX, MIN } TYPEHEAP;

template<class Type, class Comparator = SLess<Type> >
class CBinaryPriorityQueue
{
public:
	typedef CBinaryPriorityQueue<Type, Comparator> MyPQ;
	/**
	\brief Конструктор
	\param length [in] - длина исходного массива
	*/
	CBinaryPriorityQueue(const int length);
	/**
	\brief Деструктор
	*/
	~CBinaryPriorityQueue();
	/**
	\brief Конструктор копирования
	\param pq [in] - очередь
	*/
	CBinaryPriorityQueue(const MyPQ& pq);
	/**
	\brief Оператор присваивания
	\param pq [in] - очередь
	\retval this - указатель на текущий экземпляр
	*/
	MyPQ& operator=(const MyPQ& pq);
	/**
	\brief Проверка очереди на пустоту
	\retval bool - true для пустой очереди, иначе false
	*/
	bool empty() const;
	/**
	\brief Удаление первого элемента очереди
	*/
	void pop();
	/**
    \brief Вставка элемента в очередь с приоритетами
    \param val [in] - значение вставляемого элемента
    */
	void push(const Type& val);
	/**
	\brief Получение текущего количества элементов, находящихся в очереди
	\retval int - размер кучи
	*/
	int size() const;
	/**
	\brief Обмен содержимым между очередьми
	\param pq [in/out] - очередь
	*/
	void swapPriorityQueues(MyPQ& pq);
	/**
	\brief Получение значения элемента, имеющего наивысший приоритет. Сам элемент не удаляется
	\retval Type - элемент с наивысший приоритетом
	*/
	Type top() const;
private:
	int m_heapSize;		// Размер кучи
	int m_length;		// Длина массива
	Type* m_pArray;		// Исходный массив
	// Компаратор. По умолчанию max-heap (значение в любой вершине не меньше, чем значения её потомков.)
	Comparator m_comp;
	/**
	\brief Проверка главного свойства кучи
	*/
	void heapify(const int i);
	/**
	\brief Изменение длины массива
	\param newSize [in] - новая длина массива
	*/
	void resize(const int newSize);

};



template<class Type, class Comparator>
CBinaryPriorityQueue<Type, Comparator>::CBinaryPriorityQueue(const int length)
: m_heapSize(-1)
, m_length(length)
, m_comp()
{
	assert(m_length > 0);

	m_pArray = new Type[m_length];
}



template<class Type, class Comparator>
CBinaryPriorityQueue<Type, Comparator>::~CBinaryPriorityQueue()
{
	// Освобождение памяти
	delete[] m_pArray;
}



template<class Type, class Comparator>
CBinaryPriorityQueue<Type, Comparator>& CBinaryPriorityQueue<Type, Comparator>
::operator=(const CBinaryPriorityQueue<Type, Comparator>& pq)
{
	if (this != &pq)
	{
		delete[] m_pArray;
		m_heapSize = pq.m_heapSize;
		m_length = pq.m_length;
		m_comp = pq.m_comp;
		m_pArray = new Type[m_length];

		for (auto i(0); i < m_heapSize; ++i)
			m_pArray[i] = pq.m_pArray[i];
	}

	return *this;
}



template<class Type, class Comparator>
CBinaryPriorityQueue<Type, Comparator>::CBinaryPriorityQueue(const CBinaryPriorityQueue<Type, Comparator>& pq)
: m_heapSize(pq.m_heapSize)
, m_length(pq.m_length)
, m_comp(pq.m_comp)
{
	m_pArray = new Type[m_length];

	for (auto i(0); i < m_heapSize; ++i)
		m_pArray[i] = pq.m_pArray[i];
}



template<class Type, class Comparator>
bool CBinaryPriorityQueue<Type, Comparator>::empty() const
{
	//Если размер кучи == -1 - true, иначе false
	return (m_heapSize == -1);
}



template<class Type, class Comparator>
void CBinaryPriorityQueue<Type, Comparator>::pop()
{
	assert(!empty());

	m_pArray[0] = m_pArray[m_heapSize];
	--m_heapSize;
	heapify(0);
}



template<class Type, class Comparator>
void CBinaryPriorityQueue<Type, Comparator>::push(const Type& val)
{
	//Если размер кучи равен длине массива, то увеличиваем размер массива вдвое
	if (m_heapSize + 1 == m_length)
		resize(m_length * 2);

	++m_heapSize;
	int i = m_heapSize;

	// Добавление элемента в конец кучи с его последующим "подъемом" до нужного места
	while ((i > 0) && m_comp(m_pArray[(i - 1) / 2], val))
	{
		m_pArray[i] = m_pArray[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	m_pArray[i] = val;
}



template<class Type, class Comparator>
int CBinaryPriorityQueue<Type, Comparator>::size() const
{
	return (m_heapSize + 1);
}



template<class Type, class Comparator>
void CBinaryPriorityQueue<Type, Comparator>::swapPriorityQueues(CBinaryPriorityQueue<Type, Comparator>& pq)
{
	CBinaryPriorityQueue<Type> temp(*this);
	*this = pq;
	pq = temp;
}



template<class Type, class Comparator>
Type CBinaryPriorityQueue<Type, Comparator>::top() const
{
	assert(!empty());

	// Возвращение первого элемента очереди
	return m_pArray[0];
}

//Вспомогательные функции----------------------------------------------------

template<class Type, class Comparator>
void CBinaryPriorityQueue<Type, Comparator>::heapify(const int i)
{
	int change;
	int left(2 * i + 1);
	int right(2 * i + 2);
	
	//Определяем индекс наибольшего (наименьшего) элемента
	if ((left <= m_heapSize) && m_comp(m_pArray[i], m_pArray[left]))
		change = left;
	else
		change = i;
	if ((right <= m_heapSize) && m_comp(m_pArray[change], m_pArray[right]))
		change = right;
	
	//Если change == i, то элемент уже "погрузился" до нужного места
	if (change != i)
	{
		swap(m_pArray[i], m_pArray[change]);
		heapify(change);
	}
}



template<class Type, class Comparator>
void CBinaryPriorityQueue<Type, Comparator>::resize(const int newSize)
{
	if (newSize < m_length)
	{
		m_length = newSize;
	}
	else
	{
		Type* tempArr = new Type[newSize];	// Вспомогательный массив
		
		// Заполняем вспомогательный массив исходными значениями
		for (auto i(0); i < m_length; ++i)
		{
			tempArr[i] = m_pArray[i];
		}

		// Заполняем значениями по умолчанию пустую часть вспомогательного массива
		for (auto i(m_length); i < newSize; ++i)
		{
			tempArr[i] = Type();
		}

		delete[] m_pArray;
		m_pArray = tempArr;
		m_length = newSize;
	}
}

#endif //BINARY_HEAP_H