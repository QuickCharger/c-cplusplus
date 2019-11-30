SET filedir=%~dp0

cd %filedir%\protobuf-2.6.1\vs2015_x86_release
mkdir sln
cd sln
cmake ..
cmake --build . --target install --clean-first --config Release

cd %filedir%\protobuf-2.6.1\vs2015_x64_release
mkdir sln
cd sln
cmake -A x64 ..
cmake --build . --target install --clean-first --config Release

cd %filedir%\protobuf-3.11.0\vs2015_x86_release
mkdir sln
cd sln
cmake ..
cmake --build . --target install --clean-first --config Release

cd %filedir%\protobuf-3.11.0\vs2015_x64_release
mkdir sln
cd sln
cmake -A x64 ..
cmake --build . --target install --clean-first --config Release

cd %filedir%\msgpack-3.2.0\vs2015_x86_release
mkdir sln
cd sln
cmake ..
cmake --build . --target install --clean-first --config Release

cd %filedir%\msgpack-3.2.0\vs2015_x64_release
mkdir sln
cd sln
cmake -A x64 ..
cmake --build . --target install --clean-first --config Release


cd bin
rm log.log
touch log.log

echo "protobuf 2.6.1 x86" >> log.log
protobuf_2.6.1_x86.exe >> log.log
protobuf_2.6.1_x86.exe >> log.log
protobuf_2.6.1_x86.exe >> log.log
echo "protobuf 2.6.1 x64" >> log.log
protobuf_2.6.1_x64.exe >> log.log
protobuf_2.6.1_x64.exe >> log.log
protobuf_2.6.1_x64.exe >> log.log
echo "protobuf 3.11.0 x86" >> log.log
protobuf_3.11.0_x86.exe >> log.log
protobuf_3.11.0_x86.exe >> log.log
protobuf_3.11.0_x86.exe >> log.log
echo "protobuf 3.11.0 x64" >> log.log
protobuf_3.11.0_x64.exe >> log.log
protobuf_3.11.0_x64.exe >> log.log
protobuf_3.11.0_x64.exe >> log.log
echo "msgpack 3.2.0 x86" >> log.log
msgpack_3.2.0_x86.exe >> log.log
msgpack_3.2.0_x86.exe >> log.log
msgpack_3.2.0_x86.exe >> log.log
echo "msgpack 3.2.0 x64" >> log.log
msgpack_3.2.0_x64.exe >> log.log
msgpack_3.2.0_x64.exe >> log.log
msgpack_3.2.0_x64.exe >> log.log

pause
