#ifndef YED_FS_HH
#define YED_FS_HH

#include "_components.hh"

namespace FS {
	namespace File {
		std::vector <std::string> ReadIntoVector(std::string fname);
		bool                      Exists(std::string fname);
		void                      Write(std::string fname, std::string write);
	}
	namespace Directory {
		bool Exists(std::string dname);
		void Create(std::string dname);
	}
}

#endif