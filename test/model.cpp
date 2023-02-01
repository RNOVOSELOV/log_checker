#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <iostream>
#include "model.h"

Model::Model()
{
	
}

Model::~Model()
{

}


bool Model::setInputFilesDirectory(string directory)
{
	const std::filesystem::path sourcesDirectory{ directory };
	if (isValidPath(sourcesDirectory, true))
	{
		inputPath = canonical(sourcesDirectory);
		return true;
	}
	return false;
}

bool Model::setOutputFilesDirectory(string directory)
{
	const std::filesystem::path sourcesDirectory{ directory };
	if (isValidPath(sourcesDirectory, true))
	{
		outputPath = canonical(sourcesDirectory);
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
	return !inputPath.u8string().empty();
}

bool Model::outputDirectoryIsValid()
{
	cout << outputPath.u8string() << endl;
	return !outputPath.u8string().empty();
}

bool Model::cleanOutput()
{
	// TODO delete output directory
	cout << "clean" << endl;
	return true;
}

void Model::startScan()
{
	cout << "Start scan " << endl;
	startExploreDirectory();
}

void Model::startExploreDirectory()
{
	for (filesystem::directory_entry entry : filesystem::recursive_directory_iterator(inputPath))
	{
		if (entry.is_regular_file())
		{
			auto p{ entry.path() };
			cout << p.u8string() << endl;
			///	makeRootTreeNode(p);
		}
		else if (entry.is_directory())
		{
			// TODO Create directory
		}
	}
}

std::pair <LineRegExpStatus, std::string> Model::validationAndParcingHeaderLine(std::string line)
{
	string languageSpecificIncludeSubline;
	regex directiveRegEx{ "\\s*\\#[\\w\\W]*" };
	regex includeRegEx{ "\\s*" + languageSpecificIncludeSubline + "\\s*<[a-zA-Z0-9]+[.]?[h]?>\\s*" };
	regex localRegEx{ "\\s*" + languageSpecificIncludeSubline + "\\s*\"[a-zA-Z0-9]+[.]?[h]?\"\\s*" };
	regex emptyString{ "^\\s*$" };
	regex commentedLineRegEx{ "\\s*\\/\\/\\s*[\\w\\W]*" };

	if (regex_match(line, includeRegEx))
	{
		return pair(LineRegExpStatus::validIncludeHeader, getHeaderFileName(line, '<', '>'));
	}
	else if (regex_match(line, localRegEx))
	{
		return pair(LineRegExpStatus::validLocalHeader, getHeaderFileName(line, '\"', '\"'));
	}
	else if (regex_match(line, emptyString) || regex_match(line, directiveRegEx) || regex_match(line, commentedLineRegEx))
	{
		return pair(LineRegExpStatus::skipHeaderLine, "");
	}
	return pair(LineRegExpStatus::invalidHeader, "");
}

string Model::getHeaderFileName(const string rawHeader, const char firstSymbol, const char secondSymbol)
{
	auto it1 = rawHeader.find_first_of(firstSymbol) + 1;
	auto it2 = rawHeader.find_first_of(secondSymbol, it1);
	string str2(it2 - it1, '\0');
	copy(rawHeader.begin() + it1, rawHeader.begin() + it2, str2.begin());
	return str2;
}
