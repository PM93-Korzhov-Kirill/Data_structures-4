#pragma once

#define CAPACITY 17 //максимальное количество элементов таблицы

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