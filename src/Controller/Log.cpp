// Name        : Log.cpp
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Singleton class containing global variables
//============================================================================

#include <Log.h>

Log* Log::m_instance = NULL;

Log* Log::getInstance(const string& file_name) {
    if (m_instance == NULL) {
        m_instance = new Log(file_name);
    }

    return m_instance;
}

Log::Log(const string& log_file) : m_log_file(log_file) {
	m_foutP = new ofstream(m_log_file.c_str());

	if (m_foutP == NULL) {
		cout << "Could not open log file  "
				<< m_log_file << endl;
	}
}

void Log::write(const string& output) const {
	*m_foutP << output << endl;
}

void Log::close_writer() {
	delete m_instance;
}

Log::~Log() {
	m_foutP->close();
	if (m_foutP != NULL) delete m_foutP;
	m_instance = NULL;
}
