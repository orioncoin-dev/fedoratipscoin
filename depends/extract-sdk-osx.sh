set -e
echo "Run this from inside the xcode folder - see instructions for manual steps..."
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
echo "Building osx_SDK.zip ..."
cd Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk
zip -r ../../../../../../../../osx_SDK.zip .
cp osx_SDK.zip ..
=======
=======
>>>>>>> 3effb54f9cb5d6e434069053516fe245510b4292
=======
>>>>>>> 3effb54f9cb5d6e434069053516fe245510b4292
cd Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk

echo "Building osx_SDK.tar.gz ..."
find | sort | tar --no-recursion -c -T - | gzip -9n > "../../../../../../../../osx_SDK.tar.gz"
cd ../../../../../../../..

cp osx_SDK.tar.gz ..
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> 3effb54f9cb5d6e434069053516fe245510b4292
=======
>>>>>>> 3effb54f9cb5d6e434069053516fe245510b4292
=======
>>>>>>> 3effb54f9cb5d6e434069053516fe245510b4292
echo 'All done! Remember, to delete the contents of this folder when you are done.'
