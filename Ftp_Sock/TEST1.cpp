#include"API.h"
#include<iostream>
#include<fstream>
using namespace std;
void main()
{
	API api = API();
	api.clientrun();
	api.~API();
}