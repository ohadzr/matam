
#ifndef MATAM_ITEM_H
#define MATAM_ITEM_H

/**************************************
 *       Header files include         *
 **************************************/

#include <iostream>
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
            /**
             * function create a new item.
             * @param type - the type of the new item.
             * @param level - the level of the new item.
             */
            Item(const std::string &type, const int level);
            /**
             * function destroy all memory allocations for item.
             */
            ~Item();
            /**
             * function copy a given item.
             * @param item - the item to be copyed.
             */
            Item(const Item &item);
            /**
             * function get item's type.
             * @return
             * return a string of the item type name.
             */
            std::string getType();
            /**
             * function get item's level.
             * @return
             * return an int with the value of item's level.
             */
            int getLevel();
        };
    }
}

#endif //MATAM_ITEM_H
