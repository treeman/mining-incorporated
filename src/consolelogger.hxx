#pragma once

#include "logger.hxx"

class ConsoleLogger : public Logger {
private:
    virtual void write(string s) override;
};

