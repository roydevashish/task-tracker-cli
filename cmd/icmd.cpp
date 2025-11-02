#pragma once

using namespace std;

class iCMD
{
public:
	virtual void Execute(int arg_c, char *arg_v[]) = 0;
};