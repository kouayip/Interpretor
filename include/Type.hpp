#ifndef __TYPE__
#define __TYPE__

#include <iostream>

struct Auto
{
};

template <typename T>
struct Type : Auto
{
    Type(T value) : value_(value) {}

    const auto value() const
    {
        return value_;
    }

private:
    T value_;
};

typedef Type<int> Integer;
typedef Type<float> Float;
typedef Type<double> Double;
typedef Type<std::string> String;

template <typename T>
inline std::ostream &operator<<(std::ostream &out, Type<T> const(&type))
{
    out << type.value();
    return out;
};

inline std::ostream &operator<<(std::ostream &out, String const(&string))
{
    out << "\"" << string.value() << "\"";
    return out;
};

#endif