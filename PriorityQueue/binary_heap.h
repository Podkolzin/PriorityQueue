/**
\file   binary_heap.h
\brief  ���������� ������� � ������������ � ������� �������� ����.
\author ��������� �����
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
	\brief �����������
	\param length [in] - ����� ��������� �������
	*/
	CBinaryPriorityQueue(const int length);
	/**
	\brief ����������
	*/
	~CBinaryPriorityQueue();
	/**
	\brief ����������� �����������
	\param pq [in] - �������
	*/
	CBinaryPriorityQueue(const MyPQ& pq);
	/**
	\brief �������� ������������
	\param pq [in] - �������
	\retval this - ��������� �� ������� ���������
	*/
	MyPQ& operator=(const MyPQ& pq);
	/**
	\brief �������� ������� �� �������
	\retval bool - true ��� ������ �������, ����� false
	*/
	bool empty() const;
	/**
	\brief �������� ������� �������� �������
	*/
	void pop();
	/**
    \brief ������� �������� � ������� � ������������
    \param val [in] - �������� ������������ ��������
    */
	void push(const Type& val);
	/**
	\brief ��������� �������� ���������� ���������, ����������� � �������
	\retval int - ������ ����
	*/
	int size() const;
	/**
	\brief ����� ���������� ����� ���������
	\param pq [in/out] - �������
	*/
	void swapPriorityQueues(MyPQ& pq);
	/**
	\brief ��������� �������� ��������, �������� ��������� ���������. ��� ������� �� ���������
	\retval Type - ������� � ��������� �����������
	*/
	Type top() const;
private:
	int m_heapSize;		// ������ ����
	int m_length;		// ����� �������
	Type* m_pArray;		// �������� ������
	// ����������. �� ��������� max-heap (�������� � ����� ������� �� ������, ��� �������� � ��������.)
	Comparator m_comp;
	/**
	\brief �������� �������� �������� ����
	*/
	void heapify(const int i);
	/**
	\brief ��������� ����� �������
	\param newSize [in] - ����� ����� �������
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
	// ������������ ������
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
	//���� ������ ���� == -1 - true, ����� false
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
	//���� ������ ���� ����� ����� �������, �� ����������� ������ ������� �����
	if (m_heapSize + 1 == m_length)
		resize(m_length * 2);

	++m_heapSize;
	int i = m_heapSize;

	// ���������� �������� � ����� ���� � ��� ����������� "��������" �� ������� �����
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

	// ����������� ������� �������� �������
	return m_pArray[0];
}

//��������������� �������----------------------------------------------------

template<class Type, class Comparator>
void CBinaryPriorityQueue<Type, Comparator>::heapify(const int i)
{
	int change;
	int left(2 * i + 1);
	int right(2 * i + 2);
	
	//���������� ������ ����������� (�����������) ��������
	if ((left <= m_heapSize) && m_comp(m_pArray[i], m_pArray[left]))
		change = left;
	else
		change = i;
	if ((right <= m_heapSize) && m_comp(m_pArray[change], m_pArray[right]))
		change = right;
	
	//���� change == i, �� ������� ��� "����������" �� ������� �����
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
		Type* tempArr = new Type[newSize];	// ��������������� ������
		
		// ��������� ��������������� ������ ��������� ����������
		for (auto i(0); i < m_length; ++i)
		{
			tempArr[i] = m_pArray[i];
		}

		// ��������� ���������� �� ��������� ������ ����� ���������������� �������
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