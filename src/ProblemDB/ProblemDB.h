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
	//enum TrafficLoad {
	//        ZERO, TWENTYFIVE, FIFTY, SEVENTYFIVE, HUNDRED, INVALID
	//};

	struct ProblemData {
		string m_trace;
		string m_fast_plan_dir;
		string m_slow_plan_dir;

		float m_dimmer;

		unsigned m_server_A_count;
		unsigned m_server_B_count;
		unsigned m_server_C_count;

		unsigned m_server_A_status;
		unsigned m_server_B_status;
		unsigned m_server_C_status;

		unsigned m_server_A_load;
		unsigned m_server_B_load;
		unsigned m_server_C_load;

		float m_average_response_time;

		TimeSeries m_work_load;
	};

	typedef vector<string> Strings;

	static ProblemDB* getInstance();

	TimeSeries get_time_series(const string& problem_dir) const;
	const ProblemData* get_problem_data(const string& problem_dir) const;
	void get_sample_problem_dirs(Strings& problems) const;

	inline string get_header() const {return m_header;}
	unsigned get_serverA_status(const string& problem_dir) const;
	unsigned get_serverB_status(const string& problem_dir) const;
	unsigned get_serverC_status(const string& problem_dir) const;

	bool populate_db();
	void clean_db();


private:
	static ProblemDB* m_instance;
	string m_header;


	typedef map<string, ProblemData*> Database;
	Database m_sample_problem_db;
};


#endif /* PROBLEMDB_PROBLEMDB_H_ */
