#include <iostream>
#include "customvec.hpp"

int main()
{
    customvec::Vector a;
    for (int i = 0; i < 5; ++i)
    {
        a.push_back(i + 1); // 1 2 3 4 5
    }

    std::cout << "a: ";
    for (std::size_t i = 0; i < a.size(); ++i)
    {
        std::cout << a[i] << ' ';
    }
    std::cout << "\n";

    // ---- Test copy constructor ----
    customvec::Vector b = a; // calls copy ctor

    std::cout << "b (copy of a): ";
    for (std::size_t i = 0; i < b.size(); ++i)
    {
        std::cout << b[i] << ' ';
    }
    std::cout << "\n";

    // modify a, b should stay unchanged
    a[0] = 42;

    std::cout << "After modifying a[0] = 42:\n";
    std::cout << "a: ";
    for (std::size_t i = 0; i < a.size(); ++i)
    {
        std::cout << a[i] << ' ';
    }
    std::cout << "\n";

    std::cout << "b: ";
    for (std::size_t i = 0; i < b.size(); ++i)
    {
        std::cout << b[i] << ' ';
    }
    std::cout << "\n";

    // ---- Test copy assignment ----
    customvec::Vector c;
    c.push_back(100);
    c.push_back(200);

    std::cout << "c before assignment: ";
    for (std::size_t i = 0; i < c.size(); ++i)
    {
        std::cout << c[i] << ' ';
    }
    std::cout << "\n";

    c = a; // calls copy assignment

    std::cout << "c after c = a: ";
    for (std::size_t i = 0; i < c.size(); ++i)
    {
        std::cout << c[i] << ' ';
    }
    std::cout << "\n";

    return 0;
}
