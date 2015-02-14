#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <sys/time.h>
#define N 5000
//#define MAX_CLIENT 3
#define SERV_PORT 5555
#include "QuizServer.h"
int var;
char group[50][10];
int maxfd=0;
int grp=1;
int ch=0,nq;
fd_set masterfd, fdtemp;
int lfd, cfd, len,n,i,rc,fclient;
struct sockaddr_in saddr, caddr;
char buff2[100];
char tbuff[10];
int port;
void clearall(fd_set masterfd, int maxfd,int fclient);
void displaymessage(char a[],int fclient,int maxfd,fd_set masterfd);
JNIEXPORT void JNICALL Java_quizserver_QuizServer_initializesocket(JNIEnv *env, jobject obj,jint x,jstring IP)
{
	port=x;
        char *ip=(*env)->GetStringUTFChars(env,IP,0);
	memset(group[i], '\0', sizeof(group[i]));
	lfd = socket(AF_INET, SOCK_STREAM, 0);
	saddr.sin_family = AF_INET;
	//saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_addr.s_addr = inet_addr(ip);
	saddr.sin_port = htons(port);
	bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
	listen(lfd, 5);
}
JNIEXPORT jint JNICALL Java_quizserver_QuizServer_makeConnection(JNIEnv *env, jobject obj)
  {
	len = sizeof(caddr);
	cfd= accept(lfd, (struct sockaddr *)&caddr, &len);
	if(cfd< 0)
	{
		printf("\naccept error\n");
		exit(1);
	}
	strcpy(group[cfd],"Group-");
	snprintf(tbuff,sizeof(tbuff),"%d",grp++);
	strcat(group[cfd],tbuff);
	printf("%s %d\n",group[cfd],cfd);
	printf("Req from IP Addr: %s, Port No: %d\n",inet_ntop(AF_INET, &caddr.sin_addr,buff2, sizeof(buff2)),
	ntohs(caddr.sin_port));
	FD_SET(cfd,&masterfd);
	if(cfd > maxfd)
		maxfd = cfd;
  	printf(" from C!\n");
  	return cfd;
  	//return (*env)->NewStringUTF(env,group[cfd]);
  }
JNIEXPORT jstring JNICALL Java_quizserver_QuizServer_buzzerRound(JNIEnv *env, jobject obj, jint fclient, jint maxfd,jint time)
{
	char *buff,*clno;
	int i;
	char temp[20];
   	int rc=0;
   	fd_set fdtemp = masterfd;
        struct timeval timeout;
   	timeout.tv_sec = time;
   	timeout.tv_usec = 0;
   	buff=(char *)malloc(sizeof(char));
   	clno=(char *)malloc(sizeof(char));
	memset(buff, '\0', sizeof(buff));
	if(select(maxfd + 1,&masterfd,NULL, NULL, &timeout)>0)
	for(i =fclient; i <= maxfd; i++)
        {
             if(FD_ISSET(i, &masterfd))
             {
             read(i,buff,sizeof(buff));
             rc=i;
             break;
             }
        }
        printf("RC=%d",rc);
	masterfd=fdtemp;
	FD_SET(rc,&masterfd);
	//Broadcasting the group who answer
        if(rc!=0)
        {
            displaymessage(group[rc],fclient,maxfd,masterfd);
            displaymessage(" gives the answer\n",fclient,maxfd,masterfd);
        }else
            displaymessage("Timeout\n",fclient,maxfd,masterfd);
	//
	printf("Messege from client %c,%d",*buff,rc);
        if(rc!=0)
	strcpy(temp,group[rc]);
        else
            strcat(temp,"No_Group");
	strcat(temp," ");
	snprintf(clno,sizeof(clno),"%d",rc);
	strcat(temp,clno);
	strcat(temp," ");
        if(rc!=0)
	strcat(temp,buff);
        else
            strcat(temp,"nil");
	return (*env)->NewStringUTF(env,temp);	
}
JNIEXPORT jstring JNICALL Java_quizserver_QuizServer_passRound(JNIEnv *env, jobject obj, jint fclient, jint maxfd, jint currc, jint flag,jint time)
{
	char *buff;
   	buff=(char *)malloc(sizeof(char));
   	fd_set fdtemp = masterfd;
   	struct timeval timeout;
        int temp=time;
   	timeout.tv_sec = time;
   	timeout.tv_usec = 0;
	*buff='\0';
        char *t;
        t=(char *)malloc(sizeof(char));
        *t='\0';
        snprintf(t,sizeof(t),"%d",temp);
        //printf("nflnvj-----%s",t);
	clearall(masterfd,maxfd,fclient);
        write(currc,"Time to answer the question is ",35);
        write(currc,t,strlen(t));
        
	if(flag==0)
	{
		displaymessage("\nQuestion Asked To ",fclient,maxfd,masterfd);
	}
	else
		displaymessage("\nQuestion Passed To ",fclient,maxfd,masterfd);
	displaymessage(group[currc],fclient,maxfd,masterfd);
	if(select(maxfd + 1,&masterfd,NULL, NULL,&timeout)>=0)
		if(FD_ISSET(currc, &masterfd))
			read(currc,buff,sizeof(buff));
	masterfd=fdtemp;
	FD_SET(currc,&masterfd);
	masterfd=fdtemp;
	return (*env)->NewStringUTF(env,buff);	
}
JNIEXPORT void JNICALL Java_quizserver_QuizServer_closeAll(JNIEnv *env, jobject obj, jint fclient, jint maxfd)
{
	for(i=fclient;i<=maxfd;i++)
		close(i);
}
JNIEXPORT void JNICALL Java_quizserver_QuizServer_broadcastMessage(JNIEnv *env, jobject obj, jobjectArray msg, jint fclient, jint maxfd)
{
	int i;
	const char *str[5];
	char temp[1024];
	int f=fclient;
	int m=maxfd;
	jsize stringCount = (*env)->GetArrayLength(env,msg);
        for (i=0; i<stringCount; i++) 
        {
                  jstring string = (jstring) (*env)->GetObjectArrayElement(env,msg, i);
                  str[i] = (*env)->GetStringUTFChars(env,string,0);
        }	
	for(i=0;i<stringCount;i++)
	{
	strcpy(temp,str[i]);
	displaymessage(temp,fclient,maxfd,masterfd);
	memset(temp, '\0', sizeof(temp));
	}
	clearall(masterfd,m,f);
	
}
void displaymessage(char a[],int fclient,int maxfd,fd_set masterfd)
{
	int i;
	fd_set fdtemp = masterfd;
	if(select(maxfd + 1,NULL,&masterfd, NULL, NULL)>=0)
	for(i=fclient;i<=maxfd;i++)
	{
		write(i,a,strlen(a));
		write(i,"\n",1);
	}
	masterfd=fdtemp;
}
void clearall(fd_set masterfd, int maxfd,int fclient)
{
	char buff[20];
	int i;
	struct timeval timeout;
   	timeout.tv_sec = 0;
   	timeout.tv_usec = 0;
	printf("Clients Cleared\n");
	memset(buff, '\0', sizeof(buff));
	fd_set fdtemp = masterfd;
	if(select(maxfd + 1,&masterfd,NULL, NULL,&timeout)>=0)
	{
	for(i =fclient; i <= maxfd; i++)
		     if(FD_ISSET(i, &masterfd))
				read(i, buff,20);
	}
	masterfd=fdtemp;
}
