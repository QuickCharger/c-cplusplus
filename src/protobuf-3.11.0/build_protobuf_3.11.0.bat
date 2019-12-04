wget https://github.com/protocolbuffers/protobuf/releases/download/v3.11.0/protobuf-cpp-3.11.0.zip
unzip protobuf-cpp-3.11.0.zip
cd protobuf-3.11.0

SET VCVARSALL="%VS140COMNTOOLS%..\..\VC\vcvarsall.bat"

call CALL %VCVARSALL% x86

mkdir sln & cd sln
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../bin -Dprotobuf_MSVC_STATIC_RUNTIME=OFF ../cmake
cmake --build . --target install --clean-first --config Release

cd ..

call CALL %VCVARSALL% amd64
mkdir sln64 & cd sln64
cmake -A x64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../bin64 -Dprotobuf_MSVC_STATIC_RUNTIME=OFF ../cmake
cmake --build . --target install --clean-first --config Release

pause
