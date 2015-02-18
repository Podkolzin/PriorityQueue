/**
\file   binomial_heap.h
\brief  Реализация очереди с приоритетами с помощью биномиальной кучи.
\author Подколзин Павел
\date   30.04.2014
*/

#ifndef BINO_HEAP_H
#define BINO_HEAP_H

#include <limits>

template<class Type, class Comparator = SLess<Type> >
class CBinomialPriorityQueue
{
public:
	typedef CBinomialPriorityQueue<Type, Comparator> MyPQ;
	/**
	\brief Конструктор
	*/
	CBinomialPriorityQueue();
	/**
	\brief Деструктор
	*/
	~CBinomialPriorityQueue();
	/**
	\brief Конструктор копирования
	\param pq [in] - очередь
	*/
	CBinomialPriorityQueue(const MyPQ& pq);
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
	\brief Получение значения элемента, имеющего наивысший приоритет. Сам элемент не удаляется
	\retval Type - элемент с наивысший приоритетом
	*/
	Type top() const;
private:
	// Узел дерева
	template<class Type>
	struct SNode
	{
		int m_degree;			// Число детей
		Type m_key;				// Ключ вершины
		SNode* m_pChild;		// Самый левый из детей
		SNode* m_pParent;		// Родитель
		SNode* m_pSibling;		// Правый сосед
	};

	SNode<Type>* m_pRoot;		// Корень дерева
	Comparator m_comp;			// Компаратор

	/**
	\brief Удаление вершины с минимальным ключом
	*/
	void binomialHeapExtractMin()
	{
		int max = numeric_limits<int>::min();

 		SNode<Type>* temp = 0;
		SNode<Type>* tempNext = 0;
		SNode<Type>* cur = m_pRoot;
		SNode<Type>* curNext = 0;
		SNode<Type>* newNode = 0;

		// Поиск минимального ключа
		while (cur != 0)
		{
			if (cur->m_key > max)
			{
				max = cur->m_key;
				temp = cur;
				tempNext = curNext;
			}
			curNext = cur;
			cur = cur->m_pSibling;
		}

		// Удаление вершины
		if (tempNext == 0)
			m_pRoot = temp->m_pSibling;
		else
			tempNext->m_pSibling = temp->m_pSibling;

		// Обращение порядка в списке детей
		cur = temp->m_pChild;
		newNode = temp->m_pChild;
		while (cur != 0)
		{
			cur->m_pParent = 0;
			cur = cur->m_pSibling;
		}

		// Объединение куч
		m_pRoot = binomialHeapUnion(m_pRoot, newNode);
	}

	/**
	\brief Создание новой вершины
	\retval SNode<Type>* - новая вершина
	*/
	SNode<Type>* makeBinomialHeap()
	{
		SNode<Type>* newNode = new SNode<Type>;
		return newNode;
	}

	/**
	\brief Соединение двух деревьев одинакого размера
	\param node1 [in/out] - первое дерево
	\param node2 [in/out] - второе дерево
	*/
	void binomialLink(SNode<Type>* node1, SNode<Type>* node2)
	{
		node1->m_pParent = node2;
		node1->m_pSibling = node2->m_pChild;
		node2->m_pChild = node1;
		++node2->m_degree;
	}
	
	/**
	\brief Объединение двух куч
	\param node1 [in/out] - первое дерево
	\param node2 [in/out] - второе дерево
	\retval SNode<Type>* - новая куча
	*/
	SNode<Type>* binomialHeapUnion(SNode<Type>* node1, SNode<Type>* node2)
	{
		SNode<Type>* newNode = makeBinomialHeap();
		if (node1 == 0)
			newNode = node2;
		else if (node2 == 0)
			newNode = node1;
		else
			newNode = binomialHeapMerge(node1, node2);
		if (newNode == 0)
			return newNode;

		SNode<Type>* tempPrev = 0;
		SNode<Type>* temp = newNode;
		SNode<Type>* tempNext = temp->m_pSibling;


		while (tempNext != 0)
		{
			if ((temp->m_degree != tempNext->m_degree) ||
				((tempNext->m_pSibling != 0) && (tempNext->m_pSibling->m_degree == temp->m_degree)))
			{
				tempPrev = temp;
				temp = tempNext;
			}
			else
			{
				if (temp->m_key >= tempNext->m_key)
				{
					temp->m_pSibling = tempNext->m_pSibling;
					binomialLink(tempNext, temp);
				}
				else
				{
					if (tempPrev == 0)
						newNode = tempNext;
					else
					{
						tempPrev->m_pSibling = tempNext;
					}
					binomialLink(temp, tempNext);
					temp = tempNext;
				}
			}
			tempNext = temp->m_pSibling;
		}

		return newNode;
	}

	/**
	\brief Слияние корневых списков двух деревьев
	\param node1 [in/out] - первое дерево
	\param node2 [in/out] - второе дерево
	\retval SNode<Type>* - новая куча
	*/
	SNode<Type>* binomialHeapMerge(SNode<Type>* node1, SNode<Type>* node2)
	{
		SNode<Type>* newNode = makeBinomialHeap();

		SNode<Type>* temp1 = node1;
		SNode<Type>* temp2 = node2;

		SNode<Type>* temp = new SNode<Type>;

		// Выбор дерево с меньшим количеством детей 
		if (temp1->m_degree > temp2->m_degree)
			newNode = temp2;
		else
			newNode = temp1;
		if (newNode == 0)
			return newNode;
		if (newNode == temp2)
			temp2 = temp1;
		temp1 = newNode;


		while (temp2 != 0)
		{
			if (temp1->m_pSibling == 0)
			{
				temp1->m_pSibling = temp2;
				return newNode;
			}
			else if (temp1->m_pSibling->m_degree < temp2->m_degree)
				temp1 = temp1->m_pSibling;
			else
			{
				temp = temp2->m_pSibling;
				temp2->m_pSibling = temp1->m_pSibling;
				temp1->m_pSibling = temp2;
				temp1 = temp1->m_pSibling;
				temp2 = temp;
			}
		}

		return newNode;
	}

	/**
	\brief Вставка вершины
	\param key [in] - ключ вершины
	*/
	void binomialHeapInsert(const Type& key)
	{
		SNode<Type>* newNode = makeBinomialHeap();
		newNode->m_degree = 0;
		newNode->m_key = key;
		newNode->m_pChild = 0;
		newNode->m_pParent = 0;
		newNode->m_pSibling = 0;
		m_pRoot = binomialHeapUnion(m_pRoot, newNode);
	}

	/**
	\brief Поиск минимальной вершины
	\param key [in] - ключ вершины
	\retval SNode<Type>* - вершина, содержащая минимальный ключ
	*/
	SNode<Type>* binomialHeapMinimum() const
	{
		SNode<Type>* newNode = 0;
		SNode<Type>* temp = m_pRoot;
		int max = numeric_limits<int>::min();

		while (temp != 0)
		{
			if (temp->m_key > max)
			{
				max = temp->m_key;
				newNode = temp;
			}
			temp = temp->m_pSibling;
		}

		return newNode;
	}

	/**
	\brief Удаление вершины
	*/
	void binomialHeapDelete()
	{
		binomialHeapExtractMin();
	}

	/**
	\brief Копирование элементов из одного дерева в другое. Обход дерева в глубину.
	\param node1 [in/out] - первое биномиальное дерево
	\param node2 [in/out] - второе биномиальное дерево
	*/
	void navigation(SNode<Type>* node1, SNode<Type>* node2)
	{
		if (node1 != 0)
		{
			node2->m_degree = node1->m_degree;
			node2->m_key = node1->m_key;
			node2->m_pChild = node1->m_pChild;
			node2->m_pParent = node1->m_pParent;
			node2->m_pSibling = node1->m_pSibling;
			navigation(node1->m_pChild, node2->m_pChild);
			navigation(node1->m_pSibling, node2->m_pSibling);
		}
	}
};



template<class Type, class Comparator>
CBinomialPriorityQueue<Type, Comparator>::CBinomialPriorityQueue()
: m_pRoot(0)
, m_comp()
{}



template<class Type, class Comparator>
CBinomialPriorityQueue<Type, Comparator>::~CBinomialPriorityQueue()
{
	while (!empty())
		binomialHeapDelete();
}



template<class Type, class Comparator>
CBinomialPriorityQueue<Type, Comparator>::CBinomialPriorityQueue(const CBinomialPriorityQueue<Type, Comparator>& pq)
{
	m_pRoot = new SNode<Type>;
	navigation(pq.m_pRoot, m_pRoot);
	m_comp = pq.m_comp;
}



template<class Type, class Comparator>
CBinomialPriorityQueue<Type, Comparator>& CBinomialPriorityQueue<Type, Comparator>
::operator=(const CBinomialPriorityQueue<Type, Comparator>& pq)
{
	if (this != &pq)
	{
		// Удаляем дерево
		while (!empty())
			binomialHeapDelete();

		m_pRoot = new SNode<Type>;
		SNode<Type>* temp1 = m_pRoot;
		SNode<Type>* temp2 = pq.m_pRoot;
		
		// Копируем элементы
		navigation(temp2, temp1);
		m_comp = pq.m_comp;
	}

	return *this;
}



template<class Type, class Comparator>
bool CBinomialPriorityQueue<Type, Comparator>::empty() const
{
	return (m_pRoot == 0);
}



template<class Type, class Comparator>
void CBinomialPriorityQueue<Type, Comparator>::pop()
{
	assert(!empty());

	binomialHeapDelete();
}



template<class Type, class Comparator>
void CBinomialPriorityQueue<Type, Comparator>::push(const Type& val)
{
	binomialHeapInsert(val);
}



template<class Type, class Comparator>
int CBinomialPriorityQueue<Type, Comparator>::size() const
{
	int res = 0;
	int cur = 0;
	SNode<Type>* temp = m_pRoot;

	while (temp != 0)
	{
		cur = 0;

		++cur;
		for (auto i(0); i < temp->m_degree; ++i)
			cur *= 2;

		res += cur;
		temp = temp->m_pSibling;
	}

	return res;
}



template<class Type, class Comparator>
Type CBinomialPriorityQueue<Type, Comparator>::top() const
{
	assert(!empty());

	return binomialHeapMinimum()->m_key;
}

#endif // BINO_HEAP_H