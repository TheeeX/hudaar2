// Fill out your copyright notice in the Description page of Project Settings.

#include "hudAR2.h"
#include "HudGyro.h"

#include "AllowWindowsPlatformTypes.h"
#include "ThirdParty/easywsclient/include/easywsclient.h"
#include "ThirdParty/easywsclient/include/easywsclient.cpp"
#include "HideWindowsPlatformTypes.h"

#include <assert.h>
#include <CString.h>
#include <sstream>

using easywsclient::WebSocket;
static WebSocket::pointer ws = NULL;

float Qtr6[6];
std::string token;

void handle_message(const std::string & message)
{
	printf(">>> %s\n", message.c_str());
	if (message == "world") { ws->close(); }
	std::string::size_type sz = 0;
	std::stringstream ss(message);
	std::string token, qtr;
	float qtall;
	int cn;

	if (message == "Connected") {
		printf("--connected to H-Gyro\n");
	}
	else {
		while (std::getline(ss, token, ':')) {
			printf("token : %s \n", token.c_str());

			cn = 0;
			std::stringstream sq(token);
			while (std::getline(ss, qtr, ',')) {
				qtall = std::stof(qtr.substr(sz));
				Qtr6[cn] = qtall;
				cn++;
				printf("qtall : %f \n", qtall);
			}
		}
	}
}

int initQtr() {
	ws = WebSocket::from_url("ws://192.168.0.104:81/");
	assert(ws);

	return 1;
}

float* getQtr() {
	ws->send("#");
	//int qtr[3];
	//ws->send("hello");
	while (ws->getReadyState() != WebSocket::CLOSED) {
		ws->poll();
		ws->dispatch(handle_message);
		//std::string qsnd = token;
		//printf("qsnd(message) : %s \n", qsnd);
		//token = "";
		return Qtr6;
	}
	return Qtr6;
}

int endQtr() {
	delete ws;
#ifdef _WIN32
	WSACleanup();
#endif
	return 1;
}

HudGyro::HudGyro()
{
#ifdef _WIN32
	//INT rc;
	WSADATA wsaData;

	//rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("WSAStartup Failed.\n");
		//return 1;
	}
#endif

}

HudGyro::~HudGyro()
{
}
