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
	std::vector<std::string> lsf = {};
	pth = "ls ./" + path + " >> fin";
	system(pth.c_str());
	std::ifstream fin;
	fin.open("fin");
	std::cout << fin.is_open() << std::endl;
	while (!fin.eof())
	{
		fin>>str;
		lsf.push_back(str);
	}
	fin.close();
	remove("fin");
	return 0;
}

int main(){
	autoindex_cre("src");
	return 0;
}

