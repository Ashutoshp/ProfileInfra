//==================================================================================
// Name        : Tactics.h
// Author      : Ashutosh Pandey
// Version     :
// Copyright   : Your copyright notice
// Description : List all the adaptation tactics
//===================================================================================

#ifndef ADAPTOR_TACTICS_H_
#define ADAPTOR_TACTICS_H_

typedef enum TacticEnum {
    NONE,
    TICK,
    ADD_SERVER_A_START,
    ADD_SERVER_B_START,
    ADD_SERVER_C_START,
    REMOVE_SERVER_A_START,
    REMOVE_SERVER_B_START,
    REMOVE_SERVER_C_START,
    INC_DIMMER,
    DEC_DIMMER,
    DIVERT_TRAFFIC_100_0_0,
    DIVERT_TRAFFIC_75_25_0,
    DIVERT_TRAFFIC_75_0_25,
    DIVERT_TRAFFIC_50_50_0,
    DIVERT_TRAFFIC_50_0_50,
    DIVERT_TRAFFIC_50_25_25,
    DIVERT_TRAFFIC_25_75_0,
    DIVERT_TRAFFIC_25_0_75,
    DIVERT_TRAFFIC_25_50_25,
    DIVERT_TRAFFIC_25_25_50,
    DIVERT_TRAFFIC_0_100_0,
    DIVERT_TRAFFIC_0_0_100,
    DIVERT_TRAFFIC_0_75_25,
    DIVERT_TRAFFIC_0_25_75,
    DIVERT_TRAFFIC_0_50_50
} Action;

typedef enum DartTactics {
	//NONE,
	TACK,
	//TICK,
	TICK2,
	ECMON_START,
	ECMOFF_START,
	GOTIGHT_START,
	GOLOOSE_START,
	INCALT_COMPLETE,
	INCALT2_COMPLETE,
	DECALT_COMPLETE,
	DECALT2_COMPLETE
} DartAction;

#endif /* ADAPTOR_TACTICS_H_ */
