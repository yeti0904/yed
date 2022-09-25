#include "fs.hh"
#include "util.hh"

// File functions
std::vector <std::string> FS::File::ReadIntoVector(std::string fname) {
	std::ifstream             fhnd(fname);
	std::vector <std::string> ret;
	std::string               line;

	while (getline(fhnd, line)) {
		ret.push_back(line);
	}
	fhnd.close();

	return ret;
}

void FS::File::Write(std::string fname, std::string write) {
	std::ofstream fhnd(fname);

	fhnd << write;

	fhnd.close();
}