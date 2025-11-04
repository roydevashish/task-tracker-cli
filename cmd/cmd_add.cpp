#include <iostream>

#include "icmd.cpp"
#include "../task/task.cpp"

using namespace std;

class CMDAdd : public iCMD
{
private:
public:
  void Execute(int arg_c, char *arg_v[])
  {
    if (arg_c != 3)
    {
      cout << "error: invalid input" << endl;
      exit(EXIT_FAILURE);
    }

    char *task_description = arg_v[2];
    cout << "task added successfully with task id: " << "0" << endl;
  }
};