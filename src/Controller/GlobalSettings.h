// Name        : GlobalSettings.h
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Singleton class containing global variables
//============================================================================

#ifndef _GLOBALSETTINGS_H_
#define _GLOBALSETTINGS_H_

#include <iostream>
#include <string>

using namespace std;

class GlobalSettings
{
private:
        /* Here will be the instance stored. */
        static GlobalSettings* m_instance;

        // Directory to read data
        string m_source_directory;

        // Directory to write data
        string m_destination_directory;

        // Prefix for the folders to look inside source directory
        string m_directory_prefix;

        // Path to the model-checker (e.g., PRISM)
        string m_model_checker_path;

        // Path to the directory containing reactive plan for the sample problem.
        // This should be inside m_source_directory/m_directory_prefix*
        string m_reactive_plan_dir;

        // File containing reactive plan. This should be inside m_reactive_plan_dir
        //string m_reactive_plan_file;

        // Path to the directory containing deliberative plan for the sample problem.
        // This should be inside m_source_directory
        string m_deliberative_plan_dir;

        // File containing deliberative planning problem.
        // This should be inside m_deliberative_plan_dir
        string m_deliberative_spec_file;

        // File containing deliberative plan. This should be inside m_deliberative_plan_dir
        //string m_deliberative_plan_file;

        // File containing time for deliberative planning in seconds.
        // This should be inside m_deliberative_plan_dir
        string m_deliberative_planning_time_file;

        // Path to the directory containing hybrid stuff.
        // This should be inside m_destination_directory
        string m_destination_hybrid_dir;

        // Path to the directory containing deliberative only stuff.
        // This should be inside m_destination_directory
        string m_destination_deliberative_dir;

        // Template file to generate model-checker specification
        string m_template_path;

        // File containing plan. Same name used for any plan e.g., reactive or deliberative
        string m_plan_file;

        // File containing states in a planning problem.
        // This is required for understanding PRISM plans
        string m_states_file;

        // File containing labels in the context of PRISM.
        // This is particular used to know the initial state to execute a plan.
        string m_labels_file;

        // File containing model-checking result.
        // This will be inside m_destination_hybrid_dir and m_destination_deliberative_dir
        string m_result_file;

        // File containing model-checking specification for hybrid plan.
        // This will be inside m_destination_hybrid_dir and m_destination_deliberative_dir
        string m_model_checker_hybrid_spec_file;

        // File containing model-checking specification for hybrid plan.
        // This will be inside m_destination_hybrid_dir and m_destination_deliberative_dir
        string m_model_checker_spec_file;

        // File containing features of a planning problem.
        // This should be inside m_source_directory/m_directory_prefix* directory
        string m_problem_feature_file;

        string m_prism_spec_env_end_tag;

        /* Private constructor to prevent instancing. */
        GlobalSettings();

    public:
        /* Static access method. */
        static GlobalSettings* getInstance();

        inline string get_source_dir() const {return m_source_directory;}
        inline void set_source_dir(const string& dir) {m_source_directory = dir;}

        inline string get_destination_dir() const {return m_destination_directory;}
        inline void set_destination_dir(const string& dir) {m_destination_directory = dir;}

        inline string get_directory_prefix() const {return m_directory_prefix;}
        inline void set_directory_prefix(const string& prefix) {m_directory_prefix = prefix;}

        inline string get_model_checker_path() const {return m_model_checker_path;}
        inline void set_model_checker_path(const string& path) {m_model_checker_path = path;}

        inline string get_reactive_plan_dir() const {return m_reactive_plan_dir;}
        inline void set_reactive_plan_dir(const string& dir) {m_reactive_plan_dir = dir;}

        inline string get_deliberative_plan_dir() const {return m_deliberative_plan_dir;}
        inline void set_deliberative_plan_dir(const string& dir) {m_deliberative_plan_dir = dir;}

        inline string get_deliberative_spec_file() const {return m_deliberative_spec_file;}
        inline void set_deliberative_spec_file(const string& file) {m_deliberative_spec_file = file;}

        //inline string get_deliberative_plan_file() const {return m_deliberative_plan_file;}
        //inline void set_deliberative_plan_file(const string& file) {m_deliberative_plan_file = file;}

        inline string get_deliberative_planning_time_file() const {return m_deliberative_planning_time_file;}
        inline void set_deliberative_planning_time_file(const string& file) {m_deliberative_planning_time_file = file;}

        inline string get_destination_hybrid_dir() const {return m_destination_hybrid_dir;}
        inline void set_destination_hybrid_dir(const string& dir) {m_destination_hybrid_dir = dir;}

        inline string get_destination_deliberative_dir() const {return m_destination_deliberative_dir;}
        inline void set_destination_deliberative_dir(const string& dir) {m_destination_deliberative_dir = dir;}

        inline string get_template_path() const {return m_template_path;}
        inline void set_template_path(const string& path) {m_template_path = path;}

        inline string get_plan_file() const {return m_plan_file;}
        inline void set_plan_file(const string& file) {m_plan_file = file;}

        inline string get_states_file() const {return m_states_file;}
        inline void set_states_file(const string& file) {m_states_file = file;}

        inline string get_labels_file() const {return m_labels_file;}
        inline void set_labels_file(const string& file) {m_labels_file = file;}

        inline string get_result_file() const {return m_result_file;}
        inline void set_result_file(const string& file) {m_result_file = file;}

        inline string get_model_checker_spec_file() const {return m_model_checker_spec_file;}
        inline void set_model_checker_spec_file(const string& file) {m_model_checker_spec_file = file;}

        inline string get_problem_feature_file() const {return m_problem_feature_file;}
        inline void set_problem_feature_file(const string& file) {m_problem_feature_file = file;}

        inline string get_env_tag() const {return m_prism_spec_env_end_tag;}
        inline void set_env_tag(const string& file) {m_prism_spec_env_end_tag = file;}

        inline string get_reactive_plan_path() const {return m_source_directory + m_reactive_plan_dir + m_plan_file;}
        inline string get_reactive_planning_states_path() const {return m_source_directory + m_reactive_plan_dir + m_states_file;}
        inline string get_reactive_planning_labels_path() const {return m_source_directory + m_reactive_plan_dir + m_labels_file;}

        inline string get_deliberative_spec_path() const {return m_source_directory + m_deliberative_plan_dir + m_deliberative_spec_file;}
        inline string get_deliberative_plan_path() const {return m_source_directory + m_deliberative_plan_dir + m_plan_file;} // TODO not required for now
        inline string get_deliberative_planning_time_path() const {return m_source_directory + m_deliberative_plan_dir + m_deliberative_planning_time_file;}

        inline string get_hybrid_spec_path() const {return m_destination_directory + m_destination_hybrid_dir + m_model_checker_spec_file;}
        inline string get_hybrid_result_path() const {return m_destination_directory + m_destination_hybrid_dir + m_result_file;}
        inline string get_delibetaive_only_spec_path() const {return m_destination_directory + m_destination_deliberative_dir + m_model_checker_spec_file;}
        inline string get_deliberative_only_result_path() const {return m_destination_directory + m_destination_deliberative_dir + m_result_file;}

        void debug();
};
#endif
