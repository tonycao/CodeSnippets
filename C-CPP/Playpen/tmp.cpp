template<bool condition, unsigned int value>
struct print_if
{
static const unsigned int result = value;

};

template<unsigned int value>
struct print_if<false, value>
{
static const unsigned int result = (unsigned char*)value;
};

template<unsigned int value>
struct print_if_77
{
static const unsigned int result = print_if<value == 77 , value>::result;
};

int main()
{
    unsigned int test1 = print_if_77<77>::result;
    //unsigned int test2 = print_if_77<123>::result;
    return 0;
}

