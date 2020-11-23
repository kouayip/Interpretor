#ifndef __TYPE__
#define __TYPE__

#include <iostream>

template <typename T>
struct Type
{
    T value;
};

typedef Type<int> Interger;
typedef Type<float> Float;

#endif