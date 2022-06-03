#include <iostream>
#include <iomanip>
#include <type_traits>
#include <vector>



template< class T, class Alloc >
std::ostream &operator<<(std::ostream &os, const std::vector<T, Alloc>& v )
{
    os << "(";
    for (size_t i = 0; i < v.size(); i++)
        os << v[i] << (i < v.size() - 1 ? ", " : "");
    os << ")";
    return os;
}

template <typename T>
void print_vector(std::vector<T> &v)
{
    std::cout << "v : " << v << std::endl;
    std::cout << "size     : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    std::cout << "data     : " << v.data()  << std::endl;
    std::cout << "front    : " << v.front()  << std::endl;
    std::cout << "back     : " << v.back()  << std::endl;
    std::cout << "maxsize  : " << v.max_size() << std::endl << std::endl;
    std::cout << std::endl;
}

int main()
{

        std::vector<int> v;
        std::vector<int> *v1 = new std::vector<int>();
        std::vector<std::string> vs;



        for (int i = 111; i < 114; i++)
        {
            v.push_back(i);
            print_vector(v);
        }

        std::cout << "TEST " << *v.begin() << std::endl;
        std::cout << "After reserve " << std::endl;
        v.reserve(5);
        print_vector(v);
        v.push_back(3);
        v.push_back(3);
        v.push_back(3);
        print_vector(v);

        v.clear();
        // print_vector(v);
        // v.pop_back();
        v1 = NULL;
    return 0;
}