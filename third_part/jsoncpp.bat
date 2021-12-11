rem wget https://github.com/open-source-parsers/jsoncpp/archive/refs/tags/1.9.5.tar.gz
tar -zxf 1.9.5.tar.gz
pushd jsoncpp-1.9.5
mkdir tmp
pushd tmp
cmake -DCMAKE_INSTALL_PREFIX=../../jsoncpp ..
cmake --build . --target install --clean-first --config Release
popd
popd

rem rm -rf 1.9.5.tar.gz
rem  rm -rf jsoncpp-1.9.5/

pause
