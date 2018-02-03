
#include "LightLoger.h"


char LightLoger::m_szyear[5];
char LightLoger::m_szmounth[3];
char LightLoger::m_szday[3];
char LightLoger::m_szhour[3];
char LightLoger::m_szminute[3];
char LightLoger::m_szsecond[3];
char LightLoger::m_szpid[10];
char LightLoger::m_log_save_path[1024];
int LightLoger::m_log_buf_size;
int LightLoger::m_log_line_buf_size;
char LightLoger::m_file_line[11];
char* LightLoger::m_lpszlog_line_buf =NULL;// (char *)malloc(sizeof(char)*LOG_BUF_LINE_MAX_SIZE);
char* LightLoger::m_lpsz_tmp = NULL;//(char *)malloc(sizeof(char)*LOG_BUF_LINE_MAX_SIZE);
char* LightLoger::m_lpszlog_buf =NULL;// (char *)malloc(sizeof(char)*LOG_BUF_MAX_SIZE);
char LightLoger::m_isInit = 0;
char  LightLoger::m_counterbuf[16];
int  LightLoger::m_counter = 0;
char LightLoger::m_isSetCounterZero = 0;
time_t LightLoger::m_dayBeginStamp=0;
time_t LightLoger::m_lastDaybeginStamp=0;


#ifdef _WIN32
CRITICAL_SECTION  LightLoger::m_log_file_lock;
#else
pthread_mutex_t LightLoger::m_log_file_lock;
#endif // _LINUX

LightLoger::LightLoger()
{

}

LightLoger::~LightLoger()
{
    free(m_lpszlog_buf);
	free(m_lpszlog_line_buf);
	free(m_lpsz_tmp);
    log_port_destory();
    //dtor
}

int LightLoger::log_port_get_time()
{
    time_t timep;
    struct tm *p;

    time(&timep);
    p = localtime(&timep);
    if (p == NULL) {
        return -1;
    }

    strftime(m_szyear,5,"%Y",p);
    strftime(m_szmounth,3,"%m",p);
    strftime(m_szday,3,"%d",p);
    strftime(m_szhour,3,"%H",p);
    strftime(m_szminute,3,"%M",p);
    strftime(m_szsecond,3,"%S",p);

    return 0;
}

int LightLoger::log_port_init(void)
{

	if (m_isInit==0)
	{
        #ifdef _WIN32
        ::InitializeCriticalSection(&m_log_file_lock);
        #else
        pthread_mutex_init(&m_log_file_lock,NULL);
        #endif // _LINUX
		time_t t;
		time(&t);
		getThisDayBeginStamp(t);
		m_lastDaybeginStamp = m_dayBeginStamp;
		m_lpszlog_buf = (char *)malloc(sizeof(char)*LOG_BUF_MAX_SIZE);
		m_lpszlog_line_buf = (char *)malloc(sizeof(char)*LOG_BUF_LINE_MAX_SIZE);
		m_lpsz_tmp = (char *)malloc(sizeof(char)*LOG_BUF_LINE_MAX_SIZE);
		memset(m_lpszlog_buf, 0x0, LOG_BUF_MAX_SIZE);
		memset(m_lpszlog_line_buf, 0x0, LOG_BUF_LINE_MAX_SIZE);
		memset(m_lpsz_tmp, 0x0, LOG_BUF_LINE_MAX_SIZE);
		m_isInit = 1;
		return 0;
	}
	else
	{

		m_isInit = 1;
		return 0;
	}

}
int LightLoger::log_port_output_lock(void)
{

    #ifdef _WIN32
    EnterCriticalSection(&m_log_file_lock);
    #else
    pthread_mutex_lock(&m_log_file_lock);
    #endif // _LINUX
    return 0;
}
int LightLoger::log_port_output_unlock(void)
{

    #ifdef _WIN32
    ::LeaveCriticalSection(&m_log_file_lock);
    #else
    pthread_mutex_unlock(&m_log_file_lock);
    #endif // _LINUX
    return 0;
}
int LightLoger::log_port_destory(void)
{
    #ifdef _WIN32
    DeleteCriticalSection(&m_log_file_lock);
    #else
    pthread_mutex_destroy(&m_log_file_lock);
    #endif // _LINUX
    return 0;
}
int LightLoger::log_port_output(const char *log, size_t size)
{
    /*out to terminal*/
	#ifdef LOG_PRINTF_ENABLE
    printf("%s\n",log);
	#endif
    /*out to logfile*/
    return 0;

}
int LightLoger::log_port_get_pid_info()
{
//    memset(m_szpid,0,10);
//	sprintf(m_szpid, "pid:%04d", GetCurrentProcessId());
    return 0;
}
int LightLoger::add_log(char *szlog,log_mode mode)
{
    if(strlen(szlog)==0)
    {
        return -1;
    }
	#ifdef LOG_TEMP_ENABLE
	//log_get_save_path();
	//if (check_file_exist(m_log_save_path))
	//{
	//	m_counter = 0;
	//	if(make_multidir(m_log_save_path))
	//	{
	//		//return -1;
	//	}
	//}
	#endif
	//log_get_save_path();
	//if (check_file_exist(m_log_save_path))
	//{
	//	m_counter = 0;
	//	if(make_multidir(m_log_save_path))
	//	{
	//		//return -1;
	//	}
	//}
	if (mode==log_mode_business)
	{
		#ifdef LOG_DEBUG_ENABLE
		creat_debug_log(szlog);
		#ifdef LOG_TEMP_ENABLE
		if(LOG_BUF_MAX_SIZE-m_log_buf_size<strlen(m_lpszlog_line_buf)&&m_log_buf_size!=0)
		{
			if(log_flush())
			{
				return -1;
			}
			log_push_buff(m_lpszlog_line_buf);
		}
		if (log_push_buff(m_lpszlog_line_buf))
		{
			return -1;
		}
		return 0;
		#endif

		log_push_buff(m_lpszlog_line_buf);
		log_flush();
		return 0;
		#endif
	}
	else if (mode==log_mode_debug)
	{
		#ifdef LOG_BUSINESS_ENABLE
		creat_business_log(szlog);
		#ifdef LOG_TEMP_ENABLE
		if (LOG_BUF_MAX_SIZE - m_log_buf_size<strlen(m_lpszlog_line_buf) && m_log_buf_size != 0)
		{
			if (log_flush())
			{
				return -1;
			}
			log_push_buff(m_lpszlog_line_buf);
		}
		if (log_push_buff(m_lpszlog_line_buf))
		{
			return -1;
		}
		return 0;
		#endif

		log_push_buff(m_lpszlog_line_buf);
		log_flush();
		return 0;
		#endif

	}
	return -1;
}

int LightLoger::creat_debug_log(char *szstr)
{


	if (strlen(szstr)>LOG_BUF_LINE_MAX_SIZE - 1024)
	{
		return -1;
	}
	log_port_get_time();
	time_t t;
	time(&t);
	getThisDayBeginStamp(t);
	if (m_dayBeginStamp != m_lastDaybeginStamp)
	{
		m_counter = 0;
		log_flush(m_lastDaybeginStamp);
		m_lastDaybeginStamp = m_dayBeginStamp;
	}
	//log_port_get_pid_info();
	memset(m_counterbuf, 0, 16);
	sprintf(m_counterbuf, "%09d", m_counter);
	memset(m_lpszlog_line_buf, 0x0, LOG_BUF_LINE_MAX_SIZE);
	strcat(m_lpszlog_line_buf, "[ ");
	strcat(m_lpszlog_line_buf, m_counterbuf);
	strcat(m_lpszlog_line_buf, "   DEBUG    ");
	strcat(m_lpszlog_line_buf, m_szyear);
	strcat(m_lpszlog_line_buf, "-");
	strcat(m_lpszlog_line_buf, m_szmounth);
	strcat(m_lpszlog_line_buf, "-");
	strcat(m_lpszlog_line_buf, m_szday);
	strcat(m_lpszlog_line_buf, "  ");
	strcat(m_lpszlog_line_buf, m_szhour);
	strcat(m_lpszlog_line_buf, ":");
	strcat(m_lpszlog_line_buf, m_szminute);
	strcat(m_lpszlog_line_buf, ":");
	strcat(m_lpszlog_line_buf, m_szsecond);
	strcat(m_lpszlog_line_buf, " ]    ");
	strcat(m_lpszlog_line_buf, szstr);
	strcat(m_lpszlog_line_buf, "\t\n----------------------------------------------------------------------------\t\n");
	//out to hei chuang kou
	log_port_output(m_lpszlog_line_buf, strlen(m_lpszlog_line_buf));
	m_counter++;
	return 0;
}
int LightLoger::creat_business_log(char *szstr)
{

	if (strlen(szstr)>LOG_BUF_LINE_MAX_SIZE - 1024)
	{
		return -1;
	}
	log_port_get_time();

	time_t t;
	time(&t);
	getThisDayBeginStamp(t);
	if (m_dayBeginStamp != m_lastDaybeginStamp)
	{
		m_counter = 0;
		log_flush(m_lastDaybeginStamp);
		m_lastDaybeginStamp = m_dayBeginStamp;
	}

	//log_port_get_pid_info();
	memset(m_counterbuf, 0, 16);
	sprintf(m_counterbuf, "%09d", m_counter);
	memset(m_lpszlog_line_buf, 0x0, LOG_BUF_LINE_MAX_SIZE);
	strcat(m_lpszlog_line_buf, "[ ");
	strcat(m_lpszlog_line_buf, m_counterbuf);
	strcat(m_lpszlog_line_buf, "   BUSINESS ");
	strcat(m_lpszlog_line_buf, m_szyear);
	strcat(m_lpszlog_line_buf, "-");
	strcat(m_lpszlog_line_buf, m_szmounth);
	strcat(m_lpszlog_line_buf, "-");
	strcat(m_lpszlog_line_buf, m_szday);
	strcat(m_lpszlog_line_buf, "  ");
	strcat(m_lpszlog_line_buf, m_szhour);
	strcat(m_lpszlog_line_buf, ":");
	strcat(m_lpszlog_line_buf, m_szminute);
	strcat(m_lpszlog_line_buf, ":");
	strcat(m_lpszlog_line_buf, m_szsecond);
	strcat(m_lpszlog_line_buf, " ]    ");
	strcat(m_lpszlog_line_buf, szstr);
	strcat(m_lpszlog_line_buf, "\t\n----------------------------------------------------------------------------\t\n");
	//out to hei chuang kou
	log_port_output(m_lpszlog_line_buf, strlen(m_lpszlog_line_buf));
	m_counter++;
	return 0;
}
int LightLoger::log_get_save_path()
{
    memset(m_log_save_path,0x0,1024);
    if(!log_port_get_time())
    {
        strcat(m_log_save_path,LOG_SAVE_PATH);
        strcat(m_log_save_path,m_szyear);
        strcat(m_log_save_path,"//");
        strcat(m_log_save_path,m_szmounth);
        strcat(m_log_save_path,"//");
		strcat(m_log_save_path,m_szday);
        return 0;
    }
    else
    {
        return -1;
    }
}
int LightLoger::log_push_buff(char *szline_buf)
{
    size_t buf_line_size=strlen(szline_buf);
    if(LOG_BUF_MAX_SIZE-m_log_buf_size<buf_line_size)
    {
        return -1;
    }
    strcat(m_lpszlog_buf,m_lpszlog_line_buf);
    m_log_buf_size+=buf_line_size;
    return 0;
}

int LightLoger::log_flush()
{
    log_get_save_path();
	if (strlen(m_lpszlog_buf)==0)
	{
		return -1;
	}
    if(check_file_exist(m_log_save_path))
	{
		//m_counter = 1;
		log_flush(m_lastDaybeginStamp);
        if(make_multidir(m_log_save_path))
		{
           //return -1;
        }
    }
    FILE *LogFD;
    LogFD=fopen(m_log_save_path,"a+");
    if(LogFD==NULL)
    {
        return -1;
    }
    fwrite(m_lpszlog_buf,sizeof(char),strlen(m_lpszlog_buf),LogFD);
    fclose(LogFD);
    m_log_buf_size=0;
    memset(m_lpszlog_buf,0x0,LOG_BUF_MAX_SIZE);
    return 0;
}


int LightLoger::make_multidir(char *path)
{
	char buf[1024] = {0};
	memcpy(buf,path,strlen(path)-2);
	int i = 0;
	int iRet;
	int iLen;
	char* pszDir;

	if (NULL == buf)
	{
		return 0;
	}

	pszDir = _strdup(buf);
	iLen = strlen(pszDir);


	for (i = 0; i < iLen; i++)
	{
		if ((pszDir[i] == '\\' || pszDir[i] == '/')&& i>0)
		{
			pszDir[i] = '\0';


			iRet = ACCESS(pszDir, 0);
			if (iRet != 0)
			{
				iRet = MKDIR(pszDir);
				if (iRet != 0)
				{
                    printf("mkdir=%s:msg=%s\n", pszDir, strerror(errno));
                    return -1;
				}
			}

			pszDir[i] = '/';
		}
	}

	iRet = MKDIR(pszDir);
	free(pszDir);
	return iRet;
}
int LightLoger::check_file_exist(char * path)
{
    if(ACCESS(path,0)==-1)
    {
		// printf("file is not exist \n ,path is %s\n",path);

        return -1;
    }
    else
    {
        //m_count++;
		// printf("file is exist \n");
        return 0;
    }

}

int LightLoger::log_d(char*szstr)
{
	log_port_init();
    log_port_output_lock();
    if( add_log(szstr,log_mode_debug))
    {
        log_port_output_unlock();
        return -1;
    }
    log_port_output_unlock();
        return 0;
}
int LightLoger::log_b(char*szstr)
{
	log_port_init();
    log_port_output_lock();
    if( add_log(szstr,log_mode_business))
    {
        log_port_output_unlock();
        return -1;
    }

    log_port_output_unlock();
    return 0;

}
int LightLoger::log_dint(char* szlog, ...)
{
	log_port_init();
	log_port_output_lock();
	memset(m_lpsz_tmp,0,LOG_BUF_LINE_MAX_SIZE);
	va_list arg_ptr;
	int j = 0;
	va_start(arg_ptr, szlog);
	j = va_arg(arg_ptr, int);
	va_end(arg_ptr);
	//printf("%d %d\n", i, j);
	sprintf(m_lpsz_tmp,szlog,j);
	if (add_log(m_lpsz_tmp, log_mode_debug))
	{
		log_port_output_unlock();
		return -1;
	}
	log_port_output_unlock();
	    return 0;

}
int LightLoger::log_bint(char*szlog, ...)
{
	log_port_init();
	log_port_output_lock();
	memset(m_lpsz_tmp, 0, LOG_BUF_LINE_MAX_SIZE);
	va_list arg_ptr;
	int j = 0;
	va_start(arg_ptr, szlog);
	j = va_arg(arg_ptr, int);
	va_end(arg_ptr);
	//printf("%d %d\n", i, j);
	sprintf(m_lpsz_tmp, szlog, j);
	if (add_log(m_lpsz_tmp, log_mode_business))
	{
		log_port_output_unlock();
		return -1;
	}
	log_port_output_unlock();
	    return 0;
}
int LightLoger::getThisDayBeginStamp(time_t t)
{
	struct tm *l = localtime(&t);
	char buf[15];
	#ifdef _WIN32
    _snprintf(buf, sizeof(buf), "%04d%02d%02d%02d%02d%02d", l->tm_year + 1900, l->tm_mon + 1, l->tm_mday, l->tm_hour, l->tm_min, l->tm_sec);
	#else
	snprintf(buf, sizeof(buf), "%04d%02d%02d%02d%02d%02d", l->tm_year + 1900, l->tm_mon + 1, l->tm_mday, l->tm_hour, l->tm_min, l->tm_sec);
	#endif // _WIN32

	buf[14] = 0;
	memset(buf + 8, '0', 6);
	m_dayBeginStamp= charDataToTime_t(buf);
	if (m_dayBeginStamp==0)
	{
		return -1;
	}
	return 0;
}
time_t LightLoger::charDataToTime_t(char *t)
{
	char ti[20];
	strcpy(ti, t);
	char year[5] = {0};
	char mon[3] = {0};
	char day[3] = { 0 };
	char hour[3] = { 0 };
	char min[3] = { 0 };
	char sec[3] = { 0 };
	int len = strlen(ti);
	if (len<14)
	{
		for (int i = 0; i <14 - len; i++)
		{
			strcat(ti, "0");
		}
	}
	strncpy(year, ti, 4);
	strncpy(mon, ti + 4, 2);
	strncpy(day, ti + 6, 2);
	strncpy(hour, ti + 8, 2);
	strncpy(min, ti + 10, 2);
	strncpy(sec, ti + 12, 2);
	struct tm tmp_time;
	tmp_time.tm_year = atoi(year) - 1900;
	tmp_time.tm_mon = atoi(mon) - 1;
	tmp_time.tm_mday = atoi(day);
	tmp_time.tm_hour = atoi(hour);
	tmp_time.tm_min = atoi(min);
	tmp_time.tm_sec = atoi(sec);
	tmp_time.tm_isdst = 0;
	time_t tt = mktime(&tmp_time);
	return tt;
}

int LightLoger::log_get_save_path(time_t t)
{
	memset(m_log_save_path, 0x0, 1024);
	if (!log_port_get_time(t))
	{
		strcat(m_log_save_path, LOG_SAVE_PATH);
		strcat(m_log_save_path, m_szyear);
		strcat(m_log_save_path, "//");
		strcat(m_log_save_path, m_szmounth);
		strcat(m_log_save_path, "//");
		strcat(m_log_save_path, m_szday);
		return 0;
	}
	else
	{
		return -1;
	}
}
int LightLoger::log_port_get_time(time_t t)
{
	struct tm *p;

	p = localtime(&t);
	if (p == NULL) {
		return -1;
	}

	strftime(m_szyear, 5, "%Y", p);
	strftime(m_szmounth, 3, "%m", p);
	strftime(m_szday, 3, "%d", p);
	strftime(m_szhour, 3, "%H", p);
	strftime(m_szminute, 3, "%M", p);
	strftime(m_szsecond, 3, "%S", p);


	return 0;
}
int LightLoger::log_flush(time_t t)
{
	log_get_save_path(t);
	if (strlen(m_lpszlog_buf) == 0)
	{
		return -1;
	}
	if (check_file_exist(m_log_save_path))
	{
		//m_counter = 1;
		if (make_multidir(m_log_save_path))
		{
			//return -1;
		}
	}
	//log_port_get_time();
	//  strcat(m_log_save_path,m_szday);
	FILE *LogFD;
	//if (check_file_exist(m_log_save_path))
	//{

	//}
	LogFD = fopen(m_log_save_path, "a+");
	if (LogFD == NULL)
	{
		return -1;
	}
	fwrite(m_lpszlog_buf, sizeof(char), strlen(m_lpszlog_buf), LogFD);
	fclose(LogFD);
	m_log_buf_size = 0;
	memset(m_lpszlog_buf, 0x0, LOG_BUF_MAX_SIZE);
	return 0;
}

int LightLoger::log_b(char*str1,char*str2)
{
    log_port_init();
//    int len1=strlen(str1);
//    int len2=strlen(str2);
    //char *addr =(char*)malloc(len1+len2);
    memset(m_lpsz_tmp,0,LOG_BUF_LINE_MAX_SIZE);
    strcat(m_lpsz_tmp,str1);
    strcat(m_lpsz_tmp,str2);
    log_b(m_lpsz_tmp);
    //free(addr);
    return 0;
}
