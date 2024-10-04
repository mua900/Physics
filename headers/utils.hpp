#pragma once

#include <cstddef>
#include <cstdint>
#include <cstddef>
#include <cmath>
#include <vector>
#include <array>

namespace utils
{
    float float_modulo(const float& number, const float& modulo);
    int float_modulo_i(const float& number, const float& modulo);

    short positive_modulo(const short& number, const short& modulo);
    int positive_modulo(const int& number, const int& modulo);
    unsigned int positive_modulo(const unsigned int& number, const unsigned int& modulo);
    long positive_modulo(const long& number, const long& modulo);
    unsigned long positive_modulo(const unsigned long& number, const unsigned long& modulo);

    template<typename T, std::size_t size>
    T& max_std_array(const std::array<T, size>& array);

    template<typename T, std::size_t size>
    T& min_std_array(const std::array<T, size>& array);

    bool float_equality(const float& value1, const float& value2);

    template<typename T>
    inline void swap(T& a, T& b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }

    template<typename T>
    struct id_value_pair
    {
        uint16_t id;
        T value;
    };

    template<typename T>
    uint16_t min_value_id(const std::vector<id_value_pair<T>>& pairs);

    template<typename T>
    uint16_t max_value_id(const std::vector<id_value_pair<T>>& pairs);

    template<typename T, size_t array_size>
    uint16_t min_value_id(const std::array<id_value_pair<T>, array_size>& pairs);

    template<typename T, size_t array_size>
    uint16_t max_value_id(const std::array<id_value_pair<T>, array_size>& pairs);
}