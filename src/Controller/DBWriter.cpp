//===============================================================================
// Name        : DBWriter.cpp
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Code to write a csv file containing profiling results
// ===============================================================================

#include <DBWriter.h>
#include <assert.h>
#include <Log.h>

DBWriter::DBWriter(const string& file_name) : m_file_name(file_name), m_foutP(NULL) {
	// Open output file to write modified specification for model-checking
	//ofstream fout(m_file_name.c_str());
	m_foutP = new ofstream(m_file_name.c_str());

	if (m_foutP == NULL) {
		string err_msg = "Could not output database file " + m_file_name;
		cout << err_msg << endl;
		Log::getInstance()->write(err_msg);
	}
}

void DBWriter::close_writer() {
	m_foutP->close();
}

DBWriter::~DBWriter() {
	if (m_foutP != NULL) delete m_foutP;
}

void DBWriter::write_header(const string& header) const {
	*m_foutP << header;
}

void DBWriter::write_line(const string sample_problem_path, const ProblemDB::ProblemData* data, bool use_reactive) const {
	assert(m_foutP != NULL);

	*m_foutP << sample_problem_path << ",";

	*m_foutP << data->m_dimmer << ",";
	*m_foutP << data->m_server_A_count << ",";
	*m_foutP << data->m_server_B_count << ",";
	*m_foutP << data->m_server_C_count << ",";
	*m_foutP << data->m_server_A_status << ",";
	*m_foutP << data->m_server_B_status << ",";
	*m_foutP << data->m_server_C_status << ",";
	*m_foutP << data->m_server_A_load << ",";
	*m_foutP << data->m_server_B_load << ",";
	*m_foutP << data->m_server_C_load << ",";
	*m_foutP << data->m_average_response_time << ",";


	TimeSeries::const_iterator itr = data->m_work_load.begin();

	while (itr != data->m_work_load.end()) {
		*m_foutP << *itr << ",";
		++itr;
	}

	*m_foutP << use_reactive << endl;
}
