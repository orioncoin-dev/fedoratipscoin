set -e
echo "Run this from inside the xcode folder - see instructions for manual steps..."
echo "Building osx_SDK.zip ..."
cd Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk
zip -r ../../../../../../../../osx_SDK.zip .
cp osx_SDK.zip ..
echo 'All done! Remember, to delete the contents of this folder when you are done.'
