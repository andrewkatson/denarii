// Copyright (c) 2006-2013, Andrey N. Sabelnikov, www.sabelnikov.net
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// * Neither the name of the Andrey N. Sabelnikov nor the
// names of its contributors may be used to endorse or promote products
// derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER  BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//


#ifndef _MISC_LOG_EX_H_
#define _MISC_LOG_EX_H_

#ifdef __cplusplus

#include <string>
#include <sstream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"


#undef MONERO_DEFAULT_LOG_CATEGORY
#define MONERO_DEFAULT_LOG_CATEGORY "default"

#define MAX_LOG_FILE_SIZE 104850000 // 100 MB - 7600 bytes
#define MAX_LOG_FILES 50

#define FATAL_LOG 0
#define ERROR_LOG 1
#define WARNING_LOG 2
#define INFO_LOG 3
#define DEBUG_LOG 4
#define TRACE_LOG 5

static int log_level = 0;

#define ALLOWED_TO_LOG(level) \
  log_level <= level

#define MCLOG(level, x) do { \
  std::stringstream ss; \
  ss << x; \
  if (level <= log_level) { \
    switch(log_level) { \
      case 0: \
        spdlog::critical(ss.str()); \
        break; \
      case 1: \
        spdlog::error(ss.str()); \
      case 2: \
        spdlog::warn(ss.str()); \
      case 3: \
        spdlog::info(ss.str()); \
      case 4: \
        spdlog::debug(ss.str()); \
      case 5: \
        spdlog::trace(ss.str()); \
      default: \
        spdlog::critical(ss.str()); \
    } \
  } \
} while(0)

#define MCFATAL(cat,x) MCLOG(0, x)
#define MCERROR(cat,x) MCLOG(1, x)
#define MCWARNING(cat,x) MCLOG(2, x)
#define MCINFO(cat,x) MCLOG(3, x)
#define MCDEBUG(cat,x) MCLOG(4, x)
#define MCTRACE(cat,x) MCLOG(5, x)

#define MCLOG_RED(level,cat,x) MCLOG(level,x)
#define MCLOG_GREEN(level,cat,x) MCLOG(level,x)
#define MCLOG_YELLOW(level,cat,x) MCLOG(level,x)
#define MCLOG_BLUE(level,cat,x) MCLOG(level,x)
#define MCLOG_MAGENTA(level,cat,x) MCLOG(level,x)
#define MCLOG_CYAN(level,cat,x) MCLOG(level,x)

#define MLOG_RED(level,x) MCLOG_RED(level,MONERO_DEFAULT_LOG_CATEGORY,x)
#define MLOG_GREEN(level,x) MCLOG_GREEN(level,MONERO_DEFAULT_LOG_CATEGORY,x)
#define MLOG_YELLOW(level,x) MCLOG_YELLOW(level,MONERO_DEFAULT_LOG_CATEGORY,x)
#define MLOG_BLUE(level,x) MCLOG_BLUE(level,MONERO_DEFAULT_LOG_CATEGORY,x)
#define MLOG_MAGENTA(level,x) MCLOG_MAGENTA(level,MONERO_DEFAULT_LOG_CATEGORY,x)
#define MLOG_CYAN(level,x) MCLOG_CYAN(level,MONERO_DEFAULT_LOG_CATEGORY,x)

#define MFATAL(x) MCFATAL(MONERO_DEFAULT_LOG_CATEGORY,x)
#define MERROR(x) MCERROR(MONERO_DEFAULT_LOG_CATEGORY,x)
#define MWARNING(x) MCWARNING(MONERO_DEFAULT_LOG_CATEGORY,x)
#define MINFO(x) MCINFO(MONERO_DEFAULT_LOG_CATEGORY,x)
#define MDEBUG(x) MCDEBUG(MONERO_DEFAULT_LOG_CATEGORY,x)
#define MTRACE(x) MCTRACE(MONERO_DEFAULT_LOG_CATEGORY,x)
#define MLOG(x) MINFO(MONERO_DEFAULT_LOG_CATEGORY,x)

#define MGINFO(x) MCINFO(MONERO_DEFAULT_LOG_CATEGORY, x)
#define MGINFO_RED(x) MCINFO(MONERO_DEFAULT_LOG_CATEGORY, x)
#define MGINFO_GREEN(x) MCINFO(MONERO_DEFAULT_LOG_CATEGORY, x)
#define MGINFO_YELLOW(x) MCINFO(MONERO_DEFAULT_LOG_CATEGORY, x)
#define MGINFO_BLUE(x) MCINFO(MONERO_DEFAULT_LOG_CATEGORY, x)
#define MGINFO_MAGENTA(x) MCINFO(MONERO_DEFAULT_LOG_CATEGORY, x)
#define MGINFO_CYAN(x) MCINFO(MONERO_DEFAULT_LOG_CATEGORY, x)


#define MIDEBUG(init, x) MCDEBUG(MONERO_DEFAULT_LOG_CATEGORY, x)


#define LOG_ERROR(x) MERROR(x)
#define LOG_PRINT_L0(x) MWARNING(x)
#define LOG_PRINT_L1(x) MINFO(x)
#define LOG_PRINT_L2(x) MDEBUG(x)
#define LOG_PRINT_L3(x) MTRACE(x)
#define LOG_PRINT_L4(x) MTRACE(x)

#define _dbg3(x) MTRACE(x)
#define _dbg2(x) MDEBUG(x)
#define _dbg1(x) MDEBUG(x)
#define _info(x) MINFO(x)
#define _note(x) MDEBUG(x)
#define _fact(x) MDEBUG(x)
#define _mark(x) MDEBUG(x)
#define _warn(x) MWARNING(x)
#define _erro(x) MERROR(x)

// Define the platform-specific code for setting the thread name
#ifdef _WIN32
#define SET_THREAD_NAME_PLATFORM(x) SetThreadDescription(std::this_thread::native_handle(), x);
#elif defined(__linux__)
#define SET_THREAD_NAME_PLATFORM(x) pthread_setname_np(pthread_self(), x);
#else 
#define SET_THREAD_NAME_PLATFORM(x) do { \
  std::stringstream ss; \
  ss << x; \
  pthread_setname_np(ss.str().c_str()); \
} while(0); 
#endif

// Define the macro to set the thread name
#define MLOG_SET_THREAD_NAME(x) SET_THREAD_NAME_PLATFORM(x);

#ifndef LOCAL_ASSERT
#include <assert.h>
#if (defined _MSC_VER)
#define LOCAL_ASSERT(expr) {if(epee::debug::get_set_enable_assert()){_ASSERTE(expr);}}
#else
#define LOCAL_ASSERT(expr)
#endif

#endif

std::string mlog_get_default_log_path(const char *default_filename);
void mlog_configure(const std::string &filename_base, bool console, const std::size_t max_log_file_size = MAX_LOG_FILE_SIZE, const std::size_t max_log_files = MAX_LOG_FILES);
void mlog_set_categories(const char *categories);
std::string mlog_get_categories(int level);
std::string mlog_get_default_categories(int level);
void mlog_set_log_level(int level);
void mlog_set_log(const char *log);

namespace epee
{
namespace debug
{
  inline bool get_set_enable_assert(bool set = false, bool v = false)
  {
    static bool e = true;
    if(set)
      e = v;
    return e;
  }
}



#define ENDL std::endl

#define TRY_ENTRY()   try {
#define CATCH_ENTRY(location, return_val) } \
  catch(const std::exception& ex) \
{ \
  (void)(ex); \
  LOG_ERROR("Exception at [" << location << "], what=" << ex.what()); \
  return return_val; \
}\
  catch(...)\
{\
  LOG_ERROR("Exception at [" << location << "], generic exception \"...\"");\
  return return_val; \
}

#define CATCH_ENTRY_L0(lacation, return_val) CATCH_ENTRY(lacation, return_val)
#define CATCH_ENTRY_L1(lacation, return_val) CATCH_ENTRY(lacation, return_val)
#define CATCH_ENTRY_L2(lacation, return_val) CATCH_ENTRY(lacation, return_val)
#define CATCH_ENTRY_L3(lacation, return_val) CATCH_ENTRY(lacation, return_val)
#define CATCH_ENTRY_L4(lacation, return_val) CATCH_ENTRY(lacation, return_val)


#define ASSERT_MES_AND_THROW(message) {LOG_ERROR(message); std::stringstream ss; ss << message; throw std::runtime_error(ss.str());}
#define CHECK_AND_ASSERT_THROW_MES(expr, message) do {if(!(expr)) ASSERT_MES_AND_THROW(message);} while(0)


#ifndef CHECK_AND_ASSERT
#define CHECK_AND_ASSERT(expr, fail_ret_val)   do{if(!(expr)){LOCAL_ASSERT(expr); return fail_ret_val;};}while(0)
#endif

#ifndef CHECK_AND_ASSERT_MES
#define CHECK_AND_ASSERT_MES(expr, fail_ret_val, message)   do{if(!(expr)) {LOG_ERROR(message); return fail_ret_val;};}while(0)
#endif

#ifndef CHECK_AND_NO_ASSERT_MES_L
#define CHECK_AND_NO_ASSERT_MES_L(expr, fail_ret_val, l, message)   do{if(!(expr)) {LOG_PRINT_L##l(message); /*LOCAL_ASSERT(expr);*/ return fail_ret_val;};}while(0)
#endif

#ifndef CHECK_AND_NO_ASSERT_MES
#define CHECK_AND_NO_ASSERT_MES(expr, fail_ret_val, message) CHECK_AND_NO_ASSERT_MES_L(expr, fail_ret_val, 0, message)
#endif

#ifndef CHECK_AND_NO_ASSERT_MES_L1
#define CHECK_AND_NO_ASSERT_MES_L1(expr, fail_ret_val, message) CHECK_AND_NO_ASSERT_MES_L(expr, fail_ret_val, 1, message)
#endif


#ifndef CHECK_AND_ASSERT_MES_NO_RET
#define CHECK_AND_ASSERT_MES_NO_RET(expr, message)   do{if(!(expr)) {LOG_ERROR(message); return;};}while(0)
#endif


#ifndef CHECK_AND_ASSERT_MES2
#define CHECK_AND_ASSERT_MES2(expr, message)   do{if(!(expr)) {LOG_ERROR(message); };}while(0)
#endif

enum console_colors
{
  console_color_default,
  console_color_white,
  console_color_red,
  console_color_green,
  console_color_blue,
  console_color_cyan,
  console_color_magenta,
  console_color_yellow
};

bool is_stdout_a_tty();
void set_console_color(int color, bool bright);
void reset_console_color();

}

extern "C"
{

#endif

#ifdef __GNUC__
#define ATTRIBUTE_PRINTF __attribute__((format(printf, 2, 3)))
#else
#define ATTRIBUTE_PRINTF
#endif

bool merror(const char *category, const char *format, ...) ATTRIBUTE_PRINTF;
bool mwarning(const char *category, const char *format, ...) ATTRIBUTE_PRINTF;
bool minfo(const char *category, const char *format, ...) ATTRIBUTE_PRINTF;
bool mdebug(const char *category, const char *format, ...) ATTRIBUTE_PRINTF;
bool mtrace(const char *category, const char *format, ...) ATTRIBUTE_PRINTF;

#ifdef __cplusplus

}

#endif

#endif //_MISC_LOG_EX_H_
