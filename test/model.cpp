#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include "model.h"

Model::Model()
{
	
}

Model::~Model()
{

}


bool Model::setInputFilesDirectory(const string& directory)
{
	const std::filesystem::path sourcesDirectory{ directory };
	if (isValidPath(sourcesDirectory, true))
	{
		inputPath = canonical(sourcesDirectory);
		return true;
	}
	return false;
}

bool Model::setOutputFilesDirectory(const string& directory)
{
	const std::filesystem::path sourcesDirectory{ directory };
	if (isValidPath(sourcesDirectory, true))
	{
		outputPath = canonical(sourcesDirectory);
		outputPath.append("output");
		return true;
	}
	return false;
}

bool Model::isValidPath(const std::filesystem::path& p, bool checkIsDirectory)
{
	if (!exists(p))
	{
		return false;
	}
	if (checkIsDirectory && !filesystem::is_directory(p))
	{
		return false;
	}
	return true;
}

bool Model::inputDirectoryIsValid()
{
	return !inputPath.empty();
}

bool Model::outputDirectoryIsValid()
{
	return !outputPath.empty();
}

bool Model::cleanOutput()
{
	if (filesystem::exists(outputPath))
	{
		filesystem::remove_all(outputPath);
	}
	return true;
}

void Model::startScan()
{
	cleanOutput();
	filesystem::create_directory(outputPath);
	startExploreDirectory();
}

void Model::startExploreDirectory()
{
	auto basePathString{ inputPath.u8string() };
	auto basePathLength { basePathString.length() };

	for (filesystem::directory_entry entry : filesystem::recursive_directory_iterator(inputPath))
	{
		if (entry.is_regular_file())
		{
			auto currentPathString { entry.path().u8string() };
			auto pos{ currentPathString.find(basePathString) };
			auto additionalPath{ currentPathString.substr(pos + basePathLength + 1) };
			auto suffix{ makeOutputDirectorySuffixPath(additionalPath, additionalPath.length() - 1) };
			filesystem::path newPath{ outputPath };
			newPath.append(suffix);
			readLogFile(entry.path(), newPath);
		}
	}
}

string Model::makeOutputDirectorySuffixPath(string additionalPath, const size_t lastSym)
{
	auto pos{ additionalPath.find_last_of(filesystem::path::preferred_separator, lastSym) };
	if (pos == string::npos)
		return additionalPath;
	additionalPath.insert(pos, "_output");
	return makeOutputDirectorySuffixPath(additionalPath, pos);
}

void Model::readLogFile(const filesystem::path& inputFile, const filesystem::path& outputFile)
{
	ifstream rstream{ inputFile.c_str() };
	string s;
	bool writeToFileFlag = false;
	for (; getline(rstream, s);)
	{
		auto parceLineResult{ validationLine(s) };
		if (parceLineResult == LineRegExpStatus::firstLineLogMessage)
		{
			writeToFileFlag = true;
		}
		if (writeToFileFlag)
		{
			writeOutputLogFile(outputFile, s);
		}
		if (parceLineResult == LineRegExpStatus::emptyLine)
		{
			writeToFileFlag = false;
		}
	}
	rstream.close();
}

void Model::writeOutputLogFile(const filesystem::path& output, const string& line)
{
	if (!isValidPath(output.parent_path(), false))
	{
		filesystem::create_directories(output.parent_path());
	}
	ofstream wstream{ output.c_str(), ios_base::app};
	wstream << line << endl;
	wstream.close();
}

LineRegExpStatus Model::validationLine(const std::string& line)
{
	regex firstLogLine{ "\\s*\\[[EROWARNIG]*\\]\\s+[\\w\\W]*" };
	regex emptyString{ "^\\s*$" };

	if (regex_match(line, firstLogLine))
	{
		return LineRegExpStatus::firstLineLogMessage;
	}
	else if (regex_match(line, emptyString))
	{
		return LineRegExpStatus::emptyLine;
	}
	return LineRegExpStatus::anotherLineLogMessage;
}