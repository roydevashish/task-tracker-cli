#include <iostream>

#include "icmd.cpp"

using namespace std;

class CMDUpdate : public iCMD
{
private:
  iStorage *m_storage = nullptr;

public:
  CMDUpdate(iStorage *storage)
  {
    m_storage = storage;
  }

  void Execute(int arg_c, char *arg_v[])
  {
    if (arg_c != 4)
    {
      cout << "error: invalid input" << endl;
      exit(EXIT_FAILURE);
    }

    int task_id = atoi(arg_v[2]);
    char *task_description = arg_v[3];
    Task task = m_storage->UpdateTaskDescription(task_id, task_description);
    if (task.GetId() < 0)
    {
      cout << "error: unable to update task" << endl;
      exit(EXIT_FAILURE);
    }
    cout << "task updated successfully with task id: " << task_id << endl;
    task.Print();
  }
};