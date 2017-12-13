//============================================================================
// Name        : InvokePrism.h
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Code to invoke Prism to model-check the plans
//===========================================================================

#ifndef MODELCHECKING_INVOKEPRISM_H_
#define MODELCHECKING_INVOKEPRISM_H_

#include <string>
#include <iostream>

using namespace std;

class InvokePrism {

private:
	const string m_model_path;
	const string m_result_file;
	const string m_adversary_path;
	const string m_states_path;
	const string m_labels_path;
	const string m_prism_property;
	const string m_prism_property_rt;
	const string m_prism_property_prob;
	const string m_tactic_suffix;
	const string m_divert;
	const string m_engine;
	const string m_cudd;
	const string m_cuddmem;

public:
	InvokePrism(const string& model_path,
			const string& result_file,
			const string& adversary_path = "",
			const string& states_path = "",
			const string& labels_path = "");
	bool run_prism() const;
};



#endif /* MODELCHECKING_INVOKEPRISM_H_ */
