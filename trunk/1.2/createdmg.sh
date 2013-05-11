#!/bin/bash
test -d tmp || mkdir tmp
test -d bin || mkdir bin
hdiutil create tmp/brichip.dmg -ov -volname "brichip" -fs HFS+ -srcfolder "bin/"
hdiutil convert tmp/brichip.dmg -format UDZO -o brichip.dmg
rm -r tmp
