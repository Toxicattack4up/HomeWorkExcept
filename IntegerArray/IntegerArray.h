#ifndef INTEGERARRAY_H
#define INTEGERARRAY_H
#include <cstddef>
#include <exception>

class bad_range : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Index out of range";
    }
};

class bad_lenght : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Invalid length";
    }
};

class IntegerArray
{
private:
    int* data;
    size_t size;

public:
    IntegerArray();
    explicit /*предотвращение неявное преобразование типов*/ IntegerArray(size_t size);
    ~IntegerArray();

    int& operator[](size_t size);
    const int& operator[](size_t index) const;

    void resize(size_t newSize);
    void insert(size_t index, int value);
    void remove(size_t index);

    size_t getSize() const;

    IntegerArray(const IntegerArray& other);
    IntegerArray& operator=(const IntegerArray& other);
    IntegerArray(IntegerArray&& other) noexcept;
    IntegerArray& operator=(IntegerArray&& other) noexcept;
};
