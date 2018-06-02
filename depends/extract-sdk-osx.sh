set -e
echo "Run this from inside the xcode folder - see instructions for manual steps..."
cd Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk

echo "Building osx_SDK.tar.gz ..."
find | sort | tar --no-recursion -c -T - | gzip -9n > "../../../../../../../../osx_SDK.tar.gz"
cd ../../../../../../../..

cp osx_SDK.tar.gz ..
echo 'All done! Remember, to delete the contents of this folder when you are done.'
