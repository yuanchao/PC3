/*
 *  libcom.cc
 *  Utility function for Tcl/Tk to setup the com port
 *  By: Yuan Chao
 *
 *  2002/04/15
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <tcl.h>
#include <termios.h>


/*
 * serial
 *
 * Command:
 * 	setrts		RTS set
 * 	clearrts	RTS clear
 * 	setdtr		DTR set
 * 	cleardtr	DTR clear
 * 	ctson		Turn On CTS Flow Control
 * 	ctsoff		Turn On CTS Flow Control
 */

static int
linux_serial (ClientData clientData, Tcl_Interp *interp,
        int argc, char *argv[]) {

	int fd = -1;
	int value;
	unsigned char arg;
	struct termios old_termio, new_termio;

	if (argc < 2) {
		sprintf(interp->result,
		"wrong # args: should be \"linux::serialchannelName cmd\"");
		return TCL_ERROR;
	}

	sscanf(argv[1], "file%d", &fd);
	if (fd < 0) {
		sprintf(interp->result, "invalid channelName \"%s\"", argv[1]);
		return TCL_ERROR;
	}

	if (strcmp(argv[2], "setrts") == 0) {
		arg = TIOCM_RTS;
		if (ioctl(fd, TIOCMBIS, &arg) < 0) {
			sprintf(interp->result,
				"ioctl %d TIOCMBIS TIOCM_RTS failed", fd);
			return TCL_ERROR;
		}
	} else if (strcmp(argv[2], "clearrts") == 0) {
		arg = TIOCM_RTS;
		if (ioctl(fd, TIOCMBIC, &arg) < 0) {
			sprintf(interp->result,
				"ioctl %d TIOCMBIC TIOCM_RTS failed", fd);
			return TCL_ERROR;
		}
	} else if (strcmp(argv[2], "setdtr") == 0) {
		arg = TIOCM_DTR;
		if (ioctl(fd, TIOCMBIS, &arg) < 0) {
			sprintf(interp->result,
				"ioctl %d TIOCMBIS TIOCM_DTR failed", fd);
			return TCL_ERROR;
		}
	} else if (strcmp(argv[2], "cleardtr") == 0) {
		arg = TIOCM_DTR;
		if (ioctl(fd, TIOCMBIC, &arg) < 0) {
			sprintf(interp->result,
				"ioctl %d TIOCMBIC TIOCM_DTR failed", fd);
			return TCL_ERROR;
		}
	} else if (strcmp(argv[2], "ctson") == 0) {
		tcgetattr(fd, &old_termio);
		new_termio.c_cflag = old_termio.c_cflag | CRTSCTS;
		new_termio.c_cc[VMIN]  = 1;
		new_termio.c_cc[VTIME] = 0;
		tcflush(fd, TCIOFLUSH);
		tcsetattr(fd, TCSANOW, &new_termio);
	} else if (strcmp(argv[2], "ctsoff") == 0) {
		tcgetattr(fd, &old_termio);
		new_termio.c_cflag = old_termio.c_cflag & ~CRTSCTS;
		tcflush(fd, TCIOFLUSH);
		tcsetattr(fd, TCSANOW, &new_termio);
	} else if (strcmp(argv[2], "drain") == 0) {
		int delay;
		Tcl_GetInt(interp, argv[3], &delay); 
		ioctl(fd, TCSBRK, &delay);
	} else {
		sprintf(interp->result,
		"unknown command \"%s\": should be crtcsts, setrts, clearrts, setdtr, cleardtr, ctson, ctsoff or drain", argv[2]);
		return TCL_ERROR;
	}
	return TCL_OK;
}


typedef int
(*FUNCPTR)(ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]);

static struct command_table {
	char *tcl;
	FUNCPTR c;
} cmdtab[] = {
{"linux::serial",	linux_serial},
{NULL, NULL}
};

int Linux_Init (Tcl_Interp *interp)
{
	int i;

	for (i=0; cmdtab[i].tcl != NULL; ++i) {
		Tcl_CreateCommand (interp, cmdtab[i].tcl, cmdtab[i].c,
			(ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);
	}

        Tcl_EvalFile(interp, "./linux.tcl");
        return TCL_OK;
}
