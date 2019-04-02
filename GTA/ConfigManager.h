#pragma once
#ifndef __CONFIG_MANAGER_H__

#define _CRT_SECURE_NO_WARNINGS
#define __CONFIG_MANAGER_H__

#include <iostream>
#include <fstream>
#include <algorithm>

#define MAXBUF 1024 
#define DELIM "="

struct Config {
	char* inputPath;
	char* outputPath;
};


class ConfigManager
{
public:
	Config* config;
	char* fileName;

	ConfigManager(const char* fileName);
	
	void ReadConfig();
};


#endif // !__CONFIG_MANAGER_H__