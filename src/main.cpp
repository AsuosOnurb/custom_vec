#include <iostream>
#include "customvec.hpp"

int main()
{
    customvec::Vector v;

    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i * 10);
        std::cout << "Pushed " << i * 10
                  << " | size = " << v.size()
                  << ", capacity = " << v.capacity() << '\n';
    }

    std::cout << "Elements: ";
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';

    v.clear();
    std::cout << "After clear: size = " << v.size()
              << ", capacity = " << v.capacity() << '\n';

    return 0;
}
