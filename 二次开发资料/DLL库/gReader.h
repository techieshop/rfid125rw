#ifndef GREADER_H
#define GREADER_H

#if !defined(API_EXPORTS)
#define DECLSPEC __declspec(dllimport)
#else
#define DECLSPEC
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define LED_OFF    0
#define LED_RED    1
#define LED_GREEN  2
#define LED_YELLOW 3

//一台机器最多可以连接10个读写器

//**********************************************************************************************************************************

//设置读写器函数

//**********************************************************************************************************************************

//连接读写器
//参数：port->串口号，例："com1"
//      addr->读卡器地址，这个数值由程序员指定，相当于给读卡器一个身份标识，范围0~9，
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回：成功true，失败返回false
DECLSPEC BOOL WINAPI gConnReader(char *port, int addr=0);


//断开连接
//参数：addr->读卡器地址，必须与 gConnReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回true，失败返回false
DECLSPEC BOOL WINAPI gDiscReader(int addr=0);


//设置读写器波特率
//参数：baud->标准波特率
//      addr->读卡器地址，必须与 gConnReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回true，失败返回false
DECLSPEC BOOL WINAPI gSetBaud(DWORD baud, int addr=0);

//设置串口等待时间
//参数：time->等待时间，单位ms
//      addr->读卡器地址，必须与 gConnReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回true，失败返回false
DECLSPEC BOOL WINAPI gSetTimeOut(int time, int addr=0);


//获取读写器型号
//参数：model->返回读写器型号
//      len  ->返回型号长度
//      addr ->读卡器地址，必须与 gConnReader 函数的保持一致；
//             缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回true，失败返回false
DECLSPEC BOOL WINAPI gGetModel(BYTE *model, int *len, int addr=0);


//设置蜂鸣
//参数：time->蜂鸣时间，单位5MS
//      addr->读卡器地址，必须与 gConnReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回true，失败返回false
DECLSPEC BOOL WINAPI gSetBeep(BYTE time, int addr=0);


//设置LED颜色
//参数：color->0x00 = 熄灭
//             0x01 = 红色
//             0x02 = 绿色
//             0x03 = 黄色
//      addr->读卡器地址，必须与 gConnReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回true，失败返回false
DECLSPEC BOOL WINAPI gSetLED(BYTE color, int addr=0);


//读EM4100卡
//参数：ID ->返回卡号，5 BYTES
//      addr->读卡器地址，必须与 gConnReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//读卡成功返回1，读卡失败返回2，通信失败返回3
DECLSPEC int WINAPI gReadEM4100(BYTE *ID, int addr=0);

//直通函数
//参数：cmd     ->数据包命令
//      para    ->数据包参数
//      para_len->数据包参数长度
//      resp    ->返回数据包数据
//      resp_len->返回数据包数据长度
//      addr->读卡器地址，必须与 gConnReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//操作成功返回1，操作失败返回2，通信失败返回3
DECLSPEC int WINAPI gDirecteAccess(WORD cmd, BYTE *para, int para_len, BYTE *resp, int *resp_len, int addr=0);



//把 ATA5567 格式化成 EM4100 卡
//参数：ID  ->EM4100卡号，5 BYTES
//      lock->锁卡，0为不锁，否则锁卡
//      addr->读卡器地址，必须与 gConnReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回true表示与读写器通信成功，否则返回false，
//可以调用 gReadEM4100 函数验证是否写卡成功
DECLSPEC BOOL WINAPI ATA_WriteEM4100(BYTE *ID, BYTE lock, int addr=0);


//把 EM4305 格式化成 EM4100 卡
//参数：ID  ->EM4100卡号，5 BYTES
//      addr->读卡器地址，必须与 gConnReader 函数的保持一致；
//      lock->0为不锁，否则锁卡
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回0写卡成功，返回1写卡失败，返回2读写串口失败
DECLSPEC BOOL WINAPI EM_WriteEM4100(BYTE *ID, BYTE lock, int addr=0);


#ifdef __cplusplus
}
#endif

#endif