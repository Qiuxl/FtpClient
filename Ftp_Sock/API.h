#pragma once
#include<iostream>
#include"Ftp_client.h"
class API
{
public:
	API();
	~API();
	void clientrun();
protected: 
	void help();
	std::string cut_space(std::string &temp); 
	std::string get_file_dir(std::string &temp);  // ɾ���ļ�����ǰ��Ŀո�
	void login();
	void uploadfiles();  // �ϴ��ļ�����
private:
	FTP client;
};


