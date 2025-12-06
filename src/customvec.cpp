#include "customvec.hpp"
#include <algorithm> // for std::copy

namespace customvec
{
    Vector::Vector() : data_(nullptr), size_(0), capacity_(0) {}

    // Copy constructor
    Vector::Vector(const Vector &other)
        : data_(nullptr), size_(0), capacity_(0)
    {
        if (other.size() == 0)
            return;

        data_ = new int[other.size_];
        size_ = other.size_;
        capacity_ = other.size_;

        // Copy data over
        for (size_type i = 0; i < size_; ++i)
        {
            data_[i] = other.data_[i];
        }
    }

    // Copy assignment
    Vector &Vector::operator=(const Vector &other)
    {
        if (this == &other)
        {
            return *this; // self-assignment, do nothing
        }

        // Allocate mem
        int *new_data = nullptr;
        size_type new_size = other.size_;
        size_type new_capacity = other.size_;

        if (new_size > 0)
        {
            new_data = new int[new_size];
            for (size_type i = 0; i < new_size; ++i)
            {
                new_data[i] = other.data_[i];
            }
        }

        // free old mem
        delete[] data_;

        // update
        data_ = new_data;
        size_ = new_size;
        capacity_ = new_capacity;

        return *this;
    }

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
#ifdef MYVECTOR_DEBUG_BOUNDS
        assert(idx < size_ && "customvec::Vector: index out of bounds");
#endif
        return data_[idx];
    }

    const int &Vector::operator[](size_type idx) const
    {
#ifdef MYVECTOR_DEBUG_BOUNDS
        assert(idx < size_ && "my::Vector: index out of bounds");
#endif
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