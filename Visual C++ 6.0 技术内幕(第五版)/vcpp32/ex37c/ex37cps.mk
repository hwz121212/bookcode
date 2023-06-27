
ex37cps.dll: dlldata.obj ex37c_p.obj ex37c_i.obj
	link /dll /out:ex37cps.dll /def:ex37cps.def /entry:DllMain dlldata.obj ex37c_p.obj ex37c_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ex37cps.dll
	@del ex37cps.lib
	@del ex37cps.exp
	@del dlldata.obj
	@del ex37c_p.obj
	@del ex37c_i.obj
