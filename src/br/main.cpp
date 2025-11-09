// SPDX-License-Identifier: BUSL-1.1
// Copyright 2024-2025 Michael Pozhidaev <msp@luwrain.org>

#include"os.h"
#include"Service.h"
#include"CompatTest.h"

using namespace GuideCraft;
using namespace std;

class CmdLineArg;

class CmdLineParser
{
public:
  virtual ~CmdLineParser() {}

    public:
    list<const CmdLineArg*> args;
};

  class CmdLineArg
  {
  public:
    CmdLineArg(CmdLineParser& parser, char shortOpt, const string& d):
      shortOption(shortOpt), longOption(""), descr(d)
    { parser.args.push_back(this); }
    virtual ~CmdLineArg() {}

  public:
    char shortOption;
    string longOption;
    string descr;
  };

class CmdLine
{
public:
  CmdLine(int argc, char* argv[]);
  virtual ~CmdLine() {}

public:
  void printHelp();

public:
    CmdLineParser parser;
  CmdLineArg
  help{parser, 'h', "Print help and exit"},
    verbose{parser, 'v', "Enable verbose mode"};

};


int main(int argc, char* argv[])
{
  CompatTest t;
  t.run();
  return 0;
  /*
  pthread_condattr_t condattr;
  pthread_mutexattr_t mutexattr;
  pthread_rwlockattr_t rwlockattr;
  cout << pthread_condattr_init(&condattr) << endl;
    cout << pthread_mutexattr_init(&mutexattr) << endl;
      cout << pthread_rwlockattr_init(&rwlockattr) << endl;
      

  
  cout << pthread_condattr_setpshared(&condattr, PTHREAD_PROCESS_SHARED) << endl;
    cout << pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED) << endl;
        cout << pthread_rwlockattr_setpshared(&rwlockattr, PTHREAD_PROCESS_SHARED) << endl;

	int value;
	cout << "Orig " << PTHREAD_PROCESS_SHARED << endl;
	cout << pthread_mutexattr_getpshared(&mutexattr, &value) << endl;
	cout << value << endl;

		cout << pthread_rwlockattr_getpshared(&rwlockattr, &value) << endl;
	cout << value << endl;

			cout << pthread_condattr_getpshared(&condattr, &value) << endl;
	cout << value << endl;

	cout << "Creating" << endl;
	pthread_rwlock_t rwlock;
	cout << pthread_rwlock_init(&rwlock, &rwlockattr) << endl;


    
  CmdLine cmdLine(argc, argv);
  cmdLine.printHelp();
  Service serv;
  serv.run();
  printHelp();
  */
}

CmdLine::CmdLine(int argc, char* argv[])
{
}

void CmdLine::printHelp()
{
  for(auto a: parser.args)
    cout <<  a->descr << endl;
}

