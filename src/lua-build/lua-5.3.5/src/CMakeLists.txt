SET(lua_base
	lapi.c lapi.h
	lauxlib.c lauxlib.h
	lbaselib.c
	lbitlib.c
	lcode.c lcode.h
	lcorolib.c
	lctype.c lctype.h
	ldblib.c
	ldebug.c ldebug.h
	ldo.c ldo.h
	ldump.c
	lfunc.c lfunc.h
	lgc.c lgc.h
	linit.c
	liolib.c
	llex.c llex.h
	llimits.h
	lmathlib.c
	lmem.c lmem.h
	loadlib.c
	lobject.c lobject.h
	lopcodes.c lopcodes.h
	loslib.c
	lparser.c lparser.h
	lprefix.h
	lstate.c lstate.h
	lstring.c lstring.h
	lstrlib.c
	ltable.c ltable.h
	ltablib.c
	ltm.c ltm.h
	lua.h lua.hpp
	luaconf.h
	lualib.h
	lundump.c lundump.h
	lutf8lib.c
	lvm.c lvm.h
	lzio.c lzio.h
)

SET(head_files
	lua.hpp
	lua.h
	lualib.h
	lauxlib.h
	luaconf.h
)

ADD_LIBRARY(lua-build STATIC ${lua_base})
INSTALL(TARGETS lua-build CONFIGURATIONS Release DESTINATION lib)
INSTALL(FILES ${head_files} DESTINATION include)

#ADD_EXECUTABLE(lua ${lua_base} lua.c)
#INSTALL(TARGETS lua DESTINATION bin)

#ADD_EXECUTABLE(luac ${lua_base} luac.c)
#INSTALL(TARGETS luac DESTINATION bin)
