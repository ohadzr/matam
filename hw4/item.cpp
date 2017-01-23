/**************************************
 *       Header files include         *
 **************************************/

#include "item.h"

/**************************************
 *               Using                *
 **************************************/

using mtm::pokemongo::Item;

/**************************************
 *        Interface Functions         *
 **************************************/

Item::Item(const std::string &type, const int level) :
        type(std::string(type)), level(level) {
    if (!(type == "POTION" || type == "CANDY") || level <= 0)
        throw ItemInvalidArgsException();
}

Item::~Item() {}

Item::Item(const Item &item) :
        type(std::string(item.type)), level(item.level) {}

std::string Item::getType() {
    return type;
}

int Item::getLevel() {
    return level;
}