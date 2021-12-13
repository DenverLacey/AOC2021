#include <iostream>
#include <fstream>
#include <istream>
#include <string>

#define INPUT_FILE "input.txt"
std::ifstream open_input() {
	std::ifstream input(INPUT_FILE);
	if (!input.is_open()) {
		fprintf(stderr, "Could not open input file: %s\n", INPUT_FILE);
		std::cin.get();
		exit(EXIT_FAILURE);
	}
	return input;
}

int part1(std::istream &input) {
	int pos = 0, depth = 0;

	printf("\t\t%d, %d\n", pos, depth);

	std::string linestr;
	while (std::getline(input, linestr)) {
		std::string_view line = linestr;
		
		switch (line.front()) {
		case 'f': {
			line = line.substr(7);
			int movement = std::atoi(line.data());
			pos += movement;
			printf("forward %d.\t%d, %d\n", movement, pos, depth);
		} break;
		case 'd': {
			line = line.substr(5);
			int movement = std::atoi(line.data());
			depth += movement;
			printf("down %d.\t\t%d, %d\n", movement, pos, depth);
		} break;
		case 'u': {
			line = line.substr(3);
			int movement = std::atoi(line.data());
			depth -= movement;
			printf("up %d.\t\t%d, %d\n", movement, pos, depth);
		} break;

		default:
			printf("Weird input: %s\n", line.data());
			return 1;
		}
	}

	printf("Output: %d\n", pos * depth);

	return 0;
}

int part2(std::istream &input) {
	int pos = 0, depth = 0, aim = 0;

	printf("\t\t%d, %d, %d\n", pos, depth, aim);

	std::string linestr;
	while (std::getline(input, linestr)) {
		std::string_view line = linestr;

		switch (line.front()) {
		case 'f': {
			line = line.substr(7);
			int movement = std::atoi(line.data());
			pos += movement;
			depth += aim * movement;
			printf("forward %d.\t%d, %d, %d\n", movement, pos, depth, aim);
		} break;
		case 'd': {
			line = line.substr(5);
			int movement = std::atoi(line.data());
			aim += movement;
			printf("down %d.\t\t%d, %d, %d\n", movement, pos, depth, aim);
		} break;
		case 'u': {
			line = line.substr(3);
			int movement = std::atoi(line.data());
			aim -= movement;
			printf("up %d.\t\t%d, %d, %d\n", movement, pos, depth, aim);
		} break;

		default:
			printf("Weird input: %s\n", line.data());
			return 1;
		}
	}

	printf("Output: %d\n", pos * depth);
}

#define RUN(p) run_part(p, part ## p)
void run_part(int pno, int(*part)(std::istream &)) {
	std::ifstream input = open_input();

	printf("Part %d:\n", pno);
	int exit_code = part(input);
	printf("\nExit Code: %d\n\n\n", exit_code);
}

int main(int arg, const char **argv) {
	RUN(1);
	RUN(2);

	std::cin.get();
	return 0;
}