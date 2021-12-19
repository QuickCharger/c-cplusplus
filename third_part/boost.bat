rem https://www.boost.org/doc/libs/1_78_0/more/getting_started/unix-variants.html

wget https://boostorg.jfrog.io/artifactory/main/release/1.78.0/source/boost_1_78_0.tar.gz
tar -zxf boost_1_78_0.tar.gz
cd boost_1_78_0
call bootstrap.bat
call b2.exe install --prefix=../boost

pause
