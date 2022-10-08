#include "fs.hh"

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

bool FS::File::Exists(std::string fname) {
	std::ifstream fhnd;
	fhnd.open(fname);

	return fhnd.good();
}

void FS::File::Write(std::string fname, std::string write) {
	std::ofstream fhnd(fname);

	fhnd << write;

	fhnd.close();
}

// Directory functions
bool FS::Directory::Exists(std::string dname) {
	return std::filesystem::exists(dname);
}

void FS::Directory::Create(std::string dname) {
	std::filesystem::create_directory(dname);
}