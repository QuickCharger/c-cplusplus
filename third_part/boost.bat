rem https://www.boost.org/doc/libs/1_78_0/more/getting_started/unix-variants.html

wget https://boostorg.jfrog.io/artifactory/main/release/1.78.0/source/boost_1_78_0.zip
unzip boost_1_78_0.zip > null
cd boost_1_78_0
./bootstrap.bat
./b2.exe install --prefix=../boost

pause
