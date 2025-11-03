## QTM与电脑的ip设置不匹配
**问题如下：**

![image](https://github.com/iRobotCARE/Equipment-Guides/blob/main/Motion-Capture-Qualysis/TCP-IP%20interface%20not%20found.png)


**解决方案：**

进入Setting中，修改镜头系统所设置的ip，此时电脑的ip设置不是`192.168.254.1`

![](https://github.com/iRobotCARE/Equipment-Guides/blob/main/Motion-Capture-Qualysis/TCP-IP%20setting.png)

## 有线网络通信(DHCP)
动捕摄像头和电脑设备连接在一个路由下的局域网，确保路由下没有其他设备或者其他设备也设置为同一局域网。这样可以减少动捕系统的网络问题

## 导出相机的参数
在QTM中`文件`->`导出`->`json`，只选中`相机`项，可以获得相机相对于标定坐标系的齐次变换矩阵

## 导出视频
在QTM中，使用视频模式先录制，然后直接在想要的那个相机视图上右键导出
