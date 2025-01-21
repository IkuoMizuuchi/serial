#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<termios.h>
#include	<pthread.h>

#define DEBUG 1

int initializeSerial(char *dev);
void * sending_thread (void *arg);

int main (int ac, char *av[]) {
	char *devfilename="/dev/ttyACM0";
	int fd;
	static unsigned char buf[BUFSIZ];
	int ret, size;
	pthread_t sendingt;

	if (ac>1) { devfilename=av[1]; }

	fd = initializeSerial(devfilename);
	if (fd == -1) { return -1; }

	pthread_create(&sendingt, NULL, sending_thread, (void*)fd);
	
	while (1) {
		ret = read(fd,buf,BUFSIZ);
		if (ret==-1) { usleep(1000); continue; }
#if DEBUG
		fprintf(stderr, "received %d data\n", ret);
#endif
		printf("\"%s\"", buf);
		usleep(1000);
	}
}

void * sending_thread (void * arg) {
	int serial = (int)arg;
	int n;
	static unsigned char buf[BUFSIZ];
	printf("serial=%d\n", serial);
	while (1) {
		scanf("%s", buf);
		n = strlen(buf);
		buf[n]='\n';
		buf[n+1]='\0';
		printf("%s", buf);
		n = write(serial, buf, n+1);
		printf("sent %d bytes\n", n);
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
	newtio.c_cflag = B9600 | CRTSCTS | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;
	newtio.c_lflag = ICANON;	//0 for RAW mode
	newtio.c_cc[VTIME] = 0;
	newtio.c_cc[VMIN] = 1;
	tcflush(serial, TCIFLUSH);
	tcsetattr(serial, TCSANOW, &newtio);
	fprintf(stderr, "initialized serial (%s) (fd=%d)\n", dev, serial);
	return serial;
#endif
}
