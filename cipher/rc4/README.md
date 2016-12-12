Usage: ./rc4 -L lenght(byte)<br />
  -i 输入密钥的文件<br />
  -l 密钥长度<br />
  -o 输出密钥流的文件名<br />
  -L 输出密钥流的长度，字节为单位<br />
  -b 分块大小<br />
  -q 显示生成信息<br />
<br />
Example：<br />
  生成 100MB 的文件 1024*1024*100 <br />
  密钥为0的256字节<br />
  输出到 当前目录 o.dat<br />
  ./rc4 -L 104857600 -i /dev/zero -l 256 -o o.dat<br />
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
