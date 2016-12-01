Usage: python xxtea.py  -l lenght(byte) -k key -o output

  -l 生成的长度

  -k 密钥

  -o 输出文件名


PS：明文采取rand函数根据时间生成


Example：

  生成 1MB 的文件 1024*1024

  密钥 000000

  输出到 当前目录 o.dat

  python xxtea.py -l 1048576 -k 000000 -o o.dat
