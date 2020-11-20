#ifndef __ASSERT__
#define __ASSERT__

#include <iostream>
#include <typeinfo>

#include "./Utils.hpp"

class Asset
{
private:
public:
    template <typename T, typename V>
    static void equals(T actuals, V expecteds)
    {
        auto eval = [&]() -> bool {
            if (typeid(actuals) == typeid(expecteds))
                return (actuals == expecteds);
            else
                return false;
        }();

        if (!eval)
        {
            //TODO: Refator this code to create a generic method for print assert error
            std::cerr << "Assertion equals error" << std::endl;
            std::cerr << "Actual: " << std::endl;
            Utils::print(actuals, "   | ");
            std::cerr << "Expected: " << std::endl;
            Utils::print(expecteds, "   | ");
            std::cout << std::endl;
            std::exit(1); //! This is an alert exit program
        }
    };

    template <typename T, typename V, size_t n, size_t v>
    static void equals(T const (&actuals)[n], V const (&expecteds)[v])
    {
        //? Lamda operation use to evaluat equlity to another value
        auto eval = [&]() -> bool {
            if (n != v)
                return false;
            else
            {
                for (size_t i = 0; i < n; i++)
                {
                    if (actuals[i] != expecteds[i])
                        return false;
                }
                return true;
            }
        }();

        //* This is test evaluation lamda operation
        if (!eval)
        {
            //TODO: Refator this code to create a generic method for print assert error
            std::cerr << "Assertion equals error" << std::endl;
            std::cerr << "Actual: " << std::endl;
            Utils::print(actuals, "   | ");
            std::cerr << "Expected: " << std::endl;
            Utils::print(expecteds, "   | ");
            std::cout << std::endl;
            std::exit(1); //! This is an alert exit program
        }
    };
};
#endif