/*
 * DartSpecGenerator.h
 *
 *  Created on: Oct 30, 2018
 *      Author: ashutosp
 */

#ifndef ADAPTOR_DARTSPECGENERATOR_H_
#define ADAPTOR_DARTSPECGENERATOR_H_

#include <SpecGenerator.h>
#include <ReactivePlanExtraction.h>

class DartSpecGenerator: public SpecGenerator {
private:
	//const string m_sample_problem_dir;

	bool fix_reactive_actions(ofstream& fout, const bool& no_action) const;
	bool generate_hybrid_spec() const;
	bool generate_deliberative_spec() const;
	bool write_initial_state(ofstream& fout) const;
	bool copy_template_file(ofstream& fout) const;
	bool write_flags(ofstream& fout, const Strings& actions) const;

public:
	DartSpecGenerator(const string& dir);
	virtual ~DartSpecGenerator();
	bool generate_specs() const;
};

#endif /* ADAPTOR_DARTSPECGENERATOR_H_ */
