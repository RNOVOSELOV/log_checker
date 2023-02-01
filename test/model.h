#pragma once

#include <filesystem>
#include <vector>
#include <list>
#include <string>

enum class LineRegExpStatus {
	firstLineLogMessage,
	anotherLineLogMessage,
	emptyLine
};

using namespace std;

class Model
{
public:
	Model();
	~Model();

	std::string getInputDirectoryName() { return inputPath.u8string(); }
	std::string getOutputDirectoryName() { return outputPath.u8string(); }

	bool setInputFilesDirectory(const std::string&);
	bool setOutputFilesDirectory(const std::string&);

	bool inputDirectoryIsValid();
	bool outputDirectoryIsValid();

	void startScan();
	bool cleanOutput();

private:
	std::filesystem::path inputPath;
	std::filesystem::path outputPath;

	bool isValidPath(const std::filesystem::path& p, bool checkIsDirectory);
	void startExploreDirectory();

	string makeOutputDirectorySuffixPath(string, const size_t);
	void readLogFile(const filesystem::path&, const filesystem::path&);
	void writeOutputLogFile(const filesystem::path&, const string&);
	LineRegExpStatus validationLine(const std::string&);
};
