#include <iostream>

#include "icmd.cpp"

using namespace std;

class CMDDelete : public iCMD
{
private:
public:
  void Execute(int arg_c, char *arg_v[])
  {
    cout << "delete called" << endl;
  }
};