#ifndef _ODSOCKET_H_
#define _ODSOCKET_H_

#ifdef WIN32
	#include <winsock.h>
	typedef int				socklen_t;
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <fcntl.h>
	#include "errno.h"
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <arpa/inet.h>
    #include <string.h>
	typedef int				SOCKET;

	//#pragma region define win32 const variable in linux
	#define INVALID_SOCKET	-1
	#define SOCKET_ERROR	-1
	//#pragma endregion
#endif
    typedef signed char           int8;
    typedef signed short          int16;
    typedef signed int            int32;




class ODSocket {

public:
	ODSocket(SOCKET sock = INVALID_SOCKET);
	~ODSocket();

	// Create socket object for snd/recv data
	bool Create(int af, int type, int protocol = 0);

	// Connect socket
	bool Connect(const char* ip, unsigned short port);
	//#region server
	// Bind socket
	bool Bind(unsigned short port);
    
    bool UdpCreate(); //**
    
    bool UdpBind(char *serverip,int port); //**
    
    bool UdpRecv(void *buff,int buff_size,char *fromip = NULL); //**
    
    bool UdpSend(const void *buf, size_t len,int flags = 0);  //**
    
    bool UdpSetMcast(char *ip,int port);

	// Listen socket
	bool Listen(int backlog = 5); 

	// Accept socket
	bool Accept(ODSocket& s, char* fromip = NULL);
	//#endregion
    
    int Select();  //**
    
	// Send socket
	int Send(const char* buf, int len, int flags = 0);

	// Recv socket
	int Recv(char* buf, int len, int flags = 0);
	
	// Close socket
	int Close();

	// Get errno
	int GetError();
    
    // write Int32ToByte
    int Int32ToByte(int iIn,char* sOut,int& _index);
    
    // write Int16ToByte
    int Int16ToByte(int iIn,char* sOut,int& _index);
    
    //write Int8ToByte
    int Int8ToByte(int iIn,char* sOut,int& _index);
    
    //write StringToByte
    int StringToByte(char* sInfo,char* sOut,int& _index);
    
    //read getInt32
    int32 getInt32(char* sIn,int& _index);
    
    //read getInt16
    int16 getInt16(char* sIn,int& _index);
    
    //read getInt8
    int8 getInt8(char* sIn,int& _index);
    
    
	
	//#pragma region just for win32
	// Init winsock DLL 
	static int Init();	
	// Clean winsock DLL
	static int Clean();
	//#pragma endregion

	// Domain parse
	static bool DnsParse(const char* domain, char* ip);

	ODSocket& operator = (SOCKET s);

	operator SOCKET ();
    
    SOCKET getSocket();
    
    
protected:
	SOCKET m_sock;
    fd_set fdR;
    struct sockaddr_in local_addr,mcast_addr;
    

};

#endif
