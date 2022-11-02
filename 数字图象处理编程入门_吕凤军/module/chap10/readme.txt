第10讲	图象处理编程工具的介绍，简单的多媒体编程

source目录下为本章介绍的源程序
功能是LeadTools的介绍以及简单的多媒体编程，有两个目录

source\TestLead为LeadTools的介绍，用的是VC++5.0，运行时
文件c:\test.jpg必须准备好

source\TestMCI为简单的多媒体编程
命令行编译过程如下
vcvars32
cl testmci.c user32.lib vfw32.lib
