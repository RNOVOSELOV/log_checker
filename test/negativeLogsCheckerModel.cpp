#include "NegativeLogsCheckerModel.h"

#include "regex"

NegativeLogsCheckerModel::NegativeLogsCheckerModel()
{

}

NegativeLogsCheckerModel::~NegativeLogsCheckerModel()
{

}

LineRegExpStatus NegativeLogsCheckerModel::validateLine(const std::string& line)
{
	regex startWritingRegexp{ "\\s*\\[[EROWARNIG]*\\]\\s+[0-9][0-9]:[0-9][0-9]:[0-9][0-9].[0-9][0-9][0-9]\\+[0-9][0-9]:[0-9][0-9]\\s*" }; 
	regex endWritingRegexp{ "^\\s*$" };
	regex logFormatValidatorRegexp{ "\\s*\\[[EROWANIGFDBU]*\\]\\s+[0-9][0-9]:[0-9][0-9]:[0-9][0-9].[0-9][0-9][0-9]\\+[0-9][0-9]:[0-9][0-9]\\s*" };

	if (regex_match(line, startWritingRegexp))
	{
		return LineRegExpStatus::startWrite;
	}
	else if (regex_match(line, endWritingRegexp))
	{
		return LineRegExpStatus::logDelimeter;
	}
	else if (regex_match(line, logFormatValidatorRegexp))
	{
		return LineRegExpStatus::trueLogFormat;
	}
	return LineRegExpStatus::continueLastAction;
}