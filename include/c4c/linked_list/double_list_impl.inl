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
 * This file is part of the C4C library (https://github.com/QwertyQaz414/C4C).
 */

/*
 * This header has been heavily inspired by linux's linked list
 */

#include "c4c/internal/common_headers.h"

#include <stddef.h> /* for NULL */

/*------------------------------------------------------------------------------
	params
------------------------------------------------------------------------------*/

#include "c4c/internal/params/default.h"
#include "c4c/internal/params/content.h"

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
		C4C_THIS first = list->next; \
		C4C_THIS last = list->prev; \
		C4C_THIS at = head->next; \
		first->prev = head; \
		head->next = first; \
		last->next = at; \
		at->prev = last; \
	} while (0)

/*------------------------------------------------------------------------------
    linked list functions implementation
------------------------------------------------------------------------------*/

C4C_METHOD(void, _init, C4C_THIS head)
{
	head->next = head;
	head->prev = head;
}

C4C_METHOD(void, _add, C4C_THIS head, C4C_THIS new_list)
{
	_list_add_(new_list, head, head->next);
}

C4C_METHOD(void, _add_tail, C4C_THIS head, C4C_THIS new_list)
{
	_list_add_(new_list, head->prev, head);
}

C4C_METHOD(void, _delete, C4C_THIS entry)
{
	_list_delete_(entry->prev, entry->next);
	entry->next = NULL;
	entry->prev = NULL;
}

C4C_METHOD(void, _move, C4C_THIS head, C4C_THIS list)
{
	_list_delete_(list->prev, list->next);
	C4C_METHOD_CALL(_add, head, list);
}

C4C_METHOD(void, _move_tail, C4C_THIS head, C4C_THIS list)
{
	_list_delete_(list->prev, list->next);
	C4C_METHOD_CALL(_add_tail, head, list);
}

C4C_METHOD(void, _splice, C4C_THIS head, C4C_THIS list)
{
	if (!c4c_list_is_empty(list))
		_list_splice_(list, head);
}

/* undef static functions macros */
#undef _list_add_
#undef _list_delete_
#undef _list_splice_

/*------------------------------------------------------------------------------
	undef header params
------------------------------------------------------------------------------*/

#include "c4c/internal/common_headers_undef.h"

#include "c4c/internal/params/default_undef.h"
#include "c4c/internal/params/content_undef.h"
