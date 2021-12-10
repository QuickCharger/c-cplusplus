# https://www.boost.org/doc/libs/1_78_0/more/getting_started/unix-variants.html
# 安装好的库放在 boost_1_78_0/boost_lib/ 中

wget https://boostorg.jfrog.io/artifactory/main/release/1.78.0/source/boost_1_78_0.tar.gz
tar -zxf boost_1_78_0.tar.gz
rm boost_1_78_0.tar.gz

pushd boost_1_78_0
./bootstrap.sh --prefix=`pwd`/boost_lib
./b2 install
popd
