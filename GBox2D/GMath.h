/*
 MIT License
 
 Copyright (c) 2010 Andreas Loew / www.code-and-web.de
 
 For more information about htis module visit
 http://www.PhysicsEditor.de
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#pragma once

#include <stdlib.h>

/**
 * Swap two values
 * @param x first value
 * @param y second value
 */
template <class T> 
inline void swap(T& x, T& y)
{
    T t = x;
    x = y;
    y = t;
}

/**
 * Clamp a value between 2 values
 * @param v the value to clamp
 * @param min lower limit
 * @param max upper limit
 */
template <class T>
inline float clamp(T v, T min, T max)
{
    if(v < min)
    {
        return min;
    }
    if(v > max)
    {
        return max;
    }
    return v;
}

/**
 * Floating point ranged random
 * @param min minimum
 * @param max maximum
 * @result random number between min and max
 */
inline float gFloatRand(float min, float max)
{
    if(min > max)
    {
        swap(min, max);
    }
    float r = (float)rand() / (float)RAND_MAX;
    return (max-min) * r + min;
}

/**
 * Ranged random value
 * @param min minimum
 * @param max maximum
 * @result random number between min and max
 */
inline int gRangeRand(float min, float max)
{
    if(min > max)
    {
        swap(min, max);
    }
    float r = (float)rand() / (float)RAND_MAX;
    return (max-min) * r + min;
}

