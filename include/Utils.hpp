#if !defined(__UTILS__)
#define __UTILS__

#include <iostream>

class Utils
{
public:
    // Print value
    static void print(bool val, std::string prefix = "")
    {
        if (val)
            std::cout << prefix << "true" << std::endl;
        else
            std::cout << prefix << "false" << std::endl;
    }

    // Print value
    template <typename T>
    static void print(T const(&buffer), std::string prefix = "")
    {
        std::cout << prefix << buffer << std::endl;
    }

    /**
     * print
     * * Print array value to output stream
     * ? The methode is native to futur program
     * TODO: Refactor this method so that is very generic to array values
     * TODO: Refactor this method so that print char* value 
     * @param arr The param is values use to show value to output
     * @param prefix That is value prefix item value to array
     * @param toDisplay That param is to print to output or return stream
     * @param showIndex That param is to print a index of item to array
     */
    template <typename T, size_t n>
    static void print(T const (&arr)[n], std::string prefix = "", bool toDisplay = false, bool showIndex = false)
    {
        if (n > 0)
        {
            std::cout << prefix << "{" << std::endl;
            for (size_t i = 0; i < n - 1; i++)
            {
                std::cout << prefix << "  " << arr[i];
                std::cout << ", " << std::endl;
            }
            std::cout << prefix << "  " << arr[n - 1] << std::endl;
            std::cout << prefix << "}" << std::endl;
        }
        else
        {
            std::cout << prefix
                      << "{"
                      << "}" << std::endl;
        }
    }
};

#endif