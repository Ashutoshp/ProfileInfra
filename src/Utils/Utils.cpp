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
