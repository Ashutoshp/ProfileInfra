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
#include<ReactivePlanExtraction.h>


using namespace std;

class SpecGenerator {
private:
	const string m_sample_problem_dir;

public:
	SpecGenerator(const string& dir);
	void generate_specs();
	void generate_hybrid_spec();
	void generate_deliberative_spec();

};

#endif
