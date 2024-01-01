#pragma once


/*-------------------
	NetworkAddress
-------------------*/

class NetAddr_TCP
{
public:
	explicit NetAddr_TCP() = default;
	explicit NetAddr_TCP(sockaddr_in addr);
	explicit NetAddr_TCP(wstring ip, uint16 port);

	sockaddr_in&	GetSockAddr() { return m_Addr; }
	wstring			GetIpAddress();
	uint16			GetPort() { return ntohs(m_Addr.sin_port); }

public:
	static in_addr	Ip2Address(const WCHAR* ip);

private:
	sockaddr_in		m_Addr = {};
};

