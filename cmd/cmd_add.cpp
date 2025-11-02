#include <iostream>

#include "icmd.cpp"

using namespace std;

class CMDAdd : public iCMD
{
private:
public:
  void Execute(int arg_c, char *arg_v[])
  {
    cout << "add called" << endl;
  }
};