#ifndef XBUFFER_H
#define XBUFFER_H
#include <stdio.h>
#include <string.h>
#include "ZPort.h"

#define MINIMIZE_BLOCK 32						//最小块大小为32字节

//进行性能统计的类
class ZPerf {
public:
	unsigned long packet_number;				//发送/接收的数据包总数
	unsigned long remain_number;				//当前仍然在缓冲区的数目

	int max_interval;							//包之间的最大时间间隔
	int min_interval;							//包之间的最小时间间隔
	unsigned long tick_count;					//开始的时间

	short max_size;								//包的最大大小
	short min_size;								//包的最小大小
	INT64 total_size;					//总大小
	unsigned long remain_size; 
	ZPerf();
	void start();
	void stop();
	void perfPacket(int size);
	void useBuffer(int size);
	void freeBuffer(int size);
};

class ZBuffer {
public:
	char *send_buffer;							//实际使用的发送缓冲区
	char *receive_buffer;						//实际使用的接收缓冲区
	long max_send;								//发送缓冲区的大小
	long max_receive;							//接收缓冲区的大小

	char *receive_ptr;							//当前接收数据的指针
	long receive_size;							//接收数据的大小

	char *send_ptr;								//当前发送数据的指针
	long send_size;								//发送数据的大小
	char *packet_ptr;							//当前数据包的开始指针
	unsigned short packet_size;					//当前数据包的大小

	ZPerf* pRecvPerf;
	ZPerf* pSendPerf;

public:
	ZBuffer(long the_max_send, long the_max_receive) {
		pRecvPerf = NULL;
		pSendPerf = NULL;
		send_buffer = new char[the_max_send];
		if(send_buffer) max_send = the_max_send;
		else max_send = 0;
		receive_buffer = new char[the_max_receive];
		if(receive_buffer) max_receive = the_max_receive;
		else max_receive = 0;
		//recv_buffer = 0;
		//recv_buffer_size = 0;
//		pack_buffer = 0;
//		pack_buffer_size = 0;
		if (pRecvPerf)
			pRecvPerf->useBuffer(the_max_receive);
		if (pSendPerf)
			pSendPerf->useBuffer(the_max_send);
		clear();
	}
	virtual ~ZBuffer() {
		if(send_buffer) delete[] send_buffer;
		if(receive_buffer) delete[] receive_buffer;
		if (pRecvPerf)
		{
			pRecvPerf->freeBuffer(max_receive);
		}
		if (pSendPerf)
		{
			pSendPerf->freeBuffer(max_send);
		}
	}

//下面是对外提供的接口
	void stopPerf() {
		pRecvPerf = NULL;
		pSendPerf = NULL;
	}

	void startPerf(ZPerf* pRP, ZPerf* pSP) {
		pRecvPerf = pRP;
		pSendPerf = pSP;
	}

//获取可用的接收数据的缓冲区
	char *getReceiveBuffer(int &size) {
		if(receive_size + MINIMIZE_BLOCK > max_receive) {
//超出最大缓冲区，关闭连接
			return NULL;
		}
		if (receive_size < 0)
		{
			printf("receive size Negative ?!!!!\n");
			receive_size = 0;
			receive_ptr = receive_buffer;
			return NULL;
		}
		if(receive_ptr + receive_size + MINIMIZE_BLOCK > receive_buffer + max_receive) {		//尾部数据不够了
			memmove(receive_buffer, receive_ptr, receive_size);
			receive_ptr = receive_buffer;
		}
		size = max_receive - (receive_ptr - receive_buffer) - receive_size;
		return receive_ptr + receive_size;
	}
	void receiveData(int size) {
		receive_size += size;
		if (pRecvPerf)
		{
			pRecvPerf->perfPacket(size);
			pRecvPerf->packet_number++;
		}
	}
	const char *getPacket(int &size) {
		if(receive_size < sizeof(unsigned short)) return NULL;
		size = *(unsigned short *)receive_ptr;
		if (size < sizeof(unsigned short))
		{
			printf("Unexpected recv buffer reset (size = %d)\n", size);
			receive_ptr = receive_buffer;
			receive_size = 0;
			return NULL;
		}

		if(receive_size >= size) {
			const char *result = (const char *)receive_ptr + sizeof(unsigned short);
			receive_ptr += size;
			receive_size -= size;
			size -= sizeof(unsigned short);
			return result;
		}
		return NULL;
	}

	void clear() {
		receive_ptr = receive_buffer;
		receive_size = 0;

		packet_ptr = send_ptr = send_buffer;
		*(unsigned short *)send_ptr = 0;
		send_size = 0;
		packet_size = 0;
	}

//发送数据的接口分成两个函数，一个是获取当前发送的缓冲区和长度，另外一个是从缓冲区清除指定大小的数据
	char *getSendData(int &size) {
		size = packet_ptr - send_ptr;
		if(size) {
			return send_ptr;
		}
		else {
			return NULL;
		}
	}
	void sendData(int size) {
		if (size > 0) {
			send_ptr += size;
			send_size -= size;
			if (send_size <= 0) {
				send_ptr = packet_ptr = send_buffer;
				*(unsigned short *)send_ptr = 0;
			}
			if (pSendPerf)
				pSendPerf->perfPacket(size);
			if (pSendPerf)
				pSendPerf->packet_number++;
		}
	}

	bool packData(const char *data, int size) {
		if (size <= 0 ||
			send_size + size + MINIMIZE_BLOCK >= max_send) {						
			//缓冲区满，关闭连接
			return false;
		}

		if(!packet_size) {
			*(unsigned short *)packet_ptr = 0;
			packet_size += sizeof(unsigned short);
			send_size += sizeof(unsigned short);
		}

		if (send_size < 0)
		{
			printf("send size Negative ?!!!!\n");
			send_ptr = send_buffer;
			send_size = 0;
			packet_ptr = send_ptr;
			packet_size = 0;
			return false;
		}

		if(packet_ptr + packet_size + size + MINIMIZE_BLOCK >= send_buffer + max_send) {		//尾部的空间不够了
			memmove(send_buffer, send_ptr, send_size);
			packet_ptr -= (send_ptr - send_buffer);
			send_ptr = send_buffer;
		}
		memcpy(packet_ptr + packet_size, data, size);
		packet_size += size;
		send_size += size;
		return true;
	}
	char *completePacket(int &datalength) {
		if(!packet_size) {
			return NULL;
		}

		datalength = packet_size - sizeof(unsigned short);
		return packet_ptr + sizeof(unsigned short);
	}
	void sendPacket() {							//完成一个数据包
		if (!packet_size)
			return;
		*(unsigned short *)packet_ptr = packet_size;
		packet_ptr += packet_size;
		packet_size = 0;
	}
};

#endif
