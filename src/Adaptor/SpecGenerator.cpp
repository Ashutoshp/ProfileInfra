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
			fout << line; // TODO check if endl required
		}
	}

	planning_spec.close();

	return true;
}

// CUSTOMIZED
bool SpecGenerator::fix_reactive_actions(ofstream& fout) const {
	bool result = false;
	// Get reactive actions.
	// Open and close reactive plan file before other files are open later
	ReactivePlanExtraction reactivePlanExtraction(m_sample_problem_dir);

	Strings actions = reactivePlanExtraction.get_tactics_at_time();
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
	ofstream fout(GlobalSettings::getInstance()->get_hybrid_spec_path(m_sample_problem_dir).c_str());

	if (!fout) {
		cout << "Could not write hybrid specification file "
				<< GlobalSettings::getInstance()->get_hybrid_spec_path(m_sample_problem_dir) << endl;
		return result;
	}

	// Write initial states and environment
	result = write_initial_state(fout);

	if (!result) {
		// Now, write reactive action flags
		result = fix_reactive_actions(fout);
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
	ofstream fout(GlobalSettings::getInstance()->get_delibetaive_only_spec_path(m_sample_problem_dir).c_str());

	if (!fout) {
		cout << "Could not write hybrid specification file "
				<< GlobalSettings::getInstance()->get_delibetaive_only_spec_path(m_sample_problem_dir) << endl;
		return result;
	}

	// Write initial states and environment
	result = write_initial_state(fout);

	if (!result) {
		// Now, write reactive action flags
		result = fix_reactive_actions(fout);
	}

	if (!result) {
		// Finally, copy template file
		copy_template_file(fout);
	}

	// Close output file
	fout.close();

	return result;
}
