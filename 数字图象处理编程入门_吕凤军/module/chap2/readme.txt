第二讲 图象的几何变换
source目录下为本章介绍的源程序
功能是打开一幅位图，实现几何变换

命令行编译过程如下
vcvars32
rc bmp.rc
cl geotrans.c bmp.res user32.lib gdi32.lib

注意事项：
运行时，文件c:\test.bmp必须存在
