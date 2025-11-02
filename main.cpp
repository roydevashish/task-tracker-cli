#include <iostream>

#include "cmd_factory/cmd_factory.cpp"

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "error: invalid input" << endl;
    exit(EXIT_FAILURE);
  }

  char *input_cmd = argv[1];

  CMDFactory cmd_factory;
  iCMD *cmd = cmd_factory.CreateCMD(input_cmd);
  if (cmd == nullptr)
  {
    exit(EXIT_FAILURE);
  }
  cmd->Execute(argc, argv);

  return 0;
}