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

#ifndef C4C_METHOD
#define C4C_METHOD(prefix, rettype, suffix, ...) \
	C4C_FUNCTION(rettype, _C4C_CONCAT(prefix, suffix), __VA_ARGS__)
#endif

#ifndef C4C_METHOD_CALL
#define C4C_METHOD_CALL(prefix, suffix, ...) \
	C4C_FUNCTION_CALL(_C4C_CONCAT(prefix, suffix), __VA_ARGS__)
#endif

#ifndef C4C_METHOD_INLINE
#define C4C_METHOD_INLINE(prefix, rettype, suffix, ...) \
	C4C_FUNCTION_INLINE(rettype, _C4C_CONCAT(prefix, suffix), __VA_ARGS__)
#endif

#ifndef C4C_METHOD_INLINE_CALL
#define C4C_METHOD_INLINE_CALL(prefix, suffix, ...) \
	C4C_FUNCTION_INLINE_CALL(_C4C_CONCAT(prefix, suffix), __VA_ARGS__)
#endif
