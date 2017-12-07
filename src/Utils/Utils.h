//============================================================================
// Name        : Utils.h
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Utility functions
//============================================================================
#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include <string>
#include <string.h>

using namespace std;

typedef vector<string> Strings;

Strings get_prefix_matching_directories(const char* path, const char* prefix);

#endif