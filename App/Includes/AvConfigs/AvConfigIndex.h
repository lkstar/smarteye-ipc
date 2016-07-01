/*******************************************************************
|  Copyright(c) 2015-2016 Graceport Technology Development Co.,Ltd
|  All rights reserved.
|
|  版本: 1.0
|  作者: Xman [xman@graceport.cn]
|  日期: 2016年6月6日
|  说明:
|
|  版本: 1.1
|  作者:
|  日期:
|  说明:
******************************************************************/
#ifndef AVWARE_AVCONFIG_CONFIGINDEX_H_
#define AVWARE_AVCONFIG_CONFIGINDEX_H_

//配置表索引，序号不能重复，请不要随意改变。
typedef enum _AvConfigIndex{

	CONF_INDEX					= 0,
	CONF_DEVICE_UART			= 1,

	CONF_NET_SER				= 100,
	CONF_NET_SER_EMAIL			= 101,
	CONF_NET_SER_FTP 			= 102,
	CONF_NET_SER_DDNS 			= 103,
	CONF_NET_SER_UPNP 			= 104,
	CONF_NET_SER_NTP 			= 105,
	CONF_NET_COMM				= 106,

	CONF_USER_MANAGER			= 200,
	CONF_ENCODE_FORMATS			= 300,
	CONF_ENCODE_COVER			= 301,
	CONF_ENCODE_WATERMARKING    = 302,
	CONF_CAPTURE_FORMATS		= 303,
	CONF_IMAGE_FORMATS			= 304,

	CONF_ALARM_IO				= 400,
	CONF_ALARM_MD				= 401,

	CONF_NETPROTOCOL			= 501
}AvConfigIndex;

#endif //AVWARE_AVCONFIG_CONFIGINDEX_H_
