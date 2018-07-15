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

/*
 * This header has been heavily inspired by linux's linked list
 */

#include "c4c/config.h"
#include "c4c/function.h"
#include "c4c/struct.h"

/* we want a custom version of this unless the user has already a custom one */
#ifndef _C4C_SETTINGS_CONTAINER_LINKED_LIST_USE_CUSTOM_METHOD
#define C4C_METHOD(prefix, rettype, suffix, ...) \
	C4C_FUNCTION(rettype, _C4C_CONCAT(prefix, suffix), __VA_ARGS__)
#endif
#include "c4c/container_helpers.h"

#include <stddef.h> /* For NULL */

/*
Parameters:

#define C4C_PARAM_LIST_CONTENT 
#define C4C_PARAM_LIST_PREFIX 
#define C4C_PARAM_LIST_STRUCT_NAME 
*/

/*------------------------------------------------------------------------------
    linked list static functions
------------------------------------------------------------------------------*/

/*
 * Insert a new entry between two known consecutive entries. 
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
#define _list_add_(new_list, prev_one, next_one) \
	do { \
		next_one->prev = new_list; \
		new_list->next = next_one; \
		new_list->prev = prev_one; \
		prev_one->next = new_list; \
	} while (0)

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
#define _list_delete_(prev_one, next_one) \
	do { \
		next_one->prev = prev_one; \
		prev_one->next = next_one; \
	} while(0)

#define _list_splice_(list, head) \
	do { \
		C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* first = list->next; \
		C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* last = list->prev; \
		C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* at = head->next; \
		first->prev = head; \
		head->next = first; \
		last->next = at; \
		at->prev = last; \
	} while (0)

/*------------------------------------------------------------------------------
    linked list functions implementation
------------------------------------------------------------------------------*/

C4C_METHOD(C4C_PARAM_LIST_PREFIX, void, _init, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* head)
{
	head->next = head;
	head->prev = head;
}

C4C_METHOD(C4C_PARAM_LIST_PREFIX, void, _add, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* head, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* new_list)
{
	_list_add_(new_list, head, head->next);
}

C4C_METHOD(C4C_PARAM_LIST_PREFIX, void, _add_tail, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* head, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* new_list)
{
	_list_add_(new_list, head->prev, head);
}

C4C_METHOD(C4C_PARAM_LIST_PREFIX, void, _delete, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* entry)
{
	_list_delete_(entry->prev, entry->next);
	entry->next = NULL;
	entry->prev = NULL;
}

C4C_METHOD(C4C_PARAM_LIST_PREFIX, void, _move, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* head, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* list)
{
	_list_delete_(list->prev, list->next);
	C4C_METHOD_CALL(C4C_PARAM_LIST_PREFIX, _add, head, list);
}

C4C_METHOD(C4C_PARAM_LIST_PREFIX, void, _move_tail, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* head, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* list)
{
	_list_delete_(list->prev, list->next);
	C4C_METHOD_CALL(C4C_PARAM_LIST_PREFIX, _add_tail, head, list);
}

C4C_METHOD(C4C_PARAM_LIST_STRUCT_NAME, void, _splice, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* head, C4C_STRUCT_DECLARE(C4C_PARAM_LIST_STRUCT_NAME)* list)
{
	if (!c4c_list_is_empty(list))
		_list_splice_(list, head);
}

/* remove the custom version of this unless it's the user's */
#ifndef _C4C_SETTINGS_CONTAINER_LINKED_LIST_USE_CUSTOM_METHOD
#undef C4C_METHOD
#endif

/* undef static functions macros */
#undef _list_add_
#undef _list_delete_
#undef _list_splice_

/*------------------------------------------------------------------------------
    undef header params
------------------------------------------------------------------------------*/

/* The list content (type variable_name;) (eg. int a;, char a; long b;, or custom structs */
#undef C4C_PARAM_LIST_CONTENT

/* The list functions' prefix (name) (eg. my_list) */
#undef C4C_PARAM_LIST_PREFIX 

/* The list struct name (name) (eg. my_int_list, x_list) */
#undef C4C_PARAM_LIST_STRUCT_NAME
