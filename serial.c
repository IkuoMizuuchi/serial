#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<termios.h>

int initializeSerial(char *dev);

int main (int ac, char *av[]) {
	char *devfilename="/dev/ttyS7";
	int fd;
	static unsigned char buf[BUFSIZ];
	int ret, size;

	if (ac>1) { devfilename=av[1]; }

	fd = initializeSerial(devfilename);
	if (fd == -1) { return -1; }
	
	while (1) {
		ret = read(fd,buf,BUFSIZ);
		if (ret==-1) { usleep(1000); continue; }
#if DEBUG
		fprintf(stderr, "received %d data\n", ret);
#endif
		printf("received:\"%s\"\n", buf);
	}
}



int initializeSerial(char *dev) {
#if Darwin
	fprintf(stderr, "I don't know how to write communication by Mac.\n");
	fprintf(stderr, "Please investigate and write appropriate codes.\n");
#else
	struct termios oldtio, newtio;
	int serial;
	serial = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);
	if (serial == -1) {
		fprintf(stderr, "could not open serial port (%s)\n",dev);
		return -1;
	}
//	ioctl( serial , TCGETA , &oldtio );
	tcgetattr(serial, &oldtio);
	newtio = oldtio;
	newtio.c_cflag = B115200 | CRTSCTS | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;
	newtio.c_lflag = 0;
	newtio.c_cc[VTIME] = 0;
	newtio.c_cc[VMIN] = 1;
	tcflush(serial, TCIFLUSH);
	tcsetattr(serial, TCSANOW, &newtio);
	fprintf(stderr, "initialized serial (%s)\n", dev);
	return serial;
#endif
}

