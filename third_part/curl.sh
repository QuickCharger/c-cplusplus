wget https://github.com/curl/curl/releases/download/curl-7_80_0/curl-7.80.0.tar.gz
tar -zxf curl-7.80.0.tar.gz

pushd curl-7.80.0
mkdir tmp
pushd tmp
cmake -DCMAKE_INSTALL_PREFIX=`pwd`/../../curl ..
make
make install
popd
popd

rm -rf curl-7.80.0.tar.gz
rm -rf curl-7.80.0/
