#include <iostream>
#include <utility> // std::move
#include "customvec.hpp"

void print_vec(const char *name, const customvec::Vector &v)
{
    std::cout << name << " (size=" << v.size()
              << ", capacity=" << v.capacity() << "): ";

    for (std::size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}

customvec::Vector make_vector()
{
    customvec::Vector tmp;
    for (int i = 0; i < 5; ++i)
    {
        tmp.push_back(i + 1);
    }
    return tmp; // will use move or NRVO
}

int main()
{
    std::cout << "=== Move constructor with std::move ===\n";
    customvec::Vector a;
    for (int i = 0; i < 5; ++i)
        a.push_back(i + 10); // 10 11 12 13 14

    print_vec("a", a);

    customvec::Vector b = std::move(a); // move constructor

    print_vec("a after move", a);
    print_vec("b", b);

    std::cout << "\n=== Move assignment with std::move ===\n";
    customvec::Vector c;
    for (int i = 0; i < 3; ++i)
        c.push_back(100 + i); // 100 101 102
    print_vec("c before", c);

    c = std::move(b); // move assignment

    print_vec("b after move", b);
    print_vec("c after c = std::move(b)", c);

    std::cout << "\n=== Returning by value (RVO / move) ===\n";
    customvec::Vector d = make_vector(); // will use RVO or move
    print_vec("d", d);

    return 0;
}
