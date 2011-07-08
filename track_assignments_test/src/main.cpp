#include <track_assignments_test/missile.hpp>

#include <cstdlib>
#include <bitset>

#define TEST_ASSERT(x)                          \
    {                                           \
        if(!(x))                                \
            std::abort();                       \
    }

template<class T>
class TrackedType
{
public:
  template<typename Info>
  void setMember(typename Info::type const& value)
  {
    changed_.set(Info::index);
    data_.template get_member< Info >() = value;
  }

  template<typename Info>
  typename Info::type getMember() const
  {
    return data_.template get_member< Info >();
  }

  bool fieldChanged(typename T::enum_type i) const
  {
    return changed_.test(i.index());
  }

private:
  T data_;
  std::bitset<T::enum_type::size> changed_;
};

typedef TrackedType<missile::data> TrackedMissile;

int main()
{
    TrackedMissile x;

    TEST_ASSERT( !x.fieldChanged(missile::MISSILE_TYPE) );

    x.setMember< missile::MISSILE_TYPE_INFO >("ICBM");

    TEST_ASSERT( x.fieldChanged(missile::MISSILE_TYPE) );

    return 0;
}
