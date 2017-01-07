/**************************************
 *       Header files include         *
 **************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../map_mtm/map_mtm.h"
#include "../utilities.h"
#include "test_utilities.h"

/**************************************
 *              Defines               *
 **************************************/

#define MIN_DAY 1
#define MAX_DAY 31
#define MONTH_NUM 12
#define LEAP_CALCULATION ( ( !(year%4) && (year%100) ) ||                      \
                             ( (year%100) && (year%400) ) )

#define RELEASE_FOOD {                                                         \
   foodDestroy( new_food );                                                    \
   return NULL;                                                                \
}

#define FIRST 1
#define SECOND -1
#define EQUAL 0
#define FEB_MAX 29

/**************************************
 *              Structs               *
 **************************************/

typedef struct date_t {
	int day;
	int month;
	int year;
}*Date;

typedef struct food_item {
	char* name;
	int quantity;
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
static bool yearIsLeap(int year) {
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
		case ( 1 ) : if ( day <= MAX_DAY ) return true; break;
		case ( 3 ) : if ( day <= MAX_DAY ) return true; break;
		case ( 4 ) : if ( day <= (MAX_DAY-1) ) return true; break;
		case ( 5 ) : if ( day <= MAX_DAY ) return true; break;
		case ( 6 ) : if ( day <= (MAX_DAY-1) ) return true; break;
		case ( 7 ) : if ( day <= MAX_DAY ) return true; break;
		case ( 8 ) : if ( day <= MAX_DAY ) return true; break;
		case ( 9 ) : if ( day <= (MAX_DAY-1) ) return true; break;
		case ( 10 ) : if ( day <= MAX_DAY ) return true; break;
		case ( 11 ) : if ( day <= (MAX_DAY-1) ) return true; break;
		case ( 12 ) : if ( day <= MAX_DAY ) return true; break;
		case ( 2 ) :  if  ( yearIsLeap( year ) ) {
				if ( day <= FEB_MAX ) return true;
				if ( day <= (FEB_MAX-1) ) return true;
			} break;
		default : return false; break;
	}
	return false;
}

/**
 * function check if month valid to the Gregorian Calendar values.
 * @param month - the parameter to check.
 * @return
 * true if valid, false else.
 */
static bool monthIsValidMonth(int month) {
	return ((month > 0) && (month <= MONTH_NUM));
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
static Date dateCreate(int day, int month, int year) {
	if (!month)
		return NULL;
	if (!dayIsValidCheck(day, month, year))
		return NULL;
	if (!monthIsValidMonth(month))
		return NULL;
	// no check for year because maybe you are a time traveler

	Date new_date = malloc(sizeof(*new_date));
	if (!new_date)
		return NULL;

	new_date->day = day;
	new_date->month = month;
	new_date->year = year;

	return new_date;
}

/**
 * function free memory allocated to date.
 * @param date - date to free.
 */
static void dateFree(Date date) {
	free(date);
}

/**
 * function copy a date.
 * if date is valid ( was copied by this function ) it will be treated as
 * valid in other functions.
 * @param date - date t copy.
 * @return
 * NULL - if date is NULL or if out of memory, copy_date else.
 */
static Date dateCopy(Date date) {
	if (!date)
		return NULL;
	return dateCreate(date->day, date->month, date->year);
}

/**
 * function compare dates. function assert parameters not NULL.
 * @param date1 - first date.
 * @param date2 - second date.
 * @return
 * 1 if first date is later then the second date, -1 if the second is later and
 * 0 if the dates are equal.
 */
static int dateCompare(Date date1, Date date2) {
	assert(date1 && date2);
	if (date1->year > date2->year)
		return FIRST;
	if (date1->year < date2->year)
		return SECOND;

	if (date1->month > date2->month)
		return FIRST;
	if (date1->month < date2->month)
		return SECOND;

	if (date1->day > date2->day)
		return FIRST;
	if (date1->day > date2->day)
		return SECOND;

	return EQUAL;
}

/**************************************
 *          Food Functions            *
 **************************************/

/**
 * function compare names by lexicographical order. function assert parameters
 * not NULL.
 * @param food1 - first food item witch it's name will be compared.
 * @param food2 - second food item witch it's name will be compared.
 * @return
 * 1 if first name is bigger then the second name, -1 if the second
 * is bigger and 0 if the names are equal.
 */
int foodNameCompare(Food food1, Food food2) {
	assert(food1 && food2);
	int result = strcmp(food1->name, food2->name);
	if (result > 0)
		return FIRST;
	if (result < 0)
		return SECOND;

	return EQUAL;
}

/**
 * function free all memory allocated to given food.
 * @param food - the food to be destroy ( or eaten :) )
 */
static void foodDestroy(Food food) {
	if (food) {
		stringDestroy(food->name);
		free(food);
	}
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
static Food foodCreate(char* name, int quantity) {
	if ((!name) || (!strlen(name)))
		return NULL;
	if (quantity < 0)
		return NULL;
	Food new_food = malloc(sizeof(*new_food));
	if (!new_food)
		return NULL;

	new_food->quantity = quantity;

	new_food->name = stringCopy(name);
	if (!new_food->name)
		RELEASE_FOOD
	;

	return new_food;
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
static Food foodCopy(Food food) {
	if (!food)
		return NULL;
	return foodCreate(food->name, food->quantity);
}

/**************************************
 *   test Functions for Data Types    *
 **************************************/

static bool testDateCombo() {
	bool result = true;
	/* -----------------------  initialization  ----------------------- */
	Date date1 = dateCreate(-1, 12, 1999);
	Date date2 = dateCreate(7, 0, 1999);
	Date date3 = dateCreate(0, 9, 1999);
	Date date4 = dateCreate(6, 9, -1000);
	Date date5 = dateCreate(1, 3, 2005);
	Date date6 = dateCreate(1, 7, 2005);
	Date date7 = dateCreate(7, 7, 2005);
	Date date8 = dateCopy(date4);

	/* ----------------------------- tests ---------------------------- */
	TEST_DIFFERENT(result, date4, NULL);
	TEST_DIFFERENT(result, date5, NULL);
	TEST_DIFFERENT(result, date6, NULL);
	TEST_DIFFERENT(result, date7, NULL);
	TEST_DIFFERENT(result, date8, NULL);

	TEST_EQUALS(result, date1, NULL);
	TEST_EQUALS(result, date2, NULL);
	TEST_EQUALS(result, date3, NULL);

	TEST_EQUALS(result, dateCompare(date8, date4), 0);
	TEST_EQUALS(result, dateCompare(date7, date6), 1);
	TEST_EQUALS(result, dateCompare(date7, date4), 1);

	/* ------------------------  destruction  ------------------------- */
	dateFree(date1);
	dateFree(date2);
	dateFree(date3);
	dateFree(date4);
	dateFree(date5);
	dateFree(date6);
	dateFree(date7);
	dateFree(date8);

	return result;
}

static bool testFoodCombo() {
	bool result = true;
	/* -----------------------  initialization  ----------------------- */

	Food food1 = foodCreate("Shkshoka", 2);
	Food food2 = foodCreate("Pasta", 2);
	Food food3 = foodCreate("Teremiso", 3);
	Food food4 = foodCopy(food3);

	Food food5 = foodCreate("", 3);
	Food food6 = foodCreate( NULL, 3);
	Food food7 = foodCreate("Pizza", 3);

	/* ----------------------------- tests ---------------------------- */
	TEST_DIFFERENT(result, food1, NULL);
	TEST_DIFFERENT(result, food2, NULL);
	TEST_DIFFERENT(result, food3, NULL);
	TEST_DIFFERENT(result, food4, NULL);

	TEST_EQUALS(result, food5, NULL);
	TEST_EQUALS(result, food6, NULL);
    TEST_DIFFERENT(result, food7, NULL);

	TEST_EQUALS(result, foodNameCompare(food1, food4), -1);
	TEST_EQUALS(result, foodNameCompare(food3, food4), 0);

	/* ------------------------  destruction  ------------------------- */

	foodDestroy(food1);
	foodDestroy(food2);
	foodDestroy(food3);
	foodDestroy(food4);
	foodDestroy(food5);
	foodDestroy(food6);
	foodDestroy(food7);

	return result;
}

/**************************************
 *          Wrapper Functions         *
 **************************************/

/** wrapper function to dateCopy so it will be possible to work
 *  with map GDT.
 * @return
 * valid copyed date or NULL if date NULL or memory allocation failed.
 */
MapDataElement dateCopyElement(MapDataElement date_element) {
	return dateCopy((Date) date_element);
}

/** wrapper function to dateFree so it will be possible to work with
 *  map GDT*/
void dateFreeElement(MapDataElement date_element) {
	dateFree((Date) date_element);
}

/** wrapper function to foodCopy so it will be possible to work with
 *  map GDT
 *  @return
 * valid copyed food or NULL if food NULL or memory allocation failed .
 */
MapKeyElement foodCopyElement(MapKeyElement food_element) {
	return foodCopy((Food) food_element);
}

/** wrapper function to foodDestroy so it will be possible to work with
 * map GDT.
 */
void foodFreeElement(MapKeyElement food_element) {
	foodDestroy((Food) food_element);
}

/** wrapper function to foodNameCompare so it will be possible to work with
 * map GDT */
int foodNameCompareElement(MapKeyElement food_element1,
		MapKeyElement food_element2) {
	return foodNameCompare((Food) food_element1, (Food) food_element2);
}

/**************************************
 *              Map test              *
 **************************************/

static bool testGenericMapCombo() {
	bool result = true;
	/* -----------------------  initialization  ----------------------- */

	Food food1 = foodCreate("Pomela", 1);
	Food food2 = foodCreate("Pasta", 1);
	Food food3 = foodCreate("Pai", 3);
	Food food4 = foodCreate("Teremiso", 1);
	Food food5 = foodCopy(food3);

	Food food6 = foodCreate("", 3);
	Food food7 = foodCreate( NULL, 3);
	Food food8 = foodCreate("Pizza", 3);

	Date date1 = dateCreate(-1, 12, 1999);
	Date date2 = dateCreate(7, 0, 1999);
	Date date3 = dateCreate(0, 9, 1999);

	Date date4 = dateCreate(6, 9, -1000);
	Date date5 = dateCreate(1, 3, 2005);
	Date date6 = dateCreate(1, 7, 2005);
	Date date7 = dateCreate(7, 7, 2005);
	Date date8 = dateCopy(date4);

	Map refrigerator = mapCreate(foodCopyElement, dateCopyElement,
			foodFreeElement, dateFreeElement, foodNameCompareElement);

	/* ----------------------------- tests ---------------------------- */

	TEST_EQUALS(result, mapPut(refrigerator, food1, date5), MAP_SUCCESS);
	TEST_EQUALS(result, mapPut(refrigerator, food2, date5), MAP_SUCCESS);
	TEST_EQUALS(result, mapPut(refrigerator, food3, date6), MAP_SUCCESS);
	TEST_EQUALS(result, mapGetSize(refrigerator), 3);

	TEST_EQUALS(result, mapPut(refrigerator, food6, date6), MAP_NULL_ARGUMENT);
	TEST_EQUALS(result, mapPut(refrigerator, food7, date6), MAP_NULL_ARGUMENT);
	TEST_EQUALS(result, mapPut(refrigerator, food8, date7), MAP_SUCCESS);
	TEST_EQUALS(result, mapGetSize(refrigerator), 4);

	TEST_EQUALS(result, mapPut(refrigerator, food8, date1), MAP_NULL_ARGUMENT);
	TEST_EQUALS(result, mapPut(refrigerator, food8, date2), MAP_NULL_ARGUMENT);
	TEST_EQUALS(result, mapPut(refrigerator, food8, date3), MAP_NULL_ARGUMENT);
	TEST_EQUALS(result, mapGetSize(refrigerator), 4);

	TEST_EQUALS(result, mapPut(refrigerator, food2, date7), MAP_SUCCESS);
	TEST_EQUALS(result, mapGetSize(refrigerator), 4);
	Date test_date = mapGet(refrigerator, food2);
	TEST_EQUALS(result, dateCompare(test_date, date7), 0);

	Map refrigerator2 = mapCopy(refrigerator);
	TEST_EQUALS(result, mapGetSize(refrigerator2), 4);
	TEST_EQUALS(result, mapClear(refrigerator2), MAP_SUCCESS);
	TEST_EQUALS(result, mapGetSize(refrigerator2), 0);

	TEST_EQUALS(result, mapRemove(refrigerator2,food2),MAP_ITEM_DOES_NOT_EXIST);
	TEST_EQUALS(result, mapRemove(refrigerator,food6),MAP_NULL_ARGUMENT);
	TEST_EQUALS(result, mapRemove(refrigerator,food1),MAP_SUCCESS);
	test_date = mapGet(refrigerator, food1);
	TEST_EQUALS(result,test_date ,NULL);

	TEST_EQUALS(result, mapPut(refrigerator2, food8, date7), MAP_SUCCESS);
	TEST_EQUALS(result, mapPut(refrigerator2, food3, date4), MAP_SUCCESS);
	TEST_EQUALS(result, mapGetSize(refrigerator2), 2);

//	test_date = mapGetFirst(refrigerator2);
//	TEST_EQUALS(result, dateCompare(test_date, date4), 0);
//	test_date = mapGetNext(refrigerator2);
//	TEST_EQUALS(result, dateCompare(test_date, date7), 0);
//	test_date = mapGetNext(refrigerator2);
//	TEST_EQUALS(result, test_date, NULL);

	TEST_EQUALS(result, mapContains(refrigerator2, food3), true);
	TEST_EQUALS(result, mapContains(refrigerator2, food1), false);
	TEST_EQUALS(result, mapContains(refrigerator, food3), true);

	test_date = mapGet(refrigerator, food8);
	TEST_EQUALS(result, dateCompare(test_date, date7), 0);
	test_date = mapGet(refrigerator, food4);
	TEST_EQUALS(result, test_date, NULL);

	/* ------------------------  destruction  ------------------------- */

	mapDestroy(refrigerator);
	mapDestroy(refrigerator2);

	dateFree(date1);
	dateFree(date2);
	dateFree(date3);
	dateFree(date4);
	dateFree(date5);
	dateFree(date6);
	dateFree(date7);
	dateFree(date8);

	foodDestroy(food1);
	foodDestroy(food2);
	foodDestroy(food3);
	foodDestroy(food4);
	foodDestroy(food5);
	foodDestroy(food6);
	foodDestroy(food7);
	foodDestroy(food8);

	return result;
}

int main() {
	RUN_TEST(testDateCombo);
	RUN_TEST(testFoodCombo);
	RUN_TEST(testGenericMapCombo);
	return 0;
}
