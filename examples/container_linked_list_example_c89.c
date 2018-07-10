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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* FAC: Define custom implementations for some c4c macros. */
/* FAC: Enable/Disable/Change certain features by defining c4c settings macros. */

/* 1. Declare the container interface in a .h file. */
#define C4C_PARAM_DLIST_CONTENT int a; int b;
#define C4C_PARAM_DLIST_STRUCT_NAME my_list
#include "c4c/c4c_container_linked_list_decl.inl"

/* 2. Declare the container implementation in a .c file or in wherever you 
 *    want it to be. Make sure the macro params for the implementation have the
 *    same values as the interface ones.
 */
#define C4C_PARAM_DLIST_CONTENT int a; int b;
#define C4C_PARAM_DLIST_STRUCT_NAME my_list
#include "c4c/c4c_container_linked_list_impl.inl"

/* 4. Magic happens. You can now use the container for your type(s) :) */
int main(int argc, char* argv[])
{
	/* variables */
	my_list* iter;
	my_list head;
	my_list t1, t2, t3;
	
	/* init some custom types */
	head.a = 1;  head.b = 2;
	t1.a = 10;   t1.b = 20;
	t2.a = 100;  t2.b = 200;
	t3.a = 1000; t3.b = 2000;
	
	/* prepare the linked list for usage */
	my_list_init(&head);
	
	/* add your custom types to the list */
	my_list_add(&head, &t1);
	my_list_add(&head, &t2);
	my_list_add(&head, &t3);

	c4c_list_foreach(&head, iter) {
		printf("my_list (a: %d, b: %d)\n", iter->a, iter->b);
	}
	
	printf("\nis empty: %d\n\n", c4c_list_is_empty(&head));
	
	/* remove t2 from the list 'head'. t2 now is in an invalid state.
	 * Use my_list_init() to make a new list head.
	 */
	my_list_delete(&t2);
	
	c4c_list_foreach(&head, iter) {
		printf("my_list (a: %d, b: %d)\n", iter->a, iter->b);
	}

	getchar();
	return EXIT_SUCCESS;
}
