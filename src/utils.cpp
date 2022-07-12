
#include "utils.hpp"


int utils::randint(int min, int max) {
    if (max == -1) {
        max = min;
        min = 0;
    }

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uniform_law(min, max);

    return uniform_law(rng);
}

std::string utils::pad(std::string str, size_t const num, char const padding_char) {
    if(!(num > str.size())) return str;

    size_t nb_chars = num - str.size();
    str.insert(0, nb_chars / 2, padding_char);
    str.append((nb_chars+1) / 2, padding_char);
    return str;
}

std::string utils::to_lower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

std::vector<std::string> utils::vector_logs;


InvalidAction::InvalidAction(std::string msg) : msg(msg) { }

InvalidAction::~InvalidAction() { }

const char* InvalidAction::what() const throw() {
    return msg.c_str();
}

const std::string InvalidAction::what_str() const throw() {
    return msg;
}
