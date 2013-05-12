AC_INIT([brichip],[1.2],[marbri91@gmail.com])
AC_CONFIG_SRCDIR([src/chip8.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CANONICAL_HOST		#Necesario para averiguar el host
AM_INIT_AUTOMAKE([foreign])	#idem
AC_PROG_CC			#verifica si existe gcc
AC_SUBST([HOST],[$host])	#sustituye Host por el host encontrado

SOURCES="$SOURCES $srcdir/src/*.c"
case "$host" in
    *-*-darwin*)		#si es MacOSX...
	CFLAGS="-ObjC"
	INCLUDES="-I$srcdir/include"
	LDFLAGS="-framework Cocoa"
	LIBS="$srcdir/lib/libSDL-1.2.0.dylib"
	
	SOURCES="$SOURCES $srcdir/src/macosx/*.m"
	AUX="$srcdir/src/macosx/Info.plist:$srcdir/src/macosx/Info.plist.in"
	EXECUTABLE_NAME="$PACKAGE-$VERSION$OUTPUT_FORMAT"

	AC_ARG_ENABLE(gui,
		AC_HELP_STRING([--enable-gui], [Enable the GUI [[default=yes]]]),
              , enable_gui=yes)
	if test x$enable_gui == xyes; then
    		AC_DEFINE([SDL_USE_NIB_FILE],[],[Use this flag to determine whether we use SDLMain.nib or not])
		EXTRA="createapp: all
	test -d bin/$PACKAGE.app || mkdir bin/$PACKAGE.app
	mv bin/$EXECUTABLE_NAME bin/$PACKAGE.app
	cp -R $srcdir/src/macosx/SDLMain.nib bin/$PACKAGE.app
	cp $srcdir/src/macosx/Info.plist bin/$PACKAGE.app "
	fi
	;;
    *-*-mingw32*)
	LDFLAGS="-lSDL"
	INCLUDES="-I$srcdir/include -L$srcdir/lib"
	SOURCES="$SOURCES $srcdir/src/win/SDL_win32_main.c"
	LIBS="$srcidr/lib/user32.lib $srcdir/lib/comdlg32.lib"
	OUTPUT_FORMAT=".exe"
	EXECUTABLE_NAME="$PACKAGE-$VERSION$OUTPUT_FORMAT"
	;;
    *)
	LDFLAGS="-lSDL -lSDLmain"
	EXECUTABLE_NAME="$PACKAGE-$VERSION$OUTPUT_FORMAT"
	;;
esac

OBJECTS=`echo $SOURCES | sed 's,[[^ ]]*/\([[ ]]*\)\.c,$(objects)/\1.o,g'`
OBJECTS=`echo $SOURCES | sed 's,[[^ ]]*/\([[ ]]*\)\.m,$(objects)/\1.o,g'`


AC_SUBST([SOURCES],[$SOURCES])
AC_SUBST([OBJECTS],[$OBJECTS])
AC_SUBST([CFLAGS],[$CFLAGS])
AC_SUBST([INCLUDES],[$INCLUDES])
AC_SUBST([LDFLAGS],[$LDFLAGS])
AC_SUBST([LIBS],[$LIBS])
AC_SUBST([EXTRA],[$EXTRA])
AC_SUBST([EXECUTABLE_NAME],[$EXECUTABLE_NAME])
AC_SUBST([OUTPUT_FORMAT],[$OUTPUT_FORMAT])
AC_CONFIG_FILES([Makefile:Makefile.in $AUX])
AC_CONFIG_HEADER([include/config.h])
AC_OUTPUT