/*
 * DartSpecGenerator.cpp
 *
 *  Created on: Oct 30, 2018
 *      Author: ashutosp
 */

#include <DartSpecGenerator.h>
#include <ReactivePlanExtraction.h>
#include <GlobalSettings.h>
#include <fstream>
#include <Utils.h>
#include <assert.h>
#include <Log.h>
#include <ProblemDB.h>

DartSpecGenerator::DartSpecGenerator(const string& dir): SpecGenerator(dir) {
	// TODO Auto-generated constructor stub
	//cout << "m_sample_problem_dir = " << m_sample_problem_dir << endl;
}

DartSpecGenerator::~DartSpecGenerator() {
	// TODO Auto-generated destructor stub
}

// CUSTOMIZED
bool DartSpecGenerator::write_initial_state(ofstream& fout) const {
	// Open deliberative planning specification
	ifstream planning_spec(GlobalSettings::getInstance()->get_deliberative_spec_path(m_sample_problem_dir).c_str());

	if (!planning_spec) {
		cout << "Could not read deliberative planning specification file "
				<< GlobalSettings::getInstance()->get_deliberative_spec_path(m_sample_problem_dir) << endl;
		return false;
	}

	// Copy initial state and environment model
	string line;
	string env_end_tag = GlobalSettings::getInstance()->get_env_tag();

	while (getline(planning_spec, line)) {
		if (line == env_end_tag) {
			break;
		} else {
			fout << line << endl; // TODO check if endl required
		}
	}

	planning_spec.close();

	return true;
}

bool DartSpecGenerator::write_flags(ofstream& fout, const Strings& actions) const {
	fout << "// Newly added constant booleans to control the first action" << endl;
	bool pass_ecm_on = true;
	bool invalid_ecm_on = true;

	bool pass_ecm_off = true;
	bool invalid_ecm_off = true;

	bool pass_go_tight = true;
	bool invalid_go_tight = true;

	bool pass_go_loose = true;
	bool invalid_go_loose = true;

	bool pass_inc_alt = true;
	bool invalid_inc_alt = true;

	bool pass_dec_alt = true;
	bool invalid_dec_alt = true;

	bool pass_inc_alt2 = true;
	bool invalid_inc_alt2 = true;

	bool pass_dec_alt2 = true;
	bool invalid_dec_alt2 = true;

	if (find_string_in_strings("EcmOn_start", actions)) {
		fout << "const bool ecmOnS = true;" << endl;
		pass_ecm_on = false;
		invalid_ecm_on = false;
	} else {
		fout << "const bool ecmOnS = false;" << endl;
	}

	if (find_string_in_strings("EcmOff_start", actions)) {
		fout << "const bool ecmOffS = true;" << endl;
		pass_ecm_off = false;
		invalid_ecm_off = false;
	} else {
		fout << "const bool ecmOffS = false;" << endl;
	}

	if (find_string_in_strings("GoTight_start", actions)) {
		fout << "const bool goTightS = true;" << endl;
		pass_go_tight = false;
		invalid_go_tight = false;
	} else {
		fout << "const bool goTightS = false;" << endl;
	}

	if (find_string_in_strings("GoLoose_start", actions)) {
		fout << "const bool GoLooseS = true;" << endl;
		pass_go_loose = false;
		invalid_go_loose = false;
	} else {
		fout << "const bool GoLooseS = false;" << endl;
	}

	if (find_string_in_strings("IncAlt_start", actions)) {
		fout << "const bool IncAltS = true;" << endl;
		pass_inc_alt = false;
		invalid_inc_alt = false;
	} else {
		fout << "const bool IncAltS = false;" << endl;
	}

	if (find_string_in_strings("IncAlt_progress", actions)) {
		fout << "const bool IncAltPr = true;" << endl;
		pass_inc_alt = false;
		invalid_inc_alt = false;
	} else {
		fout << "const bool IncAltPr = false;" << endl;
	}

	if (find_string_in_strings("IncAlt_complete", actions)) {
		fout << "const bool IncAltC = true;" << endl;
		pass_inc_alt = false;
		invalid_inc_alt = false;
	} else {
		fout << "const bool IncAltC = false;" << endl;
	}

	if (find_string_in_strings("DecAlt_start", actions)) {
		fout << "const bool DecAltS = true;" << endl;
		pass_dec_alt = false;
		invalid_dec_alt = false;
	} else {
		fout << "const bool DecAltS = false;" << endl;
	}

	if (find_string_in_strings("DecAlt_progress", actions)) {
		fout << "const bool DecAltPr = true;" << endl;
		pass_dec_alt = false;
		invalid_dec_alt = false;
	} else {
		fout << "const bool DecAltPr = false;" << endl;
	}

	if (find_string_in_strings("DecAlt_complete", actions)) {
		fout << "const bool DecAltC = true;" << endl;
		pass_dec_alt = false;
		invalid_dec_alt = false;
	} else {
		fout << "const bool DecAltC = false;" << endl;
	}

	if (find_string_in_strings("IncAlt2_start", actions)) {
		fout << "const bool IncAlt2S = true;" << endl;
		pass_inc_alt2 = false;
		invalid_inc_alt2 = false;
	} else {
		fout << "const bool IncAlt2S = false;" << endl;
	}

	if (find_string_in_strings("IncAlt2_progress", actions)) {
		fout << "const bool IncAlt2Pr = true;" << endl;
		pass_inc_alt2 = false;
		invalid_inc_alt2 = false;
	} else {
		fout << "const bool IncAlt2Pr = false;" << endl;
	}

	if (find_string_in_strings("IncAlt2_complete", actions)) {
		fout << "const bool IncAlt2C = true;" << endl;
		pass_inc_alt2 = false;
		invalid_inc_alt2 = false;
	} else {
		fout << "const bool IncAlt2C = false;" << endl;
	}

	if (find_string_in_strings("DecAlt2_start", actions)) {
		fout << "const bool DecAlt2S = true;" << endl;
		pass_dec_alt2 = false;
		invalid_dec_alt2 = false;
	} else {
		fout << "const bool DecAlt2S = false;" << endl;
	}

	if (find_string_in_strings("DecAlt2_progress", actions)) {
		fout << "const bool DecAlt2Pr = true;" << endl;
		pass_dec_alt2 = false;
		invalid_dec_alt2 = false;
	} else {
		fout << "const bool DecAlt2Pr = false;" << endl;
	}

	if (find_string_in_strings("DecAlt2_complete", actions)) {
		fout << "const bool DecAlt2C = true;" << endl;
		pass_dec_alt2 = false;
		invalid_dec_alt2 = false;
	} else {
		fout << "const bool DecAlt2C = false;" << endl;
	}

	///////////////////////
	if (actions.size() == 0 || find_string_in_strings("EcmOn_pass", actions) || pass_ecm_on
			|| find_string_in_strings("EcmOn_invalid", actions) || invalid_ecm_on) {
		fout << "const bool ecmOnP = true;" << endl;
		fout << "const bool ecmOnI = true;" << endl;
	} else {
		fout << "const bool ecmOnP = false;" << endl;
		fout << "const bool ecmOnI = false;" << endl;
	}

	if (actions.size() == 0 || find_string_in_strings("EcmOff_pass", actions) ||  pass_ecm_off
			|| find_string_in_strings("EcmOff_invalid", actions) || invalid_ecm_off) {
		fout << "const bool ecmOffP = true;" << endl;
		fout << "const bool ecmOffI = true;" << endl;
	} else {
		fout << "const bool ecmOffP = false;" << endl;
		fout << "const bool ecmOffI = false;" << endl;
	}

	if (actions.size() == 0 || find_string_in_strings("GoTight_pass", actions) || pass_go_tight
			|| find_string_in_strings("GoTight_invalid", actions) || invalid_go_tight) {
		fout << "const bool goTightP = true;" << endl;
		fout << "const bool goTightI = true;" << endl;
	} else {
		fout << "const bool goTightP = false;" << endl;
		fout << "const bool goTightI = false;" << endl;
	}

	if (actions.size() == 0 || find_string_in_strings("GoLoose_pass", actions) || pass_go_loose
			|| find_string_in_strings("GoLoose_invalid", actions) || invalid_go_loose) {
		fout << "const bool GoLooseP = true;" << endl;
		fout << "const bool GoLooseI = true;" << endl;
	} else {
		fout << "const bool GoLooseP = false;" << endl;
		fout << "const bool GoLooseI = false;" << endl;
	}

	if (actions.size() == 0 || find_string_in_strings("IncAlt_pass", actions) || pass_inc_alt
			|| find_string_in_strings("IncAlt_invalid", actions) || invalid_inc_alt) {
		fout << "const bool IncAltP = true;" << endl;
		fout << "const bool IncAltI = true;" << endl;
	} else {
		fout << "const bool IncAltP = false;" << endl;
		fout << "const bool IncAltI = false;" << endl;
	}

	if (actions.size() == 0 || find_string_in_strings("DecAlt_pass", actions) || pass_dec_alt
			|| find_string_in_strings("DecAlt_invalid", actions) || invalid_dec_alt) {
		fout << "const bool DecAltP = true;" << endl;
		fout << "const bool DecAltI = true;" << endl;
	} else {
		fout << "const bool DecAltP = false;" << endl;
		fout << "const bool DecAltI = false;" << endl;
	}

	if (actions.size() == 0 || find_string_in_strings("IncAlt2_pass", actions) || pass_inc_alt2
			|| find_string_in_strings("IncAlt2_invalid", actions) || invalid_inc_alt2) {
		fout << "const bool IncAlt2P = true;" << endl;
		fout << "const bool IncAlt2I = true;" << endl;
	} else {
		fout << "const bool IncAlt2P = false;" << endl;
		fout << "const bool IncAlt2I = false;" << endl;
	}

	if (actions.size() == 0 || find_string_in_strings("DecAlt2_pass", actions) || pass_dec_alt2
			|| find_string_in_strings("DecAlt2_invalid", actions) || invalid_dec_alt2) {
		fout << "const bool DecAlt2P = true;" << endl;
		fout << "const bool DecAlt2I = true;" << endl;
	} else {
		fout << "const bool DecAlt2P = false;" << endl;
		fout << "const bool DecAlt2I = false;" << endl;
	}

	// TODO next 6 check are hard coded for values 1 and 2.
	// 1 means server boot up is in process and 2 means server boot up is complete
	/*if (find_string_in_strings("progressA", actions)
			|| ProblemDB::getInstance()->get_serverA_status(m_sample_problem_dir) == 1) {
		fout << "const bool psA = true;" << endl;
		pass_add_server = false;
	} else {
		fout << "const bool psA = false;" << endl;
	}

	if (find_string_in_strings("progressB", actions)
			|| ProblemDB::getInstance()->get_serverB_status(m_sample_problem_dir) == 1) {
		fout << "const bool psB = true;" << endl;
		pass_add_server = false;
	} else {
		fout << "const bool psB = false;" << endl;
	}

	if (find_string_in_strings("progressC", actions)
			|| ProblemDB::getInstance()->get_serverC_status(m_sample_problem_dir) == 1) {
		fout << "const bool psC = true;" << endl;
		pass_add_server = false;
	} else {
		fout << "const bool psC = false;" << endl;
	}

	if (find_string_in_strings("addServerA_complete", actions)
			|| ProblemDB::getInstance()->get_serverA_status(m_sample_problem_dir) == 2) {
		fout << "const bool asAc = true;" << endl;
		pass_add_server = false;
	} else {
		fout << "const bool asAc = false;" << endl;
	}

	if (find_string_in_strings("addServerB_complete", actions)
			|| ProblemDB::getInstance()->get_serverB_status(m_sample_problem_dir) == 2) {
		fout << "const bool asBc = true;" << endl;
		pass_add_server = false;
	} else {
		fout << "const bool asBc = false;" << endl;
	}

	if (find_string_in_strings("addServerC_complete", actions)
			|| ProblemDB::getInstance()->get_serverB_status(m_sample_problem_dir) == 2) {
		fout << "const bool asCc = true;" << endl;
		pass_add_server = false;
	} else {
		fout << "const bool asCc = false;" << endl;
	}

	if (find_string_in_strings("removeServerA_start", actions)) {
		fout << "const bool rsA = true;" << endl;
		pass_remove_server = false;
	} else {
		fout << "const bool rsA = false;" << endl;
	}

	if (find_string_in_strings("removeServerB_start", actions)) {
		fout << "const bool rsB = true;" << endl;
		pass_remove_server = false;
	} else {
		fout << "const bool rsB = false;" << endl;
	}

	if (find_string_in_strings("removeServerC_start", actions)) {
		fout << "const bool rsC = true;" << endl;
		pass_remove_server = false;
	} else {
		fout << "const bool rsC = false;" << endl;
	}

	if (find_string_in_strings("increaseDimmer_start", actions)) {
		fout << "const bool id = true;" << endl;
		pass_inc_dimmer = true;
	} else {
		fout << "const bool id = false;" << endl;
	}

	if (find_string_in_strings("decreaseDimmer_start", actions)) {
		fout << "const bool dd = true;" << endl;
		pass_dec_dimmer = false;
	} else {
		fout << "const bool dd = false;" << endl;
	}

	if (actions.size() == 0 || find_string_in_strings("pass_add", actions) || pass_add_server) {
		fout << "const bool ps = true;" << endl;
	} else {
		fout << "const bool ps = false;" << endl;
	}

	if (actions.size() == 0 || find_string_in_strings("pass_remove_server", actions) || pass_remove_server) {
		fout << "const bool prs = true;" << endl;
	} else {
		fout << "const bool prs = false;" << endl;
	}

	if (actions.size() == 0 || find_string_in_strings("pass_inc_dimmer", actions) || pass_inc_dimmer) {
		fout << "const bool pid = true;" << endl;
	} else {
		fout << "const bool pid = false;" << endl;
	}

	if (actions.size() == 0 || find_string_in_strings("pass_dec_dimmer", actions) || pass_dec_dimmer) {
		fout << "const bool pdd = true;" << endl;
	} else {
		fout << "const bool pdd = false;" << endl;
	}

	fout << "const bool d_100_0_0 = true;" << endl;
	fout << "const bool d_75_25_0 = true;" << endl;
	fout << "const bool d_75_0_25 = true;" << endl;
	fout << "const bool d_50_50_0 = true;" << endl;
	fout << "const bool d_50_0_50 = true;" << endl;
	fout << "const bool d_50_25_25 = true;" << endl;
	fout << "const bool d_25_75_0 = true;" << endl;
	fout << "const bool d_25_0_75 = true;" << endl;
	fout << "const bool d_25_50_25 = true;" << endl;
	fout << "const bool d_25_25_50 = true;" << endl;
	fout << "const bool d_0_100_0 = true;" << endl;
	fout << "const bool d_0_0_100 = true;" << endl;
	fout << "const bool d_0_75_25 = true;" << endl;
	fout << "const bool d_0_25_75 = true;" << endl;
	fout << "const bool d_0_50_50 = true;" << endl;*/

	return true;
}

// CUSTOMIZED
bool DartSpecGenerator::fix_reactive_actions(ofstream& fout, const bool& no_action) const {
	bool result = false;
	Strings actions;

	if (!no_action) {
		// Get reactive actions.
		ReactivePlanExtraction reactivePlanExtraction(m_sample_problem_dir);
		actions = reactivePlanExtraction.get_tactics_at_time();
		Log::getInstance()->write("Fast actions are: ");
		Strings::iterator it = actions.begin();

		while (it != actions.end()) {
			Log::getInstance()->write(*it);
			++it;
		}

		//Log::getInstance()->write("\n");
	}

	result = write_flags(fout, actions);

	return result;
}

bool DartSpecGenerator::copy_template_file(ofstream& fout) const {
	ifstream prism_template(GlobalSettings::getInstance()->get_template_path().c_str());

	if (!prism_template) {
		cout << "Could not template file " << GlobalSettings::getInstance()->get_template_path() << endl;
		assert(false);
		//return false;
	}

	string line;
	while (getline(prism_template, line)) {
		fout << line << endl; // TODO check if endl required
	}

	// Close file
	prism_template.close();

	return true;
}

bool DartSpecGenerator::generate_specs() const {
	bool result = false;

	result = generate_hybrid_spec();

	if (result) {
		result = generate_deliberative_spec();
	}

	return result;
}

bool DartSpecGenerator::generate_hybrid_spec() const {
	bool result = false;

	//cout << "Inside SpecGenerator::generate_hybrid_spec = " << GlobalSettings::getInstance()->get_hybrid_spec_path(m_sample_problem_dir) << endl;
	// Open output file to write modified specification for model-checking
	ofstream fout(GlobalSettings::getInstance()->get_hybrid_spec_path(m_sample_problem_dir).c_str());

	if (!fout) {
		cout << "Could not write hybrid specification file "
				<< GlobalSettings::getInstance()->get_hybrid_spec_path(m_sample_problem_dir) << endl;
		assert(false);

		//return result;
	}

	// Write initial states and environment
	result = write_initial_state(fout);

	if (result) {
		// Now, write reactive action flags
		result = fix_reactive_actions(fout, false);
	}

	if (result) {
		// Finally, copy template file
		copy_template_file(fout);
	}

	// Close output file
	fout.close();

	return result;
}

bool DartSpecGenerator::generate_deliberative_spec() const {
	bool result = false;
	// Open output file to write modified specification for model-checking
	ofstream fout(GlobalSettings::getInstance()->get_delibetaive_only_spec_path(m_sample_problem_dir).c_str());

	if (!fout) {
		cout << "Could not write hybrid specification file "
				<< GlobalSettings::getInstance()->get_delibetaive_only_spec_path(m_sample_problem_dir) << endl;
		assert(false);

		//return result;
	}

	// Write initial states and environment
	result = write_initial_state(fout);

	if (result) {
		// Now, write reactive action flags
		result = fix_reactive_actions(fout, true);
	}

	if (result) {
		// Finally, copy template file
		copy_template_file(fout);
	}

	// Close output file
	fout.close();

	return result;
}
