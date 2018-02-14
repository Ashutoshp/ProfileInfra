//===============================================================================
// Name        : ProblemDB.h
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Code to read and store sample problem database from a csv file
// ===============================================================================

#ifndef PROBLEMDB_PROBLEMDB_H_
#define PROBLEMDB_PROBLEMDB_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <GlobalSettings.h>


using namespace std;

class ProblemDB {

public:
	typedef vector<float> TimeSeries;
	typedef vector<string> Strings;

	static ProblemDB* getInstance();

	TimeSeries get_time_series(const string& problem_dir) const;
	void get_sample_problem_dirs(Strings& problems) const;

	bool populate_db();
	void clean_db();


private:
	static ProblemDB* m_instance;

	struct ProblemData {
		string fast_plan_dir;
		string slow_plan_dir;
		TimeSeries m_work_load;
	};

	typedef map<string, ProblemData*> Database;
	Database m_sample_problem_db;
};


#endif /* PROBLEMDB_PROBLEMDB_H_ */
