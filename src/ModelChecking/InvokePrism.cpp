//============================================================================
// Name        : InvokePrism.cpp
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Code to invoke Prism to model-check the plans
//===========================================================================
#include <InvokePrism.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
#include <string>
#include <boost/tokenizer.hpp>
#include <cstdlib>
#include <set>
#include <string.h>
#include <map>
#include <sstream>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <GlobalSettings.h>

InvokePrism::InvokePrism(const string& model_path,
		const string& result_file,
		const string& adversary_path,
		const string& states_path,
		const string& labels_path) : m_model_path(model_path),
		m_result_file(result_file),
		m_adversary_path(adversary_path),
		m_states_path(states_path),
		m_labels_path(labels_path),
		m_prism_property("Rmax=? [ F \"final\" ]"),
		m_prism_property_rt("Rmax=? [ F end ]"),
		m_prism_property_prob("Pmax=?[true U end]"),
		m_tactic_suffix("_start"),
		m_divert("divert_"),
		m_engine("-s"),
		m_cudd("-cuddmaxmem"),
		m_cuddmem("4g") {
}

bool InvokePrism::run_prism() const {
	// TODO need to throw exceptions to provide better error handling
	// TODO use Prism APIs for invocation
	// TODO customize flags for Prism invocation

    //checkPwd();
    //static int i = 0;
    //printf("i=%d\n", ++i);
    //char command[4096];

    //sprintf( command, "%s %s -pctl %s -exportadv %s -exportstates %s -exportlabels %s %s %s",
    //        PRISM, modelPath, PRISM_PROPERTY, adversaryPath, statesPath, labelsPath, CUDD, ENGINE);
    //printf("%s\n", command);
    //int res = system(command);

    //assert(res!=-1);
    //return true;*/
    //char command[40960];
    //sprintf( command, "%s %s -pctl %s -exportadv %s -exportstates %s -exportlabels %s",
     //           PRISM, modelPath, PRISM_PROPERTY, adversaryPath, statesPath, labelsPath);
    //printf("%s\n", command);

	pid_t pid = fork();
	if (pid == 0) {
		// child
		// TODO perhaps we need to pipe the output to get errorr descriptions
		// see this url for example: http://www.cs.uleth.ca/~holzmann/C/system/pipeforkexec.htmls
		int status = 0;

		//if (returnPlan) {
		    //if (simulation.getSystemModule()->par("usePredictor").boolValue()) {

		    //} else {
		//    status = execlp(PRISM, PRISM, modelPath, "-pctl", PRISM_PROPERTY, "-exportadv", adversaryPath,
		//		"-exportstates", statesPath, "-exportlabels", labelsPath, (char*) 0);
		    //}
		//} else {
		status = execlp(GlobalSettings::getInstance()->get_model_checker_path().c_str(),
						GlobalSettings::getInstance()->get_model_checker_path().c_str(),
						m_model_path.c_str(),
						"-pctl", m_prism_property.c_str(),
						//"-exportadv", m_adversary_path.c_str(),
						//"-exportlabels", m_labels_path.c_str(),
						//"-exportstates", m_states_path.c_str(),
						"-cuddmaxmem", m_cuddmem.c_str(),
						"-exportresults", m_result_file.c_str(),
						"-s", (char*) 0);
		//}

		if (status == -1) { // the only option really, otherwise execlp doesn't return
		    cout << "InvokePrism::run_prism() error: " << strerror(errno) << endl;
			return false; // error
		}
	} else if (pid == -1) {
		// error
		return false;
	} else {
		// parent
		int status;
		int rval = waitpid(pid, &status, 0);
		if (rval > 0 && WIFEXITED(status) && WEXITSTATUS(status) == 0) {
			return true;
		}
	}

	return false;
}
