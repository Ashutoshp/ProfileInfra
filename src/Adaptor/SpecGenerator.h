/*
 * SpecGenerator.h
 *
 *  Created on: Oct 30, 2018
 *      Author: ashutosp
 */

#ifndef ADAPTOR_SPECGENERATOR_H_
#define ADAPTOR_SPECGENERATOR_H_

#include <string>
#include <iostream>
#include <Utils.h>

using namespace std;

class SpecGenerator {
protected:
	const string m_sample_problem_dir;

	virtual bool fix_reactive_actions(ofstream& fout, const bool& no_action) const = 0;
	virtual bool generate_hybrid_spec() const = 0;
	virtual bool generate_deliberative_spec() const = 0;
	virtual bool write_initial_state(ofstream& fout) const = 0;
	virtual bool copy_template_file(ofstream& fout) const = 0;
	virtual bool write_flags(ofstream& fout, const Strings& actions) const = 0;
public:
	SpecGenerator(const string& dir);

	virtual ~SpecGenerator();
	virtual bool generate_specs() const = 0;
};

#endif /* ADAPTOR_SPECGENERATOR_H_ */
