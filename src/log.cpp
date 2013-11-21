#include "log.h"

Log::Log() {
    createLogFile();
    writeToLog("Created log file");
}

Log::~Log() {
    logFile.close();
}

bool Log::createLogFile() {
    std::stringstream ss;
    ss << time(NULL) << ".log";
    logFileName = ss.str();
    logFile.open(logFileName);
    return logFile.is_open();
}

void Log::writeTimeStamp() {
    time_t rTime;
    struct tm *tInfo;
    time(&rTime);
    tInfo = localtime (&rTime);

    char stamp[16];
    strftime(stamp,16,"[%T] ",tInfo);

    logFile << stamp;
}

void Log::writeToLog(std::string message) {
    writeTimeStamp();
    logFile << message << std::endl;
}

void Log::writeErrorToLog(std::string message) {
    writeTimeStamp();
    logFile << "ERROR: " << message << std::endl;
}