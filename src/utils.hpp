#ifndef HEADER_UTILS
#define HEADER_UTILS

#include <algorithm>
#include <exception>
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

    extern std::vector<std::string> vector_logs;

    std::string pad(std::string str, size_t const num, char const padding_char=' ');
    std::string to_lower(std::string str);
};


class InvalidAction : public std::exception {
    public:
        InvalidAction(std::string msg);
        ~InvalidAction();

        const char* what() const throw();
        const std::string what_str() const throw();

    private:
        std::string msg;
};


#endif // HEADER_UTILS
