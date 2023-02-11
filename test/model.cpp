#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include "model.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using namespace std::filesystem;

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
		try
		{
			inputPath = canonical(sourcesDirectory);
		}
		catch (const std::filesystem::filesystem_error& error)
		{
			cerr << "Error set input directory. Filesystem error! Code: " << error.code() << "; description: " << error.what() << endl;
			return false;
		}
		return true;
	}
	return false;
}

bool Model::setOutputFilesDirectory(const string& directory)
{
	const std::filesystem::path sourcesDirectory{ directory };
	if (isValidPath(sourcesDirectory, true))
	{
		try
		{
			outputPath = canonical(sourcesDirectory);
		}
		catch (const std::filesystem::filesystem_error& error)
		{
			cerr << "Error set output directory. Filesystem error! Code: " << error.code() << "; description: " << error.what() << endl;
			return false;
		}
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
	if (checkIsDirectory && !is_directory(p))
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
	if (exists(outputPath))
	{
		try
		{
			remove_all(outputPath);
		}
		catch (const std::filesystem::filesystem_error& error)
		{
			cerr << "Error clean output directory. Filesystem error! Code: " << error.code() << "; description: " << error.what() << endl;
			return false;
		}
	}
	return true;
}

int Model::startScan()
{
	cleanOutput();
	try
	{
		create_directory(outputPath);
	}
	catch (const std::filesystem::filesystem_error& error)
	{
		cerr << "Error create output directory. Filesystem error! Code: " << error.code() << "; description: " << error.what() << endl;
		return 0;
	}
	return startExploreDirectory();
}

int Model::startExploreDirectory()
{
	auto basePathString{ inputPath.u8string() };
	auto basePathLength { basePathString.length() };
	int count = 0;
	for (directory_entry entry : recursive_directory_iterator(inputPath))
	{
		try
		{
			if (entry.is_regular_file())
			{
				auto currentPathString{ entry.path().u8string() };
				auto pos{ currentPathString.find(basePathString) };
				auto additionalPath{ currentPathString.substr(pos + basePathLength + 1) };
				auto suffix{ makeOutputDirectorySuffixPath(additionalPath, additionalPath.length() - 1) };
				path newPath{ outputPath };
				newPath.append(suffix);
				count += readLogFile(entry.path(), newPath);
			}
		}
		catch (const std::filesystem::filesystem_error& error)
		{
			cerr << "Error process input file \"" << entry.path() << "\". Filesystem error! Code: " << error.code() << "; description: " << error.what() << endl;
		}
		catch (const std::bad_alloc& error)
		{
			cerr << "Error process input file \"" << entry.path() << "\". Failure to allocate storage! Description: " << error.what() << endl;
		}
	}
	return count;
}

string Model::makeOutputDirectorySuffixPath(string additionalPath, const size_t lastSym)
{
	auto pos{ additionalPath.find_last_of(path::preferred_separator, lastSym) };
	if (pos == string::npos)
		return additionalPath;
	additionalPath.insert(pos, "_output");
	return makeOutputDirectorySuffixPath(additionalPath, pos);
}

int Model::readLogFile(const path& inputFile, const path& outputFile)
{
	std::ifstream rstream{ inputFile.c_str() };
	string s;
	bool writeToFileFlag = false;
	int count = 0;
	bool needCheckLogFormat = true;
	for (; getline(rstream, s);)
	{
		auto parceLineResult{ validateLine(s) };
		if (parceLineResult == LineRegExpStatus::startWrite)
		{
			needCheckLogFormat = false;
			writeToFileFlag = true;
			count++;
		}
		else if (needCheckLogFormat && parceLineResult == LineRegExpStatus::trueLogFormat)
		{
			needCheckLogFormat = false;
		}
		else if (needCheckLogFormat && parceLineResult == LineRegExpStatus::logDelimeter)
		{
			continue;
		}
		else if (needCheckLogFormat)
		{
			cout << "Log format error: " << s << endl;
			needCheckLogFormat = false;
		}

		if (writeToFileFlag)
		{
			writeOutputLogFile(outputFile, s);
		}
		if (parceLineResult == LineRegExpStatus::logDelimeter)
		{
			writeToFileFlag = false;
			needCheckLogFormat = true;
		}
	}
	rstream.close();
	return count;
}

void Model::writeOutputLogFile(const path& output, const string& line)
{
	if (!isValidPath(output.parent_path(), false))
	{
		create_directories(output.parent_path());
	}
	std::ofstream wstream{ output.c_str(), std::ios_base::app};
	wstream << line << endl;
	wstream.close();
}