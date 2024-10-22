## Socket address structure
```C
struct sockaddr_in{
    // sin_family + sin_port + sin_addr + sin_zero[8] (padding)
};
typedef struct sockaddr {
    uint16_t sa_family;
    char sa_data[14];
} SA;
```
- 어떤 종류의 소켓 구조체라도 받을 수 있도록 SA로 casting하여 사용

## `socket()`
```C
#include <sys/types.h>
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
// return socket descripter, -1 on error

// socket file descripter client_fd
client_fd = Socket(AF_INET, SOCK_STREAM, 0);
// AF_INET: 32bit IP address(IPv4)
```
- socket 매개변수를 자동으로 생성하기 위해 `getaddrInfo` 함수 사용

## `connect()`
- client에서 호출, 서버로 연결 요청
```C
#include <sys/socket.h>

int connect(int clientfd, const struct sockaddr *addr, socklen_t addrlen);
// return 0, -1 on error
```
- connect function 호출 성공시 client file은 client와 server의 socket address pair로 구성됨
- `getaddrinfo` 함수를 사용하여 connect 함수에 parameter 제공

## `bind()`
```C
#include <sys/socket.h>

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
// return 0, -1 on error
```
- server에서 커널에 addr에 있는 서버 소켓 주소를 소켓 식별자 sockfd와 연결 요청
- `getaddrinfo`

## `listen()`
```C
#include <sys/socket.h>

int listen(int sockfd, int backlog);
// return 0, -1 on error
```
- server에서 sockfd를 듣기 소켓으로 전환하기 위해 사용
- blocking X

## `accept()`
```C
#include <sys/socket.h>

int accept(int listenfd, struct sockaddr *addr, int *addrlen);
// return connected file descripter, -1 on error
```
- client 연결 요청이 듣기 소켓에 도착하기를 기다림
- 도착시 addr에 client socket address 저장, return connect socket file descripter(연결 소켓) → **listen socket file descripter와 다름**
- blocking function, 하지만 socket을 unblocking socket으로 생성 가능

### listen socket과 connect socket의 분리
: listen socket 여러개 생성 후 connect에 성공할 떄마다 새 프로세스 혹은 스레드 생성으로 동시성 서버 구성

## `getaddrinfo()`
- host name, address, service name, port number의 string 표현을 socket addr structure로 변환
```C
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int getaddrinfo(const char *host, const char *service, const struct addrinfo *hints, struct addinfo **result);
// return 0, non zero error code on error

void freeaddrinfo(struct addrinfo *result);
const char *gai_strerror(int errcode);
// return error message
```
- host: 변환할 호스트 이름 or IP address
- service: 변환할 서비스 이름 또는 포트번호
- hints: 함수의 동작을 제어하는 addrinfo struct에 대한 포인터, NULL은 기본값 → ai_family, ai_socktype, ai_protocol, ai_flags만 사용 가능
- result: 검색 결과를 저장할 addrinfo 구조체의 list → 여러 IP, 프로토콜 경우의 수가 있을 수 있어서 / 최대 3개

- host와 service(port 번호)가 주어지면 대응되는 소켓 주소체를 가리키는 addrinfo structure의 linked list result를 return
- 클라이언트는 이후 list를 순회하며 각 소켓 주소들에 대해 connect가 성공할 때까지 차례로 시험
- 서버는 이후 list를 순회하며 각 소켓 주소들에 대해 bind가 성공할 때까지 차례로 시험
- 0이 아닌 에러코드 리턴시 `gai_strerror` 함수를 호출하여 에러메시지 확인
- 최종적으로 freeaddrinfo를 호출하여 리스트 반환

## `getnameinfo()`
- `getaddrinfo()`의 역 (소켓 주소 → 호스트와 서비스 이름 string)
```C
#include <sys/socket.h>
#include <netdb.h>

int getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host, size_t hostlen, char *service, size_t servlen, int flags);
// return 0, non zero error code on error
```
- sa: salen 바이트의 소켓 주소 구조체
- host: hostlen 바이트 길이 버퍼
- service: servlen 바이트의 버퍼

## example) hostinfo.c
```C
int main(argc, char **argv) {
    struct addrinfo *p, *listp, hints;
    char buf[MAXLINE];
    int rc, flags;

    if(argc != 2) {
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        exit(0);
    }

    // Get a list of addrinfo records
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;  // IPv4
    hints.ai_socktype = SOCK_STREAM;  // Connections only
    if((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        exit(1);
    }

    // Walk the list and display each IP address
    flags = NI_NUMERICHOST;  // Display address string instead of domain name
    for(p = listp; p; p = p->ai_next) {
        Getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
        printf("%s\n", buf);
    }

    // Clean up
    Freeaddrinfo(listp);
    exit(0);
}
```
: 도메인 이름과 연관된 IP 주소로의 매핑을 출력
- NI_NUMERICHOST flag 세팅시 숫자주소 스트링을 return
- NI_NUMERICSERV flag 세팅시 포트번호 대신 서비스 이름 리턴(서비스 이름 탐색과정(/etc/services) 생략)

## `open_clientfd()`
: 클라이언트에서 서버와의 연결 설정
```C
int open_clientfd(char *hostname, char *port) {
    int clientfd;
    struct addrinfo hints, *listp, *p;

    // Get a list of potential server addresses
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;  // Open a connection
    hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;  // using a numeric port arg & recommended for connections
    Getaddrinfo(hostname, port, &hints, &listp);

    // Walk the list for one that we can successfully connect to
    for(p = listp; p; p = p->ai_next) {
        // Create a socket descriptor
        if((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
            continue;  // Socket faild, try the next
        
        // Connect to the server
        if(connect (clientfd, p->ai_addr, p->ai_addrlen) != -1)
            break;  // Success
        
        Close(clientfd);  // Connect failed, try another
    }

    // Clean up
    Freeaddrinfo(listp);
    if(!p)  // All connects failed
        return -1;
    else  // The last connect succeeded
        return clientfd;
}
```
: 서버와의 연결을 설정하는 도움함수 / 프로토콜 독립적 (`getaddrinfo`)

## `open_listenfd()`
: 서버에서 port에 연결 요청을 받을 준비가 된 listen file descriptor를 return
