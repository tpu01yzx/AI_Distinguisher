#!/bin/bash

sts=/home/guest/git/AI_Distinguisher/sts/assess
cipher=/home/guest/git/AI_Distinguisher/cipher/rc4/rc4
report=/home/guest/git/test/result.txt
tmp_path=/tmp/$$

s_len=387840
N=100
c_id=0
c_len=$(($s_len*$N))

if [ -z $1 ];
then
	echo Error Args
	exit
fi

mkdir -p $(dirname $tmp_path)
mkdir -p $tmp_path

cd $tmp_path

cp -r $(dirname $sts)/experiments $tmp_path
cp -r $(dirname $sts)/data $tmp_path
cp -r $(dirname $sts)/templates $tmp_path

tmp_test=$tmp_path/test.bin
tmp_result=$tmp_path/result.txt

function generate(){
	$cipher -q -L $c_len -o $tmp_test -k /dev/urandom -O /dev/null
	$sts -L $s_len -M 1 -P -N $N -O $tmp_result -I $tmp_test > /dev/null
	echo $c_id$(cat $tmp_result) >> $report
	rm -f $tmp_test $tmp_result
}

start=$(date +%s)
echo [$$] start $1 tasks 

for((i=1; i<=$1; i++))
do
	echo [$$] task $i/$1
	generate
done

rm -rf $tmp_path

end=$(date +%s)
echo [$$] finish, total cost time: $[$end-$start]s


