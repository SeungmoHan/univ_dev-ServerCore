#include "pch.h"
#include "NetworkAddress.h"

NetAddr_TCP::NetAddr_TCP(const sockaddr_in addr) : m_Addr(addr)
{

}

NetAddr_TCP::NetAddr_TCP(const wstring ip, const uint16 port)
{
	::memset(&m_Addr, 0, sizeof(m_Addr));
	m_Addr.sin_family = AF_INET;
	m_Addr.sin_addr = Ip2Address(ip.c_str());
	m_Addr.sin_port = htons(port);
}

wstring NetAddr_TCP::GetIpAddress()
{
	WCHAR buffer[100];
	InetNtopW(AF_INET, &m_Addr.sin_addr, buffer, len32(buffer));
	return buffer;
}

in_addr NetAddr_TCP::Ip2Address(const WCHAR* ip)
{
	in_addr addr;
	InetPtonW(AF_INET, ip, &addr);
	return addr;
}
