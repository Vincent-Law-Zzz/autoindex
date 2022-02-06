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

int cre_index(std::vector<std::string> files,std::string path)
{
	std::string filename = "autoindex_";
	std::string str;
	std::vector<std::string>::iterator it = files.begin();
	int pos = path.find_last_of('/');
	str = path.substr(pos+1);
	std::string prev_path = path.substr(0,pos);
	pos = prev_path.find_last_of('/');
	if (pos != -1)
		prev_path = prev_path.substr(pos+1);
	filename = filename + str + ".html";
	std::ofstream fout(filename);
	fout << "<!DOCTYPE html>" << std::endl;
	fout << "<head>" << std::endl;
	fout << "<title> Index page </title>" << std::endl;
	fout << "</head>" << std::endl;
	fout << "<html>" << std::endl;
	fout << "<body>" << std::endl;
	if (pos != -1)
		fout << "<a href=autoindex_" + prev_path + ".html>" << 
			" back to ./" +prev_path + "</a></br>" << std::endl;
	while (it != files.end())
	{
		std::cout << *it << std::endl;
		if( isDir(path + "/" + *it))
			fout << "<a href=autoindex_" + *it + ".html>" << *it + "/</a></br>" << std::endl;
		else
			fout << "<a href=\""+ path +"/" + *it +"\"> " << *it << "</a></br>" << std::endl;
		++it;
	}
	fout << "</body>" << std::endl;
	fout << "</html>" << std::endl;
	return 0;
}

int autoindex_cre(std::string path){
	std::string str;
	std::string pth;
	std::vector<std::string> lsf;
	pth = "ls ./" + path + " >> fin";
	system(pth.c_str());
	std::ifstream fin;
	fin.open("fin");
	while (!fin.eof())
	{
		fin>>str;
		if (!fin.eof())
			lsf.push_back(str);
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
	cre_index(lsf,path);
	return 0;
}

int main(){
	autoindex_cre("./src");
	return 0;
}

