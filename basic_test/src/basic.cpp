#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

#include <example/enum.hpp>
#include "../include/example/data.hpp"

#define TEST_ASSERT(x)                           \
    {                                            \
        if(!(x))                                 \
            std::abort();                        \
    }

struct val_print {
    static std::ostringstream o;

    val_print() {}

    template<class MemberType>
    void process_member(typename MemberType::type const& v) const
    {
        o << MemberType::string() << " " << v << " ";
    }

    void unknown_member() const
    {
        TEST_ASSERT(false);
    }
};
std::ostringstream val_print::o;

// By calling with 'T' and 'const T', we can test that that const
// being on/off for the data type works correctly.
template<class T, class visitor>
void data_test_1(T& foo)
{
    TEST_ASSERT(foo.template get_indexed_member<1>() == 3);

    for(unsigned i = 0; i < example::size; ++i) {
        visitor bar;
        foo.get_runtime_indexed_member(bar, i);
    }
    TEST_ASSERT(val_print::o.str() == "example::SHOE_PRICE 45.3 example::GUM_PRICE 3 example::CAR_PRICE 20 ");
    val_print::o.str("");

    // Separately test with a temporary to make sure that it works
    // with the type inference.
    for(unsigned i = 0; i < example::size; ++i) {
        foo.get_runtime_indexed_member(visitor(), i);
    }
    TEST_ASSERT(val_print::o.str() == "example::SHOE_PRICE 45.3 example::GUM_PRICE 3 example::CAR_PRICE 20 ");
    val_print::o.str("");
}

template<class T, class visitor>
void data_test_2(T& foo)
{
    typedef std::vector<typename T::enum_type> FieldVec;
    FieldVec fields;
    fields.push_back(example::SHOE_PRICE);
    fields.push_back(example::GUM_PRICE);
    fields.push_back(example::CAR_PRICE);
    for(typename FieldVec::iterator i = fields.begin(); i != fields.end(); ++i) {
        visitor bar;
        foo.get_runtime_member(bar, *i);
    }
    TEST_ASSERT(val_print::o.str() == "example::SHOE_PRICE 23.2 example::GUM_PRICE 3 example::CAR_PRICE 20 ");
    val_print::o.str("");

    // Separately test with a temporary to make sure that it works
    // with the type inference.
    for(typename FieldVec::iterator i = fields.begin(); i != fields.end(); ++i) {
        foo.get_runtime_member(visitor(), *i);
    }
    TEST_ASSERT(val_print::o.str() == "example::SHOE_PRICE 23.2 example::GUM_PRICE 3 example::CAR_PRICE 20 ");
    val_print::o.str("");
}

int main()
{
    example::type val0 = example::SHOE_PRICE;
    example::type val1 = example::GUM_PRICE;
    example::type val2 = example::CAR_PRICE;

    TEST_ASSERT(val0.index() == 0);
    TEST_ASSERT(val1.index() == 1);
    TEST_ASSERT(val2.index() == 2);

    TEST_ASSERT(example::type::size == 3);

    example::data foo;
    foo.get_indexed_member<0>() = 45.3;
    foo.get_indexed_member<1>() = 3;
    foo.get_indexed_member<2>() = 20;
    data_test_1<example::data, val_print>(foo);
    data_test_1<example::data, const val_print>(foo);
    data_test_1<const example::data, val_print>(foo);
    data_test_1<const example::data, const val_print>(foo);

    foo.get_indexed_member<0>() = 23.2;
    data_test_2<example::data, val_print>(foo);
    data_test_2<example::data, const val_print>(foo);
    data_test_2<const example::data, val_print>(foo);
    data_test_2<const example::data, const val_print>(foo);

    return 0;
}
