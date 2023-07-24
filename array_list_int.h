/**
 *  \file array_list_int.h
 *
 *  \brief C dynamic array of int values library
 *
 * \author
 * \date:
 *
 */
#ifndef _ARRAY_LIST_INT_H_
#define _ARRAY_LIST_INT_H_

typedef struct array_list_int array_list_int;

/**
 * \brief Create a new list of int numbers.
 *
 * \return A pointer to a new list of int structure.
 */

array_list_int *array_list_create();

/**
 * \brief  Gets the value stored on index 'index'
 *
 * \param list A pointer to the list structure
 * \param index An integer with the index where to get the element
 * \param error A pointer to an integer to set error if it occur.
 * \return int The value stored on index 'index'
 */
int array_list_get(array_list_int *list, int index, int *error);

/**
 * \brief  Appends a new element to the end of the list.
 *
 * \param list A pointer to the list structure
 * \param value The value to be appended to 'list'
 * \return unsigned int
 */
unsigned int array_list_push_back(array_list_int *list, int i);

/**
 * \brief Removes the last element of the list.
 *
 * \param list A pointer to the list structure
 * \return unsigned int The total number of elements after removing the last one.
 */
unsigned int array_list_pop_back(array_list_int *list);

/**
 * \brief Gets the total number of values stored on the list 'list'
 *
 * \param list A pointer to the list structure.
 * \return unsigned int The total number of elements stored on 'list'.
 */
unsigned int array_list_size(array_list_int *list);

/**
 * \brief  Gets the index of  element 'element'.
 *
 * \param list A pointer to the list structure.
 * \param element The int number to search on the list
 * \return int  The index of element 'element' if element is in the range [0..size−1].
 * \todo Implement function.
 */
int array_list_find(array_list_int *list, int element);

/**
 * \brief Inserts int value 'value' at index 'index'. 'index' must
 *        be a valid index, between 0 and 'array_list_size'. If
 *        'index' equals to 'size' the function has the same
 *        effect of array_list_push_back().
 *
 * \param list  A pointer to the list structure.
 * \param index The index where to insert the element. Must be in the range [0..size]
 * \param value The int value to insert
 * \return unsigned int The new size of the list.
 * \todo Implement function.
 */
unsigned int array_list_insert_at(array_list_int *list, int index, int value);

/**
 * \brief Remove elemento at 'index' from 'list'. 'index' must
 *              be a valid index, between 0 and 'array_list_size'−1.
 *
 * \param list  A pointer to the list structure.
 * \param index The index where to insert the element. Must be in the range [0..size]
 * \return unsigned int The new size of the list.
 * \todo Implement function.
 */
unsigned int array_list_remove_from(array_list_int *list, int index);

/**
 * \brief Calculates the total mount of space reserved for 'list'
 *
 * \param list The list to get capacity.
 * \return unsigned int The total amount of space fot 'list'.
 */
unsigned int array_list_capacity(array_list_int *list);

/**
 * \brief Check the array_list_int 'list' occupation, in percent.
 *
 * \param list The 'list' to be checked.
 * \return double A number between 0.0 and 1.0, representing the
 * total space used as a percent from the reserved space.
 */
double array_list_percent_occupied(array_list_int *list);

/**
 * \brief Release total memory space reserved from 'list'
 *
 * \param list The list to be released
 * \todo
 */
void array_list_destroy(array_list_int *list);

#endif
