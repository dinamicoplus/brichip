AC_INIT([brichip],[1.2],[marbri91@gmail.com])
AC_CONFIG_SRCDIR([src/chip8.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CANONICAL_HOST		#Necesario para averiguar el host
AM_INIT_AUTOMAKE([foreign])	#idem
AC_PROG_CC			#verifica si existe gcc
AC_SUBST([HOST],[$host])	#sustituye Host por el host encontrado

case "$host" in
    *-*-darwin*)		#si es MacOSX...
	SYSTEM="macosx"
	CFLAGS="-ObjC"
	LDFLAGS="-framework Cocoa"
	LIBS="$srcdir/lib/$SYSTEM/*.dylib"
	SOURCES="$srcdir/src/$SYSTEM/*.m"
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
	SYSTEM="win"
	LDFLAGS="-lSDL"
	SOURCES="$srcdir/src/$SYSTEM/*.c"
	LIBS="$srcidr/lib/$SYSTEM/*.lib"
	OUTPUT_FORMAT=".exe"
	EXECUTABLE_NAME="$PACKAGE-$VERSION$OUTPUT_FORMAT"
	;;
    *)
	SYSTEM="linux"
	LDFLAGS="-lSDL -lSDLmain"
	EXECUTABLE_NAME="$PACKAGE-$VERSION$OUTPUT_FORMAT"
	;;
esac

SOURCES=`echo $srcdir/src/*.c $SOURCES`
LDFLAGS=`echo L$srcdir/lib $LDFLAGS`
INCLUDES=`echo -Iinclude -I$srcdir/include $INCLUDES`
LIBS=`echo LIBS`

OBJECTS=`echo $SOURCES | sed 's/\.c/\.o/g'`
OBJECTS=`echo $OBJECTS | sed 's/\.m/\.o/g'`

AC_SUBST([SYSTEM],[$SYSTEM])
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