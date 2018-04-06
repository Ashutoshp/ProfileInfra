//============================================================================
// Name        : ProfileInfra.cpp
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
//============================================================================

#include <iostream>
#include <GlobalSettings.h>
#include <vector>
#include <Utils.h>
#include <SpecGenerator.h>
#include <InvokePrism.h>
#include <boost/filesystem.hpp>
//#include <cstdlib>
#include <experimental/filesystem>
//#include <fstream>
#include <ProblemDB.h>
#include <DBWriter.h>
#include <Log.h>

//#include <jni.h>
//namespace fs = std::experimental::filesystem;

void do_settings() {
	GlobalSettings::getInstance()->set_source_dir("/home/ashutosp/helloWorld/");
	//GlobalSettings::getInstance()->set_destination_dir("/home/ashutosp/helloWorld/slow_only/case-3/profiling_problem/profiled_data");
	GlobalSettings::getInstance()->set_destination_dir("profiled_data");
	GlobalSettings::getInstance()->set_directory_prefix("model");
	GlobalSettings::getInstance()->set_model_checker_path("/home/ashutosp/Prism/prism/bin/prism");
	GlobalSettings::getInstance()->set_reactive_plan_dir("fast");
	GlobalSettings::getInstance()->set_deliberative_plan_dir("slow");
	GlobalSettings::getInstance()->set_deliberative_spec_file("ttimemodel.prism");
	GlobalSettings::getInstance()->set_deliberative_planning_time_file(""); // TODO
	GlobalSettings::getInstance()->set_destination_hybrid_dir("hybrid");
	GlobalSettings::getInstance()->set_destination_deliberative_dir("slow");
	GlobalSettings::getInstance()->set_template_path("/home/ashutosp/helloWorld/model-check.prism");
	GlobalSettings::getInstance()->set_plan_file("result.adv");
	GlobalSettings::getInstance()->set_states_file("result.sta");
	GlobalSettings::getInstance()->set_labels_file("result.lab");
	GlobalSettings::getInstance()->set_result_file("result");
	GlobalSettings::getInstance()->set_model_checker_spec_file("profile.prism");
	GlobalSettings::getInstance()->set_problem_feature_file(""); // TODO
	GlobalSettings::getInstance()->set_env_tag("// #ENV ENDS");
	GlobalSettings::getInstance()->set_features_file("/home/ashutosp/helloWorld/features.csv");
	GlobalSettings::getInstance()->set_time_series_length(21);
	GlobalSettings::getInstance()->set_output_db_file("/home/ashutosp/helloWorld/db.csv");
	GlobalSettings::getInstance()->set_log_file("/home/ashutosp/profile_log");
}

int main() {
	// Global settings
	do_settings();

	// Open log file
	Log::getInstance(GlobalSettings::getInstance()->get_log_file());

	// Get directories (matching prefix) for input planning problems
	//Strings input_dirs = get_prefix_matching_directories(GlobalSettings::getInstance()->get_source_dir().c_str(), GlobalSettings::getInstance()->get_directory_prefix().c_str());
	// Read feature file written during problem generation from simulation.
	ProblemDB::getInstance()->populate_db();
	Strings input_dirs;
	ProblemDB::getInstance()->get_sample_problem_dirs(input_dirs);

	if (input_dirs.size() != 0) {
		// Iterate each directory and call adaptor to write files to a given location.
		Strings::iterator iter = input_dirs.begin();

		while (iter != input_dirs.end()) {
			// adapt (source directory)
			// it will get slow and fast directory, deliberative time,
			// needs to parse fast plan to extract the action
			// use template andLog::getInstance()->write slow specification to create specification file
			// hybrid only is always fixed

			cout << "Creating profiling directories inside " << *iter << endl;
			Log::getInstance()->write("Creating profiling directories inside " + *iter);

			// Create directories
			// TODO error check
			boost::system::error_code err_code;
			bool result = boost::filesystem::create_directories(
					GlobalSettings::getInstance()->get_destination_path(*iter), err_code);
			//cout << "err_code = " << err_code << " result = " << result << " " << GlobalSettings::getInstance()->get_destination_path(*iter) << endl;
			result = boost::filesystem::create_directories(
					GlobalSettings::getInstance()->get_destination_hybrid_path(*iter), err_code);
			//cout << "err_code = " << err_code << " result = " << result << " " << GlobalSettings::getInstance()->get_destination_hybrid_path(*iter) << endl;
			result = boost::filesystem::create_directories(
					GlobalSettings::getInstance()->get_destination_deliberative_only_path(*iter), err_code);
			//cout << "err_code = " << err_code << " result = " << result << " " << GlobalSettings::getInstance()->get_destination_deliberative_only_path(*iter) << endl;

			//fs::create_directory("sandbox/1/2/b");

			//if (!result) {
				// ERROR
				// TODO better error message
			//	cerr << "ERROR: main()" << endl;
			//	break;
			//}

			//std::experimental::filesystem fs;

			SpecGenerator spec_generator(*iter);
			spec_generator.generate_specs();

			++iter;
		}

		// Do model-checking for the given location
		// Intentionally separated out the specification generation and model-checking
		iter = input_dirs.begin();

		while (iter != input_dirs.end()) {
			cout << "Profiling inside directory " << *iter << endl;
			Log::getInstance()->write("Profiling inside directory " + *iter);

			// For hybrid model
			string model_path = GlobalSettings::getInstance()->get_hybrid_spec_path(*iter);
			string result_file = GlobalSettings::getInstance()->get_hybrid_result_path(*iter);
			string adversary_file = GlobalSettings::getInstance()->get_hybrid_adversary_path(*iter);
			string states_file = GlobalSettings::getInstance()->get_hybrid_states_path(*iter);
			string labels_file = GlobalSettings::getInstance()->get_hybrid_labels_path(*iter);

			cout << "Hybrid profiling inside directory " << *iter << endl;
			Log::getInstance()->write("Hybrid profiling inside directory " + *iter);

			InvokePrism* invoke_prism = new InvokePrism(model_path, result_file, adversary_file, states_file, labels_file);
			invoke_prism->run_prism();
			delete invoke_prism;

			//  Now for slow deliberative only model
			model_path = GlobalSettings::getInstance()->get_delibetaive_only_spec_path(*iter);
			result_file = GlobalSettings::getInstance()->get_deliberative_only_result_path(*iter);
			adversary_file = GlobalSettings::getInstance()->get_deliberative_adversary_path(*iter);
			states_file = GlobalSettings::getInstance()->get_deliberative_adversary_path(*iter);
			labels_file = GlobalSettings::getInstance()->get_deliberative_labels_path(*iter);

			cout << "Deliberative only profiling inside directory " << *iter << endl;
			Log::getInstance()->write("Deliberative only profiling inside directory  " + *iter);

			invoke_prism = new InvokePrism(model_path, result_file, adversary_file, states_file, labels_file);
			invoke_prism->run_prism();
			delete invoke_prism;

			++iter;
		}

		// open a new csv file
		DBWriter db_writer = DBWriter(GlobalSettings::getInstance()->get_output_db_file());
		db_writer.write_header(ProblemDB::getInstance()->get_header());

		// Read result file from each location.
		// input dirs iterate
		iter = input_dirs.begin();

		while (iter != input_dirs.end()) {
			string hybrid_result_file = GlobalSettings::getInstance()->get_hybrid_result_path(*iter);
			string delieberative_result_file = GlobalSettings::getInstance()->get_deliberative_only_result_path(*iter);

			double hybrid_result = get_result_from_file(hybrid_result_file);
			double deliberative_result = get_result_from_file(delieberative_result_file);

			bool use_reactive = (hybrid_result > deliberative_result) ? 1 : 0;

			//const vector<float>time_series = ProblemDB::getInstance()->get_time_series(*iter);
			const ProblemDB::ProblemData* data = ProblemDB::getInstance()->get_problem_data(*iter);

			cout << "Writing results for directory " << *iter << endl;
			Log::getInstance()->write("Writing results for directory " + *iter);
			cout << "Use reactive = " << use_reactive << endl;
			Log::getInstance()->write("Use reactive = " + *iter);

			db_writer.write_line(*iter, data, use_reactive);

			++iter;
		}

		// read hybrid and slow result file
		// write to csv file
		// close the csv file

		// Write result to database i.e., features, Yes/No
		db_writer.close_writer();
		ProblemDB::getInstance()->clean_db();

		cout << "=========================== PROFILING DONE ======================" << endl;
		Log::getInstance()->write("=========================== PROFILING DONE ======================");
	} else {
		std::cerr << "ERROR: No matching directories found" << std::endl;
		Log::getInstance()->write("ERROR: No matching directories found");
	}

	Log::close_writer();

	return 0;
}

