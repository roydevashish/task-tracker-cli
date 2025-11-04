#include <iostream>

#include "icmd.cpp"

using namespace std;

class CMDDelete : public iCMD
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

    int task_id = atoi(arg_v[2]);
    cout << "task deleted successfully with task id: " << task_id << endl;
  }
};