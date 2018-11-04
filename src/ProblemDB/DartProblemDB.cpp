/*
 * DartProblemDB.cpp
 *
 *  Created on: Nov 3, 2018
 *      Author: ashutosp
 */

#include <DartProblemDB.h>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <string>
#include <Log.h>
#include <GlobalSettings.h>

/* Null, because instance will be initialized on demand. */
DartProblemDB* DartProblemDB::m_instance = NULL;

DartProblemDB* DartProblemDB::getInstance() {
    if (m_instance == NULL) {
        m_instance = new DartProblemDB();
    }

    return m_instance;
}

DartProblemDB::~DartProblemDB() {
	// TODO Auto-generated destructor stub
}

bool DartProblemDB::populate_db() {
	bool success = false;

	string features_file_path = GlobalSettings::getInstance()->get_features_file();
	ifstream features_file (features_file_path.c_str(), std::ifstream::in);
	string line;

	unsigned line_count = 0;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	while ( features_file.good() ) {
		getline (features_file, line);

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

		// Seed	 Directory	 altitude	 formation	 ecm	 incAlt_state	 decAlt_state
		//incAlt2_state	 decAlt2_state	 TR1	 TH1	 TR2	 TH2	 TR3	 TH3
		//TR4	 TH4	 TR5	 TH5	 TR6	 TH6	 TR7	 TH7	 TR8	 TH8
		//TR9	 TH9	 TR10	 TH10	 TR11	 TH11	 TR12	 TH12	 TR13	 TH13
		//TR14	 TH14	 TR15	 TH15	 TR16	 TH16	 TR17	 TH17	 TR18
		//TH18	 TR19	 TH19	 TR20	 TH20	 TR21	 TH21	 TR22	 TH22
		//TR23	 TH23	 TR24	 TH24	 TR25	 TH25	 TR26	 TH26	 TR27
		//TH27	 TR28	 TH28	 TR29	 TH29	 TR30	 TH30	 TR31	 TH31
		//TR32	 TH32	 TR33	 TH33	 TR34	 TH34	 TR35	 TH35	 TR36
		//TH36	 TR37	 TH37	 TR38	 TH38	 TR39	 TH39	 TR40	 TH40
		//TR41	 TH41	 TR42	 TH42	 TR43	 TH43	 TR44	 TH44	 TR45
		//TH45	 TR46	 TH46	 Use Reactive

		tokenizer tokens(line, boost::char_separator<char>(",\n"));
	    tokenizer::iterator it = tokens.begin();

	    if (it != tokens.end()) {
	    	data->m_seed = *it;
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
	       	data->m_altitude = *it;
	        ++it;
	    } else {
	    	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_formation = *it;
	        ++it;
	    } else {
	    	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_ecm = *it;
	    	++it;
	    } else {
	       	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_incAlt_state = *it;
	    	++it;
	    } else {
	       	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_decAlt_state = *it;
	    	++it;
	    } else {
	       	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_incAlt2_state = *it;
	    	++it;
	    } else {
	       	assert(false);
	    }

	    if (it != tokens.end()) {
	    	data->m_decAlt2_state = *it;
	    	++it;
	    } else {
	       	assert(false);
	    }

	    if (it != tokens.end()) {
	    	unsigned index = 0;

	    	while (index < GlobalSettings::getInstance()->get_dart_env_length()) {
		       	//cout << "workload = " << *it << endl;
	    		(data->m_threats).push_back(*it);
	    		++it;
	    		(data->m_targets).push_back(*it);
	        	++it;
	        	++index;
	    	}

	    	assert((data->m_targets).size() == GlobalSettings::getInstance()->get_dart_env_length()
	    			&& (data->m_targets).size() == GlobalSettings::getInstance()->get_dart_env_length());
	    } else {
	    	assert(false);
	    }

	    m_sample_problem_db.insert(std::make_pair(sample_problem_dir, data));
	}

	cout << "Read line_count = " << line_count << endl;

	features_file.close();

	return success;
}

void DartProblemDB::clean_db() {
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

void DartProblemDB::get_sample_problem_dirs(Strings& problems) const {
	Database::const_iterator it = m_sample_problem_db.begin();

	while (it != m_sample_problem_db.end()) {
		problems.push_back(it->first);
		++it;
	}
}

DartProblemDB::Threats DartProblemDB::get_threats(const string& problem_dir) const {
	Database::const_iterator itr = m_sample_problem_db.find(problem_dir);
	assert(itr != m_sample_problem_db.end());

	return itr->second->m_threats;
}

DartProblemDB::Threats DartProblemDB::get_targets(const string& problem_dir) const {
	Database::const_iterator itr = m_sample_problem_db.find(problem_dir);
	assert(itr != m_sample_problem_db.end());

	return itr->second->m_targets;
}


string DartProblemDB::get_seed(const string& problem_dir) const {
	Database::const_iterator itr = m_sample_problem_db.find(problem_dir);
	assert(itr != m_sample_problem_db.end());

	return itr->second->m_seed;
}

string DartProblemDB::get_altitude(const string& problem_dir) const {
	Database::const_iterator itr = m_sample_problem_db.find(problem_dir);
	assert(itr != m_sample_problem_db.end());

	return itr->second->m_altitude;
}

string DartProblemDB::get_formation(const string& problem_dir) const {
	Database::const_iterator itr = m_sample_problem_db.find(problem_dir);
	assert(itr != m_sample_problem_db.end());

	return itr->second->m_formation;
}

string DartProblemDB::get_ecm(const string& problem_dir) const {
	Database::const_iterator itr = m_sample_problem_db.find(problem_dir);
	assert(itr != m_sample_problem_db.end());

	return itr->second->m_ecm;
}

string DartProblemDB::get_incAlt_state(const string& problem_dir) const {
	Database::const_iterator itr = m_sample_problem_db.find(problem_dir);
	assert(itr != m_sample_problem_db.end());

	return itr->second->m_incAlt_state;
}

string DartProblemDB::get_decAlt_state(const string& problem_dir) const {
	Database::const_iterator itr = m_sample_problem_db.find(problem_dir);
	assert(itr != m_sample_problem_db.end());

	return itr->second->m_decAlt_state;
}

string DartProblemDB::get_incAlt2_state(const string& problem_dir) const {
	Database::const_iterator itr = m_sample_problem_db.find(problem_dir);
	assert(itr != m_sample_problem_db.end());

	return itr->second->m_incAlt2_state;
}

string DartProblemDB::get_decAlt2_state(const string& problem_dir) const {
	Database::const_iterator itr = m_sample_problem_db.find(problem_dir);
	assert(itr != m_sample_problem_db.end());

	return itr->second->m_decAlt2_state;
}

const DartProblemDB::ProblemData* DartProblemDB::get_problem_data(const string& problem_dir) const {
	Database::const_iterator itr = m_sample_problem_db.find(problem_dir);
	assert(itr != m_sample_problem_db.end());

	return itr->second;
}



