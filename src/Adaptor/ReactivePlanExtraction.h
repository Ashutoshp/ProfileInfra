//==================================================================================
// Name        : ReactivePlanExtraction.h
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Extracts reactive plan from a Prism generated plan (i.e., adversary)
//===================================================================================

#ifndef ADAPTOR_REACTIVEPLANEXTRACTION_H_
#define ADAPTOR_REACTIVEPLANEXTRACTION_H_

#include <string>
#include <iostream>
#include <vector>
#include <Tactics.h>
#include <Utils.h>
#include <set>
#include <map>

using namespace std;

class ReactivePlanExtraction {
private:
	const string m_adversary_path;
	const string m_states_path;
	const string m_labels_path;
	const string m_tactic_suffix; // CUSTOMIZED
	const string m_divert_str; // CUSTOMIZED

	/**
	 * Finds the actions that take place in the given states
	 *
	 * Assumption: time is the first variable in the state
	 */
	struct AdversaryRow {
		int next;
		double probability;
		string action;
	};

	typedef map<int, AdversaryRow> AdversaryTable;

	Strings get_actions(const set<int>& states) const;
	set<int> get_now_states() const;

public:
	ReactivePlanExtraction(const string& adversary_file, const string& states_file, const string& label_file);

	Strings get_tactics_at_time(const string& time = "") const; // TODO extend it for any time
};

#endif /* ADAPTOR_REACTIVEPLANEXTRACTION_H_ */
