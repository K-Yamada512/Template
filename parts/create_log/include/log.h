/*****************************************************************************/
/*
*	filename:log.h
*	about:
*		C code template headerfile
*
*	attention:
*
*	history:
*		2024/11/03:K.Yamada :create this file
*/
/*****************************************************************************/
#ifndef _INCLUDE_LOG_H_
#define _INCLUDE_LOG_H_

/*****************************************************************************/
/*                         include headerfile                                */
/*****************************************************************************/
/*standard library*/
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

/*****************************************************************************/
/*                               define macro                                */
/*****************************************************************************/
/*const*/
#define LOG_LEVEL 5
#define F_LOG_LEVEL 9
#define LOG_FILE_NAME     "log/syslog.log"        /* ログディレクトリ(通常)  */
#define LOG_FILE_MAX_SIZE 1000							/*[MB]*/

/* macro */
#define EMERGMSG(...) MSG("EMERG ",0,__VA_ARGS__)		/*0:システムの利用が不可能*/
#define FATALMSG(...) MSG("FATAL ",1,__VA_ARGS__)		/*1:致命的なエラー(プログラムの異常終了)*/
#define ALERTMSG(...) MSG("ALERT ",2,__VA_ARGS__)		/*2:何らかの対処が必要(アプリケーションがダウン)*/
#define CRITMSG(...) MSG("CRIT  ",3,__VA_ARGS__)		/*3:危機的な状態(予期しない例外)*/
#define ERRORMSG(...) MSG("ERROR ",4,__VA_ARGS__)		/*4:直ちに対処する必要のない実行時エラー*/
#define WARNMSG(...) MSG("WARN  ",5,__VA_ARGS__)		/*5:エラーではないが例外的なもの*/
#define NOTICEMSG(...) MSG("NOTICE",6,__VA_ARGS__)	    /*6:正常だが、重要なもの*/
#define INFOMSG(...) MSG("INFO  ",7,__VA_ARGS__)		/*7:関心を寄せておきたいもの*/
#define DEBUGMSG(...) MSG("DEBUG ",8,__VA_ARGS__)		/*8:開発中のデバッグ情報*/
#define TRACEMSG(...) MSG("TRACE ",9,__VA_ARGS__)		/*9:詳細な情報*/

#define _LOG(msg) "%s [%s] %s %d: %s() - "msg"\r\n"
#define _FMT __FILE__,__LINE__,__func__

/*macro overloading (引数の違いによって同名の関数を呼ぶときに動作を変える)*/
#define MSG(...) _MSG(__VA_ARGS__,_MSG4,_MSG3,_MSG2,_MSG1,_MSG0)(__VA_ARGS__)
#define _MSG(_1,_2,_3,_4,_5,_6,_7,name,...) name
#define _MSG0(lv,index,msg) do { \
    if (LOG_LEVEL >= index) { \
        fprintf(stderr,_LOG(msg),LOG_TIME(),lv,_FMT); \
    } \
    if (F_LOG_LEVEL >= index) { \
		setup_write_log(LOG_FILE_NAME); \
		fp = fopen(LOG_FILE_NAME, "a"); \
        fprintf(fp,_LOG(msg),LOG_TIME(),lv,_FMT); \
		fclose(fp); \
		setup_write_log(LOG_FILE_NAME); \
    } \
} while (0)
#define _MSG1(lv,index,msg,...) do { \
    if (LOG_LEVEL >= index) { \
        fprintf(stderr,_LOG(msg),LOG_TIME(),lv,_FMT,__VA_ARGS__); \
    } \
    if (F_LOG_LEVEL >= index) { \
		setup_write_log(LOG_FILE_NAME); \
		fp = fopen(LOG_FILE_NAME, "a"); \
        fprintf(fp,_LOG(msg),LOG_TIME(),lv,_FMT,__VA_ARGS__); \
		fclose(fp); \
		setup_write_log(LOG_FILE_NAME); \
    } \
} while (0)
#define _MSG2(lv,index,msg,...) do { \
    if (LOG_LEVEL >= index) { \
        fprintf(stderr,_LOG(msg),LOG_TIME(),lv,_FMT,__VA_ARGS__); \
    } \
    if (F_LOG_LEVEL >= index) { \
		setup_write_log(LOG_FILE_NAME); \
		fp = fopen(LOG_FILE_NAME, "a"); \
        fprintf(fp,_LOG(msg),LOG_TIME(),lv,_FMT,__VA_ARGS__); \
		fclose(fp); \
		setup_write_log(LOG_FILE_NAME); \
    } \
} while (0)
#define _MSG3(lv,index,msg,...) do { \
    if (LOG_LEVEL >= index) { \
        fprintf(stderr,_LOG(msg),LOG_TIME(),lv,_FMT,__VA_ARGS__); \
    } \
    if (F_LOG_LEVEL >= index) { \
		setup_write_log(LOG_FILE_NAME); \
		fp = fopen(LOG_FILE_NAME, "a"); \
        fprintf(fp,_LOG(msg),LOG_TIME(),lv,_FMT,__VA_ARGS__); \
		fclose(fp); \
		setup_write_log(LOG_FILE_NAME); \
    } \
} while (0)
#define _MSG4(lv,index,msg,...) do { \
    if (LOG_LEVEL >= index) { \
        fprintf(stderr,_LOG(msg),LOG_TIME(),lv,_FMT,__VA_ARGS__); \
    } \
    if (F_LOG_LEVEL >= index) { \
		setup_write_log(LOG_FILE_NAME); \
		fp = fopen(LOG_FILE_NAME, "a"); \
        fprintf(fp,_LOG(msg),LOG_TIME(),lv,_FMT,__VA_ARGS__); \
		fclose(fp); \
		setup_write_log(LOG_FILE_NAME); \
    } \
} while (0)

/*****************************************************************************/
/*                         define variable (global)                          */
/*****************************************************************************/
static FILE *fp;

/*****************************************************************************/
/*                         define structure (global)                         */
/*****************************************************************************/
/*none*/

/*****************************************************************************/
/*                                 define function                           */
/*****************************************************************************/
char* LOG_TIME();
int setup_write_log(const char *filename);
long get_file_size(const char *filename);
void remove_first_line(const char *filename);
int test_function(void);

#endif /*_INCLUDE_LOG_H_*/
