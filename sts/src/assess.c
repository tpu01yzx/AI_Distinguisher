/* --------------------------------------------------------------------------
   Title       :  The NIST Statistical Test Suite

   Date        :  December 1999

   Programmer  :  Juan Soto

   Summary     :  For use in the evaluation of the randomness of bitstreams
                  produced by cryptographic random number generators.

   Package     :  Version 1.0

   Copyright   :  (c) 1999 by the National Institute Of Standards & Technology

   History     :  Version 1.0 by J. Soto, October 1999
                  Revised by J. Soto, November 1999
                  Revised by Larry Bassham, March 2008

   Keywords    :  Pseudorandom Number Generator (PRNG), Randomness, Statistical 
                  Tests, Complementary Error functions, Incomplete Gamma 
                  Function, Random Walks, Rank, Fast Fourier Transform, 
                  Template, Cryptographically Secure PRNG (CSPRNG),
                  Approximate Entropy (ApEn), Secure Hash Algorithm (SHA-1), 
                  Blum-Blum-Shub (BBS) CSPRNG, Micali-Schnorr (MS) CSPRNG, 

   Source      :  David Banks, Elaine Barker, James Dray, Allen Heckert, 
                  Stefan Leigh, Mark Levenson, James Nechvatal, Andrew Rukhin, 
                  Miles Smid, Juan Soto, Mark Vangel, and San Vo.

   Technical
   Assistance  :  Larry Bassham, Ron Boisvert, James Filliben, Daniel Lozier,
                  and Bert Rust.

   Warning     :  Portability Issues.

   Limitation  :  Amount of memory allocated for workspace.

   Restrictions:  Permission to use, copy, and modify this software without 
                  fee is hereby granted, provided that this entire notice is 
                  included in all copies of any software which is or includes
                  a copy or modification of this software and in all copies 
                  of the supporting documentation for such software.
   -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../include/decls.h"
#include "../include/cephes.h"  
#include "../include/utilities.h"
#include "../include/getopt.h"

void	partitionResultFile(int numOfFiles, int numOfSequences, int option, int testNameID);
void	postProcessResults(int option);
int		cmp(const double *a, const double *b);
int		computeMetrics(char *s, int test);

void display_usage();
void ReadParameter(int argc, char *argv[]);
void Exit(int code, const void *more);

int
main(int argc, char *argv[])
{
	int		i;
	int		option;			/* TEMPLATE LENGTH/STREAM LENGTH/GENERATOR*/
	char	*streamFile;	/* STREAM FILENAME     */
		
	ReadParameter(argc, argv);

	if(args.inFileName != NULL) {
		option = 0; streamFile = args.inFileName;
	} else {
		option = generatorOptions(&streamFile);
	}

	if(args.pflag == 1) {
		for(i = 0; i < args.ptests; i++) {			
			testVector[args.tests[i]] = 1;
		}
		if(testVector[0] == 1) {
			for(i = 1; i <= NUMOFTESTS; i++ ) {
				testVector[i] = 1;
			}
		}
	} else {
		chooseTests();
	}

	if(args.pflag == 0) {		
		fixParameters();
	}

	openOutputStreams(option);
	invokeTestSuite(option, streamFile);
	fclose(freqfp);
	for( i=1; i<=NUMOFTESTS; i++ ) {
		if ( stats[i] != NULL )
			fclose(stats[i]);
		if ( results[i] != NULL )
			fclose(results[i]);
	}
	if ( (testVector[0] == 1) || (testVector[TEST_CUSUM] == 1) ) 
		partitionResultFile(2, args.para.numOfBitStreams, option, TEST_CUSUM);
	if ( (testVector[0] == 1) || (testVector[TEST_NONPERIODIC] == 1) ) 
		partitionResultFile(MAXNUMOFTEMPLATES, args.para.numOfBitStreams, option, TEST_NONPERIODIC);
	if ( (testVector[0] == 1) || (testVector[TEST_RND_EXCURSION] == 1) )
		partitionResultFile(8, args.para.numOfBitStreams, option, TEST_RND_EXCURSION);
	if ( (testVector[0] == 1) || (testVector[TEST_RND_EXCURSION_VAR] == 1) )
		partitionResultFile(18, args.para.numOfBitStreams, option, TEST_RND_EXCURSION_VAR);
	if ( (testVector[0] == 1) || (testVector[TEST_SERIAL] == 1) )
		partitionResultFile(2, args.para.numOfBitStreams, option, TEST_SERIAL);
	/*
	fprintf(summary, "------------------------------------------------------------------------------\n");
	fprintf(summary, "RESULTS FOR THE UNIFORMITY OF P-VALUES AND THE PROPORTION OF PASSING SEQUENCES\n");
	fprintf(summary, "------------------------------------------------------------------------------\n");
	fprintf(summary, "   generator is <%s>\n", streamFile);
	fprintf(summary, "------------------------------------------------------------------------------\n");
	fprintf(summary, " C1  C2  C3  C4  C5  C6  C7  C8  C9 C10  P-VALUE  PROPORTION  STATISTICAL TEST\n");
	fprintf(summary, "------------------------------------------------------------------------------\n");
	fflush(summary);
	*/
	postProcessResults(option);
	fclose(summary);

	return 1;
}

void ReadParameter(int argc, char *argv[])
{

	static const char *optString = "b:n:o:s:l:a:t:M:N:PL:I:O:h?";

	static const struct option longOpts[] = {
		{ "blockFrequencyBlockLength", required_argument,NULL, 'b' },
		{ "nonOverlappingTemplateBlockLength", required_argument,NULL, 'n' },
		{ "overlappingTemplateBlockLength", required_argument,NULL, 'o' },
		{ "serialBlockLength", required_argument,NULL, 's' },
		{ "linearComplexitySequenceLength", required_argument,NULL, 'l' },
		{ "approximateEntropyBlockLength", required_argument,NULL, 'a' },
		{ "parameterFromCommandline", no_argument, NULL, 'P'},
		{ "modeOfFile", required_argument, NULL, 'M'},
		{ "numOfBitStream", required_argument, NULL, 'N'},
		{ "tests", required_argument,NULL, 't' },
		{ "length", required_argument,NULL, 'L' },
		{ "input", required_argument,NULL, 'I' },
		{ "output", required_argument,NULL, 'O' },		
		{ "help", no_argument, NULL, 'h'},
		{ NULL, no_argument, NULL, 0 }
	};	
	int opt = -1;

	memset(&args, 0, sizeof(args));	
	args.para.blockFrequencyBlockLength = 128;
	args.para.nonOverlappingTemplateBlockLength = 9;
	args.para.overlappingTemplateBlockLength = 9;
	args.para.approximateEntropyBlockLength = 10;
	args.para.serialBlockLength = 16;
	args.para.linearComplexitySequenceLength = 500;
	args.para.numOfBitStreams = 100;
	args.mode = MODE_ASCII;
	args.ptests = 1;
	args.tests[0]  = 0;

	args.inFile = stdin;
	args.outFile = stdout;
    while( (opt = getopt_long( argc, argv, optString, longOpts, NULL)) != -1 ) {
        switch( opt ) {
			case 'b':
				args.para.blockFrequencyBlockLength = atoi(optarg);                
                break;
			case 'n':
				args.para.nonOverlappingTemplateBlockLength = atoi(optarg);                
                break;
			case 'o':
				args.para.overlappingTemplateBlockLength = atoi(optarg);                
                break;
			case 's':
				args.para.serialBlockLength = atoi(optarg);                
                break;
			case 'l':
				args.para.linearComplexitySequenceLength = atoi(optarg);                
                break;
			case 'a':
				args.para.approximateEntropyBlockLength = atoi(optarg);                
                break;
			case 't':				
				args.ptests = split(optarg, ",", args.tests, NUMOFTESTS);
				if(args.ptests <= 0 || Check_Range(args.tests, NUMOFTESTS, 0, NUMOFTESTS) == 0) {
					Exit(ERROR_BAD_TEST_PARAMETER, optarg);					
				}				
				break;
			case 'P':
				args.pflag = 1;
                break;
			case 'M':				
				args.mode = atoi(optarg);
				if(args.mode != MODE_ASCII && args.mode !=  MODE_BINARY) {
					Exit(ERROR_BAD_MODE_PARAMETER, optarg);	
				}
                break;
			case 'N':
				args.para.numOfBitStreams = atoi(optarg);
                break;
			case 'L':
				args.n = atoi(optarg);                
                break;
            case 'O':
                args.outFileName = optarg;
                break;
			case 'I':
                args.inFileName = optarg;
                break;
            case 'h':   /* fall-through is intentional */
            case '?':
                display_usage();	Exit(0, NULL);
                break;
            default:
                /* You won't actually get here. */
                break;
        }		
	};
	if(args.n == 0) { display_usage();	Exit(0, NULL); }
}

void display_usage()
{
	/*
	args.para.blockFrequencyBlockLength = 128;
	args.para.nonOverlappingTemplateBlockLength = 9;
	args.para.overlappingTemplateBlockLength = 9;
	args.para.approximateEntropyBlockLength = 10;
	args.para.serialBlockLength = 16;
	args.para.linearComplexitySequenceLength = 500;
	*/
	printf(""
"assess [options] --length num\n"
"  -L, --length num       length of stream to be tested. \n"
"all options:\n"
"options for tests:\n"
"  -b, --blockFrequencyBlockLength n           Default is %d.  \n"
"  -n, --nonOverlappingTemplateBlockLength n   Default is %d.  \n"
"  -o, --overlappingTemplateBlockLength n      Default is %d.  \n"
"  -a, --approximateEntropyBlockLength n       Default is %d.  \n"
"  -s, --serialBlockLength n                   Default is %d.  \n"
"  -l, --linearComplexitySequenceLength n      Default is %d.  \n"
"options for control:\n"
"  -t, --tests n1,n2,...nm          Default is 0. \n"
"                                   Could be any integers in this rang [0, %d]. \n"
"                                   0 indicates invoking all tests. \n"
"  -N, --numOfBitStream n           Default is %d. \n"
"  -M, --mode n                     Default is %d. \n"
"                                   Could be %d(%s) or %d(%s). \n"
"  -P, --parameterFromCommandline   Set parameter from command line. \n"
"  -I, --input filename             Default is stdin.  \n"
"  -O, --output filename            Default is stdout. \n"
"  -h, --help                       Show this message. \n"
"", 
args.para.blockFrequencyBlockLength,
args.para.nonOverlappingTemplateBlockLength,
args.para.overlappingTemplateBlockLength,
args.para.approximateEntropyBlockLength,
args.para.serialBlockLength,
args.para.linearComplexitySequenceLength,
NUMOFTESTS,
args.para.numOfBitStreams,
args.mode, MODE_BINARY, "BINARY", MODE_ASCII, "ASCII");
}

void Exit(int code, const void *more)
{
	if(code == ERROR_CANT_OPEN_FILE) printf("Can't open file:[%s].\n", (char *)more);
	if(code == ERROR_BAD_TEST_PARAMETER) printf("Bad parameter for -t, --test:[%s].\n", (char*)more);
	if(code == ERROR_BAD_MODE_PARAMETER) printf("Bad parameter for -M, --mode:[%s].\n", (char*)more);
	exit(code);
}

void
partitionResultFile(int numOfFiles, int numOfSequences, int option, int testNameID)
{ 
	int		i, k, m, j, start, end, num, numread;
	float	c;
	FILE	**fp = (FILE **)calloc(numOfFiles+1, sizeof(FILE *));
	int		*results = (int *)calloc(numOfFiles, sizeof(int *));
	char	*s[MAXFILESPERMITTEDFORPARTITION];
	char	resultsDir[MAX_PATH];
	
	for ( i=0; i<MAXFILESPERMITTEDFORPARTITION; i++ )
		s[i] = (char*)calloc(MAX_PATH, sizeof(char));
	
	sprintf(resultsDir, "experiments/%s/%s_results.txt", generatorDir[option], testNames[testNameID]);
	
	if ( (fp[numOfFiles] = fopen(resultsDir, "r")) == NULL ) {
		printf("%s", resultsDir);
		printf(" -- file not found. Exiting program.\n");
		exit(-1);
	}
	
	for ( i=0; i<numOfFiles; i++ ) {
			sprintf(s[i], "experiments/%s/%s_data%d.txt", generatorDir[option], testNames[testNameID], i+1);
	}
	numread = 0;
	m = numOfFiles/20;
	if ( (numOfFiles%20) != 0 )
		m++;
	for ( i=0; i<numOfFiles; i++ ) {
		if ( (fp[i] = fopen(s[i], "w")) == NULL ) {
			printf("%s", s[i]);
			printf(" -- file not found. Exiting program.\n");
			exit(-1);
		}
		fclose(fp[i]);
	}
	for ( num=0; num<numOfSequences; num++ ) {
		for ( k=0; k<m; k++ ) { 			/* FOR EACH BATCH */
			
			start = k*20;		/* BOUNDARY SEGMENTS */
			end   = k*20+19;
			if ( k == (m-1) )
				end = numOfFiles-1;
			
			for ( i=start; i<=end; i++ ) {		/* OPEN FILE */
				if ( (fp[i] = fopen(s[i], "a")) == NULL ) {
					printf("%s", s[i]);
					printf(" -- file not found. Exiting program.\n");
					exit(-1);
				}
			}
			
			for ( j=start; j<=end; j++ ) {		/* POPULATE FILE */
				fscanf(fp[numOfFiles], "%f", &c);
				fprintf(fp[j], "%f\n", c);
				numread++;
			}

			for ( i=start; i<=end; i++ )		/* CLOSE FILE */
				fclose(fp[i]);
		}
	}
	fclose(fp[numOfFiles]);
	for ( i=0; i<MAXFILESPERMITTEDFORPARTITION; i++ )
		free(s[i]);

	return;
}

int
cmp(const double *a, const double *b)
{
	if ( *a < *b )
		return -1;
	if ( *a == *b )
		return 0;
	return 1;
}

void
postProcessResults(int option)
{
	int		i, k, randomExcursionSampleSize, generalSampleSize;
	int		passRate, case1, case2, numOfFiles = 2;
	double	p_hat;
	char	s[200];
	
	for ( i=1; i<=NUMOFTESTS; i++ ) {		// FOR EACH TEST
		if ( testVector[i] ) {
			// SPECIAL CASES -- HANDLING MULTIPLE FILES FOR A SINGLE TEST
			if ( ((i == TEST_CUSUM) && testVector[TEST_CUSUM] ) ||
				 ((i == TEST_NONPERIODIC) && testVector[TEST_NONPERIODIC] ) ||
				 ((i == TEST_RND_EXCURSION) && testVector[TEST_RND_EXCURSION]) ||
				 ((i == TEST_RND_EXCURSION_VAR) && testVector[TEST_RND_EXCURSION_VAR]) || 
				 ((i == TEST_SERIAL) && testVector[TEST_SERIAL]) ) {
				
				if ( (i == TEST_NONPERIODIC) && testVector[TEST_NONPERIODIC] )  
					numOfFiles = MAXNUMOFTEMPLATES;
				else if ( (i == TEST_RND_EXCURSION) && testVector[TEST_RND_EXCURSION] ) 
					numOfFiles = 8;
				else if ( (i == TEST_RND_EXCURSION_VAR) && testVector[TEST_RND_EXCURSION_VAR] ) 
					numOfFiles = 18;
				else
					numOfFiles = 2;
				for ( k=0; k<numOfFiles; k++ ) {
					sprintf(s, "experiments/%s/%s_data%d.txt", generatorDir[option], testNames[i], k+1);
					if ( (i == TEST_RND_EXCURSION) || (i == TEST_RND_EXCURSION_VAR) ) 
						randomExcursionSampleSize = computeMetrics(s,i);
					else
						generalSampleSize = computeMetrics(s,i);
				}
			}
			else {
				sprintf(s, "experiments/%s/%s_results.txt", generatorDir[option], testNames[i]);
				generalSampleSize = computeMetrics(s,i);
			}
		}
	}
	/*
	fprintf(summary, "\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	case1 = 0;
	case2 = 0;
	if ( testVector[TEST_RND_EXCURSION] || testVector[TEST_RND_EXCURSION_VAR] ) 
		case2 = 1;
	for ( i=1; i<=NUMOFTESTS; i++ ) {
		if ( testVector[i] && (i != TEST_RND_EXCURSION) && (i != TEST_RND_EXCURSION_VAR) ) {
			case1 = 1;
			break;
		}
	}
	p_hat = 1.0 - ALPHA;
	if ( case1 ) {
		if ( generalSampleSize == 0 ) {
			fprintf(summary, "The minimum pass rate for each statistical test with the exception of the\n");
			fprintf(summary, "random excursion (variant) test is undefined.\n\n");
		}
		else {
			passRate = (int)((p_hat - 3.0 * sqrt((p_hat*ALPHA)/generalSampleSize)) * generalSampleSize);
			fprintf(summary, "The minimum pass rate for each statistical test with the exception of the\n");
			fprintf(summary, "random excursion (variant) test is approximately = %d for a\n", generalSampleSize ? passRate : 0);
			fprintf(summary, "sample size = %d binary sequences.\n\n", generalSampleSize);
		}
	}
	if ( case2 ) {
		if ( randomExcursionSampleSize == 0 )
			fprintf(summary, "The minimum pass rate for the random excursion (variant) test is undefined.\n\n");
		else {
			passRate = (int)((p_hat - 3.0 * sqrt((p_hat*ALPHA)/randomExcursionSampleSize)) * randomExcursionSampleSize);
			fprintf(summary, "The minimum pass rate for the random excursion (variant) test\n");
			fprintf(summary, "is approximately = %d for a sample size = %d binary sequences.\n\n", passRate, randomExcursionSampleSize);
		}
	}
	fprintf(summary, "For further guidelines construct a probability table using the MAPLE program\n");
	fprintf(summary, "provided in the addendum section of the documentation.\n");
	fprintf(summary, "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	*/
}

int
computeMetrics(char *s, int test)
{
	int		j, pos, count, passCount, sampleSize, expCount, proportion_threshold_min, proportion_threshold_max;
	int		freqPerBin[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	double	*A, *T, chi2, uniformity, p_hat;
	float	c;
	FILE	*fp;
	
	if ( (fp = fopen(s, "r")) == NULL ) {
		printf("%s",s);
		printf(" -- file not found. Exiting program.\n");
		exit(-1);
	}
	
	if ( (A = (double *)calloc(args.para.numOfBitStreams, sizeof(double))) == NULL ) {
		printf("Final Analysis Report aborted due to insufficient workspace\n");
		return 0;
	}
	
	/* Compute Metric 1: Proportion of Passing Sequences */
	
	count = 0; 		
	sampleSize = args.para.numOfBitStreams;
	
	if ( (test == TEST_RND_EXCURSION) || (test == TEST_RND_EXCURSION_VAR) ) { /* Special Case: Random Excursion Tests */
		if ( (T = (double *)calloc(args.para.numOfBitStreams, sizeof(double))) == NULL ) {
			printf("Final Analysis Report aborted due to insufficient workspace\n");
			return 0;
		}
		for ( j=0; j<sampleSize; j++ ) {
			fscanf(fp, "%f", &c);
			if ( c > 0.000000 )
				T[count++] = c;
		}
		
		if ( (A = (double *)calloc(count, sizeof(double))) == NULL ) {
			printf("Final Analysis Report aborted due to insufficient workspace\n");
			return 0;
		}
		
		for ( j=0; j<count; j++ )
			A[j] = T[j];
		
		sampleSize = count;
		count = 0;
		for ( j=0; j<sampleSize; j++ )
			if ( A[j] < ALPHA )
				count++;
		free(T);
	}
	else {
		if ( (A = (double *)calloc(sampleSize, sizeof(double))) == NULL ) {
			printf("Final Analysis Report aborted due to insufficient workspace\n");
			return 0;
		}
		for ( j=0; j<sampleSize; j++ ) {
			fscanf(fp, "%f", &c);
			if ( c < ALPHA )
				count++;
			A[j] = c;
		}
	}
	if ( sampleSize == 0 )
		passCount = 0;
	else
		passCount = sampleSize - count;
	
	p_hat = 1.0 - ALPHA;
	proportion_threshold_max = (int)((p_hat + 3.0 * sqrt((p_hat*ALPHA)/sampleSize)) * sampleSize);
	proportion_threshold_min = (int)((p_hat - 3.0 * sqrt((p_hat*ALPHA)/sampleSize)) * sampleSize);
	
	/* Compute Metric 2: Histogram */
	
	qsort((void *)A, sampleSize, sizeof(double), (void *)cmp);
	for ( j=0; j<sampleSize; j++ ) {
		pos = (int)floor(A[j]*10);
		if ( pos == 10 )
			pos--;
		freqPerBin[pos]++;
	}
	chi2 = 0.0;
	expCount = sampleSize/10;
	if ( expCount == 0 )
		uniformity = 0.0;
	else {
		for ( j=0; j<10; j++ )
			chi2 += pow(freqPerBin[j]-expCount, 2)/expCount;
		uniformity = cephes_igamc(9.0/2.0, chi2/2.0);
	}
	/*
	for ( j=0; j<10; j++ )			//DISPLAY RESULTS
		fprintf(summary, "%3d ", freqPerBin[j]);
	
	if ( expCount == 0 )
		fprintf(summary, "    ----    ");
	else if ( uniformity < 0.0001 )
		fprintf(summary, " %8.6f * ", uniformity);
	else
		fprintf(summary, " %8.6f   ", uniformity);
	
	if ( sampleSize == 0 )
		fprintf(summary, " ------     %s\n", testNames[test]);
	//	else if ( proportion < 0.96 )
	else if ( (passCount < proportion_threshold_min) || (passCount > proportion_threshold_max))
		fprintf(summary, "%4d/%-4d *  %s\n", passCount, sampleSize, testNames[test]);
	else
		fprintf(summary, "%4d/%-4d    %s\n", passCount, sampleSize, testNames[test]);
	*/

	if ( expCount == 0 )
		fprintf(summary, " %8.6f", 0);
	else
		fprintf(summary, " %8.6f", uniformity);

	fclose(fp);
	free(A);
	
	return sampleSize;
}
