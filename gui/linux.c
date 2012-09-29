/*
 * NAME
 *	Linux/Tcl bridge - interface to issue Linux or C command in Tcl.  It
 *	could be thought as a "C interpretor" in Tcl world.
 *
 * DESCRIPTION
 *	The Linux/Tcl bridge is an interface of Tcl for Linux programmer.
 *	Low level commands such as ioctl is supported to make Tcl more
 *	flexible for slow DAQ applications.
 */

#ifndef __SOLITON_TCL_LINUX_H
#define __SOLITON_TCL_LINUX_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <tcl.h>
#include <termios.h>


#endif

/*
 * linux_serial
 *
 *	RS-232 control which can't be achieved by fconfigure command.
 *
 *	Command:
 *		setrts		RTS set
 *		clearrts	RTS clear
 *		setdtr		DTR set
 *		cleardtr	DTR clear
 *		ctson		Turn On CTS Flow Control
 *		ctsoff		Turn On CTS Flow Control
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
