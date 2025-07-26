#pragma once

#include <atomic>
#include <thread>
#include <iostream>
#include <string>
#include <print>

#include "jNet/JNetBase.h"

using namespace std;
using namespace JNet;

int main()
{
	print("IP (s for server) >> ");

	string sIP;
	cin >> sIP;
	println("{}", sIP);

	atomic<bool> bRunning;
	bRunning.store(true);

	JNetBase::init(bRunning);
	JNetBase::initLocalAddr(sIP == "s" ? nullptr : sIP.c_str());
	thread t(JNetBase::update);

	while (bRunning.load())
	{
		bRunning.store(false);
	}

	t.join();

	return 0;
}