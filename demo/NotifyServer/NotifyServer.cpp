// ZeroMQ_server.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"

#include <zmq.hpp>
#include <string>
#include <iostream>

#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#endif


#if defined(_DEBUG) || defined(DEBUG)
#pragma comment(lib, "../../bin/Win32/Debug/v120/dynamic/libzmq.lib")
#else
#pragma comment(lib, "../../bin/Win32/Release/v120/dynamic/libzmq.lib")
#endif // DEBUG


int _tmain(int argc, _TCHAR* argv[])
{
	int major, minor, patch;
	zmq::version(&major, &minor, &patch);
	printf("current MQ version is %d.%d.%d\n");

	// Prepare our context and socket
	zmq::context_t context(1);
	zmq::socket_t publisher(context, ZMQ_PUB);
	publisher.bind("tcp://*:8005");

	while (1) {
		publisher.send("A-000000000000000000000000", ZMQ_SNDMORE);

#ifndef _WIN32
		sleep(1);
#else
		Sleep(1000);
#endif
	}

	return 0;
}


