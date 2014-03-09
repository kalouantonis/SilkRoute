#include <SilkRoute/Utils/Logger.h>

// Local file vars
LOG_LEVEL curLevel = ERR;

void setLogLevel(LOG_LEVEL level)
{
    // Set local variable curLevel to the specified level
    curLevel = level;
}

void log(LOG_LEVEL level, const QString& msg)
{
    // If the level is below or equal to the log type being
    // requested, then send message to output stream
    if(curLevel <= level)
        qDebug() << msg;
}

// Simple logging //////////////////////////////////////////////////////
void debug(const QString &msg)
{
    log(DEBUG, msg);
}

void info(const QString &msg)
{
    log(INFO, msg);
}

void error(const QString &msg)
{
    log(ERR, msg);
}

// Tagged logging //////////////////////////////////////////////////////
void debug(const QString &tag, const QString &msg)
{
    log(DEBUG, tag + ": " + msg);
}

void info(const QString &tag, const QString &msg)
{
    log(INFO, tag + ": " + msg);
}

void error(const QString &tag, const QString &msg)
{
    log(ERR, tag + ": " + msg);
}
