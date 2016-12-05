Usage: ./salsa20 -l lenght(byte)

  -l 需要生成的加密流长度
  
  -b 数据分块的大小，默认为8KB

  -k 密钥，默认为000000（ASCII）

  -o 输出加密流文件，默认为/dev/stdout 

  -s 输出密钥流到文件，默认为/dev/null（即不输出）
  
  -i 输入的数据流文件，默认为/dev/urandom （unix随机流）


Example：

  生成 100MB 的文件 1024*1024*100

  密钥 123456

  输出到 当前目录 o.dat

  ./salsa20 -l 104857600 -k 123456 -o o.dat
  
PS:
    标准输出流 /dev/stdout
    标准输入流 /dev/stdin
    标准错误流 /dev/stderr
    空设备（黑洞）/dev/null
    全是0的文件 /dev/zero
    “真”随机 /dev/random 会产生阻塞，效果好
    “伪”随机 /dev/urandom 不会阻塞，效果没那么好
    网络流 /dev/tcp[udp]/host/port 前提是建立了连接
