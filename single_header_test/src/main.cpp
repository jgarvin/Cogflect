#include <single_header_test/all.hpp>

int main()
{
    single_header_test::type x(single_header_test::FOO);

    single_header_test::data y;
    y.get_member<single_header_test::FOO_INFO>() = 3;

    return 0;
}
