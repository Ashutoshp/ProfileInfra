//============================================================================
// Name        : InvokePrism.cpp
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : Code to invoke Prism to model-check the plans
//===========================================================================

//#include <unistd.h>
//#include <sys/types.h>
#include <sys/wait.h>
//#include <fstream>
//#include <string>
#include <boost/tokenizer.hpp>
//#include <cstdlib>
//#include <set>
#include <string.h>
//#include <map>
#include <sstream>
//#include <sys/stat.h>
//#include <fcntl.h>
#include <errno.h>
#include <iostream>

using namespace std;

const char* PRISM = "/home/ashutosp/Dropbox/Prism/mdp/linux/prism/bin/prism";
//const char* PRISM_PROPERTY = "\"Rmax=? [ F \\\"final\\\" ]\"";
const char* PRISM_PROPERTY = "Rmax=? [ F \"final\" ]";
const char* PRISM_PROPERTY_RT = "Rmax=? [ F end ]";
const char* PRISM_PROPERTY_PROB = "Pmax=?[true U end]";
const char* TACTIC_SUFFIX = "_start";
const char* DIVERT = "divert_";
const char* ENGINE = "-s";
const char* CUDD = "-cuddmaxmem";
const char* CUDDMEM = "4g";

bool runPrism(const char* modelPath, const char* adversaryPath, const char* statesPath,
		const char* labelsPath, bool returnPlan) {
	// TODO need to throw exceptions to provide better error handling
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

		if (returnPlan) {
		    //if (simulation.getSystemModule()->par("usePredictor").boolValue()) {

		    //} else {
		    status = execlp(PRISM, PRISM, modelPath, "-pctl", PRISM_PROPERTY, "-exportadv", adversaryPath,
				"-exportstates", statesPath, "-exportlabels", labelsPath, (char*) 0);
		    //}
		} else {
		    status = execlp(PRISM, PRISM, modelPath, "-pctl", PRISM_PROPERTY, "-exportadv", adversaryPath,
		                    "-exportstates", statesPath, CUDD, CUDDMEM, "-s", (char*) 0);
		}

		if (status == -1) { // the only option really, otherwise execlp doesn't return
		    cout << "runPrism() error: " << strerror(errno) << endl;
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
