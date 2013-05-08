AC_INIT([brichip],[1.2],[marbri91@gmail.com])
AC_CONFIG_SRCDIR([src/chip8.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CANONICAL_HOST
AM_INIT_AUTOMAKE([foreign])
AC_PROG_CC
AC_SUBST([HOST],[$host])
case "$host" in
    *-*-darwin*)
	CFLAGS="-ObjC"
	INCLUDES="-Iinclude -I$srcdir/src/macox"
	LDFLAGS="-framework Cocoa"
	LIBS="$srcdir/lib/libSDL-1.2.0.dylib $srcdir/src/macosx/SDLmain.m"
	;;
    *-*-mingw32*)
	LDFLAGS="-lSDL"
	LIBS="$srcdir/src/win/SDL_win32_main.o"
	;;
    *)
	LDFLAGS="-lSDL -lSDLmain"
	;;
esac
AC_SUBST([CFLAGS],[$CFLAGS])
AC_SUBST([INCLUDES],[$INCLUDES])
AC_SUBST([LDFLAGS],[$LDFLAGS])
AC_SUBST([LIBS],[$LIBS])
AC_SUBST([OUTPUT_FORMAT],[$OUTPUT_FORMAT])
AC_CONFIG_FILES([Makefile:Makefile.in])
AC_OUTPUT