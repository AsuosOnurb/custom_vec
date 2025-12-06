#pragma once

#include <cstddef>
#include <cassert>

namespace customvec
{

    class Vector
    {
    public:
        using size_type = std::size_t;
        using value_type = int;

        Vector();
        Vector(const Vector &);            // Copy const.
        Vector &operator=(const Vector &); // Copy assign.
        ~Vector();

        void push_back(int value);

        int &operator[](size_type idx);
        const int &operator[](size_type idx) const;

        size_type size() const noexcept;
        size_type capacity() const noexcept;

        void clear() noexcept;

    private:
        int *data_;
        size_type size_;
        size_type capacity_;

        void reserve(size_type new_cap);
    };

}