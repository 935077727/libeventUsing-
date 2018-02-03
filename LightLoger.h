#ifndef LIGHTLOGER_H
#define LIGHTLOGER_H


#include <stdio.h>
#include <string>
//#include <iostream>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <memory.h>
#include <stdlib.h>


#ifdef _WIN32
#include <direct.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#define ACCESS _access
#define MKDIR(a) _mkdir((a))
#include <windows.h>
#else
#include <stdarg.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>
#define ACCESS(path,mode)  access(path,mode)
#define MKDIR(a) mkdir((a),0755)
#define _strdup(e) strdup(e)
#endif

//#include <Winbase.h>

#include<assert.h>

#define ASSERT(exp)	if(exp==0){LightLoger::log_b("dump at file :");LightLoger::log_b(__FILE__);LightLoger::log_bint("line :%d",__LINE__);assert(exp);}



/*
1. 日志保存到一定数量写入文件，减少i/o消耗
2. 日志分级别保存，调式日志，业务日志
3. 可以选择保存日志的日志路径
4. 选择是否打印在屏幕上。（打印在屏幕上十分拖累速度）
*/
#define LOG_BUSINESS_INFO   0x01
#define LOG_DEBUG_INFO      0x02
//#define LOG_ALL_INFO        0x03

#define LOG_BUF_MAX_SIZE    1024*100
#define LOG_BUF_LINE_MAX_SIZE 1024*2
#define LOG_SAVE_PATH       "//mnt//hda0://testlibevent"
#define LOG_BUSINESS_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_TEMP_ENABLE
#define LOG_PRINTF_ENABLE
enum log_mode
{
    log_mode_debug=LOG_BUSINESS_INFO,
    log_mode_business=LOG_DEBUG_INFO,
    //log_mode_all=LOG_ALL_INFO
};


class LightLoger

{
   private:
		#ifdef _WIN32
		static CRITICAL_SECTION  m_log_file_lock;
		#else
		static pthread_mutex_t m_log_file_lock;
		#endif // _LINUX


    public:
         LightLoger();
        virtual ~LightLoger();
        static int log_d(char*);
		static int log_b(char*);
        static int log_b(char*,char*);
		static int log_dint(char*, ...);
		static int log_bint(char*, ...);

    protected:

		static char m_szyear[5];
		static char m_szmounth[3];
		static char m_szday[3];
		static char m_szhour[3];
		static char m_szminute[3];
		static char m_szsecond[3];
		static char m_szpid[10];
		static char *m_lpszlog_buf;
		static int m_log_buf_size;
		static char *m_lpszlog_line_buf;
		static int m_log_line_buf_size;
		static char m_log_save_path[1024];
		static char m_file_line[11];
		static char *m_lpsz_tmp;

		static char m_isInit;
		static int  m_counter;
		static char m_isSetCounterZero;
		static char m_counterbuf[16];
		static char m_szThisDayBeginStamp[12];
		static time_t m_dayBeginStamp;
		static time_t m_lastDaybeginStamp;

    private:
		static int log_port_get_time();
		static int log_port_init(void);
		static int log_port_destory(void);
		static int log_port_output(const char *log, size_t size);
		static int log_port_output_lock(void);
		static int log_port_output_unlock(void);
		static int log_port_get_pid_info();
		static int add_log(char *sz, log_mode mode);
		static int creat_debug_log(char *szstr);
		static int creat_business_log(char *szstr);
		static int log_get_save_path();
		static int log_push_buff(char *szline_buf);
		static int log_flush();
		static int check_file_exist(char * path);
		static int make_multidir(char *path);
		static int getThisDayBeginStamp(time_t t);
		static time_t charDataToTime_t(char *t);
		static int log_get_save_path(time_t);
		static int log_port_get_time(time_t);
		static int log_flush(time_t);

};

#endif // LIGHTLOGER_H
