第七讲 边沿检测与提取，轮廓跟踪
source目录下为本章介绍的源程序
功能是边沿检测与提取，轮廓跟踪

命令行编译过程如下
vcvars32
rc bmp.rc
cl edge.c bmp.res user32.lib gdi32.lib

注意事项：
运行时，文件c:\test.bmp必须存在
