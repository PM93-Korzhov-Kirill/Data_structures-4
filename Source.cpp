#define CAPACITY 17 //максимальное количество элементов таблицы

#include <iostream>
#include <conio.h>
#include <locale.h>
#include <fstream>

using namespace std;

struct field_t //поле в таблице
{
   int quantity;
   string name, key;
};

struct table_t //сама таблица
{
   int size = 0;
   field_t fields[CAPACITY];
};

void insertFieldAtTable(table_t &table, field_t field); //вставляет поле в таблицу, сохраняя порядок
int getPosForFieldInsert(table_t table, field_t field); //определяет позицию в таблице, в которую поле нужно вставить
void shiftTableFieldsFromPos(table_t &table, int pos); //смещает поля в таблице, начиная с некоторого номера, освобождая место для вставки записи
void printTable(table_t table); //распечатывает таблицу в консоль
void printField(field_t field); //распечатывает поле таблицы в консоль
int getPosField(table_t table, string key); //выдаёт позицию поля в таблице по ключу. Выдаёт -1, если ничего не нашёл
void deleteField(table_t &table, string key); //удаляет поле в таблице по ключу

int main()
{
   setlocale(LC_CTYPE, "Russian");

   ifstream in("work.txt");
   table_t table;
   field_t field;

   while (in >> field.key >> field.name >> field.quantity) //пока не конец файла упорядоченно вставлять записи в таблицу
      insertFieldAtTable(table, field);

   printTable(table); //показательно распечатаем таблицу
   cout << "Какое поле по счёту сверху вы хотите удалить?" << endl;
   int field_num_for_delete = 0;
   cin >> field_num_for_delete;
   cout << "Ваше поле имело ключ:" << table.fields[field_num_for_delete - 1].key << endl; //покажем, что мы удаляем по ключу
   deleteField(table, table.fields[field_num_for_delete].key);
   cout << "Новая таблица:" << endl;
   printTable(table); // распечатываем новую таблицу

   _getch();
   return 0;
}

void insertFieldAtTable(table_t &table, field_t field)
{
   int insert_pos = getPosForFieldInsert(table, field);
   if (field.key.compare(table.fields[insert_pos].key) == 0) //при коллизиции прибавим quantity
      table.fields[insert_pos].quantity += field.quantity;
   else //если коллизиции нет, то освободим место в таблице смещением и добавим запись
   {
      shiftTableFieldsFromPos(table, insert_pos);
      table.fields[insert_pos] = field;
   }
}

int getPosForFieldInsert(table_t table, field_t field) //бинарный поиск места в массиве для вставки
{
   int left_search_edge = 0; // левый край диапазона поиска == 0
   int right_search_edge = table.size; // правый край == правый край массива + 1, так как вставить запись можем и в том числе и в самый конец таблицы
   while (left_search_edge < right_search_edge) //пока края не сойдутся
   {
      int cmp_pos = (left_search_edge + right_search_edge) / 2; //сравниваем с серединой(округление к левому краю)
      if (field.key.compare(table.fields[cmp_pos].key) <= 0) //если меньше или равна, то смещаем правый край на середину
         right_search_edge = cmp_pos;
      else //если больше, то смещаем левый край за середину на 1 позицию, чтобы избежать зацикливания. Можем это сделать, так как вариант "равно" ушёл выше
         left_search_edge = cmp_pos + 1;
   }
   return left_search_edge; //неважно какой край возвращать
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

int getPosField(table_t table, string key) //бинарный поиск поля в таблице
{
   int left_search_edge = 0; // левый край диапазона поиска == 0
   int right_search_edge = table.size - 1; // правый край == правый край массива
   while (left_search_edge < right_search_edge) //пока края не сойдутся
   {
      int cmp_pos = (left_search_edge + right_search_edge) / 2; //сравниваем с серединой(округление к левому краю)
      if (key.compare(table.fields[cmp_pos].key) <= 0) //если меньше или равна, то смещаем правый край на середину
         right_search_edge = cmp_pos;
      else //если больше, то смещаем левый край за середину на 1 позицию, чтобы избежать зацикливания. Можем это сделать, так как вариант "равно" ушёл выше
         left_search_edge = cmp_pos + 1;
   }
   if (key.compare(table.fields[left_search_edge].key) != 0)
      return -1;//если ключи не равны, то вернём -1
   return left_search_edge; //если же равны, то не важно какой край возвращать
}
void deleteField(table_t &table, string key)
{
   int field_pos = getPosField(table, key);
   if (field_pos >= 0) //если запись нашли в нашей таблице, то удаляем
   {
      for (int i = field_pos; i < table.size; i++)
         table.fields[i] = table.fields[i + 1];
      table.size--;
   }
}