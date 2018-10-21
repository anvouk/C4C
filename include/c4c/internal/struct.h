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

#ifdef C4C_FEATURE_STRUCT_NO_ALIAS

#ifndef C4C_STRUCT_DECLARE
#define C4C_STRUCT_DECLARE(name) struct name
#endif

#ifndef C4C_STRUCT_BEGIN
#define C4C_STRUCT_BEGIN(name) \
	struct name {
#endif

#ifndef C4C_STRUCT_END
#define C4C_STRUCT_END(name) \
	};
#endif

#else

#ifndef C4C_STRUCT_DECLARE
#define C4C_STRUCT_DECLARE(name) name
#endif

#ifndef C4C_STRUCT_BEGIN
#define C4C_STRUCT_BEGIN(name) \
	typedef struct name {
#endif

#ifndef C4C_STRUCT_END
#define C4C_STRUCT_END(name) \
	} name;
#endif

#endif /* C4C_FEATURE_STRUCT_NO_ALIAS */ 
