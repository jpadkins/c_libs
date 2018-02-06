
///////////////////////////////////////////////////////////////////////////////
/// @file	jp_log.h
/// @author	Jacob Adkins (jpadkins)
/// @brief	API for logging information and possibly halting execution
///
/// Each of the jpLog_ functions comes in 'info', 'warn', and 'exit' varieties,
/// indicating different error states:
///
/// info: Used for general purpose logging and does not indicate any error
/// warn: Used for indicating runtime errors (i.e. should be handled)
/// exit: Used for indicating programmer errors (i.e. assertions)
///
/// Style: Where to place sanity-checks within a function
/// ---------------------------------------------------------------------------
/// Sanity-checks, i.e. testing for NULL or other jpLog_* funcs being called
/// in response to conditionals that are along the vein of assertions, should
/// be placed before the segment where variables are declared (i.e. first in
/// the function's definition). The reasoning for this is that these types of
/// checks (usually using *exit* funcs) are used to aid development and should
/// be easy to find. Preferably *exit* funcs should be removed in production
/// by defining JP_LOG_NOEXIT before including the log.h header.
/// 
///
/// Style: When to use jpLog_* funcs vs jpLog_*If funcs
/// ---------------------------------------------------------------------------
/// - If the conditional you are checking can fit on one line, use jpLog_*If
/// - If the conditional spans multiple lines, use an if {} block
/// - Do not mix between jpLog_* and jpLog_*If for series of consecutive
///     conditionals, i.e. if one conditional in a logical grouping requires
///     an if {} block due to length, then all conditionals in the logical
///     grouping should use if {} blocks
/// - NOTE that if the log function in question is a member of the *exit*
///     variety and is being used along the vein of an assertion, then
///     jpLog_*If should always be used to ensure that these types of checks
///     can be easily removed for production builds. Prefer separating these
///     calls into two statements if the conditional causes a line break,
///     i.e.
///     
///     jpLog_exitIf(!(some_variable = some_function__create()),
///             "Failed to create some_variable");
///
///     should be
///
///     some_variable = some_variable__create();
///     jpLog_exitIf(!some_variable, "Failed to create some_variable");
///
///     Also note that this should ALWAYS be done for conditionals checking
///     the results of any form of memory allocation. If calls to functions
///     like malloc or calloc happen within a jpLog_* function, Valgrind gets
///     fussy.
///
/// @TODO Add an API for setting output stream and logging to a file
///////////////////////////////////////////////////////////////////////////////
#ifndef JPA__LOG_H
#define JPA__LOG_H

///////////////////////////////////////////////////////////////////////////////
// Necessary to allow log macros to be used as expressions
///////////////////////////////////////////////////////////////////////////////
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-value"
#endif

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////
#include <stdarg.h>

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @brief	Used internally by *_info log macros
///
/// @param	file	Name of the current file
/// @param	func	Name of the current function
/// @param	line	Current line number
/// @param	fmt     Format string
/// @param	...		Format arguments
///////////////////////////////////////////////////////////////////////////////
void jpLog__info (
        const char *file,
        const char *func,
        int line,
        const char *fmt,
        ...);

///////////////////////////////////////////////////////////////////////////////
/// @brief	Used internally by *_warn log macros
///
/// @param	file	Name of the current file
/// @param	func	Name of the current function
/// @param	line	Current line number
/// @param	fmt     Format string
/// @param	...		Format arguments
///////////////////////////////////////////////////////////////////////////////
void jpLog__warn(
        const char *file,
        const char *func,
        int line,
        const char *fmt,
        ...);

///////////////////////////////////////////////////////////////////////////////
/// @brief	Used internally by *_exit log macros
///
/// @param	file	Name of the current file
/// @param	func	Name of the current function
/// @param	line	Current line number
/// @param	fmt     Format string
/// @param	...		Format arguments
///////////////////////////////////////////////////////////////////////////////
void jpLog__exit(
        const char *file,
        const char *func,
        int line,
        const char *fmt,
        ...);

///////////////////////////////////////////////////////////////////////////////
// Macros
///////////////////////////////////////////////////////////////////////////////

#ifndef JP_LOG_NOINFO

///////////////////////////////////////////////////////////////////////////////
/// @brief Logs a message
///
/// @param msg  Message to log
///////////////////////////////////////////////////////////////////////////////
#define jpLog_info(msg) jpLog__info(__FILE__,__func__,__LINE__,"%s",msg)

///////////////////////////////////////////////////////////////////////////////
/// @brief Logs a message if expr is true
///
/// @param expr Expression to test
/// @param msg  Message to log
///////////////////////////////////////////////////////////////////////////////
#define jpLog_infoIf(expr,msg) ( (expr)?jpLog_info(msg),expr:expr )

///////////////////////////////////////////////////////////////////////////////
/// @brief Logs a formatted message
///
/// @param fmt  Format string
/// @param ...  Format arguments
///////////////////////////////////////////////////////////////////////////////
#define jpLog_infoFmt(fmt,...) jpLog__info(__FILE__,__func__,__LINE__,fmt,\
	__VA_ARGS__)

///////////////////////////////////////////////////////////////////////////////
/// @brief Logs a formatted message if expr is true
///
/// @param expr Expression to test
/// @param fmt  Format string
/// @param ...  Format arguments
///////////////////////////////////////////////////////////////////////////////
#define jpLog_infoFmtIf(expr,fmt,...)\
    ( (expr)?jpLog_infoFmt(fmt,__VA_ARGS__),expr:expr )

#else

    #define jpLog_info(...)         ( (void)(__VA_ARGS__) )
    #define jpLog_infoIf(...)       ( (void)(__VA_ARGS__) )
    #define jpLog_infoFmt(...)      ( (void)(__VA_ARGS__) )
    #define jpLog_infoFmtIf(...)    ( (void)(__VA_ARGS__) )

#endif

#ifndef JP_LOG_NOWARN

///////////////////////////////////////////////////////////////////////////////
/// @brief Logs a message indicating a runtime error
///
/// @param msg  Message to log
///////////////////////////////////////////////////////////////////////////////
#define jpLog_warn(msg) jpLog__warn(__FILE__,__func__,__LINE__,"%s",msg)

///////////////////////////////////////////////////////////////////////////////
/// @brief Logs a message indicating a runtime error if expr is true
///
/// @param expr Expression to test
/// @param msg  Message to log
///////////////////////////////////////////////////////////////////////////////
#define jpLog_warnIf(expr,msg) ( (expr)?jpLog_warn(msg),expr:expr )

///////////////////////////////////////////////////////////////////////////////
/// @brief Logs a formatted message indicating a runtime error
///
/// @param fmt  Format string
/// @param ...  Format arguments
///////////////////////////////////////////////////////////////////////////////
#define jpLog_warnFmt(fmt,...) jpLog__warn(__FILE__,__func__,__LINE__,fmt,\
	__VA_ARGS__)

///////////////////////////////////////////////////////////////////////////////
/// @brief Logs a formatted message indicating a runtime error if expr is true
///
/// @param expr Expression to test
/// @param fmt  Format string
/// @param ...  Format arguments
///////////////////////////////////////////////////////////////////////////////
#define jpLog_warnFmtIf(expr,fmt,...)\
    ( (expr)?jpLog_warnFmt(fmt,__VA_ARGS__),expr:expr )

#else

    #define jpLog_warn(...)         ( (void)(__VA_ARGS__) )
    #define jpLog_warnIf(...)       ( (void)(__VA_ARGS__) )
    #define jpLog_warnFmt(...)      ( (void)(__VA_ARGS__) )
    #define jpLog_warnFmtIf(...)    ( (void)(__VA_ARGS__) )

#endif

#ifndef JP_LOG_NOEXIT

///////////////////////////////////////////////////////////////////////////////
/// @brief Logs a message indicating a program error
///
/// The program exits after logging.
///
/// @param msg  Message to log
///////////////////////////////////////////////////////////////////////////////
#define jpLog_exit(msg) jpLog__exit(__FILE__,__func__,__LINE__,"%s",msg)

///////////////////////////////////////////////////////////////////////////////
/// @brief Logs a message indicating a program error if expr is true
///
/// The program exits after logging.
///
/// @param expr Expression to test
/// @param msg  Message to log
///////////////////////////////////////////////////////////////////////////////
#define jpLog_exitIf(expr,msg) ( (expr)?jpLog_exit(msg),expr:expr )

///////////////////////////////////////////////////////////////////////////////
/// @brief Logs a formatted message indicating a program error
///
/// The program exits after logging.
///
/// @param fmt  Format string
/// @param ...  Format arguments
///////////////////////////////////////////////////////////////////////////////
#define jpLog_exitFmt(fmt,...) jpLog__exit(__FILE__,__func__,__LINE__,fmt,\
	__VA_ARGS__)

///////////////////////////////////////////////////////////////////////////////
/// @brief Logs a formatted message indicating a program error if expr is true
///
/// The program exits after logging.
///
/// @param expr Expression to test
/// @param fmt  Format string
/// @param ...  Format arguments
///////////////////////////////////////////////////////////////////////////////
#define jpLog_exitFmtIf(expr,fmt,...)\
    ( (expr)?jpLog_exitFmt(fmt,__VA_ARGS__),expr:expr )

#else

    #define jpLog_exit(...)         ( (void)(__VA_ARGS__) )
    #define jpLog_exitIf(...)       ( (void)(__VA_ARGS__) )
    #define jpLog_exitFmt(...)      ( (void)(__VA_ARGS__) )
    #define jpLog_exitFmtIf(...)    ( (void)(__VA_ARGS__) )

#endif

// #pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic pop
// #pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic pop
// #pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic pop

// ifndef JPA__LOG_H
#endif
