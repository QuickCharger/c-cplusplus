rem win下编译openssl麻烦 需要安装perl和nasm， 简单的方法是从网上下载编译好的 例如 http://slproweb.com/download/Win32OpenSSL-3_0_1.exe
rem 源码编译 下载https://github.com/openssl/openssl/archive/refs/tags/openssl-3.0.0.tar.gz  文件NOTES-WINDOWS.md详细描述了编译步骤。命令提示符要选x86或x64不能是x86_64 最好管理员运行 否则nmake install时权限不足。 遇到了任何错误都需要删除文件夹重来 否则会遇到错误
