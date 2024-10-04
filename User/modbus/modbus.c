#include "modbus.h"

ModbusDevice devices[MAX_DEVICES];

//uint8_t	Modbus_Addr=1;			//从机地址
//uint8_t	Modbus_RX_BUFF[200];	//接收缓冲区2048字节
//uint16_t	Modbus_RX_CNT=0;		//接收计数器
//uint16_t	Modbus_RX_EN=0;			//接收倒计时
//uint8_t	Modbus_FrameFlag=0;		//帧结束标记
//uint8_t	Modbus_TX_FrameFlag=0;	//发送标记
//uint8_t	Modbus_TX_BUFF[200];	//发送缓冲区
//uint8_t	Modbus_RX_LEN=0;		//接收数据长度
//uint16_t	Modbus_TX_EN=0;			//发送倒计时

unsigned int GetCRC16(unsigned char *ptr,  unsigned char len)
{ 
    uint16_t index;
    uint8_t crcl = 0xFF;  //高CRC字节
    uint8_t crch = 0xFF;  //低CRC字节
    uint8_t  TabH[] = {  //CRC高位字节值表
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,  
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  
        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,  
        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,  
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,  
        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,  
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,  
        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,  
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,  
        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,  
        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,  
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,  
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,  
        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,  
        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,  
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,  
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  
        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,  
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  
        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,  
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,  
        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,  
        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  
        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,  
        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40  
    } ;  
    uint8_t TabL[] = {  //CRC低位字节值表
        0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,  
        0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,  
        0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,  
        0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,  
        0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,  
        0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,  
        0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,  
        0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,  
        0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,  
        0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,  
        0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,  
        0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,  
        0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,  
        0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,  
        0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,  
        0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,  
        0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,  
        0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,  
        0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,  
        0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,  
        0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,  
        0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,  
        0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,  
        0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,  
        0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,  
        0x43, 0x83, 0x41, 0x81, 0x80, 0x40  
    } ;
 
    while (len--)  //计算指定长度的CRC
    {
        index = crcl ^ *ptr++;
        crcl = crch ^ TabH[index];
        crch = TabL[index];
    }
    
    return ((crcl<<8) | crch);  
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Modbus寄存器和单片机寄存器的映射关系
//uint16_t	Modbus_IO[100];	//输出开关量寄存器指针(这里使用的是位带操作)

//////////////////////////////////////////////////////////////////////////////
//发送n个字节数据
//buff:发送区首地址
//len：发送的字节数
void Modbus_SendData(uint8_t deviceIndex, uint8_t *buff, uint8_t len)
{
    uint8_t t;
    for(t=0;t<len;t++)    
    {
        while(USART_GetFlagStatus(MODUBS_UART,USART_FLAG_TC)==RESET);
        USART_SendData(MODUBS_UART,buff[t]); 
    }     
    while(USART_GetFlagStatus(MODUBS_UART,USART_FLAG_TC)==RESET);
}

//

//uint8_t biaozhiwei[20],biaozhiwei_jiaobiao=0;
uint8_t biaozhiwei[20];
void shunxuzhixing(uint8_t deviceIndex)
{		
	printf("%d  %d  %d\r\n",biaozhiwei[0],biaozhiwei[1],biaozhiwei[2]);
/*********************设置SPD0和SPD1的值，选择p1.009寄存器的速度值0*********************/
    if(biaozhiwei[0])    
    {
        devices[deviceIndex].is_fasong_16 = 1;
        devices[deviceIndex].addr = 0x040E;   //p4.007地址
        devices[deviceIndex].data = 0x0004;   //设置SPD0为1，SPD1为0
    }    
/*********************设置SPD0和SPD1的值，选择p1.010寄存器的速度值50r/min*********************/
    if(biaozhiwei[1])    
    {
        devices[deviceIndex].is_fasong_16 = 1;
        devices[deviceIndex].addr = 0x040E;   //p4.007地址
        devices[deviceIndex].data = 0x0008;   //设置SPD0为0，SPD1为1
    }    
/***********设置SPD0和SPD1的值，选择p1.011寄存器的速度值-50r/min**********/
    if(biaozhiwei[2])    
    {
        devices[deviceIndex].is_fasong_16 = 1;
        devices[deviceIndex].addr = 0x040E;   //p4.007地址
        devices[deviceIndex].data = 0x000C;   //设置SPD0为1，SPD1为1
    }
/***********设置p3.006值，使DI1和DI2为系统参数P4.007控制**********/
   if(biaozhiwei[3])    
    {
        devices[deviceIndex].is_fasong_16 = 1;
        devices[deviceIndex].addr = 0x030C;   //p3.006地址
        devices[deviceIndex].data = 0x000C;   //设置DI3和DI4为通讯控制
    }
}


/////////////////////////////////////////////////////////////////////////////////////
//Modbus服务程序，用于处理接收到的数据(请在主函数中循环调用)
uint16_t startRegAddr;
uint16_t RegNum;
uint16_t calCRC;
//void Modbus_Service(void)
//{
//	uint16_t recCRC;
//	if(Modbus_FrameFlag==1)
//	{
//		calCRC = GetCRC16(Modbus_RX_BUFF,Modbus_RX_LEN-2);
//		recCRC=Modbus_RX_BUFF[Modbus_RX_LEN-1]|(((uint16_t)Modbus_RX_BUFF[Modbus_RX_LEN-2])<<8);
//		if(calCRC==recCRC)//CRC校验正确
//		{
//			if(Modbus_RX_BUFF[0]==Modbus_Addr)//地址正确
//			{
//				startRegAddr=(((uint16_t)Modbus_RX_BUFF[2])<<8)|Modbus_RX_BUFF[3];//获取寄存器起始地址
//				switch(Modbus_RX_BUFF[1])//根据不同的功能码进行处理
//				{
//					case 03: //读多个寄存器
//					{
////						Modbus_03_Solve();
//						break;
//					}
//					case 06: //写单个寄存器
//					{
////						is_fasong_06=0;
////						biaozhiwei[biaozhiwei_jiaobiao]=0;
////						Modbus_06_Solve();
//						break;
//					}
//					case 16: //写多个寄存器
//					{
////						Modbus_16_Solve();
//						break;
//					}
//					default:break;

//				}
//			}
//		}
//		Modbus_FrameFlag=0;//复位帧结束标志
//		Modbus_RX_CNT=0;//接收计数器清零
//		Modbus_RX_LEN = 0;
//	}
//}

#define qingqiudizhi 1
#define jicunqidizhi 0
#define jicunqichangdu 20
//uint16_t is_fasong_06=0;//是否发送06
//uint16_t jicunqi_06;
//int neirong_06;
//int data;
//int addr;
//int startaddr;
//uint16_t is_fasong_16=0;//是否发送16

//uint16_t Reg_Len;
//uint16_t Reg_Start_Addr;
void fasong03(uint8_t deviceIndex)
{
    devices[deviceIndex].Modbus_TX_FrameFlag=0;
    devices[deviceIndex].Modbus_TX_BUFF[0]=devices[deviceIndex].address;
    devices[deviceIndex].Modbus_TX_BUFF[1]=0x03;
    devices[deviceIndex].Modbus_TX_BUFF[2]=jicunqidizhi/256;
    devices[deviceIndex].Modbus_TX_BUFF[3]=jicunqidizhi%256;
    devices[deviceIndex].Modbus_TX_BUFF[4]=jicunqichangdu/256;
    devices[deviceIndex].Modbus_TX_BUFF[5]=jicunqichangdu%256;
    uint16_t calCRC = GetCRC16(devices[deviceIndex].Modbus_TX_BUFF,6);
    devices[deviceIndex].Modbus_TX_BUFF[6]=calCRC/256;
    devices[deviceIndex].Modbus_TX_BUFF[7]=calCRC%256;
    Modbus_SendData(deviceIndex, devices[deviceIndex].Modbus_TX_BUFF,8);
}
void fasong06(uint8_t deviceIndex, uint16_t jicunqi, uint16_t neirong)
{
    devices[deviceIndex].Modbus_TX_FrameFlag = 0;
    devices[deviceIndex].Modbus_TX_BUFF[0] = devices[deviceIndex].address;
    devices[deviceIndex].Modbus_TX_BUFF[1] = 0x06;
    devices[deviceIndex].Modbus_TX_BUFF[2] = jicunqi / 256;
    devices[deviceIndex].Modbus_TX_BUFF[3] = jicunqi % 256;
    devices[deviceIndex].Modbus_TX_BUFF[4] = neirong / 256;
    devices[deviceIndex].Modbus_TX_BUFF[5] = neirong % 256;
    uint16_t calCRC = GetCRC16(devices[deviceIndex].Modbus_TX_BUFF, 6);
    devices[deviceIndex].Modbus_TX_BUFF[6] = calCRC / 256;
    devices[deviceIndex].Modbus_TX_BUFF[7] = calCRC % 256;
    Modbus_SendData(deviceIndex, devices[deviceIndex].Modbus_TX_BUFF, 8);
}

void MODBUS_MASTER_SEND_16(uint8_t deviceIndex, uint16_t Reg_Start_Addr, uint16_t Reg_Len, uint16_t data)
{
    devices[deviceIndex].Modbus_TX_FrameFlag = 0;
    devices[deviceIndex].Modbus_TX_BUFF[0] = devices[deviceIndex].address;
    devices[deviceIndex].Modbus_TX_BUFF[1] = 0x10;
    devices[deviceIndex].Modbus_TX_BUFF[2] = Reg_Start_Addr / 256;
    devices[deviceIndex].Modbus_TX_BUFF[3] = Reg_Start_Addr % 256;
    devices[deviceIndex].Modbus_TX_BUFF[4] = Reg_Len / 256;
    devices[deviceIndex].Modbus_TX_BUFF[5] = Reg_Len % 256;
    devices[deviceIndex].Modbus_TX_BUFF[6] = Reg_Len * 2;
    devices[deviceIndex].Modbus_TX_BUFF[7] = data / 256;
    devices[deviceIndex].Modbus_TX_BUFF[8] = data % 256;
    devices[deviceIndex].Modbus_TX_BUFF[9] = 0;
    devices[deviceIndex].Modbus_TX_BUFF[10] = 0;

    uint16_t calCRC = GetCRC16(devices[deviceIndex].Modbus_TX_BUFF, 11);
    devices[deviceIndex].Modbus_TX_BUFF[11] = calCRC / 256;
    devices[deviceIndex].Modbus_TX_BUFF[12] = calCRC % 256;
    Modbus_SendData(deviceIndex, devices[deviceIndex].Modbus_TX_BUFF, 13);
}


void Modbus_Service_SEND(uint8_t deviceIndex)
{
    shunxuzhixing(deviceIndex);
    if(devices[deviceIndex].is_fasong_06)
    {
        fasong06(deviceIndex, devices[deviceIndex].jicunqi_06, devices[deviceIndex].neirong_06);
        devices[deviceIndex].is_fasong_06 = 0;
    }
    else if(devices[deviceIndex].is_fasong_16) 
    {
        MODBUS_MASTER_SEND_16(deviceIndex, devices[deviceIndex].addr, 2, devices[deviceIndex].data);
        devices[deviceIndex].is_fasong_16 = 0;
    }
}
void Modbus_03_Solve(uint8_t deviceIndex)
{
    uint8_t i;    
    uint16_t RegNum = (uint16_t)devices[deviceIndex].Modbus_RX_BUFF[2];
    
    for(i=0;i<RegNum;i+=2)
    {
        devices[deviceIndex].Modbus_IO[jicunqidizhi+i/2]=devices[deviceIndex].Modbus_RX_BUFF[3+i]<<8|devices[deviceIndex].Modbus_RX_BUFF[4+i];
    }
}

void Modbus_06_Solve(uint8_t deviceIndex)
{
    uint16_t startRegAddr = (((uint16_t)devices[deviceIndex].Modbus_RX_BUFF[2])<<8)|devices[deviceIndex].Modbus_RX_BUFF[3];
    devices[deviceIndex].Modbus_IO[startRegAddr]=devices[deviceIndex].Modbus_RX_BUFF[4]<<8;
    devices[deviceIndex].Modbus_IO[startRegAddr]|=((uint16_t)devices[deviceIndex].Modbus_RX_BUFF[5]);

    for(int i=0; i<6; i++) {
        devices[deviceIndex].Modbus_TX_BUFF[i] = devices[deviceIndex].Modbus_RX_BUFF[i];
    }

    uint16_t calCRC=GetCRC16(devices[deviceIndex].Modbus_TX_BUFF,6);
    devices[deviceIndex].Modbus_TX_BUFF[6]=(calCRC>>8)&0xFF;
    devices[deviceIndex].Modbus_TX_BUFF[7]=(calCRC)&0xFF;
    Modbus_SendData(deviceIndex, devices[deviceIndex].Modbus_TX_BUFF,8);
}

void Modbus_16_Solve(uint8_t deviceIndex)
{
    uint8_t i;
    uint16_t startRegAddr = (((uint16_t)devices[deviceIndex].Modbus_RX_BUFF[2])<<8)|devices[deviceIndex].Modbus_RX_BUFF[3];
    uint16_t RegNum = (((uint16_t)devices[deviceIndex].Modbus_RX_BUFF[4])<<8)|((devices[deviceIndex].Modbus_RX_BUFF[5]));
    if((startRegAddr+RegNum)<5000)
    {
        for(i=0;i<RegNum;i++)
        {
            devices[deviceIndex].Modbus_IO[startRegAddr+i]=devices[deviceIndex].Modbus_RX_BUFF[7+i*2]<<8;
            devices[deviceIndex].Modbus_IO[startRegAddr+i]|=((uint16_t)devices[deviceIndex].Modbus_RX_BUFF[8+i*2]);
        }

        for(i=0; i<11; i++) {
            devices[deviceIndex].Modbus_TX_BUFF[i] = devices[deviceIndex].Modbus_RX_BUFF[i];
        }

        uint16_t calCRC=GetCRC16(devices[deviceIndex].Modbus_TX_BUFF,11);
        devices[deviceIndex].Modbus_TX_BUFF[11]=(calCRC>>8)&0xFF;
        devices[deviceIndex].Modbus_TX_BUFF[12]=(calCRC)&0xFF;
        Modbus_SendData(deviceIndex, devices[deviceIndex].Modbus_TX_BUFF,13);
    }
    else
    {
        devices[deviceIndex].Modbus_TX_BUFF[0]=devices[deviceIndex].Modbus_RX_BUFF[0];
        devices[deviceIndex].Modbus_TX_BUFF[1]=devices[deviceIndex].Modbus_RX_BUFF[1]|0x80;
        devices[deviceIndex].Modbus_TX_BUFF[2]=0x02;
        Modbus_SendData(deviceIndex, devices[deviceIndex].Modbus_TX_BUFF,3);
    }
}

void Rec_Buf_clean(uint8_t *point, uint8_t len)
{
    int p;
    for (p=0;p<len;p++)
    {
        point[p]=0;
    }
}

void Modbus_zubao(uint8_t deviceIndex, uint8_t Res)
{
    if(devices[deviceIndex].Modbus_RX_CNT<200)
    {
        devices[deviceIndex].Modbus_RX_BUFF[devices[deviceIndex].Modbus_RX_CNT++]=Res;
        devices[deviceIndex].Modbus_RX_EN = 0;
    }
    else
    {
        Rec_Buf_clean(devices[deviceIndex].Modbus_RX_BUFF,200);
        devices[deviceIndex].Modbus_RX_CNT = 0;
    }
}

void Modbus_Is_jieshou(uint8_t deviceIndex)
{
    devices[deviceIndex].Modbus_RX_EN++;
    if((devices[deviceIndex].Modbus_RX_EN>10000) &&(devices[deviceIndex].Modbus_RX_CNT!=0))
    {
        devices[deviceIndex].Modbus_RX_LEN = devices[deviceIndex].Modbus_RX_CNT;
        devices[deviceIndex].Modbus_FrameFlag=1;
        devices[deviceIndex].Modbus_RX_EN = 0;
    }
}

void Modbus_Is_fasong(uint8_t deviceIndex)
{
    devices[deviceIndex].Modbus_TX_EN++;
    if(devices[deviceIndex].Modbus_TX_EN>10000)
    {
        devices[deviceIndex].Modbus_TX_EN=0;
        devices[deviceIndex].Modbus_TX_FrameFlag=1;
    }
}

//////Modbus功能码03处理程序///////////////////////////////////////////////////////////////////////////////////////已验证程序OK
//////读保持寄存器
//void Modbus_03_Solve(void)
//{
//	uint8_t i;	

//	RegNum= (uint16_t)Modbus_RX_BUFF[2];//获取寄存器数量
//	
//	for(i=0;i<RegNum;i+=2)
//	{
//		Modbus_IO[jicunqidizhi+i/2]=Modbus_RX_BUFF[3+i]<<8|Modbus_RX_BUFF[4+i];
//	}
//}

//////Modbus功能码06处理程序   //////////////////////////////////////////////////////////////////////////////////已验证程序OK
//////写单个保持寄存器
//void Modbus_06_Solve(void)
//{
//	Modbus_IO[startRegAddr]=Modbus_RX_BUFF[4]<<8;//高字节在前                    ////////修改为高字节在前，低字节在后
//	Modbus_IO[startRegAddr]|=((uint16_t)Modbus_RX_BUFF[5]);//低字节在后

//	Modbus_TX_BUFF[0]=Modbus_RX_BUFF[0];
//	Modbus_TX_BUFF[1]=Modbus_RX_BUFF[1];
//	Modbus_TX_BUFF[2]=Modbus_RX_BUFF[2];
//	Modbus_TX_BUFF[3]=Modbus_RX_BUFF[3];
//	Modbus_TX_BUFF[4]=Modbus_RX_BUFF[4];
//	Modbus_TX_BUFF[5]=Modbus_RX_BUFF[5];

//	calCRC=GetCRC16(Modbus_TX_BUFF,6);
//	Modbus_TX_BUFF[6]=(calCRC>>8)&0xFF;
//	Modbus_TX_BUFF[7]=(calCRC)&0xFF;
//	Modbus_SendData(Modbus_TX_BUFF,8);
//}

//////Modbus功能码16处理程序 /////////////////////////////////////////////////////////////////////////////////////////////////已验证程序OK
//////写多个保持寄存器
//void Modbus_16_Solve(void)
//{
//	uint8_t i;
//	RegNum= (((uint16_t)Modbus_RX_BUFF[4])<<8)|((Modbus_RX_BUFF[5]));//获取寄存器数量
//	if((Reg_Start_Addr+Reg_Len)<5000)//寄存器地址+数量在范围内
//	{
//		for(i=0;i<RegNum;i++)
//		{
//			Modbus_IO[startRegAddr+i]=Modbus_RX_BUFF[7+i*2]<<8; //低字节在前                 /////// 低字节在前，高字节在后正常
//			Modbus_IO[startRegAddr+i]|=((uint16_t)Modbus_RX_BUFF[8+i*2]); //高字节在后
//		}

//		Modbus_TX_BUFF[0]=Modbus_RX_BUFF[0];
//		Modbus_TX_BUFF[1]=Modbus_RX_BUFF[1];
//		Modbus_TX_BUFF[2]=Modbus_RX_BUFF[2];
//		Modbus_TX_BUFF[3]=Modbus_RX_BUFF[3];
//		Modbus_TX_BUFF[4]=Modbus_RX_BUFF[4];
//		Modbus_TX_BUFF[5]=Modbus_RX_BUFF[5];
//		Modbus_TX_BUFF[6]=Modbus_RX_BUFF[6];
//		Modbus_TX_BUFF[7]=Modbus_RX_BUFF[7];
//		Modbus_TX_BUFF[8]=Modbus_RX_BUFF[8];
//		Modbus_TX_BUFF[9]=Modbus_RX_BUFF[9];
//		Modbus_TX_BUFF[10]=Modbus_RX_BUFF[10];


//		calCRC=GetCRC16(Modbus_TX_BUFF,11);
//		Modbus_TX_BUFF[11]=(calCRC>>8)&0xFF;
//		Modbus_TX_BUFF[12]=(calCRC)&0xFF;
//		Modbus_SendData(Modbus_TX_BUFF,13);
//	}
//	else//寄存器地址+数量超出范围
//	{
//		Modbus_TX_BUFF[0]=Modbus_RX_BUFF[0];
//		Modbus_TX_BUFF[1]=Modbus_RX_BUFF[1]|0x80;
//		Modbus_TX_BUFF[2]=0x02; //异常码
//		Modbus_SendData(Modbus_TX_BUFF,3);
//	}
//}

//void Rec_Buf_clean(uint8_t *point,uint8_t len ) //清空数组
//{
//	int p;
//	for (p=0;p<len;p++)
//	{
//		point[p]=0;
//	}
//}

////用于串口接收中断，进行组包
//void Modbus_zubao(uint8_t Res)
//{
//	if(Modbus_RX_CNT<10000)
//	{
//		Modbus_RX_BUFF[Modbus_RX_CNT++]=Res;
//		Modbus_RX_EN = 0;
//	}
//	else
//	{
//		Rec_Buf_clean(Modbus_RX_BUFF,200);
//		
//		Modbus_RX_CNT = 0;
//	}
//}

//用于定时器，判断是否接收完成
//#define Modbus_RX_EN_MAX 10000
//void Modbus_Is_jieshou(void)
//{
//	Modbus_RX_EN++;
//	if((Modbus_RX_EN>Modbus_RX_EN_MAX) &&(Modbus_RX_CNT!=0))
//	{
//		Modbus_RX_LEN = Modbus_RX_CNT;
//		Modbus_FrameFlag=1;//置位帧结束标记
//		Modbus_RX_EN = 0;
//	}
//}

//#define Modbus_TX_EN_MAX 10000
//void Modbus_Is_fasong(void)
//{
//	Modbus_TX_EN++;
//	if(Modbus_TX_EN>Modbus_TX_EN_MAX)
//	{
//		Modbus_TX_EN=0;
//		Modbus_TX_FrameFlag=1;//置位帧结束标记
//	}
//}
