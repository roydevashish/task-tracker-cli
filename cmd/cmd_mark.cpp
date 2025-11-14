#include <iostream>

#include "icmd.cpp"

using namespace std;

class CMDMark : public iCMD
{
private:
  iStorage *m_storage = nullptr;

public:
  CMDMark(iStorage *storage)
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

    TASK_STATUS task_status = TaskStatusStringToEnum(arg_v[2]);
    int task_id = atoi(arg_v[3]);
    Task task = m_storage->UpdateTaskStatus(task_id, task_status);
		if (task.GetId() < 0)
		{
      cout << "error: unable to mark task" << endl;
			exit(EXIT_FAILURE);
		}
    cout << "task marked: " << task_status << " successfully with task id: " << task_id << endl;
    task.Print();
  }
};