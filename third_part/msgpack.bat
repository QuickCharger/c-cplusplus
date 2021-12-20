# make sure you have done boost.sh doxygen.bat first

wget https://github.com/msgpack/msgpack-c/releases/download/cpp-4.0.3/msgpack-cxx-4.0.3.tar.gz
tar -zxf msgpack-cxx-4.0.3.tar.gz

path=%path%;%~dp0

mkdir msgpack-cxx-4.0.3\sln
pushd msgpack-cxx-4.0.3\sln
cmake -DCMAKE_INSTALL_PREFIX=..\..\msgpack ..
cmake --build . --target install --clean-first --config Release
popd

rm msgpack-cxx-4.0.3.tar.gz
rm -rf msgpack-cxx-4.0.3

pause
