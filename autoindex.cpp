#include "autoindex.hpp"
#include <fstream>
#include <stdio.h>
#include <string> 
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>

bool isDir(std::string name)
{
	struct stat buf;
	lstat(name.c_str(),&buf);
	if (S_ISDIR(buf.st_mode))
		return true;
	else
		return false;
}

int autoindex_cre(std::string path){
	std::string str;
	std::string pth;
	std::vector<std::string> lsf;
	pth = "ls ./" + path + " >> fin";
	system(pth.c_str());
	std::ifstream fin;
	fin.open("fin");
	std::cout << "this " << path << std::endl;
	while (!fin.eof())
	{
		fin>>str;
		if (!fin.eof())
		{
			std::cout << str << std::endl;
			lsf.push_back(str);
		}
	}
	fin.close();
	remove("fin");
	std::vector<std::string>::iterator it = lsf.begin();
	while(it != lsf.end())
    	{
		if (isDir(path + "/" + (*it)))
        		autoindex_cre(path + "/" + (*it));
        	++it;
    	}
	return 0;
}

int main(){
	autoindex_cre("src");
	return 0;
}

