#include "IntegerArray.h"
// Конструктор по умолчанию, присваивающий data nullptr, и присваивающий size ноль
IntegerArray::IntegerArray() : data(nullptr), size(0) {}
// Параметризованный коструктор принимающий размер size и выделяющий для память массива data, размером size
IntegerArray::IntegerArray(size_t size) : data(new int[size]), size(size)
{
    // Проверяем условие элемента size, если он меньше 0, то выкинется исключение
    if (size < 0) throw bad_lenght();
    // В цикле мы проходим по каждому элементу массива, в котором инициализируем каждый элемент 0
    for (size_t i = 0; i < size; ++i)
    {
        data[i] = 0;
    }
}

// Деструктор удаляющий выделенную память для массива data
IntegerArray::~IntegerArray()
{
    delete[] data;
}
// Перегрузка [] для доступа к элементам массива по индексу, если индекс выходит за пределы, то будет выброшено исключение
int& IntegerArray::operator[](size_t index)
{
    if (index >= size) throw bad_range();
    return data[index];    
}

const int& IntegerArray::operator[](size_t index) const
{
    if (index >= size) throw bad_range();
    return data[index];    
}

void IntegerArray::resize(size_t newSize)
{
    if (newSize < 0) throw bad_lenght(); // Проверка на отрицательный размер
    
    int* newData = new int[newSize]; // Выделение нового массива под новые данные
    size_t minSize = (size < newSize) ? size : newSize; // Определение минимального размера для копирования

    for (size_t i = 0; i < minSize; i++) // Копирование существующих элементов
    {
        newData[i] = data[i];
    }
    for (size_t i = minSize; i < newSize; i++) // Заполнение новых элементов нулями
    {
        newData[i] = 0;
    }
    
    delete[] data; // Освобождение памяти старого массива
    data = newData; // Переназначение указателя на новые данные
    size = newSize; // Обновление размера массива
}

void IntegerArray::insert(size_t index, int value)
{
    if (index > size) throw bad_range();
    
    resize(size + 1);

    for (size_t i = size - 1; i > index; --i)
    {
        data[i] = data[i - 1]; 
    }
    data[index] = value;    
}

void IntegerArray::remove(size_t index)
{
    if (index >= size) throw bad_range(); // Проверка границ индекса, если выходит за допустимое значение, выкидываем исключение
   
    for (size_t i = index; i < size; i++) // Сдвиг элементов
    {
        data[i] = data[i + 1];
    }
    resize(size - 1); // Уменьшение размера массива
}

size_t IntegerArray::getSize() const
{
    return size;
}

IntegerArray::IntegerArray(const IntegerArray& other) : data(new int[other.size]), size(other.size) // Конструктор копирования
{
    for (size_t i = 0; i < size; i++)
    {
        data[i] = other.data[i];
    }
}

IntegerArray& IntegerArray::operator=(const IntegerArray& other) // Перегрузка оператора присваивания
{
    if (this == &other) return *this;
    
    delete[] data;
    size = other.size;
    data = new int [size];
    for (size_t i = 0; i < size; i++)
    {
        data[i] = other.data[i];
    }
    
    return *this;
}

IntegerArray::IntegerArray(IntegerArray&& other) noexcept : data(other.data), size(other.size)
{
    other.data = nullptr;
    other.size = 0;
}

IntegerArray& IntegerArray::operator=(IntegerArray&& other) noexcept
{
    if (this == &other) return *this;
    
    delete[] data;
    data = other.data;
    size = other.size;

    other.data = nullptr;
    other.size = 0;

    return *this;
}