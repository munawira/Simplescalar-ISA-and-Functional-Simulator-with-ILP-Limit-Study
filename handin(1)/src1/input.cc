#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "info.h"
#include "misc.h"
#include "ss.h"
#include "parameters.h"

extern SS_TIME_TYPE SKIP_AMT;
extern bool USE_INSTR_LIMIT;
extern SS_TIME_TYPE INSTR_LIMIT;
extern bool PERFECT_BRANCH_PREDICTION;
/////////////////////////////////////////////////////////
// For use by qsort.
// This function is used for sorting simulation args,
// a necessary step in generating the output filename.
/////////////////////////////////////////////////////////
int compare_args(const void *fa, const void *fb) {
        char **a;
        char **b;
        char A;
        char B;
 
        a = (char **)fa;
        b = (char **)fb;
 
        A = (*a)[1];
        B = (*b)[1];
 
        return( A - B );
}
/////////////////////////////////////////////////////////


/* simulator-specific options */
char *sim_optstring = "f:z:Z:P";

void
sim_options(int argc, char **argv)
{
  char c;

  bool user_specified_output = false;
  char output_filename[1024];
  time_t t;
  char timestring[32];
  unsigned int i;
  int sorted_argc;
  char **sorted_argv;
 

  /* parse options */
  getopt_init();
  while ((c = getopt_next(argc, argv, sim_optstring)) != EOF)
    {
      switch (c) {
         case 'f':
            user_specified_output = true;
            strcpy(output_filename, "out.");
            strcat(output_filename, getopt_arg);
            break;
 
	 case 'z':
	    USE_INSTR_LIMIT = true;
	    INSTR_LIMIT = atoi(getopt_arg);
	    break;

         case 'Z':
            SKIP_AMT = atoi(getopt_arg);
            break;

	case 'P':
	    PERFECT_BRANCH_PREDICTION = true;
	    break;
	

	 default:
	    break;
      }
    }

    if (USE_INSTR_LIMIT)
       INSTR_LIMIT = (SKIP_AMT + INSTR_LIMIT);

  ///////////////////////////////////////////////
  // Compute the output filename.
  // The filename is derived from non-default
  // simulation settings (i.e. sorted args).
  ///////////////////////////////////////////////
  if (!user_specified_output) {
     sorted_argc = 0;
     sorted_argv = new char *[argc];
 
     i = 1;
     while ( (i < argc) && (argv[i][0] == '-') ) {
        sorted_argv[sorted_argc] = argv[i];
        sorted_argc += 1;
 
        i += 1;
     }
 
     qsort(sorted_argv, sorted_argc, sizeof(char *), compare_args);
 
     // Now create the output filename from sorted argument list.
     strcpy(output_filename, "out.");
     if (sorted_argc == 0) {
        strcat(output_filename, "base");
     }
     else {
        for (i = 0; i < sorted_argc; i++)
           strcat(output_filename, sorted_argv[i]);
     }
  }
 
  fp_info = fopen(output_filename, "r");
  if (fp_info) {
     fclose(fp_info);
 
     time(&t);
     strftime(timestring, 32, ".%b%d.%T", localtime(&t));
     strcat(output_filename, timestring);
 
     fp_info = fopen(output_filename, "r");
     assert(!fp_info);
  }
  fp_info = fopen(output_filename, "w");


  ////////////////////////////////////
  // Print out Simulation Parameters:
  ////////////////////////////////////
  INFO("---------------------------------");

  char from[100], to[100];
  if (USE_INSTR_LIMIT) {
     INFO("FROM -> TO = %s -> %s", comma(SKIP_AMT, from, 100),
				   comma(INSTR_LIMIT, to, 100));
     //INFO("FROM -> TO = %.0f -> %.0f", (double)SKIP_AMT, (double)INSTR_LIMIT);
  }
  else {
     INFO("FROM -> TO = %s -> (end of benchmark)", comma(SKIP_AMT, from, 100));
     //INFO("FROM -> TO = %.0f -> (end of benchmark)", (double)SKIP_AMT);
  }

  INFO("---------------------------------");
  INFO("PERFECT_BRANCH_PREDICTION = %s", (PERFECT_BRANCH_PREDICTION ? "true" : "false"));
  INFO("---------------------------------");
}
