#pragma once

#define CAPACITY 17 //������������ ���������� ��������� �������

struct field_t //���� � �������
{
   int quantity;
   string name, key;
};

struct table_t //���� �������
{
   int size = 0;
   field_t fields[CAPACITY];
};