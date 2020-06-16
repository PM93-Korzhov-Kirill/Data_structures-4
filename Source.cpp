#define CAPACITY 17 //������������ ���������� ��������� �������

#include <iostream>
#include <conio.h>
#include <locale.h>
#include <fstream>

using namespace std;

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

void insertFieldAtTable(table_t &table, field_t field); //��������� ���� � �������, �������� �������
int getPosForFieldInsert(table_t table, field_t field); //���������� ������� � �������, � ������� ���� ����� ��������
void shiftTableFieldsFromPos(table_t &table, int pos); //������� ���� � �������, ������� � ���������� ������, ���������� ����� ��� ������� ������
void printTable(table_t table); //������������� ������� � �������
void printField(field_t field); //������������� ���� ������� � �������
int getPosField(table_t table, string key); //����� ������� ���� � ������� �� �����. ����� -1, ���� ������ �� �����
void deleteField(table_t &table, string key); //������� ���� � ������� �� �����

int main()
{
   setlocale(LC_CTYPE, "Russian");

   ifstream in("work.txt");
   table_t table;
   field_t field;

   while (in >> field.key >> field.name >> field.quantity) //���� �� ����� ����� ������������ ��������� ������ � �������
      insertFieldAtTable(table, field);

   printTable(table); //������������ ����������� �������
   cout << "����� ���� �� ����� ������ �� ������ �������?" << endl;
   int field_num_for_delete = 0;
   cin >> field_num_for_delete;
   cout << "���� ���� ����� ����:" << table.fields[field_num_for_delete - 1].key << endl; //�������, ��� �� ������� �� �����
   deleteField(table, table.fields[field_num_for_delete].key);
   cout << "����� �������:" << endl;
   printTable(table); // ������������� ����� �������

   _getch();
   return 0;
}

void insertFieldAtTable(table_t &table, field_t field)
{
   int insert_pos = getPosForFieldInsert(table, field);
   if (field.key.compare(table.fields[insert_pos].key) == 0) //��� ���������� �������� quantity
      table.fields[insert_pos].quantity += field.quantity;
   else //���� ���������� ���, �� ��������� ����� � ������� ��������� � ������� ������
   {
      shiftTableFieldsFromPos(table, insert_pos);
      table.fields[insert_pos] = field;
   }
}

int getPosForFieldInsert(table_t table, field_t field) //�������� ����� ����� � ������� ��� �������
{
   int left_search_edge = 0; // ����� ���� ��������� ������ == 0
   int right_search_edge = table.size; // ������ ���� == ������ ���� ������� + 1, ��� ��� �������� ������ ����� � � ��� ����� � � ����� ����� �������
   while (left_search_edge < right_search_edge) //���� ���� �� ��������
   {
      int cmp_pos = (left_search_edge + right_search_edge) / 2; //���������� � ���������(���������� � ������ ����)
      if (field.key.compare(table.fields[cmp_pos].key) <= 0) //���� ������ ��� �����, �� ������� ������ ���� �� ��������
         right_search_edge = cmp_pos;
      else //���� ������, �� ������� ����� ���� �� �������� �� 1 �������, ����� �������� ������������. ����� ��� �������, ��� ��� ������� "�����" ���� ����
         left_search_edge = cmp_pos + 1;
   }
   return left_search_edge; //������� ����� ���� ����������
}

void shiftTableFieldsFromPos(table_t &table, int insert_pos)
{
   table.size++;
   for(int i = table.size - 1; i >= insert_pos; i--)
      table.fields[i + 1] = table.fields[i];
}

void printTable(table_t table)
{
   for (int i = 0; i < table.size; i++)
      printField(table.fields[i]);
}

void printField(field_t field)
{
   cout << field.key << " " << field.name << " " << field.quantity << endl;
}

int getPosField(table_t table, string key) //�������� ����� ���� � �������
{
   int left_search_edge = 0; // ����� ���� ��������� ������ == 0
   int right_search_edge = table.size - 1; // ������ ���� == ������ ���� �������
   while (left_search_edge < right_search_edge) //���� ���� �� ��������
   {
      int cmp_pos = (left_search_edge + right_search_edge) / 2; //���������� � ���������(���������� � ������ ����)
      if (key.compare(table.fields[cmp_pos].key) <= 0) //���� ������ ��� �����, �� ������� ������ ���� �� ��������
         right_search_edge = cmp_pos;
      else //���� ������, �� ������� ����� ���� �� �������� �� 1 �������, ����� �������� ������������. ����� ��� �������, ��� ��� ������� "�����" ���� ����
         left_search_edge = cmp_pos + 1;
   }
   if (key.compare(table.fields[left_search_edge].key) != 0)
      return -1;//���� ����� �� �����, �� ����� -1
   return left_search_edge; //���� �� �����, �� �� ����� ����� ���� ����������
}
void deleteField(table_t &table, string key)
{
   int field_pos = getPosField(table, key);
   if (field_pos >= 0) //���� ������ ����� � ����� �������, �� �������
   {
      for (int i = field_pos; i < table.size; i++)
         table.fields[i] = table.fields[i + 1];
      table.size--;
   }
}