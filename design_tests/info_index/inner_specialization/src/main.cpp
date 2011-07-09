namespace misile {

struct info_index
{
    template<unsigned i>
    static inline unsigned index()
    {
        return i;
    }

    template<unsigned i>
    static inline int value();

    template<unsigned i>
    static inline const char* string();

    template<unsigned i>
    static unsigned long long name_hash();
};

template<>
inline int info_index::value<0>()
{
    return 0;
}

template<>
inline const char* info_index::string<0>()
{
    return "missile::MISSILE_TYPE";
}

template<>
inline unsigned long long info_index::name_hash<0>()
{
    return 18317973204608468020u;
}

template<>
inline int info_index::value<1>()
{
    return 1;
}

template<>
inline const char* info_index::string<1>()
{
    return "missile::LOCATION";
}

template<>
inline unsigned long long info_index::name_hash<1>()
{
    return 4666628800144805268u;
}

template<>
inline int info_index::value<2>()
{
    return 2;
}

template<>
inline const char* info_index::string<2>()
{
    return "missile::VELOCITY";
}

template<>
inline unsigned long long info_index::name_hash<2>()
{
    return 1507608000310853010u;
}

template<>
inline int info_index::value<3>()
{
    return 3;
}

template<>
inline const char* info_index::string<3>()
{
    return "missile::ACCELERATION";
}

template<>
inline unsigned long long info_index::name_hash<3>()
{
    return 17348947259799395834u;
}

}

int main()
{
    return 0;
}
