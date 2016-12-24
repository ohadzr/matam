//
// Created by ohad on 24-Dec-16.
//

#ifndef MATAM_UTILITIES_H
#define MATAM_UTILITIES_H

/**
 * Copy a given string
 *
 * @return
 *   NULL if str is NULL or memory allocation failed.
 *   copy of the str otherwise
 */
char* stringCopy(const char* str);

/**
 * Free the given str
 *
 */
void stringDestroy(char* str);


#endif //MATAM_UTILITIES_H
