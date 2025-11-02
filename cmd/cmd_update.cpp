#include <iostream>

#include "icmd.cpp"

using namespace std;

class CMDUpdate : public iCMD
{
private:
public:
  void Execute(int arg_c, char *arg_v[])
  {
    cout << "update called" << endl;
  }
};