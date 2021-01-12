#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string.h>

#define DEVICE "/dev/ttyAMA0"
#define S_TIMEOUT 1

int dev_fd = 0;

int uart_init(void)
{
    //dev_fd = open("/dev/ttyAMA0",O_RDWR | O_NOCTTY | O_NDELAY);
    dev_fd = open(DEVICE,O_RDWR | O_NOCTTY | O_NDELAY);
    if ( dev_fd< 0)
    {
      perror("open"); //這幹嘛的不知道欸
      return -1;
    }

    struct termios options;
 
    
    //tcgetattr 可得到open返回值 fd
    tcgetattr( dev_fd , &options);

    //開始設定參數
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~CSIZE;
    options.c_cflag &= ~CRTSCTS; 
    options.c_cflag |= CS8;
    options.c_cflag &= ~CSTOPB;
    options.c_iflag |= ~IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    cfsetospeed(&options, B115200);
    
    //TCSANOW 設定參數生效
    tcflush( dev_fd, TCIFLUSH); //overflow data可接收但不讀
    tcsetattr( dev_fd, TCSANOW, &options);
    
    return 0;
}


unsigned int send_total_count =0 ;
int uart_send( int fd , char *data , int datalen)
{
    int len;
    len = write(fd, data , datalen);
    if(len == datalen)
    {
      send_total_count = send_total_count + len;
      printf("send total char = %d\n",send_total_count);
    }else
    {
      tcflush( fd, TCOFLUSH); //寫入data更新 但不傳送
      return -1;
    }
    return 0;
}

unsigned int recv_total_count = 0;
int uart_recv( int fd , char *data, int datalen)
{
    int len = 0;
    int ret = 0;
    fd_set fs_read;
    struct timeval tv_timeout;
    FD_ZERO( &fs_read);
    FD_SET( fd, &fs_read);
#ifdef S_TIMEOUT
    tv_timeout.tv_sec = (10*20/115200+2);
    tv_timeout.tv_usec = 0;
    ret = select( fd+1, &fs_read, NULL, NULL, NULL);
#elif
    ret = select( fd+1, &fs_read, NULL, NULL, NULL);
#endif

    if(FD_ISSET( fd, &fs_read))
    {
       len = read( fd, data, datalen);
       recv_total_count = recv_total_count +1 ;
       printf("reciver data count = %d\n", recv_total_count);
       return len;
    }else
    {
       perror("select");
       return -1;
    }
    return 0;
}

int main( int argc, char **argv)
{
    uart_init();
    char sendbuf[50];
   // char sendbuf[50]="lanpa 覽";   
    char a,ch;
    int i=0;
  
   /* FILE *in = fopen("v.txt","r");
    while(EOF != (a=fgetc(in)))
    {          
      sendbuf[i] = a;
      i++;
    }
    */
    char recvbuf[1024];
    memset( recvbuf,0,sizeof(char)*1024);

    while(1)
    { 
       i=0;
       while((ch=getchar()) != '\n')
       {
         sendbuf[i] = ch;
         i++;
       }
      uart_send ( dev_fd, sendbuf ,1024);
      memset(sendbuf,0,sizeof(char)*1024);
      printf("\n");
      
      uart_recv( dev_fd, recvbuf, 1024);
      printf("reiver : %s\n", recvbuf);
       memset( recvbuf, 0, sizeof(char)*1024);
    }
    //fclose(in);
    close( dev_fd);
    return 0;
}
