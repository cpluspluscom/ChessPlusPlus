#!/bin/sh

#  bundle.sh
#  
#
#  Created by Steve Hall on 3/8/13.
#

# Remove old .app if exists
if [ -d bin/ChessPlusPlus.app ]; then
    echo "Removing old .app"
    rm -rf bin/ChessPlusPlus.app
fi

# Create bundle structure in bin/
echo "Creating bundle structure"
mkdir -p bin bin/ChessPlusPlus.app bin/ChessPlusPlus.app/Contents bin/ChessPlusPlus.app/Contents/MacOS bin/ChessPlusPlus.app/Contents/Resources/res bin/ChessPlusPlus.app/Contents/Frameworks

# Copy resources
echo "Copying resources to bundle"
cp -pR res bin/ChessPlusPlus.app/Contents/Resources/
cp -pR MacOS/info.plist bin/ChessPlusPlus.app/Contents
cp -pR ./config.xml bin/ChessPlusPlus.app/Contents/Resources

# Copy SFML frameworks
echo "Copying SFML Frameworks to bundle"
cp -Rn /Library/Frameworks/SFML.framework bin/ChessPlusPlus.app/Contents/Frameworks
cp -Rn /Library/Frameworks/sfml-system.framework bin/ChessPlusPlus.app/Contents/Frameworks
cp -Rn /Library/Frameworks/sfml-window.framework bin/ChessPlusPlus.app/Contents/Frameworks
cp -Rn /Library/Frameworks/sfml-graphics.framework bin/ChessPlusPlus.app/Contents/Frameworks

# Move executable
echo "Moving executable to bundle"
mv -f ./chesspp bin/ChessPlusPlus.app/Contents/MacOS
