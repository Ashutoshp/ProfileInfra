//===============================================================================
// Name        : ProblemDB.cpp
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Code to read and store sample problem database from a csv file
// ===============================================================================

#include <ProblemDB.h>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <string>
#include <Log.h>

/* Null, because instance will be initialized on demand. */
ProblemDB* ProblemDB::m_instance = NULL;

ProblemDB* ProblemDB::getInstance() {
    if (m_instance == NULL) {
        m_instance = new ProblemDB();
    }

    return m_instance;
}

bool ProblemDB::populate_db() {
	bool success = false;

	string features_file_path = GlobalSettings::getInstance()->get_features_file();
	ifstream features_file (features_file_path.c_str(), std::ifstream::in);
	string line;

	unsigned line_count = 0;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	while ( features_file.good() ) {
		getline ( features_file, line);

		++line_count;

		if (line_count == 1) {
			// Store the header to write later.
			m_header = line;
			continue;
		}

	    if (line == "") {
	    	// Kind of Hack
	    	//assert(false);
	    	//delete data;
	    	//data = NULL;
	    	continue;
	    }

		string sample_problem_dir;
		ProblemData* data = new ProblemData();

	    //cout << line << endl;




		tokenizer tokens(line, boost::char_separator<char>(",\n"));
	    tokenizer::iterator it = tokens.begin();

	    if (it != tokens.end()) {
	    	data->m_trace = *it;
	        ++it;
	    } else {
	    	assert(false);
	    }

	    if (it != tokens.end()) {
	    	sample_problem_dir = *it;
	        ++it;
	    } else {
	    	assert(false);
	    }

	    if (it != tokens.end()) {
	       	data->m_fast_plan_dir = *it;
	        ++it;
	    } else {
	    	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_slow_plan_dir = *it;
	        ++it;
	    } else {
	    	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_dimmer = atof((*it).c_str());
	    	++it;
	    } else {
	       	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_server_A_count = strtoul ((*it).c_str(), nullptr, 0);
	    	++it;
	    } else {
	       	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_server_B_count = strtoul ((*it).c_str(), nullptr, 0);
	    	++it;
	    } else {
	       	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_server_C_count = strtoul ((*it).c_str(), nullptr, 0);
	    	++it;
	    } else {
	       	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_server_A_status = strtoul ((*it).c_str(), nullptr, 0);
	    	++it;
	    } else {
	       	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_server_B_status = strtoul ((*it).c_str(), nullptr, 0);
	    	++it;
	    } else {
	       	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_server_C_status = strtoul ((*it).c_str(), nullptr, 0);
	    	++it;
	    } else {
	       	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_server_A_load = strtoul ((*it).c_str(), nullptr, 0);
	    	++it;
	    } else {
	    	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_server_B_load = strtoul ((*it).c_str(), nullptr, 0);
	    	++it;
	    } else {
	       	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_server_C_load = strtoul ((*it).c_str(), nullptr, 0);
	    	++it;
	    } else {
	       	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_average_response_time = atof ((*it).c_str());
	    	++it;
	    } else {
	       	assert(false);
	    }

	    if (it != tokens.end()) {
	    	unsigned index = 0;

	    	while (index < GlobalSettings::getInstance()->get_time_series_length()) {
		       	//cout << "workload = " << *it << endl;
	    		(data->m_work_load).push_back(atof((*it).c_str()));
	        	++it;
	        	++index;
	    	}

	    	assert((data->m_work_load).size() == GlobalSettings::getInstance()->get_time_series_length());
	    } else {
	    	assert(false);
	    }

	    m_sample_problem_db.insert(std::make_pair(sample_problem_dir, data));
	}

	cout << "Read line_count = " << line_count << endl;

	features_file.close();

	return success;
}

void ProblemDB::clean_db() {
	Database::iterator it = m_sample_problem_db.begin();

	while(it != m_sample_problem_db.end()) {
		//cout << it->first << endl;
		if (it->second != NULL) {
			delete it->second;
		}
		++it;
	}

	m_sample_problem_db.clear();
}

void ProblemDB::get_sample_problem_dirs(Strings& problems) const {
	Database::const_iterator it = m_sample_problem_db.begin();

	while (it != m_sample_problem_db.end()) {
		problems.push_back(it->first);
		++it;
	}
}

ProblemDB::TimeSeries ProblemDB::get_time_series(const string& problem_dir) const {
	/*cout << problem_dir << endl;
	Database::const_iterator it = m_sample_problem_db.begin();

	while (it != m_sample_problem_db.end()) {
		cout << it->first << endl;
		//cout << it->second->m_work_load << endl;

		if (it->first == problem_dir) {
			cout << "Match found" << endl;
		}

		++it;
	}*/

	Database::const_iterator itr = m_sample_problem_db.find(problem_dir);
	assert(itr != m_sample_problem_db.end());

	return itr->second->m_work_load;
}

unsigned ProblemDB::get_serverA_status(const string& problem_dir) const {
	Database::const_iterator itr = m_sample_problem_db.find(problem_dir);
	assert(itr != m_sample_problem_db.end());

	return itr->second->m_server_A_status;
}

unsigned ProblemDB::get_serverB_status(const string& problem_dir) const {
	Database::const_iterator itr = m_sample_problem_db.find(problem_dir);
	assert(itr != m_sample_problem_db.end());

	return itr->second->m_server_B_status;
}

unsigned ProblemDB::get_serverC_status(const string& problem_dir) const {
	Database::const_iterator itr = m_sample_problem_db.find(problem_dir);
	assert(itr != m_sample_problem_db.end());

	return itr->second->m_server_C_status;
}

const ProblemDB::ProblemData* ProblemDB::get_problem_data(const string& problem_dir) const {
	Database::const_iterator itr = m_sample_problem_db.find(problem_dir);
	assert(itr != m_sample_problem_db.end());

	return itr->second;
}


