## libjpeg库的使用之图片的读写

libjpeg一个图片解码库，在项目中需要读入图片，但不想依赖opencv的接口，这时可以libjpeg完成解码。libjpeg有两个版本，一个时原装的libjpeg，另一个则是libjpeg-turbo，这是一个使用 SIMD指令加速的解码库，大约是libjpeg的3倍的速度.

参考：
- [libjpeg官网](http://libjpeg.sourceforge.net/)
- [github: libjpeg-turbo](https://github.com/libjpeg-turbo/libjpeg-turbo)
- [使用libjpeg进行图片读取](https://blog.csdn.net/iriving_shu/article/details/77075354)

## 测试代码

readjpg.h
```
#ifndef READJPG_H
#define READJPG_H

char* readjpgfile(char* pcJpegBuf, long size);

void write_JPEG_file (char *image_buffer,
	                  char** pcJpegBuf,
	                  long *piFileLen,
	                  int quality,
	                  int image_width,
	                  int image_height);

#endif
```


readjpg.c
```
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "readjpg.h"

#include "jpeg/jpeglib.h"
#include "jpeg/jerror.h"

char* readjpgfile(char* pcJpegBuf, long size)
{
	//定义结构体
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	//产生相应变量
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	//获取头信息
	//jpeg_stdio_src(&cinfo, infile);
	jpeg_mem_src(&cinfo, pcJpegBuf, size); 
	jpeg_read_header(&cinfo, TRUE);
	printf("cinfo.image_width:%d, cinfo.image_height:%d, cinfo.num_components:%d\n",
		cinfo.image_width, cinfo.image_height, cinfo.num_components);

	//分配内存存储字节
	char *rdata=NULL;
	rdata=(char*)calloc(cinfo.image_width*cinfo.image_height*cinfo.num_components,1);

	//开始解压
	jpeg_start_decompress(&cinfo);
	printf("output_width:%d, output_height:%d\n",cinfo.output_width,cinfo.output_height);

	JSAMPROW row_pointer[1];
	while (cinfo.output_scanline < cinfo.output_height)
	{
		row_pointer[0] = & rdata[(cinfo.output_scanline)*cinfo.image_width*cinfo.num_components];
		jpeg_read_scanlines(&cinfo,row_pointer ,1);
	}

	// 结束解压
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	return rdata;
}


void
write_JPEG_file (char *image_buffer, char** pcJpegBuf, long *piFileLen, /*char * filename,*/ int quality, int image_width, int image_height)
{
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;

  FILE * outfile;		/* target file */
  JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
  int row_stride;		/* physical row width in image buffer */

  /* Step 1: allocate and initialize JPEG compression object */

  /* We have to set up the error handler first, in case the initialization
   * step fails.  (Unlikely, but it could happen if you are out of memory.)
   * This routine fills in the contents of struct jerr, and returns jerr's
   * address which we place into the link field in cinfo.
   */
  cinfo.err = jpeg_std_error(&jerr);
  /* Now we can initialize the JPEG compression object. */
  jpeg_create_compress(&cinfo);

  /* Step 2: specify data destination (eg, a file) */
  /* Note: steps 2 and 3 can be done in either order. */

  /* Here we use the library-supplied code to send compressed data to a
   * stdio stream.  You can also write your own code to do something else.
   * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
   * requires it in order to write binary files.
   */
  // if ((outfile = fopen(filename, "wb")) == NULL) {
  //   fprintf(stderr, "can't open %s\n", filename);
  //   exit(1);
  // }
  // jpeg_stdio_dest(&cinfo, outfile);

  jpeg_mem_dest(&cinfo, pcJpegBuf, piFileLen);

  /* Step 3: set parameters for compression */

  /* First we supply a description of the input image.
   * Four fields of the cinfo struct must be filled in:
   */
  cinfo.image_width = image_width; 	/* image width and height, in pixels */
  cinfo.image_height = image_height;
  cinfo.input_components = 3;		/* # of color components per pixel */
  cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
  /* Now use the library's routine to set default compression parameters.
   * (You must set at least cinfo.in_color_space before calling this,
   * since the defaults depend on the source color space.)
   */
  jpeg_set_defaults(&cinfo);
  /* Now you can set any non-default parameters you wish to.
   * Here we just illustrate the use of quality (quantization table) scaling:
   */
  jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

  /* Step 4: Start compressor */

  /* TRUE ensures that we will write a complete interchange-JPEG file.
   * Pass TRUE unless you are very sure of what you're doing.
   */
  jpeg_start_compress(&cinfo, TRUE);

  /* Step 5: while (scan lines remain to be written) */
  /*           jpeg_write_scanlines(...); */

  /* Here we use the library's state variable cinfo.next_scanline as the
   * loop counter, so that we don't have to keep track ourselves.
   * To keep things simple, we pass one scanline per call; you can pass
   * more if you wish, though.
   */
  row_stride = image_width * 3;	/* JSAMPLEs per row in image_buffer */

  while (cinfo.next_scanline < cinfo.image_height) {
    /* jpeg_write_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could pass
     * more than one scanline at a time if that's more convenient.
     */
    row_pointer[0] = & image_buffer[cinfo.next_scanline * row_stride];
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }

  /* Step 6: Finish compression */

  jpeg_finish_compress(&cinfo);
  /* After finish_compress, we can close the output file. */
  // fclose(outfile);

  /* Step 7: release JPEG compression object */

  /* This is an important step since it will release a good deal of memory. */
  jpeg_destroy_compress(&cinfo);

  /* And we're done! */
}
```


test.c
```
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>

#include "readjpg.h"

int main(int argc ,char **argv)
{
	char* filename="test.jpg";
	int fd=0;
    struct stat stat;
    int size=0;
	fd = open(filename, O_RDONLY);
    if (fd < 1) {
        printf("Cannot open file: %s\n", filename);
    }
    if (fstat(fd, &stat) == -1) {
        printf("Cannot stat: %s\n", filename);
    } else {
        size = stat.st_size;
        printf("size is %d\n",size);
    }

    // 分配内存保存文件内容
	char *pcJpegBuf = (char*)malloc(size);
	int n=read(fd,pcJpegBuf,size);
	if(n!=size){
		printf("read != size\n");
	}

	// 读取jpg图片，返回rgb数据
	char* rgb = readjpgfile(pcJpegBuf, size);
	if(rgb!=NULL){
		printf("%p\n",rgb);
	}

	// 将rgb数据写入到jpg文件
	char *image_buffer = NULL;
	long len;
	write_JPEG_file (rgb, &image_buffer, &len, 100, 1920, 1080);
	printf("len is %d, buffer is %p\n",(int)len, image_buffer);

	// 写入到文件
	static FILE* fImg = NULL;
	if (fImg == NULL)
	{
		fImg = fopen("result.jpg", "wb+");
	}
	fwrite(image_buffer, 1, len, fImg);
	fflush(fImg);
	
	if(image_buffer != NULL){
		free(image_buffer);
	}
	if(rgb!=NULL){
		free(rgb);
	}
	
	return 0;
}
```
