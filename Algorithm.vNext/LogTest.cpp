#include "Test.h"

void LogTest::Init(void)
{
	Add("Default", [&]() {
		Logger().WriteError("Error: %d\n", LogLevel::Error);
		Logger().WriteWarning("Warning: %d\n", LogLevel::Warning);
		Logger().WriteInformation("Information: %d\n", LogLevel::Information);
		Logger().WriteVerbose("Verbose: %d\n", LogLevel::Verbose);
	});

	Add("Error", [&]() {
		ostringstream os;
		Log log(os, LogLevel::Error);
		log.WriteVerbose("Verbose");
		ASSERT1(0 == os.str().length());
		log.WriteInformation("Information");
		ASSERT1(0 == os.str().length());
		log.WriteWarning("Warning");
		ASSERT1(0 == os.str().length());
		log.WriteError("Error");
		ASSERT1(5 <= os.str().length());
	});

	Add("Warning", [&]() {
		ostringstream os;
		Log log(os, LogLevel::Warning);
		log.WriteVerbose("Verbose");
		ASSERT1(0 == os.str().length());
		log.WriteInformation("Information");
		ASSERT1(0 == os.str().length());
		log.WriteWarning("Warning");
		ASSERT1(7 <= os.str().length());
		log.WriteError("Error");
		ASSERT1(12 <= os.str().length());
	});

	Add("Information", [&]() {
		ostringstream os;
		Log log(os, LogLevel::Information);
		log.WriteVerbose("Verbose");
		ASSERT1(0 == os.str().length());
		log.WriteInformation("Information");
		ASSERT1(11 <= os.str().length());
		log.WriteWarning("Warning");
		ASSERT1(18 <= os.str().length());
		log.WriteError("Error");
		ASSERT1(23 <= os.str().length());
	});

	Add("Verbose", [&]() {
		ostringstream os;
		Log log(os, LogLevel::Verbose);
		log.WriteVerbose("Verbose");
		ASSERT1(7 <= os.str().length());
		log.WriteInformation("Information");
		ASSERT1(18 == os.str().length());
		log.WriteWarning("Warning");
		ASSERT1(25 <= os.str().length());
		log.WriteError("Error");
		ASSERT1(30 <= os.str().length());
	});
}