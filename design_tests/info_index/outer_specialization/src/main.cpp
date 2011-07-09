namespace misile {

template<unsigned i>
struct info_index;

template<>
struct info_index<0>
{
    static const unsigned index = 0;
    static const int value = 0;
    inline static const char* string() { return "missile::MISSILE_TYPE"; }
    static const unsigned long long name_hash = 18317973204608468020u;
};

typedef info_index<0> MISSILE_TYPE_INFO;

template<>
struct info_index<1>
{
    static const unsigned index = 1;
    static const int value = 1;
    inline static const char* string() { return "missile::LOCATION"; }
    static const unsigned long long name_hash = 4666628800144805268u;
};

typedef info_index<1> LOCATION_INFO;

template<>
struct info_index<2>
{
    static const unsigned index = 2;
    static const int value = 2;
    inline static const char* string() { return "missile::VELOCITY"; }
    static const unsigned long long name_hash = 1507608000310853010u;
};

typedef info_index<2> VELOCITY_INFO;

template<>
struct info_index<3>
{
    static const unsigned index = 3;
    static const int value = 3;
    inline static const char* string() { return "missile::ACCELERATION"; }
    static const unsigned long long name_hash = 17348947259799395834u;
};

typedef info_index<3> ACCELERATION_INFO;

}

int main()
{
    return 0;
}
