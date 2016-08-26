// ZeroMQ_server.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"

#include <zmq.hpp>
#include <string>
#include <iostream>

#if defined(_DEBUG) || defined(DEBUG)
#pragma comment(lib, "../../bin/Win32/Debug/v120/dynamic/libzmq.lib")
#else
#pragma comment(lib, "../../bin/Win32/Release/v120/dynamic/libzmq.lib")
#endif // DEBUG

int _tmain(int argc, _TCHAR* argv[])
{
	// Prepare our context and socket
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REP);
	socket.bind("tcp://*:5555");

	while (1) {
		zmq::message_t request;

		// Wait for next request from client
		socket.recv(&request);
		std::cout << "Received Hello" << std::endl;

		// Do some 'work'
// 		Sleep(100);

		// Send reply back to client

		zmq::message_t reply(5);
		memcpy((void *)reply.data(), "AAAAA", 5);
		socket.send(reply);
	}

	return 0;
}


