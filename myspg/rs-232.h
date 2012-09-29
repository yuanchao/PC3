/*****************************
//      class RS_232
//
//  To manipulate the COM Port
//
*******************************/

class RS_232{

 public:
  RS_232( int port, int speed, int check, int data, int stop );
  RS_232();
  ~RS_232(){};

  int Init();

  int Read( char* );
  int Write( char*, int );


 private:
  char buffer[96];
  int Port, Speed, Check, Data, Stop;
  int fd;
  void *old;

  void delay(int);
  void undelay();
  static void handler(int);

};



