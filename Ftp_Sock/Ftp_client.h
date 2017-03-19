#pragma once
#include<winsock.h>
#include<iostream>
#include<vector>
#include"./dev/common/commandparameter.h"
class FTP
{
public:
	FTP();
	~FTP();
	void set_userInfo(std::shared_ptr<usr_psd> &temp);
	bool creatSock();
	bool login();
	bool CD_command(std::string &directory);
	bool get_file(std::string filename);
	bool upload_file();    // upload files,not directories
	int send_command(std::string &s);
	bool cmd_list();   //get the current context of the directory 
	bool open_datatrs();   // open the data transfer mode 
	bool check_response(char a);   //use to check whether the response is right or not
	bool check_sock_alive(SOCKET &clientSocket);  // to check whether the socket is connected or not
	void add_file_path(std::string &path);
	std::string get_dir();
	inline int getFileCount()
	{
		return filecount;
	}
	inline void ClearVector()
	{
		std::vector<std::string>().swap(filename);
		std::vector<std::string>().swap(filepath);
	}
protected:

	void getfileName();   //从文件路径容器中获得文件名字
	void get_port_from_pasv(std::string &s, int &p1, int &p2);
	int GetFileData(const char *file_path);    // GET the size of file given 

private:
	char recbuffer[4096];
	char sendbuff[4096];
	char ip[30];  // 用于存放ip地址
	int filecount;
	std::vector<std::string> filepath;
	std::vector<std::string> filename;
	std::string CurrentDir;    //用于存放当前的目录
	SOCKET sock_ctrl;  //for transfer control commands
	SOCKET sock_data;  // for data transfer
	std::shared_ptr<usr_psd> info;
};
