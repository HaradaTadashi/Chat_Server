#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h>
#include <WinSock2.h>	// WinSock�p
#include <iostream>
#include<string>
#include<vector>
#include<set>
#include <algorithm>
#pragma comment( lib, "ws2_32.lib" )

const unsigned short PORT = 8080;	// �T�[�o�̃|�[�g�ԍ�

std::vector <PCSTR> IP;
//std::set<std::string> IP;
std::string message = "";
bool flag = false;

int main()
{
	std::cout << "server" << std::endl;



	// WinSock�̏�����	WSAStartup()
	WSADATA  wsaData;

	// WinSock2.2 ����������
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		// �G���[����
	}

	SOCKET  sock;

	// UDP�\�P�b�g�̍쐬
	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		// �G���[
	}
	/*u_long arg = 0x01;
	ioctlsocket(sock, FIONBIO, &arg);*/

	// �|�[�g�ԍ��̊��蓖��	bind()
	SOCKADDR_IN  bindAddr;
	memset(&bindAddr, 0, sizeof(bindAddr));		// 0�N���A�ŏ�����
	bindAddr.sin_family = AF_INET;					// IPv4�A�h���X�g�p
	bindAddr.sin_port = htons(PORT);
	bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);	// ���ׂĂ̎�����NIC���Ώ�


	// �|�[�g�ԍ����蓖��
	if (bind(sock, (sockaddr*)&bindAddr, sizeof(bindAddr)) == SOCKET_ERROR)
	{
		// �G���[����
	}



	// �펞�ғ��Ŗ������[�v
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
			// �G���[����
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

	// �����������[�v���I�������
	// UDP�\�P�b�g�j��		closesocket()
	closesocket(sock);
	// WinSock�I������		WSACleanup()
	WSACleanup();
	return 0;	// ����I���ƐM���āI
}
