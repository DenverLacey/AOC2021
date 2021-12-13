#include <iostream>
#include <string>
#include <fstream>

const char *filepath = "input.txt";

int part1() {
	int num_larger_measurements = 0;
	int previous_depth;

	std::ifstream input(filepath);
	if (!input.is_open()) {
		fprintf(stderr, "Could not open file: %s\n", filepath);
		return 1;
	}

	std::string line;

	std::getline(input, line);
	previous_depth = std::stoi(line);

	printf("%d\n", previous_depth);

	while (std::getline(input, line)) {
		int current_depth = std::stoi(line);
		bool has_increased = current_depth > previous_depth;

		if (has_increased) {
			num_larger_measurements++;
		}

		previous_depth = current_depth;

		printf("%d %s\n", previous_depth, has_increased ? "(increased)" : "");
	}

	printf("Output: %d\n", num_larger_measurements);

	return 0;
}

#define MEASUREMENTS_COUNT 3

int group_sum(int *measurements) {
	int sum = measurements[0];
	for (int i = 1; i < MEASUREMENTS_COUNT; i++) {
		sum += measurements[i];
	}
	return sum;
}

void add_measurement(int *measurements, int measurement) {
	memmove(measurements, &measurements[1], (MEASUREMENTS_COUNT - 1) * sizeof(int));
	measurements[MEASUREMENTS_COUNT - 1] = measurement;
}

int part2() {
	int num_larger_measurements = 0;
	int previous_group = 0;
	int previous_sum;
	int measurements[MEASUREMENTS_COUNT];

	std::ifstream input(filepath);
	if (!input.is_open()) {
		fprintf(stderr, "Could not open file: %s\n", filepath);
		return 1;
	}

	std::string line;
	for (int i = 0; i < MEASUREMENTS_COUNT; i++) {
		std::getline(input, line);
		measurements[i] = std::stoi(line);
	}

	previous_sum = group_sum(measurements);
	printf("Group %4d: %d\n", previous_group, previous_sum);

	while (std::getline(input, line)) {
		add_measurement(measurements, std::stoi(line));
		int current_sum = group_sum(measurements);
		bool has_increased = current_sum > previous_sum;

		if (has_increased) {
			num_larger_measurements++;
		}

		previous_group++;
		previous_sum = current_sum;

		printf("Group %4d: %d %s\n", previous_group, previous_sum, has_increased ? "(increased)" : "");
	}

	printf("Output: %d\n", num_larger_measurements);

	return 0;
}

void run_part(int pno, int(*part)()) {
	printf("Part %d:\n", pno);
	int exit_code = part();
	printf("\nExit Code: %d\n\n\n", exit_code);
}

int main(int argc, const char **argv) {
	run_part(1, part1);
	run_part(2, part2);

	std::cin.get();
	return 0;
}

