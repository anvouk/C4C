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

/*------------------------------------------------------------------------------
	parameters
------------------------------------------------------------------------------*/

/**
 * Description:
 * 		The container's struct name.
 *
 * Expected type:
 * 		<name>
 *
 * Examples:
 * 		my_int_vec
 * 		x_list
 */
/*
#define C4C_PARAM_STRUCT_NAME
*/

/**
 * Description:
 * 		The container's functions' prefix.
 *
 * Expected type:
 * 		<name>
 *
 * Examples:
 * 		my_vec
 * 		t1lst
 */
/*
#define C4C_PARAM_PRFIX
*/

/*------------------------------------------------------------------------------
	parameters checks
------------------------------------------------------------------------------*/

#ifndef C4C_PARAM_STRUCT_NAME
#  error C4C_PARAM_STRUCT_NAME must be defined for the current container.
#endif

#ifndef C4C_PARAM_PREFIX
#  error C4C_PARAM_PREFIX must be defined for the current container.
#endif
