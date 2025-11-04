#include <iostream>

#include "icmd.cpp"

using namespace std;

class CMDList : public iCMD
{
private:
public:
  void Execute(int arg_c, char *arg_v[])
  {
    if (arg_c < 2 && arg_c > 3)
    {
      cout << "error: invalid input" << endl;
      exit(EXIT_FAILURE);
    }

    if (arg_c == 2)
    {
      cout << "list of all tasks" << endl;
      exit(EXIT_SUCCESS);
    }

    if (arg_c == 3)
    {
      TASK_STATUS task_status = TaskStatusStringToEnum(arg_v[2]);
      cout << "list of all tasks with task status: " << TaskStatusEnumToString(task_status) << endl;
      exit(EXIT_SUCCESS);
    }
  }
};