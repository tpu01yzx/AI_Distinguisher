/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                       D E B U G G I N G  A I D E S
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "config.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                              M A C R O S
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define MAX(x,y)             ((x) <  (y)  ? (y)  : (x))
#define MIN(x,y)             ((x) >  (y)  ? (y)  : (x))
#define isNonPositive(x)     ((x) <= 0.e0 ?   1  : 0)
#define isPositive(x)        ((x) >  0.e0 ?   1 : 0)
#define isNegative(x)        ((x) <  0.e0 ?   1 : 0)
#define isGreaterThanOne(x)  ((x) >  1.e0 ?   1 : 0)
#define isZero(x)            ((x) == 0.e0 ?   1 : 0)
#define isOne(x)             ((x) == 1.e0 ?   1 : 0)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
                         G L O B A L  C O N S T A N T S
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define ALPHA							0.01	/* SIGNIFICANCE LEVEL */
#define MAXNUMOFTEMPLATES				148		/* APERIODIC TEMPLATES: 148=>temp_length=9 */
#define NUMOFTESTS						15		/* MAX TESTS DEFINED  */
#define NUMOFGENERATORS					10		/* MAX PRNGs */
#define MAXFILESPERMITTEDFORPARTITION	148
#define	TEST_FREQUENCY					1
#define	TEST_BLOCK_FREQUENCY			2
#define	TEST_CUSUM						3
#define	TEST_RUNS						4
#define	TEST_LONGEST_RUN				5
#define	TEST_RANK						6
#define	TEST_FFT						7
#define	TEST_NONPERIODIC				8
#define	TEST_OVERLAPPING				9
#define	TEST_UNIVERSAL					10
#define	TEST_APEN						11
#define	TEST_RND_EXCURSION				12
#define	TEST_RND_EXCURSION_VAR			13
#define	TEST_SERIAL						14
#define	TEST_LINEARCOMPLEXITY			15


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                   G L O B A L   D A T A  S T R U C T U R E S
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

typedef unsigned char	BitSequence;

typedef struct _testParameters {
	int		blockFrequencyBlockLength;
	int		nonOverlappingTemplateBlockLength;
	int		overlappingTemplateBlockLength;
	int		serialBlockLength;
	int		linearComplexitySequenceLength;
	int		approximateEntropyBlockLength;
	int		numOfBitStreams;
} TP;

typedef struct _globalArgs_t {  
	int		n;	
	char pflag;
	char npflag;
	TP para;
	int tests[NUMOFTESTS];
	int ptests;
	int mode;
    char *outFileName;    /* -O option */
    FILE *outFile;    
	char *inFileName;    /* -I option */
    FILE *inFile;        
} globalArgs_t;

#define DEC_DIGITS_OF_INT32		(12)
#define TIME_STR_LEN			(64)

#define NO_ERROR					(0)
#define ERROR_CANT_OPEN_FILE		(1)
#define ERROR_BAD_TEST_PARAMETER	(2)
#define ERROR_BAD_MODE_PARAMETER	(3)

#define MODE_ASCII	(0)
#define MODE_BINARY	(1)

#ifndef MAX_PATH
#ifdef _MAX_PATH
#define MAX_PATH _MAX_PATH
#else
#define MAX_PATH 256
#endif
#endif