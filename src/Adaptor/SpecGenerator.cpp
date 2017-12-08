//============================================================================
// Name        : SpecGenerator.cpp
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Prism Specification Generator that enforces reactive plan
//				 until deliberative plan is ready
//===========================================================================

#include <SpecGenerator.h>
#include <ReactivePlanExtraction.h>
#include <GlobalSettings.h>
#include <fstream>

SpecGenerator::SpecGenerator(const string& dir): m_sample_problem_dir(dir) {

}

// CUSTOMIZED
bool SpecGenerator::write_initial_state(ofstream& fout) const {
	// Open deliberative planning specification
	ifstream planning_spec(GlobalSettings::getInstance()->get_deliberative_spec_path().c_str());

	if (!planning_spec) {
		cout << "Could not read deliberative planning specification file "
				<< GlobalSettings::getInstance()->get_deliberative_spec_path() << endl;
		return false;
	}

	// Copy initial state and environment model
	string line;
	string env_end_tag = GlobalSettings::getInstance()->get_env_tag();

	while (getline(planning_spec, line)) {
		if (line == env_end_tag) {
			break;
		} else {
			fout << line; // TODO check if endl required
		}
	}

	planning_spec.close();

	return true;
}

// CUSTOMIZED
bool SpecGenerator::write_flags(ofstream& fout, const Strings& actions) const {
	fout << "// Newly added constant booleans to control the first action" << endl;

	if (find_string_in_strings("addServerA_start", actions)) {
		fout << "const bool asA = true;" << endl;
	} else {
		fout << "const bool asA = false;" << endl;
	}

	if (find_string_in_strings("addServerB_start", actions)) {
		fout << "const bool asB = true;" << endl;
	} else {
		fout << "const bool asB = false;" << endl;
	}

	if (find_string_in_strings("addServerC_start", actions)) {
		fout << "const bool asC = true;" << endl;
	} else {
		fout << "const bool asC = false;" << endl;
	}

	if (actions.size() == 0 || find_string_in_strings("pass_add", actions)) {
		fout << "const bool ps = true;" << endl;
	} else {
		fout << "const bool ps = false;" << endl;
	}

	if (find_string_in_strings("progressA", actions)) {
		fout << "const bool psA = true;" << endl;
	} else {
		fout << "const bool psA = false;" << endl;
	}

	if (find_string_in_strings("progressB", actions)) {
		fout << "const bool psB = true;" << endl;
	} else {
		fout << "const bool psB = false;" << endl;
	}

	if (find_string_in_strings("progressC", actions)) {
		fout << "const bool psC = true;" << endl;
	} else {
		fout << "const bool psC = false;" << endl;
	}

	if (find_string_in_strings("addServerA_complete", actions)) {
		fout << "const bool asAc = true;" << endl;
	} else {
		fout << "const bool asAc = false;" << endl;
	}

	if (find_string_in_strings("addServerB_complete", actions)) {
		fout << "const bool asBc = true;" << endl;
	} else {
		fout << "const bool asBc = false;" << endl;
	}

	if (find_string_in_strings("addServerC_complete", actions)) {
		fout << "const bool asCc = true;" << endl;
	} else {
		fout << "const bool asCc = false;" << endl;
	}

	if (find_string_in_strings("removeServerA_start", actions)) {
		fout << "const bool rsA = true;" << endl;
	} else {
		fout << "const bool rsA = false;" << endl;
	}

	if (find_string_in_strings("removeServerB_start", actions)) {
		fout << "const bool rsB = true;" << endl;
	} else {
		fout << "const bool rsB = false;" << endl;
	}

	if (find_string_in_strings("removeServerC_start", actions)) {
		fout << "const bool rsC = true;" << endl;
	} else {
		fout << "const bool rsC = false;" << endl;
	}

	if (actions.size() == 0 || find_string_in_strings("pass_remove_server", actions)) {
		fout << "const bool prs = true;" << endl;
	} else {
		fout << "const bool prs = false;" << endl;
	}

	if (actions.size() == 0 || find_string_in_strings("pass_inc_dimmer", actions)) {
		fout << "const bool pid = true;" << endl;
	} else {
		fout << "const bool pid = false;" << endl;
	}

	if (find_string_in_strings("increaseDimmer_start", actions)) {
		fout << "const bool id = true;" << endl;
	} else {
		fout << "const bool id = false;" << endl;
	}

	if (find_string_in_strings("decreaseDimmer_start", actions)) {
		fout << "const bool dd = true;" << endl;
	} else {
		fout << "const bool dd = false;" << endl;
	}

	if (actions.size() == 0 || find_string_in_strings("pass_dec_dimmer", actions)) {
		fout << "const bool pdd = true;" << endl;
	} else {
		fout << "const bool pdd = false;" << endl;
	}

	fout << "const bool d_100_0_0 = true" << endl;
	fout << "const bool d_75_25_0 = true" << endl;
	fout << "const bool d_75_0_25 = true" << endl;
	fout << "const bool d_50_50_0 = true" << endl;
	fout << "const bool d_50_0_50 = true" << endl;
	fout << "const bool d_50_25_25 = true" << endl;
	fout << "const bool d_25_75_0 = true" << endl;
	fout << "const bool d_25_0_75 = true" << endl;
	fout << "const bool d_25_50_25 = true" << endl;
	fout << "const bool d_25_25_50 = true" << endl;
	fout << "const bool d_0_100_0 = true" << endl;
	fout << "const bool d_0_0_100 = true" << endl;
	fout << "const bool d_0_75_25 = true" << endl;
	fout << "const bool d_0_25_75 = true" << endl;
	fout << "const bool d_0_50_50 = true" << endl;

	return true;
}

// CUSTOMIZED
bool SpecGenerator::fix_reactive_actions(ofstream& fout, bool no_action) const {
	bool result = false;
	Strings actions;

	if (!no_action) {
		// Get reactive actions.
		ReactivePlanExtraction reactivePlanExtraction;
		actions = reactivePlanExtraction.get_tactics_at_time();
	}

	result = write_flags(fout, actions);

	return result;
}

bool SpecGenerator::copy_template_file(ofstream& fout) const {
	ifstream prism_template(GlobalSettings::getInstance()->get_template_path().c_str());

	if (!prism_template) {
		cout << "Could not template file " << GlobalSettings::getInstance()->get_template_path() << endl;
		return false;
	}

	string line;
	while (getline(prism_template, line)) {
		fout << line; // TODO check if endl required
	}

	// Close file
	prism_template.close();

	return true;
}

bool SpecGenerator::generate_specs() const {
	bool result = false;

	result = generate_hybrid_spec();

	if (result) {
		result = generate_deliberative_spec();
	}

	return result;
}

bool SpecGenerator::generate_hybrid_spec() const {
	bool result = false;

	// Open output file to write modified specification for model-checking
	ofstream fout(GlobalSettings::getInstance()->get_hybrid_spec_path().c_str());

	if (!fout) {
		cout << "Could not write hybrid specification file "
				<< GlobalSettings::getInstance()->get_hybrid_spec_path() << endl;
		return result;
	}

	// Write initial states and environment
	result = write_initial_state(fout);

	if (!result) {
		// Now, write reactive action flags
		result = fix_reactive_actions(fout, false);
	}

	if (!result) {
		// Finally, copy template file
		copy_template_file(fout);
	}

	// Close output file
	fout.close();

	return result;
}

bool SpecGenerator::generate_deliberative_spec() const {
	bool result = false;
	// Open output file to write modified specification for model-checking
	ofstream fout(GlobalSettings::getInstance()->get_delibetaive_only_spec_path().c_str());

	if (!fout) {
		cout << "Could not write hybrid specification file "
				<< GlobalSettings::getInstance()->get_delibetaive_only_spec_path() << endl;
		return result;
	}

	// Write initial states and environment
	result = write_initial_state(fout);

	if (!result) {
		// Now, write reactive action flags
		result = fix_reactive_actions(fout, true);
	}

	if (!result) {
		// Finally, copy template file
		copy_template_file(fout);
	}

	// Close output file
	fout.close();

	return result;
}
