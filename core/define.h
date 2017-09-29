#ifndef DEFINE_H
#define DEFINE_H

#define ALL(arr) arr.begin(), arr.end()

// default rights
#define PERM_READ   "READ"
#define PERM_ADD    "ADD"
#define PERM_EDIT   "EDIT"
#define PERM_DELETE "DELETE"

#define DEC_MULTIPLE 100
#define TO_DEC(num) QDecDouble((double)num / DEC_MULTIPLE)
#define FROM_DEC(num) num.toDouble() * DEC_MULTIPLE

#ifndef APP_NAME
    #define APP_NAME "QodbAPP"
#endif

#ifndef PLUGIN_ROOT
    #ifdef _WIN32
    #define PLUGIN_ROOT "/../../plugins"
    #else
    #ifdef _DEBUG
        #define PLUGIN_ROOT "/../plugins"
    #else
        #define PLUGIN_ROOT "/../lib/" APP_NAME "/plugins"
    #endif
    #endif
#endif

#ifndef REPORT_ROOT
    #ifdef _WIN32
    #define REPORT_ROOT "/../../reports"
    #else
    #ifdef _DEBUG
        #define REPORT_ROOT "/../reports"
    #else
        #define REPORT_ROOT "/../share/" APP_NAME "/reports"
    #endif
    #endif
#endif

#endif // DEFINE_H

