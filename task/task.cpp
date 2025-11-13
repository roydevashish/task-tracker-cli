#pragma once
#include <iostream>

#include "task_status.cpp"

using namespace std;

class Task
{
private:
  int m_id;
  char *m_description;
  TASK_STATUS m_status;
  char m_created_at[20];
  char m_updated_at[20];

public:
  Task()
  {
    m_id = -1;
    strcpy(m_description, "default description");
    m_status = DONE;
    strcpy(m_created_at, "0000-00-00 00:00:00");
    strcpy(m_updated_at, "0000-00-00 00:00:00");
  }

  Task(int task_id, char *task_description, TASK_STATUS task_status, char *created_at, char *updated_at)
  {
    m_id = task_id;
    strcpy(m_description, task_description);
    m_status = task_status;
    strcpy(m_created_at, created_at);
    strcpy(m_updated_at, updated_at);
  }

  Task(int task_id, char *task_description, TASK_STATUS task_status)
  {
    m_id = task_id;
    strcpy(m_description, task_description);
    m_status = task_status;
    strcpy(m_created_at, "0000-00-00 00:00:00");
    strcpy(m_updated_at, "0000-00-00 00:00:00");
  }

  int SetTaskId(int task_id)
  {
    m_id = task_id;
    return 0;
  }

  int SetTaskDescription(char *task_description)
  {
    strcpy(m_description, task_description);
    return 0;
  }

  int SetTaskStatus(TASK_STATUS task_status)
  {
    m_status = task_status;
    return 0;
  }

  int SetCreatedAt(char *task_created_at)
  {
    strcpy(m_created_at, task_created_at);
    return 0;
  }

  int SetUpdatedAt(char *task_updated_at)
  {
    strcpy(m_updated_at, task_updated_at);
    return 0;
  }

  int Set(int task_id, char *task_description, TASK_STATUS task_status, char *created_at, char *updated_at)
  {
    m_id = task_id;
    strcpy(m_description, task_description);
    m_status = task_status;
    strcpy(m_created_at, created_at);
    strcpy(m_updated_at, updated_at);
    return 0;
  }

  void Print()
  {
    cout << "id: " << m_id << endl;
    cout << "description: " << m_description << endl;
    cout << "status: " << TaskStatusEnumToString(m_status) << endl;
    cout << "created at: " << m_created_at << " \t" << "updated at: " << m_updated_at << endl
         << endl;
  }

  int GetId()
  {
    return m_id;
  }
};