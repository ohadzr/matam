
#ifndef MATAM_ITEM_H
#define MATAM_ITEM_H

/**************************************
 *       Header files include         *
 **************************************/

#include "exceptions.h"

/**************************************
 *       Namespace and Classes        *
 **************************************/

namespace mtm {
    namespace pokemongo {
        class Item {
        private:
            std::string type;
            int level;
        public:
            Item(const std::string &type, const int level);

            ~Item();

            Item(const Item &item);

            std::string getType();

            int getLevel();
        };
    }
}

#endif //MATAM_ITEM_H
