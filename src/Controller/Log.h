// Name        : Log.cpp
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Singleton class containing global variables
//============================================================================

#ifndef CONTROLLER_LOG_H_
#define CONTROLLER_LOG_H_

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Log {
private:
	static Log* m_instance;
	const string m_log_file;
	ofstream* m_foutP;

	Log(const string& file_name);
    ~Log();

public:
    /* Static access method. */
    static Log* getInstance(const string& file_name = "");
    static void close_writer();
    void write(const string& output) const;

};

#endif /* CONTROLLER_LOG_H_ */
