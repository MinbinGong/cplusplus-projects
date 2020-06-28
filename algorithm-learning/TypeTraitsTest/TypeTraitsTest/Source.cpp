#include <iostream>
#include <type_traits>

int main()
{
    //std::cout << "is_const: " << std::endl;
    //std::cout << "int: " << std::is_const<int>::value << std::endl;
    //std::cout << "const int: " << std::is_const<const int>::value << std::endl;
    //std::cout << "const int&: " << std::is_const<const int&>::value << std::endl;
    //std::cout << "const int*: " << std::is_const<const int*>::value << std::endl;
    //std::cout << "int* const: " << std::is_const<int* const>::value << std::endl;

    std::cout << std::is_same<int, int>::value << "\n";
    std::cout << std::is_same<int, unsigned int>::value << "\n";
    std::cout << std::is_same<int, signed int>::value << "\n";

    return 0;
}