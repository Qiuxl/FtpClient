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
	std::string get_file_dir(std::string &temp);  // 删除文件名字前后的空格
	void login();
	void uploadfiles();  // 上传文件函数
private:
	FTP client;
};


