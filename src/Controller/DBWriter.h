//===============================================================================
// Name        : DBWriter.cpp
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Code to write a csv file containing profiling results
// ===============================================================================

#ifndef CONTROLLER_DBWRITER_H_
#define CONTROLLER_DBWRITER_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ProblemDB.h>

//#include <map>
//#include <GlobalSettings.h>
//#include <ProblemDB.h>


using namespace std;

class DBWriter {
	private:
		const string m_file_name;
		ofstream* m_foutP;
		//static DBWriter* m_instance;

		//struct ProblemData {
		typedef vector<float> TimeSeries;

		//	string fast_plan_dir;
		//	string slow_plan_dir;
		//	TimeSeries m_work_load;
		//};

		//typedef map<string, ProblemData*> Database;
		//Database m_sample_problem_db;

	public:
		//static ProblemDB* getInstance();
		//bool populate_db();
		//void clean_db();
	DBWriter(const string& file_name);
	void close_writer();
	~DBWriter();
	void write_header(const string& header) const;
	void write_line(const string sample_problem_path,
			const ProblemDB::ProblemData* data, bool use_reactive) const;
};



#endif /* CONTROLLER_DBWRITER_H_ */
