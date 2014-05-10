#pragma once

#include "logger.hxx"

class StdoutLogger : public Logger {
private:
    virtual void write(string s) override;
};

