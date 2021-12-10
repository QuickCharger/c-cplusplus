wget https://github.com/openssl/openssl/archive/refs/tags/openssl-3.0.0.tar.gz
tar -xzf openssl-3.0.0.tar.gz
rm openssl-3.0.0.tar.gz.tar.gz

pushd openssl-openssl-3.0.0/
./config --prefix=`pwd`/../openssl
make
make install
popd

rm -rf openssl-openssl-3.0.0/
