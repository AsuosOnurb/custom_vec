#include <iostream>
#include <string>
#include "customvec.hpp"

template <typename T>
void print_vec(const char *name, const customvec::Vector<T> &v)
{
    std::cout << name << " (size=" << v.size()
              << ", capacity=" << v.capacity() << "): ";

    for (std::size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}

int main()
{
    std::cout << "=== Vector<int> ===\n";
    customvec::Vector<int> vi;
    for (int i = 0; i < 5; ++i)
    {
        vi.push_back(i * 10);
    }
    print_vec("vi", vi);

    std::cout << "\n=== Vector<std::string> ===\n";
    customvec::Vector<std::string> vs;
    vs.push_back("hello");
    vs.push_back("world");
    vs.push_back(std::string("from temp"));

    print_vec("vs", vs);

    // test copy
    customvec::Vector<std::string> vs_copy = vs;
    vs[0] = "HELLO";
    std::cout << "After modifying vs[0]:\n";
    print_vec("vs", vs);
    print_vec("vs_copy", vs_copy);

    // test move
    customvec::Vector<std::string> vs_moved = std::move(vs);
    print_vec("vs after move", vs);
    print_vec("vs_moved", vs_moved);

    return 0;
}
