rem 需要手动执行下面的命令

wget https://github.com/curl/curl/releases/download/curl-7_80_0/curl-7.80.0.tar.gz
tar -zxf curl-7.80.0.tar.gz
cd curl-7.80.0\winbuild
CALL "%VS140COMNTOOLS%\..\..\VC\vcvarsall.bat" x86
nmake /f makefile.vc mode=static ENABLE_IDN=no debug=no
cd ../..
mkdir curl
cp -r curl-7.80.0/builds/libcurl-vc-x86-release-static-ipv6-sspi-schannel/* curl/
rm -rf curl-7.80.0

pause
