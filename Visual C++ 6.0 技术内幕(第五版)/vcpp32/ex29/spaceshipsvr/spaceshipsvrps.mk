
spaceshipsvrps.dll: dlldata.obj spaceshipsvr_p.obj spaceshipsvr_i.obj
	link /dll /out:spaceshipsvrps.dll /def:spaceshipsvrps.def /entry:DllMain dlldata.obj spaceshipsvr_p.obj spaceshipsvr_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del spaceshipsvrps.dll
	@del spaceshipsvrps.lib
	@del spaceshipsvrps.exp
	@del dlldata.obj
	@del spaceshipsvr_p.obj
	@del spaceshipsvr_i.obj
