#ifndef HEADER_UTILS
#define HEADER_UTILS

#include <algorithm>
#include <random>
#include <string>
#include <vector>


namespace utils {

    template<typename T>
    std::vector<T> choice(std::vector<T> vect, int nb_samples=1) {
        std::vector<T> elts;
        std::sample(vect.begin(), vect.end(), std::back_inserter(elts),
                    nb_samples, std::mt19937{std::random_device{}()});
        return elts;
    }


    std::string pad(std::string str, size_t const num, char const padding_char=' ');
};

#endif // HEADER_UTILS
