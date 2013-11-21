#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

class Log {
public:
    Log();
    ~Log();
    void writeToLog(std::string message);
    void writeErrorToLog(std::string message);
private:
    std::ofstream logFile;
    std::string logFileName;
    bool createLogFile();
    void writeTimeStamp();
protected:

};

#endif // LOG_H