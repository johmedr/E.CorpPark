#include "../include/Can.h"

Can::Can() 
{
	/* open socket */
	if ((_sockNum = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("socket");
		return 1;
	}

	_sockAddr.can_family = AF_CAN;

	strcpy(_ifr.ifr_name, "can0");
	if (ioctl(_sockNum, SIOCGIFINDEX, &ifr) < 0) {
		perror("SIOCGIFINDEX");
		return 1;
	}
	_sockAddr.can_ifindex = _ifr.ifr_ifindex;

	/* disable default receive filter on this RAW socket */
	/* This is obsolete as we do not read from the socket at all, but for */
	/* this reason we can remove the receive list in the Kernel to save a */
	/* little (really a very little!) CPU usage.                          */
	setsockopt(_sockNum, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);

	if (bind(_sockNum, (struct sock_sockAddr *)&_sockAddr, sizeof(_sockAddr)) < 0) {
		perror("bind");
		return 1;
	}
}

Can::~Can() 
{
	close(_sockNum); 
}

void Can::write(uint8_t buffer[]) 
{
	struct can_frame frame;
	int nbytes; 
	
	if (parse_canframe(buff, &frame))
	{
		fprintf(stderr, "\nWrong CAN-frame format!\n\n");
		fprintf(stderr, "Try: <can_id>#{R|data}\n");
		fprintf(stderr, "can_id can have 3 (SFF) or 8 (EFF) hex chars\n");
		fprintf(stderr, "data has 0 to 8 hex-values that can (optionally)");
		fprintf(stderr, " be seperated by '.'\n\n");
		fprintf(stderr, "e.g. 5A1#11.2233.44556677.88 / 123#DEADBEEF / ");
		fprintf(stderr, "5AA# /\n     1F334455#1122334455667788 / 123#R ");
		fprintf(stderr, "for remote transmission request.\n\n");
		return 1;
	}

	if ((nbytes = write(_sockNum, &frame, sizeof(frame))) != sizeof(frame)) {
		perror("write");
		return 1;
	}
	

}

Can::CanFrame Can::read() 
{

}