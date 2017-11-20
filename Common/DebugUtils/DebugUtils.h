#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H

#define TRACE(type, str)    \
    Serial.print(millis());     \
    Serial.print(" : "); \
    Serial.print(type); \
    Serial.print(" : ");  \
    Serial.print(str); \
    Serial.print(" : ");      \
    Serial.println(__PRETTY_FUNCTION__); \
    Serial.flush();

#define TRACE_FORMATED(type, str, format)    \
    Serial.print(millis());     \
    Serial.print(" : "); \
    Serial.print(type); \
    Serial.print(" : ");  \
    Serial.print(str,format); \
    Serial.print(" : ");      \
    Serial.println(__PRETTY_FUNCTION__); \
    Serial.flush();


#ifdef TRACE_LEVEL_DEBUG
    #ifndef TRACE_LEVEL_ERROR
        #define TRACE_LEVEL_ERROR
    #endif
    #define DEBUG_PRINT(str)  TRACE("DEBUG", str)
    #define DEBUG_PRINT_FORMATED(str, format)   TRACE("DEBUG", str, format)
#else
    #define DEBUG_PRINT(str)
    #define DEBUG_PRINT_FORMATED(str, format)
#endif

#ifdef TRACE_LEVEL_ERROR
    #ifndef TRACE_LEVEL_INFO
        #define TRACE_LEVEL_INFO
    #endif
    #define ERROR_PRINT(str)  TRACE("ERROR", str)
    #define ERROR_PRINT_FORMATED(str, format)   TRACE("ERROR", str, format)
#else
    #define ERROR_PRINT(str)
    #define ERROR_PRINT_FORMATED(str, format)
#endif



#ifdef TRACE_LEVEL_INFO
    #define INFO_PRINT(str)  TRACE("INFO ", str)
    #define INFO_PRINT_FORMATED(str, format)   TRACE("INFO ", str, format)
#else
    #define INFO_PRINT(str)
    #define INFO_PRINT_FORMATED(str, format)
#endif
#endif