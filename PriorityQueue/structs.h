/**
\file   structs.h
\brief  �������� ��� ����������� �������.
\author ��������� �����
\date   30.04.2014
*/


#ifndef STRUCTS_H
#define STRUCTS_H

// �������, ������������ ��������� ����� ���������.
// ��������� "������ ���" �������� (operator<) �� ������ ����� ����������.
template<class Type = void>
struct SLess
{
	bool operator()(const Type& left, const Type& right) const
	{
		return (left < right);
	}
};

// �������, ������������ ��������� ����� ���������.
// ��������� "������ ���" �������� (operator>) �� ������ ����� ����������.
template<class Type = void>
struct SGreater
{
	bool operator()(const Type& left, const Type& right) const
	{
		return (left > right);
	}
};

#endif // STRUCTS_H