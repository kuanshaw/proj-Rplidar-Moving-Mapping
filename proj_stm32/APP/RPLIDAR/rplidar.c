#include "rplidar.h"
#include "usart3.h"
#include "usart.h"

#define SENDDATA_MODE 1				//1-发送十六进制数据  0-发送角度，距离等数据

u8 STOP_FALG;
u8 SCAN_FALG;

void Send_Cmd(u8 Cmd)
{
		USART3->DR = 0xA5;
		while((USART3->SR & 0x40) == 0);
		USART3->DR = Cmd;
		while((USART3->SR & 0x40) == 0);
}

void Rplidar_BuildGroups(rplidar_response_measurement_node_t *nodebuffer, u16 count)
{
	u16 i, j;
	int dist_q2[2];
  int angle_q6[2];
	
	if(count==0)
	{
		return;
	}
	
	for(i=0, j=0; j<count; j++)
	{
		nodebuffer[j].sync_quality = USART3_RX_BUF[i++];
		
		angle_q6[0] = USART3_RX_BUF[i++];
		angle_q6[1] = USART3_RX_BUF[i++];
		nodebuffer[j].angle_q6_checkbit = (u16)((angle_q6[1]<<8) + angle_q6[0]);	
	
		dist_q2[0] = USART3_RX_BUF[i++];
		dist_q2[1] = USART3_RX_BUF[i++];
		nodebuffer[j].distance_q2 = (u16)((dist_q2[1]<<8) + dist_q2[0]);
	}
}

void Rplidar_SendData(rplidar_response_measurement_node_t *nodebuffer, u16 len, u16 count)
{
	//串口1
	u16 i;
	u16 checkbit;
	u16 syncbit[2];				///!!!!校检位

	if(USART3_RX_BUF[0]==0xa5 && USART3_RX_BUF[1]==0x5a)
	{
		for(i=0; i<len; i++)
		{
			printf("%x", USART3_RX_BUF[i]);
		}
	}
	
	if(SCAN_FALG==1)		//如果开始扫描则打开数据校检
	{
		for(i=0; i<count; i++)
		{
			syncbit[0] = nodebuffer[i].sync_quality & RPLIDAR_RESP_MEASUREMENT_SYNCBIT;
			syncbit[1] = (nodebuffer[i].sync_quality>>1) & RPLIDAR_RESP_MEASUREMENT_SYNCBIT;
			checkbit = nodebuffer[i].angle_q6_checkbit & RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT;

			if(checkbit!=1 || (syncbit[0]!= !syncbit[1]))
			{
				continue;
			}
				
			if((nodebuffer[i].distance_q2==0) || (nodebuffer[i].sync_quality>>RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT)==0)		//如果距离为零或点的质量为零
			{
				continue;
			}
				
			#if SENDDATA_MODE 
				printf("%x", (u8)nodebuffer[i].sync_quality);
				printf("%x", (u16)nodebuffer[i].angle_q6_checkbit);
				printf("%x", (u16)nodebuffer[i].distance_q2);

			#else
				printf("\r\n");
				printf("%d", nodebuffer[i].sync_quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT);
				printf("\r\n");
				printf("%lf", (double)(nodebuffer[i].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) / 64.0f);
				printf("\r\n");
				printf("%lf", (double)nodebuffer[i].distance_q2 / 4.0f);
			#endif
				
			if(STOP_FALG==1)		//停止标志
			{
				break;
			}
		}
	}
}

void Rplidar_Manage_Data(rplidar_response_measurement_node_t *nodebuffer, u16 count)
{
	int i, j;
	u16 checkbit;
	//u16 syncbit[2];		///!!!!校检位
	float expect_angle;		//预设角度
	rplidar_response_measurement_node_t temp;
	
	if(count==0)
	{
		return;
	}
	//角度
	for(i=0; i<count; i++)
	{
		if(nodebuffer[i].distance_q2 == 0)
		{
			continue;
		}
		checkbit = nodebuffer[i].angle_q6_checkbit & RPLIDAR_RESP_MEASUREMENT_CHECKBIT;		//保存校检位
		expect_angle = (nodebuffer[i].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) /64.0;		//角度
		
		if(expect_angle > 360.0f)
		{
			expect_angle -= 360.0f;
			nodebuffer[i].angle_q6_checkbit = ((u16)(expect_angle * 64.0f) << RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) + checkbit; 
		}
	}
	//排序
	for (i=0; i < (count-1); i++)
	{
		for (j = (i+1); j < count; j++)
		{
			if(nodebuffer[i].angle_q6_checkbit > nodebuffer[j].angle_q6_checkbit)			//按角度大小排序
			{
				temp = nodebuffer[i];
				nodebuffer[i] = nodebuffer[j];
				nodebuffer[j] = temp;
			}
		}
	}
}






