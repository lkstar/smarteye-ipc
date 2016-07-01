/******************************************************************* 
 |  Copyright(c) 2015-2016 Graceport Technology Development Co.,Ltd
 |  All rights reserved. 
 |
 |  版本: 1.0 
 |  作者: Knight [knight@graceport.cn]
 |  日期: 2016年6月6日
 |  说明: 
 |   
 |  版本: 1.1 
 |  作者: 
 |  日期: 
 |  说明: 
 ******************************************************************/
#ifndef _AVWARETYPE_H_
#define _AVWARETYPE_H_


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <fcntl.h>
#if defined(__cplusplus)
#include <map>
#include <list>
#include <queue>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#if defined (WIN32)
#include <io.h>
#include <WS2tcpip.h>
#elif defined (__GNUC__)
#include "sys/prctl.h"
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <dirent.h>
#include <sys/socket.h>
#include <sys/reboot.h>
#include <sys/uio.h>
#include <netdb.h>
#else

#endif

#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifdef SHARE_EXPORTS

#if defined (WIN32)

#if defined (USE_STATIC_LIB)
#define AVWARE_API
#else
#define AVWARE_API __declspec(dllexport)
#endif

#else //else define win32
#define AVWARE_API __attribute__((visibility("default")))
#endif //end define win32

#else //else PROTOSHARE_EXPORTS

#if defined(WIN32)
#if defined (USE_STATIC_LIB)
#define AVWARE_API
#else
#define AVWARE_API __declspec(dllimport)
#endif

#else
#define AVWARE_API
#endif

#endif //end PROTOSHARE_EXPORTS

#if defined(WIN32)
#define socklen_t int
#else
#define INVALID_SOCKET -1
#endif


typedef int					av_32,		av_sint, av_int;
typedef unsigned int		av_u32,		av_uint;
typedef short				av_16,		av_sshort, av_short;
typedef unsigned short		av_u16,		av_ushort;
typedef double				av_double;
typedef float				av_float;
typedef char				av_char;
typedef unsigned char		av_uchar;
typedef void				av_void;
typedef long				av_long;
#ifdef WIN32
typedef __int64                 av_64,	av_slonglong;
typedef unsigned __int64        av_u64, av_ulonglong;
#elif defined(__GNUC__)
typedef long long               av_64,	av_slonglong;
typedef unsigned long long      av_u64, av_ulonglong;
#elif defined(__TCS__)
typedef signed   long long int  av_64,	av_slonglong;
typedef unsigned long long int  av_u64, av_ulonglong;
#endif


//////////////////////////////////////////////////////////////////////////
//##配置表默认信息
#ifndef ConfMaxCaptureChn
#define ConfMaxCaptureChn		1
#endif

#ifndef ConfMaxSerial
#define ConfMaxSerial			4
#endif

#ifndef ConfMaxCover
#define ConfMaxCover			4
#endif

#ifndef ConfMaxWaterMarking
#define ConfMaxWaterMarking		2
#endif

#ifndef ConfMaxNetComm
#define ConfMaxNetComm			5
#endif

#ifndef ConfMaxIoAlarmIn
#define ConfMaxIoAlarmIn		1
#endif

#ifndef ConfMaxDecodeChn
#define ConfMaxDecodeChn		32
#endif

#ifndef ConfMaxUser
#define ConfMaxUser 10
#endif

//////////////////////////////////////////////////////////////////////////

//四舍五入 取倍数
#define MultipleRound(target,multiple) (target) = ((((target)+(multiple)/2)/(multiple))*multiple)
//取最大的的倍数
#define MultipleMax(target,multiple) (target) = ((((target)+(multiple - 1))/(multiple))*multiple)
//取最小的倍数
#define MultipleMin(target,multiple) (target) = (((target)/(multiple))*(multiple))


#define AppRunMSec() (long)(clock()*(1000.0/CLOCKS_PER_SEC))

#if defined(WIN32)

#if _MSC_VER < 1400
	#ifndef snprintf
	#define snprintf _snprintf
	#endif
#else
	#ifndef snprintf
	#define snprintf sprintf_s
	#endif
#endif

#ifndef inline
#define inline __inline
#endif

#ifndef strcasecmp
#define strcasecmp _stricmp
#endif

#ifndef strncasecmp
#define strncasecmp _strnicmp
#endif
#else
#define sprintf_s sprintf
#endif

typedef enum{
	av_false = 0,
	av_true,
}av_bool;
static const char sAvBoolStrings[][10] = { "av_true", "av_false" };
#define GetAvBoolString(b) sAvBoolStrings[b]

typedef struct{
	char *base;
	int   len;
	int   size;
}av_buf;


typedef void av_mutex;
typedef void av_sem;
typedef void av_cond;


#if defined(WIN32)
#include <pthread.h>
typedef pthread_t av_thread_t;
#else
typedef pthread_t av_thread_t;
#endif


typedef union {
	av_uchar c[4];
	av_u32   u;
}av_addr;

//avWare func for bsp call
extern av_void *AvMemoryPoolMalloc(size_t size);
extern av_void *AvMemoryPoolRealloc(av_void *ptr, size_t size);
extern av_void  AvMemoryPoolFree(av_void *ptr);


#ifdef HAVE_MemPool
#define AvMalloc AvMemoryPoolMalloc
#define AvFree AvMemoryPoolFree
#define AvRealloc AvMemoryPoolRealloc
#else
#define AvMalloc malloc
#define AvFree free
#define AvRealloc realloc
#endif



#define AvMask(x) (0x01 << (x))

#define av_findMaxMask(result, SupportMask, type) \
	do \
	{\
		for(int i = 31; i >= 0; i--){\
			if (AvMask(i) & (SupportMask)){\
				(result) = (type)(i);\
				break;\
			}\
		}\
	} while (0)

#define av_findMinMask(result, SupportMask, type) \
	do\
	{\
		for(int i = 0; i < 32; i++){\
			if (AvMask(i) & (SupportMask)){\
				(result) = (type)i;\
				break;\
			}\
		}\
	} while (0)


#if 0
#define AvAddr2NetAddr(x) htonl((x))
#define AvAddr2StrAddr(src, dest) do \
{\
	sprintf(dest, "%d.%d.%d.%d", src.c[0], src.c[1], src.c[2], src.c[3]);\
} while (0)


#define StrAddr2AvAddr(src, dest) do \
{\
	int addr[4];\
	sscanf(src, "%d.%d.%d.%d", &addr[0], &addr[1], &addr[2], &addr[3]); \
	dest.c[0] = addr[0];dest.c[1] = addr[1]; dest.c[2] = addr[2];dest.c[3] = addr[3];\
} while (0)
#define StrAddr2AvAddr_s(src, dest)do\
{\
	if (NULL != src){\
		int addr[4];\
		sscanf(src, "%d.%d.%d.%d", &addr[0], &addr[1], &addr[2], &addr[3]); \
		dest.c[0] = addr[0];dest.c[1] = addr[1]; dest.c[2] = addr[2];dest.c[3] = addr[3];\
	}\
}while (0)
#endif




#define AvStrSplice(h,t) (#h##t)
#if defined(WIN32)
#define AvConfigFile(f) "./configs/"##f
#else
#define AvConfigFile(f) f
#endif


#if defined(WIN32)
#pragma warning(disable:32)
#pragma warning(disable:34)
#pragma warning(disable:36)
#endif



#define D_StreamSync_Code 0x06010000

#pragma pack(4)
typedef struct {
	av_u32			sync;
	av_u32			index;

	av_u64			pts;

	av_u16			SizeHight;
	av_u16			SizeWidth;

	av_uchar		Channel;
	av_uchar		Slave;
	av_uchar		Comp;
	av_uchar		FrameType;

	av_u32			Length;

	av_uchar		FrameRate;
	av_uchar		res[3];
}C_FormatStreamHead;
#pragma pack()

#if defined(WIN32)
int FormatStreamHeadSize();
int  FormatStreamHead(int Channel, int Slave, unsigned int comp/*av_comp_t*/, unsigned int freamt,/*av_frame_type*/
	int FrameRate, int ImageWidth, int ImageHeigh,
	av_u64 pts, av_u32 playloadLength, char *data);
#else
inline  int FormatStreamHeadSize();
inline int  FormatStreamHead(int Channel, int Slave, unsigned int comp/*av_comp_t*/, unsigned int freamt,/*av_frame_type*/
	int FrameRate, int ImageWidth, int ImageHeigh,
	av_u64 pts, av_u32 playloadLength, char *data);
#endif


#if defined(WIN32)
#include   <windows.h>
#ifndef PATH_HR
#define PATH_HR '\\'
#endif
#define av_warning(fmt,...) do {printf("[%s][%d]=>", NULL == strrchr(__FILE__, PATH_HR)? __FILE__:(char *)(strrchr(__FILE__, PATH_HR) + 1), __LINE__);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);printf(fmt, ##__VA_ARGS__); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);}while(0)
#define av_error(fmt,...) do {printf("[%s][%d]=>", NULL == strrchr(__FILE__, PATH_HR)? __FILE__:(char *)(strrchr(__FILE__, PATH_HR) + 1), __LINE__);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);printf(fmt, ##__VA_ARGS__); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);}while(0)
#define av_msg(fmt,...) do {printf("[%s][%d]=>", NULL == strrchr(__FILE__, PATH_HR)? __FILE__:(char *)(strrchr(__FILE__, PATH_HR) + 1), __LINE__);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); printf(fmt, ##__VA_ARGS__); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);}while(0)

#else
#define PATH_HR '/'
#define av_warning(fmt,...) printf("[%s][%d]=>\033[1;33m" fmt "\033[m", NULL == strrchr(__FILE__, PATH_HR)? __FILE__:(char *)(strrchr(__FILE__, PATH_HR) + 1), __LINE__,##__VA_ARGS__)
#define av_error(fmt,...) printf("[%s][%d]=>\033[0;32;31m" fmt "\033[m", NULL == strrchr(__FILE__, PATH_HR)? __FILE__:(char *)(strrchr(__FILE__, PATH_HR) + 1), __LINE__,##__VA_ARGS__)
#define av_msg(fmt,...) printf("[%s][%d]=>\033[1;32m" fmt "\033[m", NULL == strrchr(__FILE__, PATH_HR)? __FILE__:(char *)(strrchr(__FILE__, PATH_HR) + 1), __LINE__,##__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif

