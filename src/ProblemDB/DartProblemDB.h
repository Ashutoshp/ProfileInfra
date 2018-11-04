/*
 * DartProblemDB.h
 *
 *  Created on: Nov 3, 2018
 *      Author: ashutosp
 */

#ifndef PROBLEMDB_DARTPROBLEMDB_H_
#define PROBLEMDB_DARTPROBLEMDB_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class DartProblemDB {
public:
	typedef vector<string> Threats;
	typedef vector<string> Targets;
	typedef vector<string> Strings;

	struct ProblemData {
		string m_seed;
		string m_altitude;
		string m_formation;
		string m_ecm;
		string m_incAlt_state;
		string m_decAlt_state;
		string m_incAlt2_state;
		string m_decAlt2_state;
		Threats m_threats;
		Targets m_targets;
	};

	//DartProblemDB();
	virtual ~DartProblemDB();

	static DartProblemDB* getInstance();

	Threats get_threats(const string& problem_dir) const;
	Targets get_targets(const string& problem_dir) const;

	const ProblemData* get_problem_data(const string& problem_dir) const;
	void get_sample_problem_dirs(Strings& problems) const;

	inline string get_header() const {return m_header;}

	string get_seed(const string& problem_dir) const;
	string get_altitude(const string& problem_dir) const;
	string get_formation(const string& problem_dir) const;
	string get_ecm(const string& problem_dir) const;
	string get_incAlt_state(const string& problem_dir) const;
	string get_decAlt_state(const string& problem_dir) const;
	string get_incAlt2_state(const string& problem_dir) const;
	string get_decAlt2_state(const string& problem_dir) const;

	bool populate_db();
	void clean_db();

private:
	static DartProblemDB* m_instance;
	string m_header;


	typedef map<string, ProblemData*> Database;
	Database m_sample_problem_db;
};

#endif /* PROBLEMDB_DARTPROBLEMDB_H_ */
