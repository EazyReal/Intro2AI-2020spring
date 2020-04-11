#echo "hi" > test.txt
#x0=$((1+$RANDOM % 100))
#echo $((1+$RANDOM % 100)) >> test.txt
#echo $x0 >> test.txt

#g++ -o out -std=c++17 game.cpp

algoN=4
maxN=$1
deltaN=$2
testN=$3

rm -rf testcases
mkdir testcases

for board_size in $(seq 5 ${deltaN} ${maxN});
do
    echo "" > ./testcases/N${board_size}.txt

    for test_id in $(seq 1 1 ${testN});
    do
            x1=$((0+$RANDOM % $board_size))
            x2=$((0+$RANDOM % $board_size))
            y1=$((0+$RANDOM % $board_size))
            y2=$((0+$RANDOM % $board_size))
            echo $board_size $x1 $x2 $y1 $y2 >> ./testcases/N${board_size}.txt
            #run ./out < board_size algo_id $
            #echo $board_size 1 $x1 $x2 $y1 $y2 | ./out >> testout.txt
    done
done