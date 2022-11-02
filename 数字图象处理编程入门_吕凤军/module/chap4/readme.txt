第四讲 图象的半影调和抖动技术
source目录下为本章介绍的源程序
功能是实现图案化和抖动技术，以及bmp2txt

命令行编译过程如下
vcvars32
rc bmp.rc
cl dither.c bmp.res user32.lib gdi32.lib

注意事项：
运行时，文件c:\test.bmp必须存在
