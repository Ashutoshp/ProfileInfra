//===============================================================================
// Name        : DBWriter.cpp
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Code to write a csv file containing profiling results
// ===============================================================================

#include <DBWriter.h>
#include <assert.h>


DBWriter::DBWriter(const string& file_name) : m_file_name(file_name), m_foutP(NULL) {
	// Open output file to write modified specification for model-checking
	//ofstream fout(m_file_name.c_str());
	m_foutP = new ofstream(m_file_name.c_str());

	if (m_foutP == NULL) {
		cout << "Could not output database file "
				<< m_file_name << endl;
	}
}

void DBWriter::close_writer() {
	m_foutP->close();
}

DBWriter::~DBWriter() {
	if (m_foutP != NULL) delete m_foutP;
}

void DBWriter::write_line(const string sample_problem_path, const TimeSeries& time_series, bool use_reactive) const {
	assert(m_foutP != NULL);

	*m_foutP << sample_problem_path << ",";

	TimeSeries::const_iterator itr = time_series.begin();

	while (itr != time_series.end()) {
		*m_foutP << *itr << ",";
		++itr;
	}

	*m_foutP << use_reactive << endl;
}

