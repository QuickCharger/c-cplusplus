wget https://github.com/open-source-parsers/jsoncpp/archive/refs/tags/1.9.5.tar.gz
tar -zxf 1.9.5.tar.gz

mkdir jsoncpp-1.9.5/sln
pushd jsoncpp-1.9.5/sln
cmake -DCMAKE_INSTALL_PREFIX=`pwd`/../../jsoncpp ..
cmake --build . --target install --clean-first --config Release
popd

rm -rf 1.9.5.tar.gz
rm -rf jsoncpp-1.9.5/
