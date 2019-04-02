#include "ConfigManager.h"
#include <Windows.h>


ConfigManager::ConfigManager(const char* fileName)
{
	int size = strlen(fileName);
	this->fileName = new char[size + 1];
	strcpy(this->fileName, fileName);

	this->config = new Config();
}

void ConfigManager::ReadConfig()
{
	char* str = new char[256];
	GetPrivateProfileStringA(
		"MainSection",
		"inputPath",
		NULL,
		str,
		256,
		"D://config.ini");
	this->config->inputPath = str;
	/*FILE *file = fopen(this->fileName, "r");

	if (file != NULL)
	{
		char line[MAXBUF];
		int i = 0;

		while (fgets(line, sizeof(line), file) != NULL)
		{
			char *cfline;
			cfline = strstr((char *)line, DELIM);
			cfline = cfline + strlen(DELIM);

			if (i == 0) {
				memcpy(config->inputPath, cfline, strlen(cfline));
			}
			else if (i == 1) {
				memcpy(config->outputPath, cfline, strlen(cfline));
			}

			i++;
		}
		fclose(file);
	}*/
}