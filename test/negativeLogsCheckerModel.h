#pragma once
#include "model.h"

class NegativeLogsCheckerModel :
    public Model
{
public:
    NegativeLogsCheckerModel();
    virtual ~NegativeLogsCheckerModel();
protected:
    virtual LineRegExpStatus validateLine(const std::string& line);
};

