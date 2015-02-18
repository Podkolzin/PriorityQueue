/**
\file   binomial_heap.h
\brief  ���������� ������� � ������������ � ������� ������������ ����.
\author ��������� �����
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
	\brief �����������
	*/
	CBinomialPriorityQueue();
	/**
	\brief ����������
	*/
	~CBinomialPriorityQueue();
	/**
	\brief ����������� �����������
	\param pq [in] - �������
	*/
	CBinomialPriorityQueue(const MyPQ& pq);
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
	\brief ��������� �������� ��������, �������� ��������� ���������. ��� ������� �� ���������
	\retval Type - ������� � ��������� �����������
	*/
	Type top() const;
private:
	// ���� ������
	template<class Type>
	struct SNode
	{
		int m_degree;			// ����� �����
		Type m_key;				// ���� �������
		SNode* m_pChild;		// ����� ����� �� �����
		SNode* m_pParent;		// ��������
		SNode* m_pSibling;		// ������ �����
	};

	SNode<Type>* m_pRoot;		// ������ ������
	Comparator m_comp;			// ����������

	/**
	\brief �������� ������� � ����������� ������
	*/
	void binomialHeapExtractMin()
	{
		int max = numeric_limits<int>::min();

 		SNode<Type>* temp = 0;
		SNode<Type>* tempNext = 0;
		SNode<Type>* cur = m_pRoot;
		SNode<Type>* curNext = 0;
		SNode<Type>* newNode = 0;

		// ����� ������������ �����
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

		// �������� �������
		if (tempNext == 0)
			m_pRoot = temp->m_pSibling;
		else
			tempNext->m_pSibling = temp->m_pSibling;

		// ��������� ������� � ������ �����
		cur = temp->m_pChild;
		newNode = temp->m_pChild;
		while (cur != 0)
		{
			cur->m_pParent = 0;
			cur = cur->m_pSibling;
		}

		// ����������� ���
		m_pRoot = binomialHeapUnion(m_pRoot, newNode);
	}

	/**
	\brief �������� ����� �������
	\retval SNode<Type>* - ����� �������
	*/
	SNode<Type>* makeBinomialHeap()
	{
		SNode<Type>* newNode = new SNode<Type>;
		return newNode;
	}

	/**
	\brief ���������� ���� �������� ��������� �������
	\param node1 [in/out] - ������ ������
	\param node2 [in/out] - ������ ������
	*/
	void binomialLink(SNode<Type>* node1, SNode<Type>* node2)
	{
		node1->m_pParent = node2;
		node1->m_pSibling = node2->m_pChild;
		node2->m_pChild = node1;
		++node2->m_degree;
	}
	
	/**
	\brief ����������� ���� ���
	\param node1 [in/out] - ������ ������
	\param node2 [in/out] - ������ ������
	\retval SNode<Type>* - ����� ����
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
	\brief ������� �������� ������� ���� ��������
	\param node1 [in/out] - ������ ������
	\param node2 [in/out] - ������ ������
	\retval SNode<Type>* - ����� ����
	*/
	SNode<Type>* binomialHeapMerge(SNode<Type>* node1, SNode<Type>* node2)
	{
		SNode<Type>* newNode = makeBinomialHeap();

		SNode<Type>* temp1 = node1;
		SNode<Type>* temp2 = node2;

		SNode<Type>* temp = new SNode<Type>;

		// ����� ������ � ������� ����������� ����� 
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
	\brief ������� �������
	\param key [in] - ���� �������
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
	\brief ����� ����������� �������
	\param key [in] - ���� �������
	\retval SNode<Type>* - �������, ���������� ����������� ����
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
	\brief �������� �������
	*/
	void binomialHeapDelete()
	{
		binomialHeapExtractMin();
	}

	/**
	\brief ����������� ��������� �� ������ ������ � ������. ����� ������ � �������.
	\param node1 [in/out] - ������ ������������ ������
	\param node2 [in/out] - ������ ������������ ������
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
		// ������� ������
		while (!empty())
			binomialHeapDelete();

		m_pRoot = new SNode<Type>;
		SNode<Type>* temp1 = m_pRoot;
		SNode<Type>* temp2 = pq.m_pRoot;
		
		// �������� ��������
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