// ZeroMQ_demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <zmq.h>
#include <string.h>
#include <stdio.h>

#if defined(_DEBUG) || defined(DEBUG)
#pragma comment(lib, "../../bin/Win32/Debug/v120/dynamic/libzmq.lib")
#else
#pragma comment(lib, "../../bin/Win32/Release/v120/dynamic/libzmq.lib")
#endif // DEBUG

int _tmain(int argc, _TCHAR* argv[])
{
	void *context = zmq_init(1);

	// Socket to talk to server
	printf("Connecting to hello world server…\n");

	void *requester = zmq_socket(context, ZMQ_REQ);
	int ret = zmq_connect(requester, "tcp://localhost:5555");
	printf("ret = %d\n", ret);
	
	int request_nbr;
	
	while (1)
	{
		for (request_nbr = 0; request_nbr != 10; request_nbr++)
		{
// 			char * data = "123456789-123456789-123456789";
// 			int data_len = strlen(data);

			zmq_msg_t request;
			
			zmq_msg_more(&request);

			zmq_msg_init_size(&request, 5);
			memcpy(zmq_msg_data(&request), "hello", 5);
			printf("Sending Hello %d…\n", request_nbr);
			zmq_send(requester, &request, sizeof(zmq_msg_t), 0);
			zmq_msg_close(&request);

			zmq_msg_t reply;
			zmq_msg_init(&reply);
			zmq_recv(requester, &reply, sizeof(zmq_msg_t), 0);
			printf("Received World %d\n", request_nbr);
			zmq_msg_close(&reply);
		}
 		Sleep(10);
	};

	zmq_close(requester);
	zmq_term(context);
	
	return 0;
}
