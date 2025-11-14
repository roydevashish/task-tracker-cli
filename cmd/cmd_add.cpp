#include <iostream>

#include "icmd.cpp"
#include "../task/task.cpp"
#include "../storage/storage_sqlite.cpp"

using namespace std;

class CMDAdd : public iCMD
{
private:
  iStorage *m_storage = nullptr;

public:
  CMDAdd(iStorage *storage)
  {
    m_storage = storage;
  }

  void Execute(int arg_c, char *arg_v[])
  {
    if (arg_c != 3)
    {
      cout << "error: invalid input" << endl;
      exit(EXIT_FAILURE);
    }

    char *task_description = arg_v[2];
    Task new_task = m_storage->CreateTask(task_description);
    if (new_task.GetId() < 0)
    {
      cout << "error: unable to create new task" << endl;
      exit(EXIT_FAILURE);
    }
    cout << "task added successfully with task id: " << new_task.GetId() << endl;
  }
};