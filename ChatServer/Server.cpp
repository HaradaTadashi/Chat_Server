#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h>
#include <WinSock2.h>	// WinSock用
#include <iostream>
#include<string>
#include<vector>
#include<set>
#include <algorithm>
#pragma comment( lib, "ws2_32.lib" )

const unsigned short PORT = 8080;	// サーバのポート番号

std::vector <PCSTR> IP;
//std::set<std::string> IP;
std::string message = "";
bool flag = false;

int main()
{
	std::cout << "server" << std::endl;



	// WinSockの初期化	WSAStartup()
	WSADATA  wsaData;

	// WinSock2.2 初期化処理
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		// エラー処理
	}

	SOCKET  sock;

	// UDPソケットの作成
	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		// エラー
	}
	/*u_long arg = 0x01;
	ioctlsocket(sock, FIONBIO, &arg);*/

	// ポート番号の割り当て	bind()
	SOCKADDR_IN  bindAddr;
	memset(&bindAddr, 0, sizeof(bindAddr));		// 0クリアで初期化
	bindAddr.sin_family = AF_INET;					// IPv4アドレス使用
	bindAddr.sin_port = htons(PORT);
	bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);	// すべての自分のNICが対象


	// ポート番号割り当て
	if (bind(sock, (sockaddr*)&bindAddr, sizeof(bindAddr)) == SOCKET_ERROR)
	{
		// エラー処理
	}



	// 常時稼働で無限ループ
	while (true)
	{
		char buff[1024] /*= ""*/;
		char ipAddr[256] /*= ""*/;
		

		SOCKADDR_IN fromAddr;
		int fromlen = sizeof(fromAddr);

		int ret = recvfrom(sock, (char*)&buff, sizeof(buff), 0, (sockaddr*)&fromAddr, &fromlen);
		
        inet_ntop(AF_INET, &fromAddr.sin_addr, ipAddr, sizeof(ipAddr));
		IP.push_back(ipAddr);
		
		std::cout << ipAddr << ":" << buff << std::endl;

		if (ret == true)
		{
			flag = true;
		}
		if (ret == SOCKET_ERROR)
		{
			// エラー処理
		}
		

		

		decltype(IP)::iterator result = std::unique(IP.begin(), IP.end());
		IP.erase(result, IP.end());

		SOCKADDR_IN toAddr;
		int tolen = sizeof(toAddr);
		memset(&toAddr, 0, sizeof(toAddr));
		toAddr.sin_family = AF_INET;
		toAddr.sin_port = htons(PORT);

			/*for (int i = 0; i < IP.size(); i++)
			{*/
				/*inet_pton(AF_INET, ipAddr, &toAddr.sin_addr.s_addr);*/
				
				/*message.append(ipAddr);
				message.append(":"); 
				message.append(buff);
				message.append("\r\n");
				ret = sendto(sock, message.c_str(), sizeof(message), 0, (SOCKADDR*)&fromAddr, sizeof(fromAddr));*/
				//std::cout << message.c_str() << std::endl;

		       
			   ret = sendto(sock, buff, sizeof(buff), 0, (struct sockaddr*)&fromAddr, sizeof(fromAddr));
			   ret = sendto(sock, ipAddr, sizeof(ipAddr), 0, (struct sockaddr*)&fromAddr, sizeof(fromAddr));

			/*}*/
		
		
		


	}

	// もし無限ループが終わったら
	// UDPソケット破棄		closesocket()
	closesocket(sock);
	// WinSock終了処理		WSACleanup()
	WSACleanup();
	return 0;	// 正常終了と信じて！
}
