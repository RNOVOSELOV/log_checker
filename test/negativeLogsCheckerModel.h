#pragma once
#include "model.h"

class NegativeLogsCheckerModel final :
    public Model
{
public:
    NegativeLogsCheckerModel();
    virtual ~NegativeLogsCheckerModel();
protected:
    virtual LineRegExpStatus validateLine(const std::string& line) override;
};

