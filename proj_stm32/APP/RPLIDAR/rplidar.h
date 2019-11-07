#ifndef __RPLIDAR_H
#define __RPLIDAR_H

#include "sys.h"  

//命令列表
#define RPLIDAR_CMD_STOP               0x25
#define RPLIDAR_CMD_SCAN               0x20
#define RPLIDAR_CMD_FORCE_SCAN         0x21
#define RPLIDAR_CMD_RESET              0x40

#define RPLIDAR_CMD_GET_DEVICE_INFO    0x50
#define RPLIDAR_CMD_GET_DEVICE_HEALTH  0x52

#define RPLIDAR_RESP_MEASUREMENT_SYNCBIT        (0x1<<0)
#define RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT  2
#define RPLIDAR_RESP_MEASUREMENT_CHECKBIT       (0x1<<0)
#define RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT    1

void Send_Cmd(u8 Cmd);

extern u8 STOP_FALG;		//停止标志
extern u8 SCAN_FALG;		//

typedef struct _rplidar_response_measurement_node_t 
{
	u8    sync_quality;      // syncbit:1;syncbit_inverse:1;quality:6;
	u16   angle_q6_checkbit; // check_bit:1; angle_q6:15;
	u16   distance_q2;
} rplidar_response_measurement_node_t;				//节点


void Rplidar_BuildGroups(rplidar_response_measurement_node_t *nodebuffer, u16 count);
void Rplidar_SendData(rplidar_response_measurement_node_t *nodebuffer, u16 len, u16 count);
void Rplidar_Manage_Data(rplidar_response_measurement_node_t *nodebuffer, u16 count);




#endif



