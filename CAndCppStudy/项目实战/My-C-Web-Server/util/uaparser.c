#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "uap.h"
#include "regexes.yaml.h"


static int getmonth(struct tm* local)   // return month index ,eg. Oct->10
{
	char buf[8];
	int i;
	static char *months[]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

	strftime(buf,127,"%b",local);
	for(i=0;i<12;++i)
	{
		if(!strcmp(buf,months[i]))
			return i+1;
	}
	return 0;
}

void writetime(FILE* fp)
{
	time_t timeval;
	char other[24];
	char year[8];
	char together[64];
	int month;

	(void)time(&timeval);
	struct tm *local=localtime(&timeval);

/* get year */
	strftime(year,7,"%Y",local);
/*get month */
	month=getmonth(local);
/*get other */
	strftime(other,23,"%d %H:%M:%S",local);
/*together all */
	sprintf(together,"%s/%d/%s\r\n",year,month,other);
	fwrite(together,strlen(together),1,fp);
}


void save_uac(char *buf,char* cwd)
{
      FILE *fp = fopen(strcat(cwd,"/uac.txt"),"a+");  
      writetime(fp);
      fputs(buf,fp);  
      fclose(fp);  
}
int main() {
	char *buf,*cwd,info[4096];
	buf = getenv("UAC_AGENT");
    cwd=getenv("CURRENT_PATH");
    //creat obj 
	struct uap_parser *ua_parser = uap_parser_create();
	struct uap_useragent_info *ua_info = uap_useragent_info_create();
    //set obj 
	uap_parser_read_buffer(ua_parser, ___uap_core_regexes_yaml, ___uap_core_regexes_yaml_len);
    
	if (uap_parser_parse_string(ua_parser, ua_info, buf)) {
		memset(info,0,sizeof(info));
		sprintf(info," user_agent.family\t%s\n",     ua_info->user_agent.family);
		sprintf(info,"%s user_agent.major\t%s\n",   info,ua_info->user_agent.major);
		sprintf(info,"%s user_agent.minor\t%s\n",   info,ua_info->user_agent.minor);
		sprintf(info,"%s user_agent.patch\t%s\n",   info,ua_info->user_agent.patch);
		sprintf(info,"%s os.family\t%s\n",          info,ua_info->os.family);
		sprintf(info,"%s os.major\t%s\n",           info,ua_info->os.major);
		sprintf(info,"%s os.minor\t%s\n",           info,ua_info->os.minor);
		sprintf(info,"%s os.patch\t%s\n",           info,ua_info->os.patch);
		sprintf(info,"%s os.patchMinor\t%s\n",      info,ua_info->os.patch);
		sprintf(info,"%s device.family\t%s\n",      info,ua_info->device.family);
		sprintf(info,"%s device.brand\t%s\n",       info,ua_info->device.brand);
		sprintf(info,"%s device.model\t%s\n",       info,ua_info->device.model);
		sprintf(info,"%s ********************************\n\n",       info);
		save_uac(info,cwd);
	}

	uap_parser_destroy(ua_parser);
	uap_useragent_info_destroy(ua_info);

	return 0;
}
