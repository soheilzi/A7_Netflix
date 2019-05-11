#include "sequence_generator.h"

using namespace std;

Sequence_generator::Sequence_generator() {
	number = 1;
}

int Sequence_generator::get_number() {
	number++;
	return number--;
}