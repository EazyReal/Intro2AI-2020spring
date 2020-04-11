# usage

algoN=4
maxN=$1
deltaN=$2
testN=$3

# algoN independent
./tc_generate.sh $maxN $deltaN $testN

rm -rf results
mkdir results

# exp
g++ -o tmpout -std=c++17 exp.cpp
echo $maxN $deltaN $testN | ./tmpout
rm tmpout