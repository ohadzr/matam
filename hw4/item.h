//
// Created by ohad on 21-Jan-17.
//

#ifndef MATAM_ITEM_H
#define MATAM_ITEM_H

#include "exceptions.h"

namespace mtm {
    namespace pokemongo {
        class Item {
        private:
            std::string type;
            int level;
        public:
            Item(const std::string &type, const int level) :
                    type(std::string(type)), level(level) {
                if (!(type == "POTION" || type == "CANDY") || level <= 0)
                    throw ItemInvalidArgsException();
            }

            ~Item() {}

            Item(const Item &item) :
                    type(std::string(item.type)), level(item.level) {}
            std::string getType() {
                return type;
            }
            int getLevel() {
                return level;
            }
        };
    }
}

#endif //MATAM_ITEM_H
