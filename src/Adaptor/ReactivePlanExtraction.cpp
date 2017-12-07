//==================================================================================
// Name        : ReactivePlanExtraction.cpp
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Extracts reactive plan from a Prism generated plan (i.e., adversary)
//===================================================================================

#include <ReactivePlanExtraction.h>
#include <GlobalSettings.h>
#include <fstream>
#include <sstream>
#include <boost/tokenizer.hpp>
#include <string.h>

ReactivePlanExtraction::ReactivePlanExtraction() : m_tactic_suffix("_start"), m_divert_str("divert_") {}

Strings ReactivePlanExtraction::get_tactics_at_time(const string& time) const {
	// TODO expand it for database. CUSTOMIZED
	set<int> states = this->get_now_states();
	Strings actions = get_actions(states);

	return actions;
}

/**
 * Finds the states that correspond to the current time.
 *
 * Assumption: time is the first variable in the state
 */
set<int> ReactivePlanExtraction::get_now_states() const {
	// TODO throw exception on error (but be careful with the method that calls this one)

	/* CUSTOMIZED
	 * Format:
	 * (time,s,env_turn,addServer_state,addServer_go,removeServer_state,removeServer_go,servers)
	 * 0:(0,0,false,0,false,0,true,1)
	 * 1:(0,0,false,0,true,0,true,1)
	 *
	 * From the second line on, the format is:
	 * <state>:(<value1>,<value2>,...)
	 */
	set<int> states;
	ifstream fin(GlobalSettings::getInstance()->get_reactive_planning_states_path().c_str());

	if (!fin) {
		cout << "Could not read input file " << GlobalSettings::getInstance()->get_reactive_planning_states_path() << endl;
		return states;
	}

	string line;
	bool first_line = true;

	while (getline(fin, line)) {
		if (first_line) {
			first_line = false;
			continue;
		}

		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
		tokenizer tokens(line, boost::char_separator<char>(":(,)"));
		tokenizer::iterator it = tokens.begin();

		if (it != tokens.end()) {
			int state = atoi(it->c_str());
			if (++it != tokens.end()) {
				if (*it == "0") {
					states.insert(state);
					//cout << "State @0: " << state << endl;
					continue;
				}
			}
		}
		break;
	}
	fin.close();

	return states;
}

Strings ReactivePlanExtraction::get_actions(const set<int>& states) const {
	// TODO throw exception on error

	/* CUSTOMIZED
	 * The format is like this:
	 * 4673 ?
	 * 0 3 1 clk
	 * 1 0 1 addServer_nostart
	 * 2 4 1
	 *
	 * From the second like on, <from state> <to state> <probability> [<action>]]
	 */


	Strings actions;
	typedef set<string> StringSet;
	StringSet action_set;
	ifstream fin(GlobalSettings::getInstance()->get_reactive_plan_path().c_str());

	if (!fin) {
		cout << "Could not read input file " << GlobalSettings::getInstance()->get_reactive_plan_path() << endl;
		return actions;
	}

	// first, load the adversary table for the states at time 0
	AdversaryTable table;

	size_t suffix_length = strlen(m_tactic_suffix.c_str());
	size_t divert_prefix_len = strlen(m_divert_str.c_str());
	string line;

	bool first_line = true;

	while (getline(fin, line)) {
		if (first_line) {
			first_line = false;
			continue;
		}

		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
		tokenizer tokens(line, boost::char_separator<char>(" "));
		tokenizer::iterator it = tokens.begin();

		if (it != tokens.end()) {
			int state = atoi(it->c_str());
			//cout << "state = " << state << endl;
			if (states.find(state) != states.end()) { // this is one of the relevant states
				AdversaryRow row;
				++it; // point to target state;
				row.next = atoi(it->c_str());
				++it; // point to the probability
				row.probability = atof(it->c_str());
				if (++it != tokens.end()) { // has action
					size_t action_length = it->length();
					//cout << "action### " << *it << endl;
					if (action_length > suffix_length || action_length > divert_prefix_len) {
						if (it->compare(action_length - suffix_length, suffix_length, m_tactic_suffix) == 0
						        || strncmp((*it).c_str(), m_divert_str.c_str(), divert_prefix_len) == 0) { // it's a tactic start action
							row.action = *it;
						}
					}
				}
				table.insert(pair<int, AdversaryRow>(state, row));
			}
		}
	}

	fin.close();

	// now find the initial state;
	/*
	 * assumptions:
	 * 	0 is "initial", and 0 is always the first label if it appears in a row
	 */
	int state = -1;
	ifstream labels(GlobalSettings::getInstance()->get_reactive_planning_labels_path().c_str());

	if (!labels) {
		cout << "Could not read input file " << GlobalSettings::getInstance()->get_reactive_planning_labels_path() << endl;
		return actions;
	}

	first_line = false;

	while (getline(labels, line)) {
		if (first_line) {
			first_line = false;
			continue;
		}

		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
		tokenizer tokens(line, boost::char_separator<char>(": "));
		tokenizer::iterator it = tokens.begin();

		if (it != tokens.end()) {
			int row_state = atoi(it->c_str());
			if (++it != tokens.end()) {
				int label_number = atoi(it->c_str());
				if (label_number == 0) {
					state = row_state;
					break;
				}
			}
		}
	}

	labels.close();

	/*
	 * Now walk the table from the initial state collecting the actions
	 * If we get to a point where the transition has prob < 1, we stop
	 * because it is probably the environment making a stochastic transition,
	 * which means that the system turn ended
	 */
	//printf("state %d, table size = %u\n", state, table.size());

	AdversaryTable::iterator row_it;

	while ((row_it = table.find(state)) != table.end()) {
		AdversaryRow& row = row_it->second;

		if (!row.action.empty()) {
			actions.push_back(row.action);
		}

		cout << row.action << "#" << row.probability << "##" << row.next << endl;

		if (row.probability < 1.0) {
			break;;
		}
		state = row.next;
	}

	return actions;
}



