#include <iostream>

#include "../cmd/icmd.cpp"
#include "../cmd/cmd_add.cpp"
#include "../cmd/cmd_update.cpp"
#include "../cmd/cmd_delete.cpp"
#include "../cmd/cmd_mark.cpp"
#include "../cmd/cmd_list.cpp"

using namespace std;

class CMDFactory
{
private:
public:
  iCMD *CreateCMD(char *input_cmd)
  {
    iCMD *cmd = nullptr;

    if (!strcmp(input_cmd, "add"))
    {
      CMDAdd cmd_add;
      cmd = &cmd_add;
    }
    else if (!strcmp(input_cmd, "update"))
    {
      CMDUpdate cmd_update;
      cmd = &cmd_update;
    }
    else if (!strcmp(input_cmd, "delete"))
    {
      CMDDelete cmd_delete;
      cmd = &cmd_delete;
    }
    else if (!strcmp(input_cmd, "mark"))
    {
      CMDMark cmd_mark;
      cmd = &cmd_mark;
    }
    else if (!strcmp(input_cmd, "list"))
    {
      CMDList cmd_list;
      cmd = &cmd_list;
    }
    else
    {
      cout << "error: invalid input" << endl;
      exit(EXIT_FAILURE);
    }

    return cmd;
  }
};