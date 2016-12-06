/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
U T I L I T I E S
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "../include/externs.h"
#include "../include/utilities.h"
#include "../include/generators.h"
#include "../include/stat_fncs.h"

int
displayGeneratorOptions()
{
	int		option = 0;

	printf("           G E N E R A T O R    S E L E C T I O N \n");
	printf("           ______________________________________\n\n");
	printf("    [0] Input File                 [1] Linear Congruential\n");
	printf("    [2] Quadratic Congruential I   [3] Quadratic Congruential II\n");
	printf("    [4] Cubic Congruential         [5] XOR\n");
	printf("    [6] Modular Exponentiation     [7] Blum-Blum-Shub\n");
	printf("    [8] Micali-Schnorr             [9] G Using SHA-1\n\n");
	printf("   Enter Choice: ");
	scanf("%d", &option);
	printf("\n\n");

	return option;
}


int
generatorOptions(char** streamFile)
{
	char	file[MAX_PATH];
	int		option = NUMOFGENERATORS+1;
	FILE	*fp;	
	
	while ( (option < 0) || (option > NUMOFGENERATORS) ) {
		option = displayGeneratorOptions();
		switch( option ) {
			case 0:
				printf("\t\tUser Prescribed Input File: ");
				scanf("%s", file);
				*streamFile = (char*)calloc(MAX_PATH, sizeof(char));
				//sprintf(*streamFile, "%s", file);
				strncpy(*streamFile, file, MAX_PATH);
				printf("\n");
				if ( (fp = fopen(*streamFile, "r")) == NULL ) {
					printf("File Error:  file %s could not be opened.\n",  *streamFile);
					exit(-1);
				}
				else
					fclose(fp);
				break;
			case 1:
				*streamFile = "Linear-Congruential";
				break;
			case 2:
				*streamFile = "Quadratic-Congruential-1";
				break;
			case 3:
				*streamFile = "Quadratic-Congruential-2";
				break;
			case 4:
				*streamFile = "Cubic-Congruential";
				break;
			case 5:
				*streamFile = "XOR";
				break;
			case 6:
				*streamFile = "Modular-Exponentiation";
				break;
			case 7:
				*streamFile = "Blum-Blum-Shub";
				break;
			case 8:
				*streamFile = "Micali-Schnorr";
				break;
			case 9:
				*streamFile = "G using SHA-1";
				break;
				
			/* INTRODUCE NEW PRNG NAMES HERE */
			/*
			case 10:  *streamFile = "myNewPRNG";
				break;
			*/
			default:
				printf("Error:  Out of range - Try again!\n");
				break;
		}
	}
	return option;
}


void
chooseTests()
{
	int		i;
	
	printf("                S T A T I S T I C A L   T E S T S\n");
	printf("                _________________________________\n\n");
	printf("    [01] Frequency                       [02] Block Frequency\n");
	printf("    [03] Cumulative Sums                 [04] Runs\n");
	printf("    [05] Longest Run of Ones             [06] Rank\n");
	printf("    [07] Discrete Fourier Transform      [08] Nonperiodic Template Matchings\n");
	printf("    [09] Overlapping Template Matchings  [10] Universal Statistical\n");
	printf("    [11] Approximate Entropy             [12] Random Excursions\n");
	printf("    [13] Random Excursions Variant       [14] Serial\n");
	printf("    [15] Linear Complexity\n\n");
	printf("         INSTRUCTIONS\n");
	printf("            Enter 0 if you DO NOT want to apply all of the\n");
	printf("            statistical tests to each sequence and 1 if you DO.\n\n");
	printf("   Enter Choice: ");
	scanf("%d", &testVector[0]);
	printf("\n");
	if ( testVector[0] == 1 )
		for( i=1; i<=NUMOFTESTS; i++ )
			testVector[i] = 1;
	else {
		printf("         INSTRUCTIONS\n");
		printf("            Enter a 0 or 1 to indicate whether or not the numbered statistical\n");
		printf("            test should be applied to each sequence.\n\n");
		printf("      123456789111111\n");
		printf("               012345\n");
		printf("      ");
		for ( i=1; i<=NUMOFTESTS; i++ ) 
			scanf("%1d", &testVector[i]);
		printf("\n\n");
	}
}


void
fixParameters()
{
	int		counter, testid;
	
	//  Check to see if any parameterized tests are selected
	if ( (testVector[TEST_BLOCK_FREQUENCY] != 1) && (testVector[TEST_NONPERIODIC] != 1) && 
		 (testVector[TEST_OVERLAPPING] != 1) && (testVector[TEST_APEN] != 1) &&
		 (testVector[TEST_SERIAL] != 1) && (testVector[TEST_LINEARCOMPLEXITY] != 1) )
			return;
		
	do {
		counter = 1;
		printf("        P a r a m e t e r   A d j u s t m e n t s\n");
		printf("        -----------------------------------------\n");
		if ( testVector[TEST_BLOCK_FREQUENCY] == 1 )
			printf("    [%d] Block Frequency Test - block length(M):         %d\n", counter++, args.para.blockFrequencyBlockLength);
		if ( testVector[TEST_NONPERIODIC] == 1 )
			printf("    [%d] NonOverlapping Template Test - block length(m): %d\n", counter++, args.para.nonOverlappingTemplateBlockLength);
		if ( testVector[TEST_OVERLAPPING] == 1 )
			printf("    [%d] Overlapping Template Test - block length(m):    %d\n", counter++, args.para.overlappingTemplateBlockLength);
		if ( testVector[TEST_APEN] == 1 )
			printf("    [%d] Approximate Entropy Test - block length(m):     %d\n", counter++, args.para.approximateEntropyBlockLength);
		if ( testVector[TEST_SERIAL] == 1 )
			printf("    [%d] Serial Test - block length(m):                  %d\n", counter++, args.para.serialBlockLength);
		if ( testVector[TEST_LINEARCOMPLEXITY] == 1 )
			printf("    [%d] Linear Complexity Test - block length(M):       %d\n", counter++, args.para.linearComplexitySequenceLength);
		printf("\n");
		printf("   Select Test (0 to continue): ");
		scanf("%1d", &testid);
		printf("\n");
		
		counter = 0;
		if ( testVector[TEST_BLOCK_FREQUENCY] == 1 ) {
			counter++;
			if ( counter == testid ) {
				printf("   Enter Block Frequency Test block length: ");
				scanf("%d", &args.para.blockFrequencyBlockLength);
				printf("\n");
				continue;
			}
		}
		if ( testVector[TEST_NONPERIODIC] == 1 ) {
			counter++;
			if ( counter == testid ) {
				printf("   Enter NonOverlapping Template Test block Length: ");
				scanf("%d", &args.para.nonOverlappingTemplateBlockLength);
				printf("\n");
				continue;
			}
		}
		if ( testVector[TEST_OVERLAPPING] == 1 ) {
			counter++;
			if ( counter == testid ) {
				printf("   Enter Overlapping Template Test block Length: ");
				scanf("%d", &args.para.overlappingTemplateBlockLength);
				printf("\n");
				continue;
			}
		}
		if ( testVector[TEST_APEN] == 1 ) {
			counter++;
			if ( counter == testid ) {
				printf("   Enter Approximate Entropy Test block Length: ");
				scanf("%d", &args.para.approximateEntropyBlockLength);
				printf("\n");
				continue;
			}
		}
		if ( testVector[TEST_SERIAL] == 1 ) {
			counter++;
			if ( counter == testid ) {
				printf("   Enter Serial Test block Length: ");
				scanf("%d", &args.para.serialBlockLength);
				printf("\n");
				continue;
			}
		}
		if ( testVector[TEST_LINEARCOMPLEXITY] == 1 ) {
			counter++;
			if ( counter == testid ) {
				printf("   Enter Linear Complexity Test block Length: ");
				scanf("%d", &args.para.linearComplexitySequenceLength);
				printf("\n");
				continue;
			}
		}
	} while ( testid != 0 );
}


void
fileBasedBitStreams(char *streamFile)
{
	FILE	*fp;
	int		mode = args.mode;
	
	if(args.pflag == 0) {
		printf("   Input File Format:\n");
		printf("    [0] ASCII - A sequence of ASCII 0's and 1's\n");
		printf("    [1] Binary - Each byte in data file contains 8 bits of data\n\n");
		printf("   Select input mode:  ");
		scanf("%1d", &mode);
		printf("\n");
	}

	if ( mode ==  MODE_ASCII) {
		if ( (fp = fopen(streamFile, "r")) == NULL ) {
			printf("ERROR IN FUNCTION fileBasedBitStreams:  file %s could not be opened.\n",  streamFile);
			exit(-1);
		}
		readBinaryDigitsInASCIIFormat(fp, streamFile);
		fclose(fp);
	}
	else if ( mode == MODE_BINARY ) {
		if ( (fp = fopen(streamFile, "rb")) == NULL ) {
			printf("ERROR IN FUNCTION fileBasedBitStreams:  file %s could not be opened.\n", streamFile);
			exit(-1);
		}
		readHexDigitsInBinaryFormat(fp);
		fclose(fp);
	}
}


void
readBinaryDigitsInASCIIFormat(FILE *fp, char *streamFile)
{
	int		i, j, num_0s, num_1s, bitsRead, bit;
	
	if ( (epsilon = (BitSequence *) calloc(args.n, sizeof(BitSequence))) == NULL ) {
		printf("BITSTREAM DEFINITION:  Insufficient memory available.\n");
		printf("Statistical Testing Aborted!\n");
		return;
	}
	printf("     Statistical Testing In Progress.........\n\n");   
	for ( i=0; i<args.para.numOfBitStreams; i++ ) {
		num_0s = 0;
		num_1s = 0;
		bitsRead = 0;
		for ( j=0; j<args.n; j++ ) {
			if ( fscanf(fp, "%1d", &bit) == EOF ) {
				printf("ERROR:  Insufficient data in file %s.  %d bits were read.\n", streamFile, bitsRead);
				fclose(fp);
				free(epsilon);
				return;
			}
			else {
				bitsRead++;
				if ( bit == 0 ) 
					num_0s++;
				else 
					num_1s++;
				epsilon[j] = bit;
			}
		}
		fprintf(freqfp, "#[%s] BITSREAD = %d 0s = %d 1s = %d\n", 
			gettime(), bitsRead, num_0s, num_1s);	
		fflush(freqfp);	
		nist_test_suite(i);
	}
	free(epsilon);
}


void
readHexDigitsInBinaryFormat(FILE *fp)
{
	int		i, done, num_0s, num_1s, bitsRead;
	BYTE	buffer[1];
	
	if ( (epsilon = (BitSequence *) calloc(args.n,sizeof(BitSequence))) == NULL ) {
		printf("BITSTREAM DEFINITION:  Insufficient memory available.\n");
		return;
	}

	printf("     Statistical Testing In Progress.........\n\n");   
	for ( i=0; i<args.para.numOfBitStreams; i++ ) {
		num_0s = 0;
		num_1s = 0;
		bitsRead = 0;
		done = 0;
		do {
			if ( fread(buffer, sizeof(BYTE), 1, fp) != 1 ) {
				printf("READ ERROR:  Insufficient data in file.\n");
				free(epsilon);
				return;
			}
			done = convertToBits(buffer, 8, args.n, &num_0s, &num_1s, &bitsRead);
		} while ( !done );
		fprintf(freqfp, "#[%s] BITSREAD = %d 0s = %d 1s = %d\n", 
			gettime(), bitsRead, num_0s, num_1s);	
		fflush(freqfp);	
		nist_test_suite(i);		
	}
	free(epsilon);
}


int
convertToBits(BYTE *x, int xBitLength, int bitsNeeded, int *num_0s, int *num_1s, int *bitsRead)
{
	int		i, j, count, bit;
	BYTE	mask;
	int		zeros, ones;

	count = 0;
	zeros = ones = 0;
	for ( i=0; i<(xBitLength+7)/8; i++ ) {
		mask = 0x80;
		for ( j=0; j<8; j++ ) {
			if ( *(x+i) & mask ) {
				bit = 1;
				(*num_1s)++;
				ones++;
			}
			else {
				bit = 0;
				(*num_0s)++;
				zeros++;
			}
			mask >>= 1;
			epsilon[*bitsRead] = bit;
			(*bitsRead)++;
			if ( *bitsRead == bitsNeeded )
				return 1;
			if ( ++count == xBitLength )
				return 0;
		}
	}
	
	return 0;
}


void
openOutputStreams(int option)
{
	int		i, numOfBitStreams, numOfOpenFiles = 0;
	char	freqfn[MAX_PATH], summaryfn[MAX_PATH], statsDir[MAX_PATH], resultsDir[MAX_PATH];
	
	sprintf(freqfn, "experiments/%s/freq.txt", generatorDir[option]);
	if ( (freqfp = fopen(freqfn, "w")) == NULL ) {
		printf("\t\tMAIN:  Could not open freq file: <%s>", freqfn);
		exit(-1);
	}
	sprintf(summaryfn, "experiments/%s/finalAnalysisReport.txt", generatorDir[option]);
	if ( (summary = fopen(summaryfn, "w")) == NULL ) {
		printf("\t\tMAIN:  Could not open stats file: <%s>", summaryfn);
		exit(-1);
	}

	if ( args.outFileName != NULL && (args.outFile = fopen(args.outFileName, "w")) == NULL ){
		printf("\t\tMAIN:  Could not open output file: <%s>", args.outFileName);
		exit(-1);
	}
	
	for( i=1; i<=NUMOFTESTS; i++ ) {
		if ( testVector[i] == 1 ) {
			sprintf(statsDir, "experiments/%s/%s_stats.txt", generatorDir[option], testNames[i]);
			sprintf(resultsDir, "experiments/%s/%s_results.txt", generatorDir[option], testNames[i]);
			if ( (stats[i] = fopen(statsDir, "w")) == NULL ) {	/* STATISTICS LOG */
				printf("ERROR: LOG FILES COULD NOT BE OPENED.\n");
				printf("       MAX # OF OPENED FILES HAS BEEN REACHED = %d\n", numOfOpenFiles);
				printf("-OR-   THE OUTPUT DIRECTORY DOES NOT EXIST.\n");
				exit(-1);
			}
			else
				numOfOpenFiles++;
			if ( (results[i] = fopen(resultsDir, "w")) == NULL ) {	/* P_VALUES LOG   */
				 printf("ERROR: LOG FILES COULD NOT BE OPENED.\n");
				 printf("       MAX # OF OPENED FILES HAS BEEN REACHED = %d\n", numOfOpenFiles);
				 printf("-OR-   THE OUTPUT DIRECTORY DOES NOT EXIST.\n");
				 exit(-1);
			}
			else
				numOfOpenFiles++;
		}
	}
	if(args.pflag == 0) {
		printf("   How many bitstreams? ");
		scanf("%d", &numOfBitStreams);
		args.para.numOfBitStreams = numOfBitStreams;
		printf("\n");
	}
}

void
invokeTestSuite(int option, char *streamFile)
{	
	fprintf(freqfp, "#=======================BEGIN=======================\n");
	fprintf(freqfp, "#[%s] FILE = %s , ALPHA = %6.4f\n", gettime(), streamFile, ALPHA);	
	fprintf(freqfp, "#[%s] Filling bitstream.\n", gettime());
	if ( option != 0 )
		printf("#Statistical Testing In Progress.........\n\n");
	switch( option ) {
		case 0:
			fileBasedBitStreams(streamFile);
			//collsion8xor();
			break;
		case 1:
			lcg();
			break;
		case 2:
			quadRes1();
			break;
		case 3:
			quadRes2();
			break;
		case 4:
			cubicRes();
			break;
		case 5:
			exclusiveOR();
			break;
		case 6:
			modExp();
			break;
		case 7:
			bbs();
			break;
		case 8:
			micali_schnorr();
			break;
		case 9:
			SHA1();
			break;
			
		/* INTRODUCE NEW PSEUDO RANDOM NUMBER GENERATORS HERE */
			
		default:
			printf("Error in invokeTestSuite!\n");
			break;
	}
	fprintf(freqfp, "#[%s] Filled bitstream.\n", gettime());
	printf("     Statistical Testing Complete!!!!!!!!!!!!\n\n");
}


#define TEST1(f, arg1) \
do{ \
	fprintf(freqfp, "#[%s] "#f"(%d) is running.\n", gettime(), arg1); \
	f(arg1); \
	fprintf(freqfp, "#[%s] "#f"(%d) is finished.\n", gettime(), arg1); \
}while(0)

#define TEST2(f, arg1, arg2) \
do{ \
	fprintf(stdout, "\r#[%s] "#f"(%d, %d).\n", gettime(), arg1, arg2); \
	fprintf(freqfp, "#[%s] "#f"(%d, %d) is running.\n", gettime(), arg1, arg2); \
	f(arg1, arg2); \
	fprintf(freqfp, "#[%s] "#f"(%d, %d) is finished.\n", gettime(), arg1, arg2); \
}while(0)

void
nist_test_suite(int k)
{

	fprintf(stdout, "%d/%d\n", k, args.para.numOfBitStreams);

	if ( (testVector[0] == 1) || (testVector[TEST_FREQUENCY] == 1) ) 
		TEST1(Frequency, args.n);

	if ( (testVector[0] == 1) || (testVector[TEST_BLOCK_FREQUENCY] == 1) ) 
		TEST2(BlockFrequency, args.para.blockFrequencyBlockLength, args.n);
	
	if ( (testVector[0] == 1) || (testVector[TEST_CUSUM] == 1) ) 
		TEST1(CumulativeSums, args.n);
	
	if ( (testVector[0] == 1) || (testVector[TEST_RUNS] == 1) ) 
		TEST1(Runs, args.n);

	if ( (testVector[0] == 1) || (testVector[TEST_LONGEST_RUN] == 1) ) 
		TEST1(LongestRunOfOnes, args.n);
	
	if ( (testVector[0] == 1) || (testVector[TEST_RANK] == 1) ) 
		TEST1(Rank, args.n);
	
	if ( (testVector[0] == 1) || (testVector[TEST_FFT] == 1) ) 
		TEST1(DiscreteFourierTransform, args.n);
	
	if ( (testVector[0] == 1) || (testVector[TEST_NONPERIODIC] == 1) ) 
		TEST2(NonOverlappingTemplateMatchings, args.para.nonOverlappingTemplateBlockLength, args.n);
	
	if ( (testVector[0] == 1) || (testVector[TEST_OVERLAPPING] == 1) )
		TEST2(OverlappingTemplateMatchings, args.para.overlappingTemplateBlockLength, args.n);
	
	if ( (testVector[0] == 1) || (testVector[TEST_UNIVERSAL] == 1) )
		TEST1(Universal, args.n);
	
	if ( (testVector[0] == 1) || (testVector[TEST_APEN] == 1) )
		TEST2(ApproximateEntropy, args.para.approximateEntropyBlockLength, args.n);
	
	if ( (testVector[0] == 1) || (testVector[TEST_RND_EXCURSION] == 1) )
		TEST1(RandomExcursions, args.n);
	
	if ( (testVector[0] == 1) || (testVector[TEST_RND_EXCURSION_VAR] == 1) )
		TEST1(RandomExcursionsVariant, args.n);
	
	if ( (testVector[0] == 1) || (testVector[TEST_SERIAL] == 1) )
		TEST2(Serial, args.para.serialBlockLength, args.n);
	
	if ( (testVector[0] == 1) || (testVector[TEST_LINEARCOMPLEXITY] == 1) )
		TEST2(LinearComplexity, args.para.linearComplexitySequenceLength, args.n);
}

int split(const char *src, const char *separator, int *dest, int size)
{
	char *buffer = NULL;
    char *pNext;
	int bs = size * DEC_DIGITS_OF_INT32 + 1;
    int p = 0; 
	
	
    if (src == NULL || strlen(src) == 0) return 0;
    if (separator == NULL || strlen(separator) == 0) separator = ","; 

	buffer = malloc(bs);
	if(buffer == NULL) return 0;
	strncpy(buffer, src, bs);

    pNext = strtok(buffer,separator);
    while(pNext != NULL && p < size)
    {
		dest[p] = atoi(pNext); p++;
        pNext = strtok(NULL,separator);
    }

	free(buffer);
	return p;    
}

char Check_Range(const int *arr, int num, int min, int max) 
{
	int i;
	for(i = 0; i < num; i++) {
		if(arr[i] < min || arr[i] > max) return 0;
	}
	return 1;
}

char *gettime()
{
	time_t t = time(0); 
    static char tstr[TIME_STR_LEN]; 
    strftime(tstr, sizeof(tstr), "%Y/%m/%d %X",localtime(&t) );     
    return tstr; 
}
