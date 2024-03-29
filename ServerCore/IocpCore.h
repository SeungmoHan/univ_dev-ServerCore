#pragma once




/*------------------
	Iocp Object
-------------------*/
class IocpObject : public enable_shared_from_this<IocpObject>
{
public:
	virtual ~IocpObject() = default;
	virtual HANDLE GetHandle() abstract;
	virtual void Dispatch(class IocpEvent* iocpEvent, int32 numberOfBytes = 0) abstract;
};




/*--------------
	Iocp Core
--------------*/

class IocpCore
{
public:
	IocpCore();
	~IocpCore();

	HANDLE		GetHande() const { return m_IocpHandle; }

	bool		Register(IocpObjectPtr iocpObject) const;
	bool		Dispatch(uint32 timeOutMs = INFINITE) const;

private:
	HANDLE m_IocpHandle;
};
