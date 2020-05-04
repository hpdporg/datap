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

TEST(TranscendentalTests, SineTest) {

	double input = 0.41;
	double result = 0.0;
	fprintf(stdout, "\nInput: %f\n", input);

	result = sine(input);

	fprintf(stdout, "\nResult: %f\n", result);
	ASSERT_NEAR(.3986, result, .0005);




}



TEST(TranscendentalTests, SineTest2) {

	double input = .537;
	double result = 0.0;
	fprintf(stdout, "\nInput: %f\n", input);

	result = sine(input);

	fprintf(stdout, "\nResult: %f\n", result);
	ASSERT_NEAR(.5115, result, .0005);




}

TEST(TranscendentalTests, CosineTest) {

	double input = 0.41;
	double result = 0.0;
	fprintf(stdout, "\nInput: %f\n", input);

	result = cosine(input);

	fprintf(stdout, "\nResult: %f\n", result);
	ASSERT_NEAR(.9171, result, .0005);




}

TEST(TranscendentalTests, CosineTest2) {

	double input = .537;
	double result = 0.0;
	fprintf(stdout, "\nInput: %f\n", input);

	result = cosine(input);

	fprintf(stdout, "\nResult: %f\n", result);
	ASSERT_NEAR(.8592, result, .0005);




}

TEST(TranscendentalTests, TangentTest) {

	double input = 0.41;
	double result = 0.0;
	fprintf(stdout, "\nInput: %f\n", input);

	result = tangent(input);

	fprintf(stdout, "\nResult: %f\n", result);
	ASSERT_NEAR(.4346, result, .0005);




}

TEST(TranscendentalTests, TangentTest2) {

	double input = .537;
	double result = 0.0;
	fprintf(stdout, "\nInput: %f\n", input);

	result = tangent(input);

	fprintf(stdout, "\nResult: %f\n", result);
	ASSERT_NEAR(.5953, result, .0005);




}