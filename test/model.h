#pragma once

#include <filesystem>
#include <vector>
#include <list>
#include <string>

enum class LineRegExpStatus {
	startWrite,
	endWrite,
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

	void startScan();
	bool cleanOutput();

protected:
	virtual LineRegExpStatus validateLine(const std::string&) = 0;

private:
	std::filesystem::path inputPath;
	std::filesystem::path outputPath;

	bool isValidPath(const std::filesystem::path& p, bool checkIsDirectory);
	void startExploreDirectory();

	string makeOutputDirectorySuffixPath(string, const size_t);
	void readLogFile(const filesystem::path&, const filesystem::path&);
	void writeOutputLogFile(const filesystem::path&, const string&);
};
