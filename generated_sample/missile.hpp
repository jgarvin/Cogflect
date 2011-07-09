#ifndef INCLUDED_TRACK_ASSIGNMENTS_TEST_MISSILE_HPP
#define INCLUDED_TRACK_ASSIGNMENTS_TEST_MISSILE_HPP

#include <string>

/*[[[cog

  import cogflect as cf

  fields = [
  ["name",              "type",          "tags"],
  ["MISSILE_TYPE",      "std::string",   None  ],
  ["LOCATION",          "double[3]",     None  ],
  ["VELOCITY",          "double[3]",     None  ],
  ["ACCELERATION",      "double[3]",     None  ]
  ]

  cf.Enum("missile", fields)
  cf.CppClass("missile", fields)

  ]]]*/

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

namespace missile {

class type;
class data;

template<unsigned i>
struct info_index;

template<>
struct info_index<0>
{
    static const unsigned index = 0;
    static const int value = 0;
    inline static const char* string() { return "missile::MISSILE_TYPE"; }
    typedef std::string type;
    typedef missile::type enum_type;
    typedef missile::data data_type;
    static const unsigned long long name_hash = 18317973204608468020u;
};

typedef info_index<0> MISSILE_TYPE_INFO;

template<>
struct info_index<1>
{
    static const unsigned index = 1;
    static const int value = 1;
    inline static const char* string() { return "missile::LOCATION"; }
    typedef cogflect::type_passthrough< double[3] >::type type;
    typedef missile::type enum_type;
    typedef missile::data data_type;
    static const unsigned long long name_hash = 4666628800144805268u;
};

typedef info_index<1> LOCATION_INFO;

template<>
struct info_index<2>
{
    static const unsigned index = 2;
    static const int value = 2;
    inline static const char* string() { return "missile::VELOCITY"; }
    typedef cogflect::type_passthrough< double[3] >::type type;
    typedef missile::type enum_type;
    typedef missile::data data_type;
    static const unsigned long long name_hash = 1507608000310853010u;
};

typedef info_index<2> VELOCITY_INFO;

template<>
struct info_index<3>
{
    static const unsigned index = 3;
    static const int value = 3;
    inline static const char* string() { return "missile::ACCELERATION"; }
    typedef cogflect::type_passthrough< double[3] >::type type;
    typedef missile::type enum_type;
    typedef missile::data data_type;
    static const unsigned long long name_hash = 17348947259799395834u;
};

typedef info_index<3> ACCELERATION_INFO;

// This is a constant rather than a function so that it
// can be used as a template parameter. In C++0x we can change
// it to be a function using the 'constexpr' keyword.
static const unsigned size = 4;

class type
{
private:
    int val_;

    explicit inline type(int val) : val_(val) {}

public:
    inline type(type const& other) : val_(other.val_) {}
    inline type& operator=(type other) { val_ = other.val_; }

    template<class Info>
    static inline type make_from_info()
    {
        return type(Info::value);
    }

    template<class Action>
    static inline void value_switcher(int value, Action& action)
    {
        switch(value)
        {
            case MISSILE_TYPE_INFO::value:
                action.template action< MISSILE_TYPE_INFO >();
                break;
            case LOCATION_INFO::value:
                action.template action< LOCATION_INFO >();
                break;
            case VELOCITY_INFO::value:
                action.template action< VELOCITY_INFO >();
                break;
            case ACCELERATION_INFO::value:
                action.template action< ACCELERATION_INFO >();
                break;
            default:
                action.default_action();
                break;
        }
    }

    template<class Action>
    static inline void index_switcher(unsigned index, Action& action)
    {
        switch(index)
        {
            case MISSILE_TYPE_INFO::index:
                action.template action< MISSILE_TYPE_INFO >();
                break;
            case LOCATION_INFO::index:
                action.template action< LOCATION_INFO >();
                break;
            case VELOCITY_INFO::index:
                action.template action< VELOCITY_INFO >();
                break;
            case ACCELERATION_INFO::index:
                action.template action< ACCELERATION_INFO >();
                break;
            default:
                action.default_action();
                break;
        }
    }

    template<class Action>
    inline void switcher(Action& action) const
    {
        value_switcher(val_, action);
    }

    inline int value() const
    {
        return val_;
    }

    inline unsigned index() const
    {
        cogflect::store_index_action sw;
        switcher(sw);
        return sw.index;
    }

    inline const char* string() const
    {
        cogflect::store_string_action sw;
        switcher(sw);
        return sw.str;
    }

    template<unsigned long long>
    struct info_with_hash
    {
        typedef cogflect::false_t type;
    };

    // This is a constant rather than a function so that it
    // can be used as a template parameter. In C++0x we can change
    // it to be a function using the 'constexpr' keyword.
    static const unsigned size = 4;

};

template<>
struct type::info_with_hash<18317973204608468020u>
{
    typedef MISSILE_TYPE_INFO type;
};

template<>
struct type::info_with_hash<4666628800144805268u>
{
    typedef LOCATION_INFO type;
};

template<>
struct type::info_with_hash<1507608000310853010u>
{
    typedef VELOCITY_INFO type;
};

template<>
struct type::info_with_hash<17348947259799395834u>
{
    typedef ACCELERATION_INFO type;
};

namespace {

const type MISSILE_TYPE(type::make_from_info<MISSILE_TYPE_INFO>());
const type LOCATION(type::make_from_info<LOCATION_INFO>());
const type VELOCITY(type::make_from_info<VELOCITY_INFO>());
const type ACCELERATION(type::make_from_info<ACCELERATION_INFO>());

}

}

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

/*
TODO: Pull this stuff out and give access to a
get_same_member<T> template that given an info template
from one class gets you the same named T in the other
class.
*/

template<class SourceMemberType, class TargetMemberType>
struct shape_assign_helper
{
    inline static void assign(typename SourceMemberType::type& v,
                              typename TargetMemberType::data_type& d)
    {
        v = d.template get_member<TargetMemberType>();
    }
};

template<class SourceMemberType>
struct shape_assign_helper<SourceMemberType, cogflect::false_t>
{
    // no-op when target doesn't have the same member
    // use ellipses since no sensible type for second argument
    inline static void assign(...)
    {
    }
};

template<class Source, class Target>
struct shape_assign
{
    inline shape_assign(Target& target)
      : target_(target)
    {}

    template<class MemberType>
    void process_member(typename MemberType::type& v) const
    {
        // Check if target type has a member with the same name by checking if
        // it has a member with the same name_hash as the current member type being
        // iterated.

        typedef typename Target::enum_type target_enum_type;
        typedef typename target_enum_type::template info_with_hash<MemberType::name_hash>::type
            potential_type;

        shape_assign_helper<MemberType, potential_type>::assign(v, target_);
    }

    Target& target_;
};

}

#endif

namespace missile {

class data
{
public:
    typedef missile::type enum_type;

    // TODO: iterate public/protected/private independently?
    // TODO: iterate over members with a tag? <-- public/protected/private tags
    // TODO: tag to indicate reflection is available

    template<typename T>
    typename T::type& get_member();

    template<typename T>
    typename T::type const& get_member() const;

    template<unsigned index>
    typename missile::info_index<index>::type& get_indexed_member()
    {
        return get_member< info_index<index> >();
    }

    template<unsigned index>
    typename missile::info_index<index>::type const& get_indexed_member() const
    {
        return get_member< info_index<index> >();
    }

    template<typename Processor>
    inline void get_runtime_member(Processor& p, type value)
    {
        cogflect::pass_member_action<Processor, data> tmp(p, *this);
        value.switcher(tmp);
    }

    template<typename Processor>
    inline void get_runtime_member(Processor const& p, type value)
    {
        cogflect::pass_member_action<const Processor, data> tmp(p, *this);
        value.switcher(tmp);
    }

    template<typename Processor>
    inline void get_runtime_member(Processor& p, type value) const
    {
        cogflect::pass_member_action<Processor, const data> tmp(p, *this);
        value.switcher(tmp);
    }

    template<typename Processor>
    inline void get_runtime_member(Processor const& p, type value) const
    {
        cogflect::pass_member_action<const Processor, const data> tmp(p, *this);
        value.switcher(tmp);
    }

    template<typename Processor>
    inline void get_runtime_indexed_member(Processor& p, unsigned index)
    {
        cogflect::pass_member_action<Processor, data> tmp(p, *this);
        type::index_switcher(index, tmp);
    }

    template<typename Processor>
    inline void get_runtime_indexed_member(Processor& p, unsigned index) const
    {
        cogflect::pass_member_action<Processor, const data> tmp(p, *this);
        type::index_switcher(index, tmp);
    }

    template<typename Processor>
    inline void get_runtime_indexed_member(Processor const& p, unsigned index)
    {
        cogflect::pass_member_action<const Processor, data> tmp(p, *this);
        type::index_switcher(index, tmp);
    }

    template<typename Processor>
    inline void get_runtime_indexed_member(Processor const& p, unsigned index) const
    {
        cogflect::pass_member_action<const Processor, const data> tmp(p, *this);
        type::index_switcher(index, tmp);
    }

    template<class VisitorT>
    inline void for_all_members(VisitorT& visitor)
    {
        visitor.
           template process_member<MISSILE_TYPE_INFO>(missile_type_);
        visitor.
           template process_member<LOCATION_INFO>(location_);
        visitor.
           template process_member<VELOCITY_INFO>(velocity_);
        visitor.
           template process_member<ACCELERATION_INFO>(acceleration_);
    }

    template<class VisitorT>
    inline void for_all_members(VisitorT& visitor) const
    {
        visitor.
           template process_member<MISSILE_TYPE_INFO>(missile_type_);
        visitor.
           template process_member<LOCATION_INFO>(location_);
        visitor.
           template process_member<VELOCITY_INFO>(velocity_);
        visitor.
           template process_member<ACCELERATION_INFO>(acceleration_);
    }

    template<class VisitorT>
    inline void for_all_members(VisitorT const& visitor)
    {
        visitor.
           template process_member<MISSILE_TYPE_INFO>(missile_type_);
        visitor.
           template process_member<LOCATION_INFO>(location_);
        visitor.
           template process_member<VELOCITY_INFO>(velocity_);
        visitor.
           template process_member<ACCELERATION_INFO>(acceleration_);
    }

    template<class VisitorT>
    inline void for_all_members(VisitorT const& visitor) const
    {
        visitor.
           template process_member<MISSILE_TYPE_INFO>(missile_type_);
        visitor.
           template process_member<LOCATION_INFO>(location_);
        visitor.
           template process_member<VELOCITY_INFO>(velocity_);
        visitor.
           template process_member<ACCELERATION_INFO>(acceleration_);
    }

    template<class TargetType>
    inline void shape_assign(TargetType const& other)
    {
        cogflect::shape_assign<data, TargetType> visitor;
        for_all_members(visitor);
    }


private:
    std::string missile_type_;
    cogflect::type_passthrough< double[3] >::type location_;
    cogflect::type_passthrough< double[3] >::type velocity_;
    cogflect::type_passthrough< double[3] >::type acceleration_;
}; // class data

template<>
inline MISSILE_TYPE_INFO::type& data::get_member<MISSILE_TYPE_INFO>()
{
    return missile_type_;
}

template<>
inline LOCATION_INFO::type& data::get_member<LOCATION_INFO>()
{
    return location_;
}

template<>
inline VELOCITY_INFO::type& data::get_member<VELOCITY_INFO>()
{
    return velocity_;
}

template<>
inline ACCELERATION_INFO::type& data::get_member<ACCELERATION_INFO>()
{
    return acceleration_;
}

template<>
inline MISSILE_TYPE_INFO::type const& data::get_member<MISSILE_TYPE_INFO>() const
{
    return missile_type_;
}

template<>
inline LOCATION_INFO::type const& data::get_member<LOCATION_INFO>() const
{
    return location_;
}

template<>
inline VELOCITY_INFO::type const& data::get_member<VELOCITY_INFO>() const
{
    return velocity_;
}

template<>
inline ACCELERATION_INFO::type const& data::get_member<ACCELERATION_INFO>() const
{
    return acceleration_;
}

} // namespace missile
//[[[end]]]

#endif
