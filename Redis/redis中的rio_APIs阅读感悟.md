## redis中的rio_APIs阅读感悟

对FILE/BUFFER/FDs封装了统一的接口，用到了工厂方法模式。

## 实例
```
#ifndef _IO_H
#define _IO_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>

//typedef int off_t

class IO
{
public:
	IO():cksum(0), processed_bytes(0),max_processing_chunk(0){}

	size_t read(void* buf, size_t len){
		while (len) {
            size_t bytes_to_read = (max_processing_chunk && max_processing_chunk < len) ? max_processing_chunk : len;
            if (read_imp(buf,bytes_to_read) == 0)
                return 0;
            update_cksum(buf,bytes_to_read);
            buf = (char*)buf + bytes_to_read;
            len -= bytes_to_read;
            processed_bytes += bytes_to_read;
        }
        return 1;
    }

	size_t write(const void* buf, size_t len){
		while (len) {
			size_t bytes_to_write = (max_processing_chunk && max_processing_chunk < len) ? max_processing_chunk : len;
            update_cksum(buf,bytes_to_write);
            if (write_imp(buf,bytes_to_write) == 0)
                return 0;
            buf = (char*)buf + bytes_to_write;
            len -= bytes_to_write;
            processed_bytes += bytes_to_write;
        }
        return 1;
	}
	virtual int tell()=0;
	virtual int flush()=0;
	virtual void update_cksum(const void* buf, size_t len){};
private:
	virtual size_t read_imp(void* buf, size_t len)=0;
	virtual size_t write_imp(const void* buf, size_t len)=0;
private:
	int cksum;
	size_t processed_bytes;
	size_t max_processing_chunk;
};


class IO_File:public IO
{
public:
	IO_File(FILE* f):IO(), fp(f), buffered(0), autosync(0){}

	int tell(){
		return ftell(fp);
	}

	int flush(){
		return (fflush(fp) == 0) ? 1 : 0;
	}

private:
	size_t read_imp(void* buf, size_t len){
		return fread(buf,len,1,fp);
	}

	size_t write_imp(const void* buf, size_t len){
		size_t retval;
		retval=fwrite(buf,len,1,fp);
		if(autosync && buffered >= autosync){
			fflush(fp);
			//fdatasync(fp);
			buffered=0;
		}
		return retval;
	}
private:
	FILE* fp;
	int buffered;
	int autosync;
};


// class IO_Buffer:public IO
// {

// };

void test()
{
	FILE* f=fopen("test.txt","ab+");
	char p[1024]="i love you";
	
	IO* io=new IO_File(f);
	//io->write(p,5);

	memset(p,0,1024);
	io->read(p,5);
	p[6]=0;
	printf("%s\n",p);

	//fwrite(p,5,1,f);

	fclose(f);
}

#endif // _IO_H
```
