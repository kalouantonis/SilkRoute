#ifndef LOGGER_H
#define LOGGER_H

#include <QDebug>

enum LOG_LEVEL
{
    DEBUG = 0,  /// Developer debug info
    INFO,       /// User info
    ERR         /// Critical errors
};


/// Allow setting of log level globaly
void setLogLevel(LOG_LEVEL level);

// Simple logging //////////////////////////////////////////////////////
/// Send debug message string to console
void debug(const QString& msg);
/// Send info message string to console
void info(const QString& msg);
/// Send error message string to console
void error(const QString& msg);


// Tagged logging //////////////////////////////////////////////////////
/// Send debug message string to console, along with tag.
/// tag is used to identify method that is logging
void debug(const QString& tag, const QString& msg);
/// Send info message string to console, along with tag.
void info(const QString& tag, const QString& msg);
/// Send error message string to console, along with tag.
void error(const QString& tag, const QString& msg);

#endif // LOGGER_H
