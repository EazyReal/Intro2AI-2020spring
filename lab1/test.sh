#echo "hi" > test.txt
#x0=$((1+$RANDOM % 100))
#echo $((1+$RANDOM % 100)) >> test.txt
#echo $x0 >> test.txt

#g++ -o out -std=c++17 game.cpp

board_size=10

echo "" > test.txt
echo "" > testout.txt

for test_id in $(seq 1 1 10);
do
    x1=$((0+$RANDOM % $board_size))
    x2=$((0+$RANDOM % $board_size))
    y1=$((0+$RANDOM % $board_size))
    y2=$((0+$RANDOM % $board_size))
    echo $board_size 1 $x1 $x2 $y1 $y2 >> test.txt
    #run ./out < board_size algo_id $
    echo $board_size 1 $x1 $x2 $y1 $y2 | ./out >> testout.txt
done 