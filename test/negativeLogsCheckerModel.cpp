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
	regex startWritingRegexp{ "\\s*\\[[EROWARNIG]*\\]\\s+[\\w\\W]*" };
	regex endWritingRegexp{ "^\\s*$" };

	if (regex_match(line, startWritingRegexp))
	{
		return LineRegExpStatus::startWrite;
	}
	else if (regex_match(line, endWritingRegexp))
	{
		return LineRegExpStatus::endWrite;
	}
	return LineRegExpStatus::continueLastAction;
}