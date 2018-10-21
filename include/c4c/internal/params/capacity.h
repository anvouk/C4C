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
 * 		The container's stored capacity.
 *
 * Expected type:
 * 		<size_t> (> 0)
 *
 * Examples:
 * 		10
 * 		64
 */
/*
#define C4C_PARAM_CAPACITY 
*/

/*------------------------------------------------------------------------------
	parameters checks
------------------------------------------------------------------------------*/

#ifndef C4C_PARAM_CAPACITY
#  error C4C_PARAM_CAPACITY must be defined for the current container.
#else
#  if C4C_PARAM_CAPACITY <= 0
#    error C4C_PARAM_CAPACITY must be greater than zero.
#  endif
#endif
