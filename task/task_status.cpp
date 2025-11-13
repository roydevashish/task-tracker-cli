#pragma once
#include <iostream>

using namespace std;

enum TASK_STATUS
{
  TODO,
  INPROGRESS,
  DONE
};

const char *TaskStatusEnumToString(TASK_STATUS task_status)
{
  switch (task_status)
  {
  case TODO:
    return "todo";
  case INPROGRESS:
    return "in-progress";
  case DONE:
    return "done";
  default:
    exit(EXIT_FAILURE);
  }
}

TASK_STATUS TaskStatusStringToEnum(char *task_status)
{
  if (!strcmp(task_status, "todo"))
  {
    return TODO;
  }
  else if (!strcmp(task_status, "in-progress"))
  {
    return INPROGRESS;
  }
  if (!strcmp(task_status, "done"))
  {
    return DONE;
  }

  cout << "error: invalid input" << endl;
  exit(EXIT_FAILURE);
}

TASK_STATUS TaskStatusIntToEnum(int task_status)
{
  switch (task_status)
  {
  case TODO:
    return TODO;
  case INPROGRESS:
    return INPROGRESS;
  case DONE:
    return DONE;
  default:
    exit(EXIT_FAILURE);
  }
}