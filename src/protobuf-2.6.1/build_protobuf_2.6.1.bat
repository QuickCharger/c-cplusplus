wget https://github.com/protocolbuffers/protobuf/releases/download/v2.6.1/protobuf-2.6.1.zip
unzip protobuf-2.6.1.zip
cd protobuf-2.6.1

CALL "%VS140COMNTOOLS%\..\..\VC\vcvarsall.bat" x86

cd vsprojects

devenv protobuf.sln /Upgrade

sed -i 's/%(PreprocessorDefinitions)/_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS;%(PreprocessorDefinitions)/g' libprotobuf.vcxproj
sed -i 's/%(PreprocessorDefinitions)/_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS;%(PreprocessorDefinitions)/g' protoc.vcxproj
sed -i 's/%(PreprocessorDefinitions)/_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS;%(PreprocessorDefinitions)/g' libprotoc.vcxproj

devenv protobuf.sln /Rebuild "Release|Win32" /Project libprotobuf
devenv protobuf.sln /Rebuild "Release|Win32" /Project protoc

cd .. & mkdir bin & cd bin & mkdir bin & mkdir include & mkdir lib & cd ..

XCOPY vsprojects\Release\protoc.exe bin\bin\ /S /Y
XCOPY vsprojects\Release\libprotobuf.lib bin\lib\ /S /Y
XCOPY src bin\include\ /S /Y

pause
