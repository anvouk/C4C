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

#ifndef __C4C_CONFIG_H__
#define __C4C_CONFIG_H__

/**
 * @file
 *
 * Common macro patterns:<br>
 * - Macros prefixed with an underscore must not be modified.
 * - Macros postfixed with an underscore are for internal usage.
 * - Macros prefixed and postfixed with a double underscore are header guards.
 * - Macros prefixed with '_C4C_SETTINGS_' can be defined before including the 
 *   header to enable some frequently used pattern.
 * - Files with the .inl extension are 'template' headers. Include them in the project,
 *   look at the end of those file and you'll see macros like '#undef C4C_PARAM_xxx' each
 *   with its own comment specifing what it does and what values you can put in (with some
 *   examples too). These macros must be correctly #defined before including the .inl file.
 * - Macros starting with 'C4C_' can be custom defined before including the .h file
 *   to customize their behaviour.
 *
 * @note This library uses <a href="https://semver.org/">Semantic Versioning 2.0.0</a>
 */

#define _C4C_STR_(x) #x
#define _C4C_STR _C4C_STR_

#define _C4C_CONCAT_(a, b) a##b
#define _C4C_CONCAT _C4C_CONCAT_

#define _C4C_VERSION_MAJOR 0
#define _C4C_VERSION_MINOR 3
#define _C4C_VERSION_PATCH 0
#define _C4C_VERSION_STATE "alpha"

#define _C4C_VERSION_STR \
	_C4C_STR(_C4C_VERSION_MAJOR) "." \
	_C4C_STR(_C4C_VERSION_MINOR) "." \
	_C4C_STR(_C4C_VERSION_PATCH) "-" \
	_C4C_VERSION_STATE

#define _C4C_VERSION_MAKE(maj, min, patch) \
	((maj) << 16) | ((min) << 8) | (patch))

/*------------------------------------------------------------------------------
	C4C errors API
------------------------------------------------------------------------------*/

typedef enum {
	/* <= 0 is an error. Check the function's doc for more info. */
	c4c_success = 1
	/* > 1 is a success but a corner case happened.
	* Might not get what you expected. Check the function's doc for more info.
	*/
} c4c_res_t;

#define c4c_succeeded(fn) \
	((fn) >= c4c_success)

#endif /* __C4C_CONFIG_H__ */
