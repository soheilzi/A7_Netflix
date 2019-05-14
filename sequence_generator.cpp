#include "sequence_generator.h"

using namespace std;

SequenceGenerator::SequenceGenerator() {
	number = 1;
}

int SequenceGenerator::get_number() {
	number++;
	return number - 1;
}