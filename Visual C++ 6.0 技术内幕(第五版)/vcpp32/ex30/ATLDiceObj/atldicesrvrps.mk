
atldicesrvrps.dll: dlldata.obj atldicesrvr_p.obj atldicesrvr_i.obj
	link /dll /out:atldicesrvrps.dll /def:atldicesrvrps.def /entry:DllMain dlldata.obj atldicesrvr_p.obj atldicesrvr_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del atldicesrvrps.dll
	@del atldicesrvrps.lib
	@del atldicesrvrps.exp
	@del dlldata.obj
	@del atldicesrvr_p.obj
	@del atldicesrvr_i.obj
