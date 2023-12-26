#pragma once

#include <map>
#include <string>

namespace Project {

const std::map<std::string, bool> PRIMES_DATA = {
    {"2", true},
    {"3", true},
    {"5", true},
    {"6", false},
    {"7", true},
    {"8", false},
    {"9", false},
    {"11", true},
    {"433", true},
    {"561", false},
    {"829", true},
    {"29341", false},
    {"63973", false},
    {"512461", false},
    {"4257452468389", true},
    {"2428095424619", true},
    {"53982894593057", true},
};

}