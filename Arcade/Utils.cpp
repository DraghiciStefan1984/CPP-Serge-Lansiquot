/*
 * Utils.cpp
 *
 *  Created on: Jan. 8, 2019
 *      Author: serge
 */

#include "Utils.h"
#include <cmath>
#include <algorithm>
#include <cctype>


bool IsEqual(float x, float y)
{
	return fabsf(x - y) < EPSILON;
}

bool IsGreaterThanOrEqual(float x, float y)
{
	return x > y || IsEqual(x, y);
}

bool IsLessThanOrEqual(float x, float y)
{
	return x < y || IsEqual(x, y);
}

float MillisecondsToSeconds(unsigned int milliseconds)
{
	return static_cast<float>(milliseconds) / 1000.0f;
}

unsigned int GetIndex(unsigned int width, unsigned int r, unsigned int c)
{
	return r * width + c;
}

bool StringCompare(const string& a, const string& b)
{
	if (a.length() == b.length())
	{
		return equal(b.begin(), b.end(), a.begin(), [](unsigned char a, unsigned char b) { return tolower(a) == tolower(b); });
	}
	return false;
}
