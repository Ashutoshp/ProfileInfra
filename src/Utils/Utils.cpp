//============================================================================
// Name        : Utils.cpp
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Utility functions
//============================================================================

#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <Utils.h>
#include <string.h>
#include <assert.h>
#include <fstream>
#include <stdlib.h>

Strings get_prefix_matching_directories(const char* path, const char* prefix) {
	Strings directories;

	if (path != NULL && prefix != NULL) {
		DIR * d = opendir(path); // open the path

		if(d != NULL) {
			struct dirent * dir; // for the directory entries

			// if we were able to read something from the directory
			while ((dir = readdir(d)) != NULL) {
				string dir_name = dir->d_name;

				if(dir->d_type == DT_DIR && strncmp(dir_name.c_str(), prefix, strlen(prefix)) == 0) {
					char full_path[255];
					sprintf(full_path, "%s/%s", path, dir->d_name);
					//cout << full_path << endl;
					directories.push_back(full_path);
				}
			}

			closedir(d); // finally close the directory
		}
	}

    return directories;
}

bool find_string_in_strings(const string& str, const Strings& strings) {
	bool found = false;
	Strings::const_iterator itr = strings.begin();

	while (itr != strings.end()) {
		if (*itr == str) {
			found = true;
			break;
		}
		++itr;
	}

	return found;
}

double get_result_from_file(const string& file_name) {
	ifstream result_file (file_name.c_str(), std::ifstream::in);

	assert(result_file.good());

	string line;

	getline (result_file, line);
	assert(line == "Result");

	assert(result_file.good());
	getline (result_file, line);

	char* end;

	double result = strtod(line.c_str(), &end);

	return result;
}

