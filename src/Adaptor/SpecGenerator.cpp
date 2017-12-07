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

SpecGenerator::SpecGenerator(const string& dir): m_sample_problem_dir(dir) {

}

void SpecGenerator::generate_specs() {
	generate_hybrid_spec();
	generate_deliberative_spec();
}

void SpecGenerator::generate_hybrid_spec() {
	// Get reactive actions
	// Open output file
	// Open deliberative planning specification
	// copy initial state
	// write reactive action flags
	// copy remaining
	// close output file
}

void SpecGenerator::generate_deliberative_spec() {

}
