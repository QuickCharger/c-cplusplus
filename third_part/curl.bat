rem wget https://github.com/curl/curl/releases/download/curl-7_80_0/curl-7.80.0.tar.gz
rem tar -zxf curl-7.80.0.tar.gz

cd curl-7.80.0
mkdir sln
cd sln
cmake ..
cmake --build . --target install --clean-first --config Release
pause
cd ../..
rm -rf curl-7.80.0.tar.gz
rm -rf curl-7.80.0/
