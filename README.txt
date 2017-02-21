For running the makefile for EDF and LLF case, use the below example as
reference

/* EDF */
make EX_NUM=EX0    
/* This runs the EDF feasibility test code for ex0 test case provided as 
part of assignment. Change EX0 to EX1, EX2,... EX8 to try for different examples */

/* LLF */
make EX_NUM=EX0

There is a debug macro by the name DEBUG_PRINT which can be enabled for
more detailed logs.

There are test specific macros that can be enabled/disabled to run
specific tests

RUN_TIMING_ANALYSIS_TEST: Macro to run timing analysis test for EDF/LLF

RUN_WORST_CASE_RESP_TIME_FEASIBILITY_TEST: Macro to run processor demand 
analysis test for EDF.

RUN_PROCESSOR_UTIL_TEST: Macro to run processor utility test for
EDF/LLF.  
