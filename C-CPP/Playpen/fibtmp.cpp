#include <iostream>

//main template
template<int N>
struct Fib
{
    enum{ Result = Fib<N-1>::Result + Fib<N-2>::Result};
};

//specialized template
template<>
struct Fib<1>
{
    enum{ Result = 1 };
};

//specialized template
template<>
struct Fib<0>
{
    enum{ Result = 0 };
};

int main()
{
    int i = Fib<30>::Result;
    std::cout << i << std::endl;
}
