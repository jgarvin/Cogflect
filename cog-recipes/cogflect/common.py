#!/usr/bin/env python

import cog

__common_big_string="""
#ifndef INCLUDED_COGFLECT_COMMON_COMMON_FUNCTIONS
#define INCLUDED_COGFLECT_COMMON_COMMON_FUNCTIONS

namespace cogflect {

// This seemingly useless template is a workaround
// for an oddity of C++ syntax. You can declare an
// array like this:
//
//     double foo[3];
//
// But not like this:
//
//     double[3] foo;
//
// Which means that some of the type information is
// on the left and some is on the right when declaring
// arrays. Cogflect lets you specify an element type of
// "double[3]", which is made possible by this template.
// You can use it to declare the array like this:
//
//     type_passthrough<double[3]>::type foo;
//
// Thus keeping all the type information on the left
// side.
template<typename T>
struct type_passthrough {
    typedef T type;
};

}

#endif

"""

__enum_big_string="""
#ifndef INCLUDED_COGFLECT_ENUM_COMMON_FUNCTIONS
#define INCLUDED_COGFLECT_ENUM_COMMON_FUNCTIONS

namespace cogflect {

struct store_index_action
{
    unsigned index;

    // We don't waste an instruction initializing
    // index because the type system guarantees
    // this switch will always succeed.
    inline store_index_action()
    {}

    template<class T>
    inline void action()
    {
        index = T::index;
    }

    inline void default_action()
    {}
};

struct store_string_action
{
    const char* str;

    template<class T>
    inline void action()
    {
        str = T::string();
    }

    inline void default_action()
    {}
};

struct true_t {};
struct false_t {};

}

#endif

"""

__cppclass_big_string="""
#ifndef INCLUDED_COGFLECT_CPPCLASS_COMMON_FUNCTIONS
#define INCLUDED_COGFLECT_CPPCLASS_COMMON_FUNCTIONS

namespace cogflect {

template<typename Visitor, typename DataType>
struct pass_member_action
{
    inline pass_member_action(Visitor& v, DataType& d)
        : visitor_(v),
          data_(d)
    {}

    template<typename MemberType>
    inline void action()
    {
        visitor_.
            template process_member<MemberType>(
                data_.template get_member<MemberType>());
    }

    inline void default_action()
    {
        visitor_.unknown_member();
    }

    Visitor& visitor_;
    DataType& data_;
};

}

#endif

"""

__generated_common_common = False
__generated_enum_common = False
__generated_cppclass_common = False

def generate_common_common():
    global __generated_common_common
    if __generated_common_common:
        return

    __generated_common_common = True

    cog.out(__common_big_string)

def generate_enum_common():
    global __generated_enum_common
    if __generated_enum_common:
        return

    generate_common_common()

    __generated_enum_common = True

    cog.out(__enum_big_string)

def generate_cppclass_common():
    global __generated_cppclass_common
    if __generated_cppclass_common:
        return

    generate_common_common()

    __generated_cppclass_common = True

    cog.out(__cppclass_big_string)
