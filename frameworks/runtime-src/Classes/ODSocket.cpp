#include "ODSocket.h"
#include <stdio.h>
#ifdef WIN32
	#pragma comment(lib, "wsock32")
#endif


ODSocket::ODSocket(SOCKET sock)
{
	m_sock = sock;
}

ODSocket::~ODSocket()
{
}

int ODSocket::Init()
{
#ifdef WIN32
	/*
	http://msdn.microsoft.com/zh-cn/vstudio/ms741563(en-us,VS.85).aspx

	typedef struct WSAData { 
		WORD wVersion;								//winsock version
		WORD wHighVersion;							//The highest version of the Windows Sockets specification that the Ws2_32.dll can support
		char szDescription[WSADESCRIPTION_LEN+1]; 
		char szSystemStatus[WSASYSSTATUS_LEN+1]; 
		unsigned short iMaxSockets; 
		unsigned short iMaxUdpDg; 
		char FAR * lpVendorInfo; 
	}WSADATA, *LPWSADATA; 
	*/
	WSADATA wsaData;
	//#define MAKEWORD(a,b) ((WORD) (((BYTE) (a)) | ((WORD) ((BYTE) (b))) << 8)) 
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);//win sock start up
	if ( ret ) {
//		cerr << "Initilize winsock error !" << endl;
		return -1;
	}
#endif
	
	return 0;
}
//this is just for windows
int ODSocket::Clean()
{
#ifdef WIN32
		return (WSACleanup());
#endif
		return 0;
}

ODSocket& ODSocket::operator = (SOCKET s)
{
	m_sock = s;
	return (*this);
}

ODSocket::operator SOCKET ()
{
	return m_sock;
}
//create a socket object win/lin is the same
// af:
bool ODSocket::Create(int af, int type, int protocol)
{
	m_sock = socket(af, type, protocol);
	if ( m_sock == INVALID_SOCKET ) {
		return false;
	}
	return true;
}

bool ODSocket::Connect(const char* ip, unsigned short port)
{
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = inet_addr(ip);
	svraddr.sin_port = htons(port);
	int ret = connect(m_sock, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if ( ret == SOCKET_ERROR ) {
		return false;
	}
	return true;
}

bool ODSocket::Bind(unsigned short port)
{
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = INADDR_ANY;
	svraddr.sin_port = htons(port);

	int opt =  1;
	if ( setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0 ) 
		return false;

	int ret = bind(m_sock, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if ( ret == SOCKET_ERROR ) {
		return false;
	}
	return true;
}

bool ODSocket::UdpCreate(){
    m_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if ( m_sock == INVALID_SOCKET ) {
		return false;
	}
	return true;
}

bool ODSocket::UdpBind(char *serverip,int port){
    
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	local_addr.sin_port = htons(port);
    int err = bind(m_sock, (struct sockaddr*)&local_addr, sizeof(local_addr));
    if (err == SOCKET_ERROR) {
        return false;
    }
    
    /*设置回环许可*/
    int loop = 0;
    err = setsockopt(m_sock,IPPROTO_IP, IP_MULTICAST_LOOP,&loop, sizeof(loop));
    if(err < 0)
    {
        perror("setsockopt():IP_MULTICAST_LOOP");
        return false;
    }
    struct ip_mreq mreq; /*加入广播组*/
    mreq.imr_multiaddr.s_addr    = inet_addr(serverip); /*广播地址*/
    mreq.imr_interface.s_addr    = htonl(INADDR_ANY); /*网络接口为默认*/
    /*将本机加入广播组*/
    err = setsockopt(m_sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq, sizeof(mreq));
    if (err < 0)
    {
        perror("setsockopt():IP_ADD_MEMBERSHIP");
        return false;
    }
    
//    int BUFF_SIZE = 256;
//    int times = 0;
//    socklen_t addr_len = 0;
//    char buff[BUFF_SIZE];
//    int n = 0;
//    /*循环接收广播组的消息，5次后退出*/
//    for(times = 0;times<5;times++)
//    {
//        addr_len = sizeof(local_addr);
//        memset(buff, 0,BUFF_SIZE); /*清空接收缓冲区*/
//        /*接收数据*/
//        n = recvfrom(m_sock, &buff, BUFF_SIZE, 0,(struct sockaddr*)&local_addr, &addr_len);
//        if( n== -1)
//        {
//            perror("recvfrom()");
//        }
//        /*打印信息*/
//        printf("Recv %dst    message from server:%s\n", times, buff);
//        sleep(5);
//    }
//    /*退出广播组*/
//    err = setsockopt(m_sock,IPPROTO_IP,IP_DROP_MEMBERSHIP,&mreq, sizeof(mreq));
//    close(m_sock);
    return true;
}

bool ODSocket::UdpRecv(void *buff,int buff_size,char *fromip){
    socklen_t addr_len = 0;
    int n = 0;
    addr_len = sizeof(local_addr);
    
    /*接收数据*/
    n = recvfrom(m_sock, buff, buff_size, 0,(struct sockaddr*)&local_addr, &addr_len);
    if( n== -1)
    {
        perror("recvfrom()");
    }
    
    if ( fromip != NULL )
		sprintf(fromip, "%s", inet_ntoa(local_addr.sin_addr));
    
    return true;
}

bool ODSocket::UdpSend(const void *buff, size_t len,int flag){
    socklen_t addr_len = 0;
    int n = 0;
    addr_len = sizeof(mcast_addr);
    n = sendto(m_sock, buff, len, flag,(struct sockaddr*)&mcast_addr,addr_len);
    if (n<0) {
        return false;
    }
    return true;
}

bool ODSocket::UdpSetMcast(char *ip, int port){
    memset(&mcast_addr, 0, sizeof(mcast_addr));
    mcast_addr.sin_family = AF_INET;
    mcast_addr.sin_addr.s_addr = inet_addr(ip);
    mcast_addr.sin_port = htons(port);
    return true;
}


//for server
bool ODSocket::Listen(int backlog)
{
	int ret = listen(m_sock, backlog);
	if ( ret == SOCKET_ERROR ) {
		return false;
	}
	return true;
}

bool ODSocket::Accept(ODSocket& s, char* fromip)
{
	struct sockaddr_in cliaddr;
	socklen_t addrlen = sizeof(cliaddr);
	SOCKET sock = accept(m_sock, (struct sockaddr*)&cliaddr, &addrlen);
	if ( sock == SOCKET_ERROR ) {
		return false;
	}

	s = sock;
	if ( fromip != NULL )
		sprintf(fromip, "%s", inet_ntoa(cliaddr.sin_addr));
    
	return true;
}

int ODSocket::Send(const char* buf, int len, int flags)
{
	int bytes;
	int count = 0;

	while ( count < len ) {

		bytes = send(m_sock, buf + count, len - count, flags);
		if ( bytes == -1 || bytes == 0 )
			return -1;
		count += bytes;
	} 

	return count;
}

int ODSocket::Select(){
    FD_ZERO(&fdR);
	FD_SET(m_sock, &fdR);
	struct timeval mytimeout;
	mytimeout.tv_sec=3;
	mytimeout.tv_usec=0;
	int result= select(m_sock+1,&fdR,NULL,NULL,NULL);
	// 第一个参数是 0 和 sockfd 中的最大值加一
	// 第二个参数是 读集, 也就是 sockset
	// 第三, 四个参数是写集和异常集, 在本程序中都为空
	// 第五个参数是超时时间, 即在指定时间内仍没有可读, 则出错
	if(result != SOCKET_ERROR && result != 0){
        if(FD_ISSET(m_sock,&fdR)){
            return 1;
        }else {
            return 0;
        }
	}
    else{
        return -1;
    }
	/*else if(result==0){
     return -4;
     }*/
	
}

int ODSocket::Recv(char* buf, int len, int flags)
{
	return (recv(m_sock, buf, len, flags));
}

int ODSocket::Close()
{
#ifdef WIN32
	return (closesocket(m_sock));
#else
	return (close(m_sock));
#endif
}

int ODSocket::GetError()
{
#ifdef WIN32
	return (WSAGetLastError());
#else
	return (errno);
#endif
}


int ODSocket::Int32ToByte(int iIn,char* sOut,int& _index)
{
    int i = 3;
    while(i >=0)
    {
        sOut[i + _index] = iIn>>((3-i)*8) & 0xff;
        i--;
    }
    return (_index+=4);
}


int ODSocket::Int16ToByte(int iIn,char* sOut,int& _index)
{
    int i = 1;
    while (i>=0) {
        sOut[i+_index] = iIn>>((1-i)*8) & 0xff;
        i--;
    }
    return (_index+=2);
}


int ODSocket::Int8ToByte(int iIn,char* sOut,int& _index)
{
    sOut[_index] = iIn&0xff;
    return (++_index);
}


int ODSocket::StringToByte(char* sInfo,char* sOut,int& _index)
{
    long len = strlen(sInfo);
    memcpy(sOut+_index, sInfo, strlen(sInfo));
    return (_index+=len);
}


int32 ODSocket::getInt32(char* sIn,int& _index)
{
    int i = 3;
    int32 tempInt32 = 0;
    while(i>=0){
        tempInt32 |= (sIn[i+_index] & 0xff) << ((3-i)*8);
        i--;
    }
    _index+=4;
    return tempInt32;
}


int16 ODSocket::getInt16(char* sIn,int& _index)
{
    int i = 1;
    int32 tempInt16 = 0;
    while(i>=0){
        tempInt16 |= (sIn[i+_index] & 0xff) << ((1-i)*8);
        i--;
    }
    _index+=2;
    return tempInt16;
}


int8 ODSocket::getInt8(char* sIn,int& _index)
{
    int32 tempInt8 = 0;
    tempInt8 |= (sIn[_index] & 0xff);
    ++_index;
    return tempInt8;
}



//char* ODSocket::getCStr(char* )


SOCKET ODSocket::getSocket(){
    return m_sock;
}




bool ODSocket::DnsParse(const char* domain, char* ip)
{
	struct hostent* p;
	if ( (p = gethostbyname(domain)) == NULL )
		return false;
		
	sprintf(ip, 
		"%u.%u.%u.%u",
		(unsigned char)p->h_addr_list[0][0], 
		(unsigned char)p->h_addr_list[0][1], 
		(unsigned char)p->h_addr_list[0][2], 
		(unsigned char)p->h_addr_list[0][3]);
	
	return true;
}
