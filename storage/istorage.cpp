#include <iostream>
#include <vector>

#include "../task/task.cpp"

using namespace std;

class iStorage
{
public:
  virtual Task CreateTask(string task_description) = 0;
  virtual Task UpdateTaskDescription(int task_id, string task_description) = 0;
  virtual Task UpdateTaskStatus(int task_id, TASK_STATUS task_status) = 0;
  virtual Task GetTaskById(int task_id) = 0;
  virtual vector<Task> GetAllTasks() = 0;
  virtual vector<Task> GetTasksByTaskStatus(TASK_STATUS task_status) = 0;
  virtual int DeleteTask(int task_id) = 0;
};