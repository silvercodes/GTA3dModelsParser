#include "ConfigManager.h"
#include "Reader.h"


void main()
{
	/*Reader reader = Reader();
	reader.readDFF("D://MyProjects//GTA//models//mp5lng.dff");*/

	ConfigManager manager = ConfigManager("D://config.txt");
	manager.ReadConfig();
}