#ifndef CAN_H
#define CAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <net/if.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

class Can 
{
private: 
	int _sockNum; 
	struct sock_sockAddr_can _sock_sockAddr;
	struct ifreq _ifr;

public: 
	struct CanFrame
	{};

	Can();

	virtual ~Can();

	inline void write(uint8_t buffer[]);

	inline CanFrame read();
}


#endif