第三讲 图象的平滑（去噪声），锐化
source目录下为本章介绍的源程序
功能是实现图象的平滑（去噪声），锐化

命令行编译过程如下
vcvars32
rc bmp.rc
cl smooth.c bmp.res user32.lib gdi32.lib

注意事项：
运行时，文件c:\test.bmp必须存在
