#pragma once

#include <filesystem>
#include <vector>
#include <list>
#include <string>

enum class LineRegExpStatus {
	startWrite,
	logDelimeter,
	trueLogFormat,
	continueLastAction,
};

using namespace std;

class Model
{
public:
	Model();
	virtual ~Model();

	std::string getInputDirectoryName() { return inputPath.u8string(); }
	std::string getOutputDirectoryName() { return outputPath.u8string(); }

	bool setInputFilesDirectory(const std::string&);
	bool setOutputFilesDirectory(const std::string&);

	bool inputDirectoryIsValid();
	bool outputDirectoryIsValid();

	int startScan();
	bool cleanOutput();

protected:
	virtual LineRegExpStatus validateLine(const std::string&) = 0;

private:
	std::filesystem::path inputPath;
	std::filesystem::path outputPath;

	bool isValidPath(const std::filesystem::path& p, bool checkIsDirectory);
	int startExploreDirectory();

	string makeOutputDirectorySuffixPath(string, const size_t);
	int readLogFile(const filesystem::path&, const filesystem::path&);
	void writeOutputLogFile(const filesystem::path&, const string&);
};
