//============================================================================
// Name        : SpecGenerator.h
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Prism Specification Generator that enforces reactive plan
//				 until deliberative plan is ready
//===========================================================================
#ifndef _SPECGENERATOR_H_
#define _SPECGENERATOR_H_

#include <string>
#include <iostream>
#include <ReactivePlanExtraction.h>
#include <SpecGenerator.h>

using namespace std;

class CloudSpecGenerator : public SpecGenerator {
private:
	const string m_sample_problem_dir;

	bool fix_reactive_actions(ofstream& fout, const bool& no_action) const;
	bool generate_hybrid_spec() const;
	bool generate_deliberative_spec() const;
	bool write_initial_state(ofstream& fout) const;
	bool copy_template_file(ofstream& fout) const;
	bool write_flags(ofstream& fout, const Strings& actions) const;

public:
	CloudSpecGenerator(const string& dir);
	bool generate_specs() const;
};

#endif
