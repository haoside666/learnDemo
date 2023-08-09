#ifndef __COMMON__
#define __COMMON__

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <stdint.h>
#include <fcntl.h>
#define _PATH_ "/"
#define _PROJ_ID_ 0x6666
#define _SIZE_ 8192
#define OPEN_MAX 1024
#define MAXBUF 4096

#define MSG_QUEUE_TYPE 1
#define GENERAL_TYPE 2

#define BASH_TYPE 1
#define FILE_UPLOAD_TYPE 2
#define FILE_DOWNLOAD_TYPE 3
#define BASH_REPLY_TYPE 4
#define FILE_UPLOAD_REPLY_TYPE 5
#define FILE_DOWNLOAD_REPLY_TYPE 6

struct msgbuf
{
    long mtype;
    char mtext[MAXBUF];
};

struct msg
{
    long type;
    union
    {
        struct msgbuf mymsgbuf;
        char message[MAXBUF];
    }content;
};

#define __AES__

#ifdef __AES__
#define BLOCKSIZE 16  //AES-128分组长度为16字节
// uint8_t y[4] -> uint32_t x
#define LOAD32H(x, y) \
  do { (x) = ((uint32_t)((y)[0] & 0xff)<<24) | ((uint32_t)((y)[1] & 0xff)<<16) | \
             ((uint32_t)((y)[2] & 0xff)<<8)  | ((uint32_t)((y)[3] & 0xff));} while(0)

// uint32_t x -> uint8_t y[4]
#define STORE32H(x, y) \
  do { (y)[0] = (uint8_t)(((x)>>24) & 0xff); (y)[1] = (uint8_t)(((x)>>16) & 0xff);   \
       (y)[2] = (uint8_t)(((x)>>8) & 0xff); (y)[3] = (uint8_t)((x) & 0xff); } while(0)

// 从uint32_t x中提取从低位开始的第n个字节
#define BYTE(x, n) (((x) >> (8 * (n))) & 0xff)

/* used for keyExpansion */
// 字节替换然后循环左移1位
#define MIX(x) (((S[BYTE(x, 2)] << 24) & 0xff000000) ^ ((S[BYTE(x, 1)] << 16) & 0xff0000) ^ \
                ((S[BYTE(x, 0)] << 8) & 0xff00) ^ (S[BYTE(x, 3)] & 0xff))

// uint32_t x循环左移n位
#define ROF32(x, n)  (((x) << (n)) | ((x) >> (32-(n))))
// uint32_t x循环右移n位
#define ROR32(x, n)  (((x) >> (n)) | ((x) << (32-(n))))

typedef struct{
    uint32_t eK[44], dK[44];    // encKey, decKey
    int Nr; // 10 rounds
}AesKey;

/* for 128-bit blocks, Rijndael never uses more than 10 rcon values */
// AES-128轮常量
#define KEY_LEN 16
#endif

static int com_creat_queue(int flags);
extern int creat_queue();
extern int get_queue();
extern int send_msg(int msgqueue_id,int who,char *msg);
extern int recv_msg(int msgqueue_id,int want,char out[],int out_len);
extern int delete_queue(int msgqueue_id);
extern ssize_t Writen(int fd, const void *vptr, size_t n);
extern ssize_t Readn(int fd, void *vptr, size_t n);
extern int setNonBlocking(int sock);
extern int setBlocking(int sock);
extern int FilePathParse(const char *sFilePath, char *sDir, char *sFileName);
#ifdef __AES__
static int loadStateArray(uint8_t (*state)[4], const uint8_t *in) ;
static int storeStateArray(uint8_t (*state)[4], uint8_t *out) ;
static int keyExpansion(const uint8_t *key, uint32_t keyLen, AesKey *aesKey) ;
static int addRoundKey(uint8_t (*state)[4], const uint32_t *key) ;
static int subBytes(uint8_t (*state)[4]);
static int invSubBytes(uint8_t (*state)[4]);
static int shiftRows(uint8_t (*state)[4]) ;
static int invShiftRows(uint8_t (*state)[4]);
static uint8_t GMul(uint8_t u, uint8_t v) ;
static int mixColumns(uint8_t (*state)[4]);
static int invMixColumns(uint8_t (*state)[4]) ;
static int aesEncrypt(const uint8_t *key, uint32_t keyLen, const uint8_t *pt, uint8_t *ct, uint32_t len);
static int aesDecrypt(const uint8_t *key, uint32_t keyLen, const uint8_t *ct, uint8_t *pt, uint32_t len);
extern void encryption(char *p_buf,char *c_buf);
extern void decode(char *p_buf,char *c_buf);
#endif

#endif
