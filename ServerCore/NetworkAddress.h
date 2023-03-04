#pragma once


/*-------------------
	NetworkAddress
-------------------*/

class NetAddress
{
public:
	NetAddress() = default;
	NetAddress(sockaddr_in addr);
	NetAddress(wstring ip, uint16 port);

	sockaddr_in&	GetSockAddr() { return m_Addr; }
	wstring			GetIpAddress();
	uint16			GetPort() { return ntohs(m_Addr.sin_port); }

public:
	static in_addr	Ip2Address(const WCHAR* ip);

private:
	sockaddr_in		m_Addr = {};
};

