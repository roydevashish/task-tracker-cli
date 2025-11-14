#include <iostream>

#include "icmd.cpp"

using namespace std;

class CMDDelete : public iCMD
{
private:
  iStorage *m_storage = nullptr;

public:
  CMDDelete(iStorage *storage)
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

    int task_id = atoi(arg_v[2]);
    int deleted_task_id = m_storage->DeleteTask(task_id);
		if (deleted_task_id < 0)
		{
      cout << "error: unable to delete task" << endl;
			exit(EXIT_FAILURE);
		}
    cout << "task deleted successfully with task id: " << task_id << endl;
  }
};