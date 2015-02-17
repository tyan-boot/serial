#串口操作类

```c++
#include "serial.h"

Serial com; //初始化一个对象
com.openCom("COM1");  //打开COM1
com.setTimeOut(); //设置超时信息
com.setBCD(); //设置BCD信息

char tmp[1];
com.ReadCom(tmp,1); //从缓冲区读取一字节到tmp
com.WriteCom(tmp,10;  //写入一字节
int i = com.num_of_input(); //得到缓冲区数量

//如需进行其他操作，使用
com.hCom
//来引用已打开的串口

com.close() //关闭串口
```

##如需获得更多帮助，请联系tyan-boot@outlook.com
