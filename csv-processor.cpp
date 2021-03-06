// csv-processor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> extract_column_from_csv(std::string filename, int column) {
	std::ifstream file(filename);

	std::string line;

	std::vector<std::string> output_col;
	while (file >> line) {
		std::stringstream ss(line);
		std::vector<std::string> results;
		while (ss.good()) {
			std::string csv;
			std::getline(ss, csv, ',');
			results.push_back(csv);
		}
		if ((int)(results.size()) - 1 >= column && column >= 0) {
			output_col.push_back(results[column]);
		}
	}
	return output_col;
}

std::vector<double> make_monotonically_increasing(std::vector<std::string>& csv_col) {
	std::vector<double> results;
	for (auto& num_str : csv_col) {
		
		try {
			std::stod(num_str);
		}
		catch (...) {
			// do nothing
			continue;
		}
		double num = std::stod(num_str);
		if (results.size() > 0) {
			if (results[results.size() - 1] < num) {
				num = results[results.size() - 1];
			}
		}
		results.push_back(num);
	}
	return results;
}

void write_out_column_as_csv(std::string filename, std::string column_name, const std::vector<double>& col) {
	std::ofstream file(filename);
	file << "iteration,";
	file << column_name << "\n";

	for (size_t i = 0; i < col.size(); ++i) {
		file << i << ",";
		file << col[i] << "\n";
	}
	file.flush();
}

int main()
{
	std::string filename;
	std::getline(std::cin, filename);
	auto result_col = extract_column_from_csv(filename, 7);
	auto double_col = make_monotonically_increasing(result_col);
	write_out_column_as_csv("results.csv", "score", double_col);
    return 0;
}

