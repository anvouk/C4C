/*
 * The MIT License
 *
 * Copyright 2018 Andrea Vouk.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "c4c/config.h"
#include "c4c/function.h"
#include "c4c/struct.h"

#include "c4c/container_helpers.h"

#include <stddef.h> /* For size_t */

/*
Parameters:

#define C4C_PARAM_LIST_CONTENT 
#define C4C_PARAM_LIST_PREFIX 
#define C4C_PARAM_LIST_STRUCT_NAME 
*/

/*------------------------------------------------------------------------------
   linked list struct definition
------------------------------------------------------------------------------*/

/**
 * Double linked list.
 */
C4C_STRUCT_BEGIN(C4C_PARAM_LIST_STRUCT_NAME)
	C4C_PARAM_LIST_CONTENT
	struct C4C_PARAM_LIST_STRUCT_NAME* next;
	struct C4C_PARAM_LIST_STRUCT_NAME* prev;
C4C_STRUCT_END(C4C_PARAM_LIST_STRUCT_NAME)

/*------------------------------------------------------------------------------
    linked list functions
------------------------------------------------------------------------------*/

/**
 * Prepare the linked list for usage.
 * 
 * @param head The linked list head.
 */
C4C_METHOD(C4C_PARAM_LIST_PREFIX, void, _init, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* head);

/**
 * Insert a new entry after the specified head.
 * 
 * @param head list Head to add it after.
 * @param new_list New entry to be added.
 */
C4C_METHOD(C4C_PARAM_LIST_PREFIX, void, _add, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* head, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* new_list);

/**
 * Insert a new entry before the specified head.
 * 
 * @param head list Head to add it before.
 * @param new_list New entry to be added.
 */
C4C_METHOD(C4C_PARAM_LIST_PREFIX, void, _add_tail, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* head, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* new_list);

/**
 * Deletes entry from list.
 * 
 * @param entry The element to delete from the list.
 * 
 * @warning c4c_list_is_empty on entry does not return true after this, the entry 
 *          is in an undefined state (next and prev are set to NULL).
 */
C4C_METHOD(C4C_PARAM_LIST_PREFIX, void, _delete, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* entry);

/**
 * Delete from one list and add as another's head.
 * 
 * @param head The head that will precede our entry.
 * @param list The entry to move.
 */
C4C_METHOD(C4C_PARAM_LIST_PREFIX, void, _move, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* head, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* list);

/**
 * Delete from one list and add as another's tail.
 * 
 * @param head The head that will follow our entry.
 * @param list The entry to move.
 */
C4C_METHOD(C4C_PARAM_LIST_PREFIX, void, _move_tail, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* head, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* list);

/**
 * Join two lists.
 * 
 * @param head The place to add it in the first list.
 * @param list The new list to add.
 */
C4C_METHOD(C4C_PARAM_LIST_PREFIX, void, _splice, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* head, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* list);

/*------------------------------------------------------------------------------
    linked list generic functions
------------------------------------------------------------------------------*/

#ifndef c4c_list_is_empty
/**
 * Test whether a list is empty.
 * 
 * @param head The list to test.
 * 
 * @return 1 if the list is empty. 0 otherwise.
 */
#define c4c_list_is_empty(head) \
	((head)->next == (head))
#endif

#ifndef c4c_list_foreach
/**
 * Iterate over a list.
 * 
 * @param head The head of the list.
 * @param pos The struct to use as a loop counter.
 */
#define c4c_list_foreach(head, pos) \
	for (pos = (head)->next; pos != (head); pos = pos->next)
#endif

#ifndef c4c_list_foreach_backward
/**
 * Iterate over a list backwards.
 * 
 * @param head The head of the list.
 * @param pos The struct to use as a loop counter.
 */
#define c4c_list_foreach_backward(head, pos) \
	for (pos = (head)->prev; pos != (head); pos = pos->prev)
#endif

#ifndef c4c_list_foreach_safe
/**
 * Iterate over a list safe against removal of list entry.
 * 
 * @param head The head of the list.
 * @param pos The struct to use as a loop counter.
 * @param n Another struct to use as temporary storage.
 */
#define c4c_list_foreach_safe(head, pos, n) \
	for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)
#endif

#ifndef c4c_list_foreach_safe_backward
/**
 * Iterate over a list backwards safe against removal of list entry.
 * 
 * @param head The head of the list.
 * @param pos The struct to use as a loop counter.
 * @param n	Another struct to use as temporary storage.
 */
#define c4c_list_foreach_safe_backward(head, pos, n) \
	for (pos = (head)->prev, n = pos->prev; pos != (head); pos = n, n = pos->prev)
#endif

/*------------------------------------------------------------------------------
    undef header params
------------------------------------------------------------------------------*/

/* The list content (type variable_name;) (eg. int a;, char a; long b;, or custom structs */
#undef C4C_PARAM_LIST_CONTENT

/* The list functions' prefix (name) (eg. my_list) */
#undef C4C_PARAM_LIST_PREFIX 

/* The list struct name (name) (eg. my_int_list, x_list) */
#undef C4C_PARAM_LIST_STRUCT_NAME
