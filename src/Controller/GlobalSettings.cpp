//============================================================================
// Name        : GlobalSettings.cpp
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Singleton class containing global variables
//============================================================================

#include <GlobalSettings.h>

/* Null, because instance will be initialized on demand. */
GlobalSettings* GlobalSettings::m_instance = NULL;

GlobalSettings* GlobalSettings::getInstance() {
    if (m_instance == NULL) {
        m_instance = new GlobalSettings();
    }

    return m_instance;
}

GlobalSettings::GlobalSettings() : m_time_series_length(0) {

}

void GlobalSettings::debug() {
	cout << "m_source_directory = " << m_source_directory << endl;
    cout << "m_destination_directory = " << m_destination_directory << endl;
    cout << "m_directory_prefix = " << m_directory_prefix << endl;
    cout << "m_model_checker_path = " << m_model_checker_path << endl;
    cout << "m_reactive_plan_dir = " << m_reactive_plan_dir << endl;
    cout << "m_deliberative_plan_dir = " << m_deliberative_plan_dir << endl;
    cout << "m_deliberative_spec_file = " << m_deliberative_spec_file << endl;
    cout << "m_deliberative_planning_time_file = " << m_deliberative_planning_time_file << endl;
    cout << "m_destination_hybrid_dir = " << m_destination_hybrid_dir << endl;
    cout << "m_destination_deliberative_dir = " << m_destination_deliberative_dir << endl;
    cout << "m_template_path = " << m_template_path << endl;
    cout << "m_plan_file = " << m_plan_file << endl;
    cout << "m_states_file = " << m_states_file << endl;
    cout << "m_labels_file = " << m_labels_file << endl;
    cout << "m_result_file = " << m_result_file << endl;
    cout << "m_model_checker_spec_file = " << m_model_checker_spec_file << endl;
    cout << "m_problem_feature_file = " << m_problem_feature_file << endl;
    cout << "m_prism_spec_env_end_tag = " << m_prism_spec_env_end_tag << endl;
}
