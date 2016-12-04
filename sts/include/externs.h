
#include "../include/defs.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                   G L O B A L   D A T A  S T R U C T U R E S 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

extern BitSequence	*epsilon;				// BIT STREAM
extern FILE			*stats[NUMOFTESTS+1];	// FILE OUTPUT STREAM
extern FILE			*results[NUMOFTESTS+1];	// FILE OUTPUT STREAM
extern FILE			*freqfp;				// FILE OUTPUT STREAM
extern FILE			*summary;				// FILE OUTPUT STREAM
extern int			testVector[NUMOFTESTS+1];
extern globalArgs_t args;

extern char	generatorDir[NUMOFGENERATORS][20];
extern char	testNames[NUMOFTESTS+1][32];