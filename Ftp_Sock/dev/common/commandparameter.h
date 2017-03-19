#pragma once 
#include<iostream>
#include"common.h"

class usr_psd:public basic_pramater
{
public:
	usr_psd();
	~usr_psd();
	void set_paramater(std::string ip,std::string user = "anonymous",std::string psd = "none");
	std::string get_ip();
	std::string get_usr();
	std::string get_psd();
private:
	std::string ip_addr;   // it can be eather url or ip address
	std::string usr_name;  // if no usr name required,just set as anonymous
	std::string psd;   //
	//stri
	/* data */
	
};