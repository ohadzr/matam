/**************************************
 *       Header files include         *
 **************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <../utilities,h>
#include "../map_mtm.h"
#include "test_utilities.h"
#include "../utilities.h"

/**************************************
 *              Defines               *
 **************************************/

#define MIN_DAY 1
#define MAX_DAY 31
#define MONTH_NUM 12
#define LEAP_CALCULATION ( ( !(year%4) && (year%100) ) ||                      \
                             ( (year%100) && (year%400) ) )
#define RELEASE_FOOD( food ) {                                                 \
   foodDestroy( map );                                                         \
   return NULL;                                                               \
}

#define FIRST 1
#define SECOND -1
#define EQUAL 0
#define FEB_MAX 29

/**************************************
 *              Structs               *
 **************************************/

typedef struct date {
    int day;
    int month;
    int year;
}*Date;

typedef struct food_item {
    char* name;
    int quantity;
    Date expiration_date;
}*Food;

/**************************************
 *          Date Functions            *
 **************************************/

/**
 * function check if year is a leap year.
 * @param year - the checked year.
 * @return
 * true if year if a leap year, false else.
 */
static bool yearIsLeap( int year ) {
    return LEAP_CALCULATION;
}

/**
 * function check if day has valid value.
 * @param day - the value to check.
 * @return
 * true if valid, false else.
 */
static bool dayIsValidCheck( int day , int month , int year ) {
    if ( ! ( (day <= MAX_DAY) && (day >= MIN_DAY) ) ) return false;
    switch ( month ) {
        case ( 1 ) : if ( day <= MAX_DAY ) return true;
        case ( 3 ) : if ( day <= MAX_DAY ) return true;
        case ( 4 ) : if ( day <= (MAX_DAY-1) ) return true;
        case ( 5 ) : if ( day <= MAX_DAY ) return true;
        case ( 6 ) : if ( day <= (MAX_DAY-1) ) return true;
        case ( 7 ) : if ( day <= MAX_DAY ) return true;
        case ( 8 ) : if ( day <= MAX_DAY ) return true;
        case ( 9 ) : if ( day <= (MAX_DAY-1) ) return true;
        case ( 10 ) : if ( day <= MAX_DAY ) return true;
        case ( 11 ) : if ( day <= (MAX_DAY-1) ) return true;
        case ( 12 ) : if ( day <= MAX_DAY ) return true;
        case ( 2 ) :  if  ( yearIsLeap( year ) ) {
                if ( day <= FEB_MAX ) return true;
                if ( day <= (FEB_MAX-1) ) return true;
        }
    }
    return false;
}

/**
 * function check if month valid to the Gregorian Calendar values.
 * @param month - the parameter to check.
 * @return
 * true if valid, false else.
 */
static bool monthIsValidMonth( int month ) {
    return ( (month > 0) && (month <= MONTH_NUM) );
}

/**
 * function update the date element in a food item.
 * if date is valid ( was created by this function ) it will be treated as
 * valid in other functions.
 * @param day - will be the expiration date day.
 * @param month - will be the expiration date month.
 * @param year - will be the expiration date year.
 * @return
 * NULL - if memory allocation failed or if parameters were NULL or invalid.
 * return a new date else.
*/
static Date dateCreate( int day , int month , int year ) {
    if  (!month)  return NULL;
    if ( !dayIsValidCheck( day , month , year ) ) return NULL;
    if ( !monthIsValidMonth( month ) ) return NULL;

    Date new_date = malloc(sizeof(*new_date));
    if ( !new_date ) return NULL;

    new_date->day = day ;
    new_date->month = month  ;
    new_date->year = year ;

    return new_date;
}

/**
 * function free memory allocated to date.
 * @param date - date to free.
 */
static void dateFree( Date date ) {
    free( date );
}

/**
 * function copy a date.
 * if date is valid ( was copied by this function ) it will be treated as
 * valid in other functions.
 * @param date - date t copy.
 * @return
 * NULL - if date is NULL or if out of memory, copy_date else.
 */
static Date date_copy( Date date ) {
    if ( !date ) return NULL;
    return dateCreate( date->day , date->month , date->year );
}

/**
 * function compare dates.
 * @param food1 - first food item witch it's expiration_date will be compared.
 * @param food2 - second food item witch it's expiration_date will be compared.
 * @return
 * 1 if first date is later then the second date, -1 if the second is later and
 * 0 if the dates are equal.
 */
int dateCompare( Food food1 , Food food2 ) {
    assert( food1 && food2 );
    if ( food1->expiration_date->year > food2->expiration_date->year )
        return FIRST;
    if ( food1->expiration_date->year<food2->expiration_date->year )
        return SECOND;

    if ( food1->expiration_date->month > food2->expiration_date->month )
        return FIRST;
    if ( food1->expiration_date->month < food2->expiration_date->month )
        return SECOND;

    if ( food1->expiration_date->day > food2->expiration_date->day )
        return FIRST;
    if ( food1->expiration_date->day > food2->expiration_date->day )
        return SECOND;

    return EQUAL;
}

/**************************************
 *          Food Functions            *
 **************************************/

/**
 * function compare quantity .
 * @param food1 - first food item witch it's quantity will be compared.
 * @param food2 - second food item witch it's quantity will be compared.
 * @return
 * 1 if first quantity is bigger then the second quantity, -1 if the second
 * is bigger and 0 if the quantity are equal.
 */
int quantityCompare( Food food1 , Food food2 ) {
    assert( food1 && food2 );
    if ( food1->quantity > food2->quantity ) return FIRST;
    if ( food1->quantity > food2->quantity ) return SECOND;

    return EQUAL;
}

/**
 * function compare names by lexicographical order.
 * @param food1 - first food item witch it's name will be compared.
 * @param food2 - second food item witch it's name will be compared.
 * @return
 * 1 if first name is bigger then the second name, -1 if the second
 * is bigger and 0 if the names are equal.
 */
int nameCompare(  Food food1 , Food food2 ) {
    assert( food1 && food2 );
    int result = strcmp( food1->name , food2->name );
    if ( result > 0 )  return FIRST;
    if ( result < 0 ) return SECOND;

    return EQUAL;
}

/**
 * function create new food.
 * if food is valid ( was created by this function ) it will be treated as
 * valid in other functions.
 * @param name - will be the doods name.
 * @param quantity  - will be food number.
 * @param date - expiration date of food.
 * @return
 * NULL - if memory allocation failed or if parameters were NULL or invalid.
 * return a new food else.
 */
static Food foodCreate( char* name , int quantity , Date expiration_date ) {
    if ( (!name) || (!expiration_date) || (!strlen(name)) ) return NULL;
    if ( quantity < 0 )  return NULL;
    Food new_food = malloc(sizeof(*new_food));
    if ( !new_food ) return NULL;

    new_food->quantity = quantity;
    new_food->expiration_date = date_copy( expiration_date );
    if( !new_food->expiration_date ) RELEASE_FOOD;

    new_food->name = stringCopy( name );
    if ( !new_food->name ) RELEASE_FOOD;

    return new_food;
}

/**
 * function free all memory allocated to given food.
 * @param food - the food to be destroy ( or eaten :) )
 */
static void foodDestroy( Food food ) {
    if ( !food ) return;
    dateFree( food->expiration_date );
    free( food );
}

/**
 * the dream function that can copy given food.
 * if food is valid ( was created by this function ) it will be treated as
 * valid in other functions.
 * @param food - the food to be copied.
 * @return
 * NULL - if food was NULL or if memory allocation failed.
 * copy of the given food else.
 */
static Food foodCopy( Food food ) {
    if ( !food ) return NULL;
    return foodCreate( food->name , food->quantity , food->expiration_date);
}


static bool testDateCombo() {
    bool result = true;
/* -----------------------  initialization  ----------------------- */

/* ----------------------------- tests ---------------------------- */

/* ------------------------  destruction  ------------------------- */

    return result;
}

/**************************************
 *    test Functions for Data Type    *
 **************************************/

int main() {
    RUN_TEST(testDateCombo);
    RUN_TEST(testFoodCombo);
    RUN_TEST(testGenericMapCombo);
    return 0;
}




