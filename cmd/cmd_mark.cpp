#include <iostream>

#include "icmd.cpp"

using namespace std;

class CMDMark : public iCMD
{
private:
public:
  void Execute(int arg_c, char *arg_v[])
  {
    cout << "mark called" << endl;
  }
};