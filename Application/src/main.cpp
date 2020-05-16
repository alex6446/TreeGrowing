#include "TreeGrowing/TreeGrowing.h"
#include <cstring>

int main(int argc, char **argv) {

	if (argc <= 1) {
	    World world;
	    while (world.exists()) {
	        world.update();
	        world.draw();
	    }
	} else if (argc == 2) {
		if (!strcmp(argv[1], "editor")) {
			std::cout << "Editor starting..." << std::endl;
			/* Start the editor */
		} else {
			std::cout << "ERROR::UNKNOWN_PARAMETER" << std::endl;
		}
	} else {
		std::cout << "ERROR::TOO_MANY_PARAMETERS" << std::endl;
	}
}