#include "datap.h"
#include "Transcendental.h"



TEST(TranscendentalTests, ArcTangentTest) {

	double input = 0.41;
	double result = 0.0;
	fprintf(stdout, "\nInput: %f\n", input);

	result = arctangent(input);
	
	fprintf(stdout,"\nResult: %f\n", result);
	ASSERT_NEAR(.3890, result,.0005);



}

TEST(TranscendentalTests, ArcTangentTest2) {

	double input = .537;
	double result = 0.0;
	fprintf(stdout, "\nInput: %f\n", input);

	result = arctangent(input);

	fprintf(stdout, "\nResult: %f\n", result);
	ASSERT_NEAR(.4928, result, .0005);



}

