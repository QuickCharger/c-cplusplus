# https://www.boost.org/doc/libs/1_78_0/more/getting_started/unix-variants.html

wget https://boostorg.jfrog.io/artifactory/main/release/1.78.0/source/boost_1_78_0.tar.gz
tar -zxf boost_1_78_0.tar.gz

pushd boost_1_78_0
./bootstrap.sh --prefix=`pwd`/../boost
./b2 install
popd

rm boost_1_78_0.tar.gz
rm -rf boost_1_78_0
