#include "NetFT.h"
#include <iostream>

int main(int argc, char** argv) {
	RESPONSE resp;
	int i;
	const char* AXES[] = { "Fx", "Fy", "Fz", "Tx", "Ty", "Tz" };

	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " IPADDRESS" << std::endl;
		return -1;
	}

	try {
		NetFT netft(argv[1]);
		netft.communicate(resp);

		/* Output the response data. */
		std::cout << "Status: 0x" << std::hex << resp.status << std::endl;
		for (i = 0; i < 6; i++) {
			std::cout << AXES[i] << ": " << std::dec << resp.FTData[i] << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}
