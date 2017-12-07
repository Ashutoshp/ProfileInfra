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

SpecGenerator::SpecGenerator(const string& dir): m_sample_problem_dir(dir) {

}

void SpecGenerator::generate_specs() {
	generate_hybrid_spec();
	generate_deliberative_spec();
}

void SpecGenerator::generate_hybrid_spec() {
	// Get reactive actions
	ReactivePlanExtraction reactivePlanExtraction;
	Strings actions = reactivePlanExtraction.get_tactics_at_time();

	// Open output file
	// Open deliberative planning specification
	// Open template
	// copy initial state
	// write reactive action flags
	// copy remaining
	// close output file
}

void SpecGenerator::generate_deliberative_spec() {
	// Only initial state needs to be copied here
	// Rest is fixed
}
