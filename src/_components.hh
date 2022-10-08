#ifndef YED__COMPONENTS_HH
#define YED__COMPONENTS_HH

// macros
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#define PLATFORM_WINDOWS
#elif defined(__APPLE__)
	#define PLATFORM_APPLE
#elif defined(__linux__)
	#define PLATFORM_LINUX
#elif defined(__unix__)
	#define PLATFORM_UNIX
#endif

// C standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// C++ standard libraries
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>

#endif
