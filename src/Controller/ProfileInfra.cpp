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
//#include <jni.h>


void do_settings() {
	GlobalSettings::getInstance()->set_source_dir("/home/ashutosp/helloWorld/slow_only/case-3/profiling_problem/");
	GlobalSettings::getInstance()->set_destination_dir("/home/ashutosp/helloWorld/slow_only/case-3/profiling_problem/profiled_data");
	GlobalSettings::getInstance()->set_directory_prefix("model");
	GlobalSettings::getInstance()->set_model_checker_path("");
	GlobalSettings::getInstance()->set_reactive_plan_dir("fast");
	GlobalSettings::getInstance()->set_deliberative_plan_dir("slow");
	GlobalSettings::getInstance()->set_deliberative_spec_file("ttimemodel.prism");
	GlobalSettings::getInstance()->set_deliberative_planning_time_file(""); // TODO
	GlobalSettings::getInstance()->set_destination_hybrid_dir("hybrid");
	GlobalSettings::getInstance()->set_destination_deliberative_dir("slow");
	GlobalSettings::getInstance()->set_template_path("/home/ashutosp/helloWorld/slow_only/case-3/profiling_problem/profiled_data/profile.prism");
	GlobalSettings::getInstance()->set_plan_file("");
	GlobalSettings::getInstance()->set_states_file("");
	GlobalSettings::getInstance()->set_labels_file("");
	GlobalSettings::getInstance()->set_result_file("result");
	GlobalSettings::getInstance()->set_model_checker_spec_file("profile.prism");
	GlobalSettings::getInstance()->set_problem_feature_file(""); // TODO
}

int main() {
	// Global settings
	do_settings();

	// Get directories (matching prefix) for input planning problems
	Strings input_dirs = get_prefix_matching_directories(GlobalSettings::getInstance()->get_source_dir().c_str(), GlobalSettings::getInstance()->get_directory_prefix().c_str());

	if (input_dirs.size() != 0) {
		// Iterate each directory and call adaptor to write files to a given location.
		Strings::iterator iter = input_dirs.begin();

		while (iter != input_dirs.end()) {
			//
			// adapt (source directory)
			// it will get slow and fast directory, deliberative time,
			// needs to parse fast plan to extract the action
			// use template and slow specification to create specification file
			// hybrid only is always fixed
			SpecGenerator specGenerator(*iter);
			++iter;
		}
	} else {
		std::cerr << "ERROR: No matching directories found" << std::endl;
	}

	// Run model-checker for given location

	// Read result file from each location

	// Write result to database i.e., features, Yes/No

	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	/*JavaVM *vm;
	JNIEnv *env;
	JavaVMInitArgs vm_args;
	vm_args.version = JNI_VERSION_1_8;
	vm_args.nOptions = 0;
	vm_args.ignoreUnrecognized = 1;

	JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
	//options[0].optionString = "-Djava.class.path=.";   // where to find java .class
	options[0].optionString = "-Xss1280k";

	vm_args.options = options;

	// Construct a VM
	jint res = JNI_CreateJavaVM(&vm, (void **)&env, &vm_args);
	delete options;

	// Construct a String
	jstring jstr = env->NewStringUTF("Hello World");

	// First get the class that contains the method you need to call
	jclass clazz = env->FindClass("java/lang/String");

	// Get the method that you want to call
	jmethodID to_lower = env->GetMethodID(clazz, "toLowerCase",
	                                      "()Ljava/lang/String;");
	// Call the method on the object
	jobject result = env->CallObjectMethod(jstr, to_lower);

	// Get a C-style string
	const char* str = env->GetStringUTFChars((jstring) result, NULL);

	printf("%s\n", str);

	// Clean up
	env->ReleaseStringUTFChars(jstr, str);

	// Shutdown the VM.
	vm->DestroyJavaVM();*/

	return 0;
}

