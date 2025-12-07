#pragma once

#include <cstddef>
#include <cassert>
#include <utility>

namespace customvec
{
    template <typename T>
    class Vector
    {
    public:
        using size_type = std::size_t;
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using pointer = T *;
        using const_pointer = const T *;

        Vector() noexcept : data_(nullptr), size_(0), capacity_(0) {}

        // Copy const.
        Vector(const Vector &other)
            : data_(nullptr), size_(0), capacity_(0)
        {
            if (other.size_ == 0)
            {
                return;
            }

            data_ = new T[other.size_];
            size_ = other.size_;
            capacity_ = other.size_;

            for (size_type i = 0; i < size_; ++i)
            {
                data_[i] = other.data_[i]; // copy elements
            }
        }

        // Copy assign.
        Vector &operator=(const Vector &other)
        {
            if (this == &other)
            {
                return *this;
            }

            // allocate new memory
            pointer new_data = nullptr;
            size_type new_size = other.size_;
            size_type new_capacity = other.size_;

            if (new_size > 0)
            {
                new_data = new T[new_size];
                for (size_type i = 0; i < new_size; ++i)
                {
                    new_data[i] = other.data_[i];
                }
            }

            // free old memory
            delete[] data_;

            // assign new state
            data_ = new_data;
            size_ = new_size;
            capacity_ = new_capacity;

            return *this;
        }

        // move constr.
        // move constructor
        Vector(Vector &&other) noexcept
            : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
        {
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }

        // move assign.
        Vector &operator=(Vector &&other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }

            delete[] data_;

            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;

            return *this;
        }

        ~Vector()
        {
            delete[] data_;
        }

        reference operator[](size_type idx)
        {
#ifdef MYVECTOR_DEBUG_BOUNDS
            assert(idx < size_ && "customvec::Vector: index out of bounds");
#endif
            return data_[idx];
        }

        const_reference operator[](size_type idx) const
        {
#ifdef MYVECTOR_DEBUG_BOUNDS
            assert(idx < size_ && "customvec::Vector: index out of bounds");
#endif
            return data_[idx];
        }

        void clear() noexcept
        {
            size_ = 0;
        }

        // Public accessors for size and capacity
        size_type size() const noexcept { return size_; }
        size_type capacity() const noexcept { return capacity_; }

        void push_back(const T &value)
        {
            ensure_capacity_for_one_more();
            data_[size_] = value;
            ++size_;
        }

        void push_back(T &&value)
        {
            ensure_capacity_for_one_more();
            data_[size_] = std::move(value);
            ++size_;
        }

    private:
        pointer data_;
        size_type size_;
        size_type capacity_;

        void reserve(size_type new_cap)
        {
            if (new_cap <= capacity_)
            {
                return;
            }

            pointer new_data = new T[new_cap];

            // copy existing elements
            for (size_type i = 0; i < size_; ++i)
            {
                new_data[i] = data_[i];
            }

            delete[] data_;

            data_ = new_data;
            capacity_ = new_cap;
        }

        void ensure_capacity_for_one_more()
        {
            if (size_ == capacity_)
            {
                size_type new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
                reserve(new_cap);
            }
        }
    };

}