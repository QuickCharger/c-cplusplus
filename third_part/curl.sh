wget https://github.com/curl/curl/releases/download/curl-7_80_0/curl-7.80.0.tar.gz
tar -zxf curl-7.80.0.tar.gz

mkdir curl-7.80.0/sln
pushd curl-7.80.0/sln
cmake -DCMAKE_INSTALL_PREFIX=`pwd`/../../curl ..
cmake --build . --target install --clean-first --config Release
popd

rm -rf curl-7.80.0.tar.gz
rm -rf curl-7.80.0/
