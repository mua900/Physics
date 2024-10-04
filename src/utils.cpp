#include <utils.hpp>

namespace utils
{
    float float_modulo(const float& number, const float& modulo)
    {
        return number - (int)(number / modulo) * modulo;
    }

    short positive_modulo(const short& number, const short& modulo)
    {
        return ((number % modulo) + modulo) % modulo;
    }

    int positive_modulo(const int& number, const int& modulo)
    {
        return ((number % modulo) + modulo) % modulo;
    }

    unsigned int positive_modulo(const unsigned int& number, const unsigned int& modulo)
    {
        return ((number % modulo) + modulo) % modulo;
    }

    long positive_modulo(const long& number, const long& modulo)
    {
        return ((number % modulo) + modulo) % modulo;
    }

    unsigned long positive_modulo(const unsigned long& number, const unsigned long& modulo)
    {
        return ((number % modulo) + modulo) % modulo;
    }

    template<typename T, std::size_t size>
    T& max_std_array(const std::array<T, size>& array)
    {
        const T& max = array[0];
        for (size_t i = 0; i < array.size(); ++i)
        {
            if (max < array[i])
            {
                max = array[i];
            }
        }
        return max;
    }

    template<typename T, std::size_t size>
    T& min_std_array(const std::array<T, size>& array)
    {
        const T& min = array[0];
        for (std::size_t i = 0; i < array.size(); ++i)
        {
            if (min > array[i])
            {
                min = array[i];
            }
        }
        return min;
    }

    bool float_equality(const float& value1, const float& value2)
    {
        return std::fabs(value1 - value2) < 0.001f;
    }

    int float_modulo_i(const float &number, const float &modulo)
    {
        return (int)(number - (int)(number / modulo));
    }

    template<typename T>
    uint16_t min_value_id(const std::vector<id_value_pair<T>>& pairs)
    {
        uint8_t min_index = 0;
        for (size_t i = 1; i < pairs.size(); i++)
        {
            if (pairs.at(i).value < pairs.at(min_index).value)
            {
                min_index = i;
            }
        }
        return pairs.at(min_index).id;
    }

    template<typename T>
    uint16_t max_value_id(const std::vector<id_value_pair<T>>& pairs)
    {
        uint8_t min_index = 0;
        for (size_t i = 1; i < pairs.size(); i++)
        {
            if (pairs.at(i).value > pairs.at(min_index).value)
            {
                min_index = i;
            }
        }
        return pairs.at(min_index).id;
    }

    template<typename T, size_t array_size>
    uint16_t min_value_id(const std::array<id_value_pair<T>, array_size>& pairs)
    {
        uint8_t min_index = 0;
        for (size_t i = 1; i < array_size; i++)
        {
            if (pairs.at(i).value < pairs.at(min_index).value)
            {
                min_index = i;
            }
        }
        return pairs.at(min_index).id;
    }

    template<typename T, size_t array_size>
    uint16_t max_value_id(const std::array<id_value_pair<T>, array_size>& pairs)
    {
        uint8_t max_index = 0;
        for (size_t i = 1; i < array_size; i++)
        {
            if (pairs.at(i).value > pairs.at(max_index).value)
            {
                max_index = i;
            }
        }
        return pairs.at(max_index).id;
    }
}
