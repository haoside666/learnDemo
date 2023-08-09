#include "./common.h"

void strTopackage(char *buf,package_pt pkg)
{
    sscanf(buf,"dest_ip:%s,dest_port:%hud,content:%s",
        pkg->dest_ip,&pkg->dest_port,pkg->content);
}

void packageTostr(char *buf,package_pt pkg)
{
    sprintf(buf,"dest_ip:%s,dest_port:%d,content:%s",
        pkg->dest_ip,pkg->dest_port,pkg->content);
}

