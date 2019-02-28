//
// Created by Chrim14 on 06.10.2017.
//

#ifndef PROCY_LOGGING_H
#define PROCY_LOGGING_H

#include <string>
#include <iostream>
#include <plog/Log.h>

/**
    Severity level:
    none    = 0
    fatal   = 1
    error   = 2
    warning = 3
    info    = 4
    debug   = 5
    verbose = 6
**/

//static plog::RollingFileAppender<plog::TxtFormatter> fileAppender("Debugger/debugging.txt", 100, 0);

static void lInfo(const std::string &text) {


    LOGI_(1) << text;
    LOGI_(2) << text;

}

static void lDebug(const std::string &text) {

    LOGD_(1) << text;
}

static void lWarning(const std::string &text) {

    LOGW_(1) << text;
    LOGW_(2) << text;
}

static void lFatal(const std::string &text) {

    LOGF_(1) << text;
    LOGF_(2) << text;
}

static void lError(const std::string &text) {

    LOGE_(1) << text;
    LOGE_(2) << text;
}

static void lVerbose(const std::string &text) {

    LOG(plog::verbose) << text;
}

static void lNone(const std::string &text) {

    LOGN_(1) << text;
    LOGN_(2) << text;
}

#endif //PROCY_LOGGING_H

