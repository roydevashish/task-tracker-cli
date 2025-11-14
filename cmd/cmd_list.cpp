#include <iostream>

#include "icmd.cpp"

using namespace std;

class CMDList : public iCMD
{
private:
  iStorage *m_storage = nullptr;

public:
  CMDList(iStorage *storage)
  {
    m_storage = storage;
  }

  void Execute(int arg_c, char *arg_v[])
  {
    if (arg_c < 2 && arg_c > 3)
    {
      cout << "error: invalid input" << endl;
      exit(EXIT_FAILURE);
    }

    if (arg_c == 2)
    {
      vector<Task> tasks = m_storage->GetAllTasks();
      for (auto task : tasks)
      {
        task.Print();
      }
    }

    if (arg_c == 3)
    {
      TASK_STATUS task_status = TaskStatusStringToEnum(arg_v[2]);
      vector<Task> tasks = m_storage->GetTasksByTaskStatus(task_status);
      for (auto task : tasks)
      {
        task.Print();
      }
    }
  }
};