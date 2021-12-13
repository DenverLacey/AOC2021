#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>

#define INPUT_FILE "test.txt"
std::ifstream open_input() {
	std::ifstream input(INPUT_FILE);
	if (!input.is_open()) {
		fprintf(stderr, "Could not open input file: %s\n", INPUT_FILE);
		std::cin.get();
		exit(EXIT_FAILURE);
	}
	return input;
}

#define NUM_BITS 5
struct Processed {
	int zeros[NUM_BITS] = { 0 };
	int ones[NUM_BITS] = { 0 };
	std::vector<int> numbers;
};

Processed process_input(std::istream &input) {
	Processed processed;

	std::string line;
	while (std::getline(input, line)) {
		int number = 0;
		
		for (int i = 0; i < NUM_BITS; i++) {
			int bit = NUM_BITS - i - 1;
			if (line[i] == '0') {
				processed.zeros[bit]++;
			} else {
				processed.ones[bit]++;
				number |= 1 << bit;
			}
		}

		processed.numbers.push_back(number);
	}

	printf("Occurences:\n");
	for (int i = 0; i < NUM_BITS; i++) {
		printf("%4d: %d zeros, %d ones  -  %d\n", i, processed.zeros[i], processed.ones[i], processed.ones[i] > processed.zeros[i] ? 1 : 0);
	}

	printf("Numbers:\n");
	for (int i = 0; i < processed.numbers.size(); i++) {
		int number = processed.numbers[i];
		printf("%4d: %d\n", i, number);
	}

	return processed;
}

struct Power_Consumption_Rates {
	int gamma_rate;
	int epsilon_rate;
};

Power_Consumption_Rates decode_rates(Processed occurences) {
	int gamma = 0;
	int epsilon = 0;

	for (int i = 0; i < NUM_BITS; i++) {
		if (occurences.ones[i] > occurences.zeros[i]) {
			gamma |= 1 << i;
		} else {
			epsilon |= 1 << i;
		}
	}

	printf("Gamma Rate: %d\nEpsilon Rate: %d\n", gamma, epsilon);

	return { gamma, epsilon };
}

int part1(std::istream &input) {
	int gamma;
	int epsilon;

	Processed occurences = process_input(input);
	Power_Consumption_Rates rates = decode_rates(occurences);
	
	printf("Output: %d\n", rates.gamma_rate * rates.epsilon_rate);

	return 0;
}

struct Life_Support_Ratings {
	int oxygen;
	int co2;
};

Life_Support_Ratings decode_ratings(Processed processed) {
	Life_Support_Ratings ratings;
	
	bool *remaining = new bool[processed.numbers.size()];
	memset(remaining, true, processed.numbers.size() * sizeof(bool));
	int num_remaining = processed.numbers.size();
	int idx_last_remaining = -1;

	for (int bit = NUM_BITS - 1; bit >= 0; bit--) {
		int most_common = processed.zeros[bit] > processed.ones[bit] ? 0 : 1;

		for (int i = 0; i < num_remaining; i++) {
			if (!remaining[i]) { 
				continue; 
			}
			
			int number = processed.numbers[i];
			if ((number & (1 << bit)) != most_common << bit) {
				remaining[i] = false;
				num_remaining--;
			} else {
				idx_last_remaining = i;
			}

			if (num_remaining == 1) {
				break;
			}
		}

		if (num_remaining == 1) {
			break;
		}
	}

	assert(idx_last_remaining != -1);
	ratings.oxygen = processed.numbers[idx_last_remaining];
	
	memset(remaining, true, processed.numbers.size() * sizeof(bool));
	num_remaining = processed.numbers.size();
	idx_last_remaining = -1;

	for (int bit = NUM_BITS - 1; bit >= 0; bit--) {
		int most_common = processed.ones[bit] > processed.zeros[bit] ? 1 : 0;

		for (int i = 0; i < num_remaining; i++) {
			if (!remaining[i]) {
				continue;
			}

			int number = processed.numbers[i];
			if ((number & (1 << bit)) == most_common << bit) {
				remaining[i] = false;
				num_remaining--;
			} else {
				idx_last_remaining = i;
			}

			if (num_remaining == 1) {
				break;
			}
		}

		if (num_remaining == 1) {
			break;
		}
	}

	assert(idx_last_remaining != -1);
	ratings.co2 = processed.numbers[idx_last_remaining];

	delete remaining;

	return ratings;
}

int part2(std::istream &input) {
	Processed processed = process_input(input);
	Life_Support_Ratings ratings = decode_ratings(processed);

	printf("Output: %d\n", ratings.oxygen * ratings.co2);

	return 0;
}

#define RUN_PART(p) run_part(p, part ## p)
void run_part(int pno, int(*part)(std::istream &)) {
	std::ifstream input = open_input();

	printf("Part %d:\n", pno);
	int exit_code = part(input);
	printf("\nExit Code: %d\n\n\n", exit_code);
}

int main(int arg, const char **argv) {
	// RUN_PART(1);
	RUN_PART(2);

	std::cin.get();
	return 0;
}