#include "stdlib.h"
#include "stdio.h"
#include "./cJSON.h"
 
#define FIELD_TYPE_DOUBLE	0 //DOUBLE有符号整形
#define FIELD_TYPE_DOUBLE_U	1 //DOUBLE无符号整形
#define FIELD_TYPE_FLOAT	2 //FLOAT有符号整形
#define FIELD_TYPE_FLOAT_U	3 //FLOAT无符号整形
#define FIELD_TYPE_INT		4 //有符号整形(4字节)
#define FIELD_TYPE_INT_U	5 //无符号整形(4字节)
#define FIELD_TYPE_SHORT	6 //有符号短整形(2字节)
#define FIELD_TYPE_SHORT_U	7 //无符号短整形(2字节)
#define FIELD_TYPE_CHAR		8 //有符号字符(2字节)
#define FIELD_TYPE_CHAR_U	9 //无符号字符(2字节)
#define FIELD_TYPE_STRING	10 //字符串
#define FTILD_TYPE_TIME		11 //时间
 
//描述：js格式解析，只处理一层的js格式
struct TJS{
	char *Field;  //客户定义的字段
	int FieldType; //字段的格式类型，如整形，字符串
	cJSON *pJON; //json解析之后的字符串数据，实际使用时需将字符串转化成对应字段Field的数据
};
 
//根据客户定义的js字段填充如下结构体
struct TJS g_TJsCfg[] = {
	{"startTime", FTILD_TYPE_TIME},
	{"endTime", FTILD_TYPE_TIME},
	{"UUID", FIELD_TYPE_STRING},
	{"subDeviceID", FTILD_TYPE_TIME},
	{"UserType", FIELD_TYPE_INT},
	{"CredenceType", FIELD_TYPE_INT},
	{"credenceNo", FIELD_TYPE_STRING},
	{"userName", FIELD_TYPE_STRING},
	{"userID", FIELD_TYPE_STRING},
	{"opTime", FTILD_TYPE_TIME},
	{"placeNo", FIELD_TYPE_STRING},
	{"placeLockNo", FIELD_TYPE_STRING},
};
 
int g_iJsCfgNum = sizeof(g_TJsCfg)/sizeof(g_TJsCfg[0]);
 
//描述：以下根据具体的需求提取数据，这里只是纯粹的用于验证JSON解析的数据是否正确
void printf_js(cJSON *pJSON, int FieldType)
{
	switch(FieldType)
	{
	case FIELD_TYPE_DOUBLE:
	case FIELD_TYPE_DOUBLE_U:	
		printf("Name: %s, Data:%s\n", pJSON->string, pJSON->valuestring);
		break;
	case FIELD_TYPE_FLOAT:
		break;
	case FIELD_TYPE_FLOAT_U:
		break;
	case FIELD_TYPE_INT:
	case FIELD_TYPE_INT_U:
		printf("Name: %s, Data:%s\n", pJSON->string, pJSON->valuestring);
		break;
	case FIELD_TYPE_SHORT:
		break;
	case FIELD_TYPE_SHORT_U:
		break;
	case FIELD_TYPE_CHAR:
		break;
	case FIELD_TYPE_CHAR_U:
		break;
	case FIELD_TYPE_STRING:
	case FTILD_TYPE_TIME:
		printf("Name: %s, Data:%s\n", pJSON->string, pJSON->valuestring);
		break;
	default:
		printf("Unsupport fmt:%d\n", FieldType);
	}
}
 
void parse_js(void)
{
	//假设接收到客户的js字段数据为
	char *pRevJson = "{\"startTime\":\"2017-11-10 08:00:01\",\
		\"endTime\":\"2020-11-10 08:00:01\",\
		\"UUID\":\"ca23bc4456de223de11a3a7a8ac1d2e3\",\
		\"subDeviceID\":\"2020-11-10 08:00:01\",\
		\"UserType\":\"1\",\
		\"CredenceType\":\"5\",\
		\"credenceNo\":\"粤A123456\",\
		\"userName\":\"张三\",\
		\"userID\":\"1002\",\
		\"opTime\":\"2017-11-10 08:00:01\",\
		\"placeNo\":\"CA12001\",\
		\"placeLockNo\":\"1234566\"\
	}";
	
	int idx;
 
	
	//1. 初始化接收到的客户端json数据
	cJSON *root = cJSON_Parse(pRevJson); 
	if(!root) {
		printf("get root faild !\n");
		return;
	}
	//2. 解析客户的数据
	for (idx=0; idx<g_iJsCfgNum; idx++)
		g_TJsCfg[idx].pJON = cJSON_GetObjectItem(root, g_TJsCfg[idx].Field);
	
	//3. 提取客户的数据
	for (idx=0; idx<g_iJsCfgNum; idx++)
	{
		if (g_TJsCfg[idx].pJON)
			printf_js(g_TJsCfg[idx].pJON, g_TJsCfg[idx].FieldType);
		else
			printf("Name:%s, No data!\n", g_TJsCfg[idx].pJON->string);
	}
	
	//4. 释放内存，防止内存泄露！！！
	if (root)
		cJSON_Delete(root);
}
 
int main(int argc, char **argv)
{
	parse_js();
	
	return 0;

}