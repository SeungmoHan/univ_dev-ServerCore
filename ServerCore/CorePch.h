#pragma once

#include "Types.h"
#include "CoreMacro.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"
#include "Container.h"

#include <Windows.h>
#include <iostream>
using namespace std;

#include "Lock.h"

#include "ObjectPool.h"
#include "TypeCast.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")
#include <timeapi.h>
#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#include "Logger.h"
#include "Memory.h"

#include "SendBuffer.h"
#include "Session.h"
#include "LockQueue.h"