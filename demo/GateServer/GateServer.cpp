// ZeroMQ_server.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <thread>

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





void request_reply()
{
	// Prepare our context and socket
	zmq::context_t context(6);
	zmq::socket_t socket(context, ZMQ_REP);
	socket.bind("tcp://*:8001");

	while (true) {
		zmq::message_t request;

		// Wait for next request from client
		socket.recv(&request);
		std::cout << "Received Hello" << std::endl;

		// Send reply back to client
		zmq::message_t reply(6);
		memcpy((void *)reply.data(), "World", 5);
		socket.send(reply);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int major, minor, patch;
	zmq::version(&major, &minor, &patch);
	printf("current MQ version is %d.%d.%d\n");

	// request reply
	{
		std::thread t2(request_reply);
		t2.join();
	}

	return 0;
}


