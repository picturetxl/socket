

## SOCKET

### 接口

#### 头文件

```c
#include <sys/types.h>
#include <sys/socket.h>
```
#### API

##### socket
```c
int socket(int domain,int type,int protocol);
```
+ domain
+ AF_UNIX unix域协议
+ type
  + SOCK_STREAM : TCP
  + SOCK_DGRAM : UDP
+ protocol
  + 0



> 常常使用:

```c
int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
```








### Example 1 : 本地客户和本地服务器(一次只能连接一个客户)



