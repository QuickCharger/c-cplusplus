rem make sure you have done boost.sh doxygen.bat first

rem wget https://github.com/msgpack/msgpack-c/releases/download/cpp-1.4.0/msgpack-1.4.0.tar.gz
tar -zxf msgpack-1.4.0.tar.gz

mkdir msgpack-1.4.0\\sln
pushd msgpack-1.4.0\\sln
cmake -DCMAKE_INSTALL_PREFIX=..\\..\\msgpack ..
cmake --build . --target install --clean-first --config Release
popd

pause
