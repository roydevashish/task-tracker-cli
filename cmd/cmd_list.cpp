#include <iostream>

#include "icmd.cpp"

using namespace std;

class CMDList : public iCMD
{
private:
public:
  void Execute(int arg_c, char *arg_v[])
  {
    cout << "list called" << endl;
  }
};