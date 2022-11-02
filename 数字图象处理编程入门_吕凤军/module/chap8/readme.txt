第八讲 图象的检测，模板匹配
source目录下为本章介绍的源程序
功能是图象的检测，模板匹配

命令行编译过程如下
vcvars32
rc bmp.rc
cl detect.c bmp.res user32.lib gdi32.lib

注意事项：
运行时，文件c:\test.bmp必须存在
