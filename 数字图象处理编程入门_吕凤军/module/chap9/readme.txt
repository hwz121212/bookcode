第九讲 图象的压缩编码，JPEG压缩编码标准
source目录下为本章介绍的源程序
功能是行程编码，JPEG压缩编码（基本系统）

命令行编译过程如下
vcvars32
rc bmp.rc
cl compress.c bmp.res user32.lib gdi32.lib

注意事项：
运行时，文件c:\test.pcx；c:\test.jpg必须存在
