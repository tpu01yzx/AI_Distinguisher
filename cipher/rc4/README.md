Usage: ./rc4 -l lenght(byte)<br />
  -l 需要生成的加密流长度<br />
  -b 数据分块的大小，默认为8KB<br />
  -k 密钥，默认为000000（ASCII）<br />
  -o 输出加密流文件，默认为/dev/stdout <br />
  -s 输出密钥流到文件，默认为/dev/null（即不输出）<br />
  -i 输入的数据流文件，默认为/dev/urandom （unix随机流）<br />
<br />
Example：<br />
  生成 100MB 的文件 1024*1024*100 <br />
  密钥 123456<br />
  输出到 当前目录 o.dat<br />
  ./rc4 -l 104857600 -k 123456 -o o.dat<br />
<br />
PS:<br />
    标准输出流 /dev/stdout<br />
    标准输入流 /dev/stdin<br />
    标准错误流 /dev/stderr<br />
    空设备（黑洞）/dev/null<br />
    全是0的文件 /dev/zero<br />
    “真”随机 /dev/random 会产生阻塞，效果好<br />
    “伪”随机 /dev/urandom 不会阻塞，效果没那么好<br />
    网络流 /dev/tcp[udp]/host/port 前提是建立了连接<br />
