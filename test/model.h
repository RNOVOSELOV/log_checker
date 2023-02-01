#pragma once

#include <filesystem>
#include <vector>
#include <list>
#include <string>

enum class LineRegExpStatus {
	skipHeaderLine,
	validLocalHeader,	
	validIncludeHeader,	
	invalidHeader	
};

using namespace std;

class Model
{
public:
	Model();
	~Model();

	std::string getInputDirectoryName() { return inputPath.u8string(); }
	std::string getOutputDirectoryName() { return outputPath.u8string(); }

	bool setInputFilesDirectory(std::string);
	bool setOutputFilesDirectory(std::string);

	bool inputDirectoryIsValid();
	bool outputDirectoryIsValid();

	void startScan();
	bool cleanOutput();


	
	
	
	

protected:
	/// <summary>
	/// //////////
	/// </summary>
	/// <param name="line"></param>
	/// <returns></returns>
	virtual std::pair <LineRegExpStatus, std::string> validationAndParcingHeaderLine(std::string line);	// Парсинг строки из хедера на отсновании регулярки



private:
	std::filesystem::path inputPath;
	std::filesystem::path outputPath;

	bool isValidPath(const std::filesystem::path& p, bool checkIsDirectory);
	void startExploreDirectory();


	////////////////////
	string getHeaderFileName(const string rawHeader, const char firstSymbol, const char secondSymbol);
				// Обход файлов


};
