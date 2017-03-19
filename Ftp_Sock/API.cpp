#include"Ftp_client.h"
#include<string>
#include<iostream>
#include"API.h"
using namespace std;

#include"dev\common\commandparameter.h"
#define LOGIN 1
#define QUIT 2
//FTP client = FTP();

API::API()
{
	client = FTP();
}
API::~API()
{
	//delete client;
}
// 主运行函数
void API::clientrun()
{
	cout << "=====================================================" << endl;
	cout << "\t Welcome come to mini FTP client \t" << endl;
	int choice;
	while (1)
	{
		cout << "please input your choice\n1/longin to a ftp server\n2/quit" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			login();
			break;
		case 2:
			break;
		default:
			break;
		}
		if (choice == 2)
			break;
		if (choice != 1 && choice != 2){
			cin.clear();
			cin.ignore();
		}
	}
	cout << "thank you for using my mini ftp client ^ ^" << endl;
	cout << "Bye" << endl;
	Sleep(1000);
	return;
}
// help 函数
void API::help()
{
	cout << "Now you can input the cmd below, including \"CD\", \"RETR\" \"STOR\"" << endl;
	cout << "to back to uper directory just input \"CD ..\"" << endl;
	cout << "to download files, just input \"RETR filename\"" << endl;
	cout << "to upload files just input STOR,and we'll guide you later" << endl;
	cout << "to quit,just input \"quit\"" << endl;
	cout << "to go to the login window just input \" back \"" << endl;
}

string API::cut_space(string &temp)
{
	string str;
	for (int i = 0; i < temp.length(); i++)
	{
		if (temp[i] != ' ')
			str += temp[i];
	}
	return str;
}

string API::get_file_dir(string &temp)
{
	// 删除前后的空格，中间不管
	// 文件的前后可能存在多个空格，删除
	string file_dir;
	int i;
	for (i = 0; i < temp.length(); i++)
	{
		if (temp[i] != ' ')
			break;
	}
	file_dir.assign(temp, i,temp.length() - i);
	if (file_dir[file_dir.length() - 1] != ' ')
		return file_dir;
	else
	{
		for (i = file_dir.length() - 1; i >= 0 && file_dir[i] != ' '; i--);
		file_dir.assign(file_dir, 0, i);
		return  file_dir;
	}
}
void API::login()
{
	// 登录函数
	shared_ptr<usr_psd> ptr(new usr_psd());
	string name;
	string url;
	string password;
	string command;
	char cmd[4096];
	cout << "please input the server ip such as software.cc98.org or 10.10.98.16" << endl;
	cin >> url;  // 去除前后的空格
	url = cut_space(url);
	cout << "please input the user name,if none just input \"anonymous\" " << endl;
	cin >> name;
	cout << "please input the password , if not needed, just input \"none\" " << endl;
	cin >> password;
	ptr->set_paramater(url, name, password);
	client.set_userInfo(ptr);
	if (client.creatSock() == false)   // 加载socket失败
	{
		cout << "create socket failed" << endl;
		return;
	}
	try{
		// 用户名或者密码错误，或者网络不通
		if (client.login() == false) 
		{
			cout << "failed because of the wrong user name or wrong pass word" << endl;
			return;
		}
		else
		{
			if (client.cmd_list() == false)
			{
				cout << "could not fetch the files and directories from the server.please try the LS command!" << endl;
			}
		}
	}
	catch (string &e)
	{
		cout << e << endl;   // 登录失败
		return; 
	}
	cout << "login success,the directory is listed above " << endl;
	help();
	int index;
	string dir;
	string filename;
	getchar();  // 吃掉缓冲区中的换行符
	while (1)
	{
		memset(cmd, 0, sizeof(cmd));
		cin.getline(cmd,200,'\n');
		command = string(cmd);
	//	cout << command;
		if ((index= command.find("CD")) != std::string::npos)   // CD 命令
		{
			command.erase(0, 2);
			if (command.length() == 0)
			{
				cout << "you haven't input a directory" << endl;
				continue;
			}
			dir = get_file_dir(command);
			try{
				client.CD_command(dir);
			}
			catch (string &e)
			{
				cout << e << endl;
			}
			cout << "Directory change to" + client.get_dir() << endl;
		}
		else if ((index = command.find("help")) != std::string::npos)
		{
			help();
		}
		else if ((index = command.find("RETR")) != std::string::npos)
		{
			command.erase(0, 4);
			filename = get_file_dir(command);
			try{
				if (client.get_file(filename))
					cout << "file " << filename + " is downloaded " << endl;
				else
					cout << "file "+ filename+ " not exist" << endl;
			}
			catch (string &e)
			{
				cout << e << endl;
			} 
			
		}
		else if ((index = command.find("quit")) != std::string::npos || 
				(index = command.find("bye")) != std::string::npos)
		{
			cout << "thank you for using my mini ftp client ^ ^" << endl;
			cout << "Bye" << endl;
			Sleep(1000);
			client.~FTP();   // 析构
			exit(0);
		}
		else if ((index = command.find("STOR")) != std::string::npos)
		{
			uploadfiles();
		}
		else if ((index = command.find("ls")) != std::string::npos ||
			(index = command.find("LS")) != std::string::npos)
		{
			system("cls");
			try{
				client.cmd_list();
			}
			catch (string &e)
			{
				cout << e << endl;
			}
			cout << "directory change to" + client.get_dir() << endl;
		}
		else if ((index = command.find("back")) != std::string::npos)
		{
			break;
		}
		else if ((index = command.find("pwd")) != std::string::npos||
			(index = command.find("PWD")) != std::string::npos)
		{
			cout << "current directory is " + client.get_dir() << endl;
		}
		else{
			cout << "the command you input is not legal,if you need help,just input \"help\"" << endl;
		}
	}

}

void API::uploadfiles()   // 上传文件函数
{
	cout << "pleas input the file path correctly,if no more,just input \"end\"" << endl;
	char name[1024];
	client.ClearVector();
	while (1)
	{
		memset(name, 0, sizeof(name));
		cin.getline(name, 1024, '\n');
		if (string(name) == "end")
			break;
		client.add_file_path(string(name));    // 在此之前必须先清空容器
	//	cout << "name: " << name << endl;
	}
	try{
		client.upload_file();
	}
	catch (string &e)
	{
		cout << e << endl;
	}
	cout << "total " << client.getFileCount() << " files have been uploaded" << endl;
}