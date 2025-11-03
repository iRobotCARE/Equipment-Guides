#include "NetFT.h"
#include <iostream>

project::project(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// 其他初始化代码


	connect(ui.pushButton_28, SIGNAL(clicked()), this, SLOT(ATI_connect()), Qt::UniqueConnection);//ATI连接


}

//采用ATI力传感器对机器人末端力进行获取
void project::ATI_connect()
{
	RESPONSE resp;
	int i;
	const char* AXES[] = { "Fx", "Fy", "Fz", "Tx", "Ty", "Tz" };

	const char* ip_address = "192.168.1.1"; // IP 地址为固定值

	try {
		NetFT netft(ip_address);
		netft.communicate(resp);

		std::cout << "Status: 0x" << std::hex << resp.status << std::endl;
		std::cout << std::fixed << std::setprecision(6); // 设置输出格式为固定小数点，并显示6位小数

		std::cout << "Status: 0x" << std::hex << resp.status << std::endl;
		for (i = 0; i < 6; i++) {
			std::cout << AXES[i] << ": " << std::dec << resp.FTData[i] / 1000000.0 << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
