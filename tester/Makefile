DEST =  tester

OBJS =  tester.o rs-232.o
 
INCS = -I. -I/usr/local/include -I/usr/src/linux/include -I/usr/local/nigpib

LIBS =  -L/usr/local/lib -L/usr/local/nigpib -lgpib

#CFLAGS = -O $(INCS)
CPPFLAGS = -g -O $(INCS)

$(DEST):        $(OBJS)
	$(CXX) -o $(DEST1) $(OBJS1) $(LIBS) $(SYSLIB)

clean:
	rm -f $(OBJS) $(MODULE)


