
static const char * copyrightAndLicense
	= "Copyright (c) 2001, by David B. Apfelbaum.\n"
	  "All rights reserved.\n"
	  "\n"
	  "Standard BSD Open-Source License:\n"
	  "\n"
	  "Redistribution and use in source and binary forms,\n"
	  "with or without modification, are permitted provided\n"
	  "that the following conditions are met:\n"
	  "\n"
	  " + Redistributions of source code must retain the\n"
	  "   above copyright notice, this list of conditions\n"
	  "   and the following disclaimer.\n"
	  "\n"
	  " + Redistributions in binary form must reproduce the\n"
	  "   above copyright notice, this list of conditions\n"
	  "   and the following disclaimer in the documentation\n"
	  "   and/or other materials provided with the\n"
	  "   distribution. \n"
	  "\n"
	  " + Neither the name of David B. Apfelbaum nor the\n"
	  "   names of any contributors may be used to endorse\n"
	  "   or promote products derived from this software\n"
	  "   without specific prior written permission. \n"
	  "\n"
	  "THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS\n"
	  "AND CONTRIBUTORS \"AS IS\" AND ANY EXPRESS OR IMPLIED\n"
	  "WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE\n"
	  "IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR\n"
	  "A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT\n"
	  "SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY\n"
	  "DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR\n"
	  "CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,\n"
	  "PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF\n"
	  "USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)\n"
	  "HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,\n"
	  "WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT\n"
	  "(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY\n"
	  "WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED\n"
	  "OF THE POSSIBILITY OF SUCH DAMAGE.\n";
static void copyrightAndLicense_markUsed()
	{ (void)&copyrightAndLicense_markUsed; (void)&copyrightAndLicense; }



#include "Thread.H"
#include "Mutex.H"

#define POUT(X)  cout << # X " = " << (X) << endl


class testThread : public Thread
{
 public:
  virtual void run();
};

Mutex  aMutex ( Mutex::ERROR_CHECK );

/*virtual*/ void
testThread::run()
{
  for (int i=0;  i<5;  i++ )
  {
    aMutex.lock();
    POUT ( aMutex );
    cout << "i=" << setw(2) << i << "  Thread: " << this << endl;
    aMutex.unlock();
    sleep(1);
  }
}


void runThread()
{
  for (int i=0;  i<5;  i++ )
  {
    aMutex.lock();
    POUT ( aMutex );
    cout << "i=" << setw(2) << i << "  Thread: unknown" << endl;
    aMutex.unlock();
    sleep(1);
  }
}

int
main()
{
  testThread   t1,t2,t3,t4;
  Thread       t5;

  POUT( t5.setThreadFunction ( & runThread ) );

  POUT ( t1 );

  POUT ( aMutex );

  aMutex . lock();

  POUT ( aMutex );

  POUT ( t1.start() );
  POUT ( t2.start() );
  POUT ( t3.start() );
  POUT ( t4.start() );
  POUT ( t5.start() );

  POUT ( t1 );

  aMutex . unlock();

  sleep ( 7 );
  POUT ( t5 );
  cout << "ending..." << endl;
}
