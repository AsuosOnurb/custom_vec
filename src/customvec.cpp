#include "customvec.hpp"
#include <algorithm> // for std::copy

namespace customvec
{
    Vector::Vector() : data_(nullptr), size_(0), capacity_(0) {}

    Vector::~Vector()
    {
        delete[] data_;
    }

    void Vector::reserve(size_type new_capacity)
    {
        if (new_capacity <= capacity_)
            return;

        // Allocate new buffer and copy data over
        int *new_data = new int[new_capacity];
        for (size_type idx = 0; idx < size_; ++idx)
            new_data[idx] = data_[idx];

        // Free old buffer
        delete[] data_;

        data_ = new_data;
        capacity_ = new_capacity;
    }

    void Vector::push_back(int value)
    {
        if (size_ == capacity_)
        {
            size_type new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reserve(new_capacity);
        }

        data_[size_] = value;
        size_++;
    }

    int &Vector::operator[](size_type idx)
    {
        return data_[idx];
    }

    const int &Vector::operator[](size_type idx) const
    {
        return data_[idx];
    }

    Vector::size_type Vector::size() const noexcept
    {
        return size_;
    }

    Vector::size_type Vector::capacity() const noexcept
    {
        return capacity_;
    }

    void Vector::clear() noexcept
    {
        // Keep allocated mem., and just logically empty the vector, just to preven reallocation.
        size_ = 0;
    }
}