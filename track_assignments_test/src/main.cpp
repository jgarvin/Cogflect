#include <track_assignments_test/missile.hpp>

#include <cstdlib>
#include <bitset>

#define TEST_ASSERT(x)                          \
    {                                           \
        if(!(x))                                \
            std::abort();                       \
    }

class TrackedMissile : public missile::data {
public:
    template<typename Info>
    void set_member(typename Info::type const& value)
    {
        changed_.set(Info::index);
        get_member< Info >() = value;
    }

    bool fieldChanged(missile::type i) const
    {
        return changed_.test(i.index());
    }

private:
    std::bitset<missile::size> changed_;
};

int main()
{
    TrackedMissile x;

    TEST_ASSERT( !x.fieldChanged(missile::MISSILE_TYPE) );

    x.set_member< missile::MISSILE_TYPE_INFO >("ICBM");

    TEST_ASSERT( x.fieldChanged(missile::MISSILE_TYPE) );

    return 0;
}
