
## iSCSI

iSCSI( Internet Small Computer System Interface 互联网小型计算机系统接口)是由IBM 下属的两大研发机构一一加利福尼亚AImaden和以色列Haifa研究中心共同开发的，是一个供硬件设备使用的、可在IP协议上层运行的SCSI指令集，是一种开放的基于IP协议的工业技术标准。该协议可以用TCP/IP对SCSI指令进行封装，使得这些指令能够通过基于IP网络进行传输，从而实现SCSI 和TCP/IP协议的连接。


## 过程
iSCSI的工作过程：当iSCSI主机应用程序发出数据读写请求后，操作系统会生成一个相应的SCSI命令，该SCSI命令在iSCSI initiator层被封装成ISCSI消息包并通过TCP/IP传送到设备侧，设备侧的iSCSI target层会解开iSCSI消息包，得到SCSI命令的内容，然后传送给SCSI设备执行；设备执行SCSI命令后的响应，在经过设备侧iSCSI target层时被封装成ISCSI响应PDU，通过TCP/IP网络传送给主机的ISCSI initiator层，iSCSI initiator会从ISCSI响应PDU里解析出SCSI响应并传送给操作系统，操作系统再响应给应用程序。

## SCSI
小型计算机系统接口（英语：Small Computer System Interface; 简写：SCSI），一种用于计算机和智能设备之间（硬盘、软驱、光驱、打印机、扫描仪等）系统级接口的独立处理器标准。 SCSI是一种智能的通用接口标准。


