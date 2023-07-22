#pragma once

template< typename InstanceType>
class Singleton
{
protected:
	Singleton() {};
	~Singleton() {};
public:
	static InstanceType* Instance()
	{
		static InstanceType instance;
		return &instance;
	}
};
