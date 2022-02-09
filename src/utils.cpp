
#include "utils.hpp"


std::string utils::pad(std::string str, size_t const num, char const padding_char) {
    if(!(num > str.size())) return str;

    size_t nb_chars = num - str.size();
    str.insert(0, nb_chars / 2, padding_char);
    str.append((nb_chars+1) / 2, padding_char);
    return str;
}


InvalidAction::InvalidAction(std::string msg) : msg(msg) { }

InvalidAction::~InvalidAction() { }

const char* InvalidAction::what() const throw() {
    return msg.c_str();
}
