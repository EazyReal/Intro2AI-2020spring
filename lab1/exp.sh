#for fast git operations
#for further info., just go see function sub 
#maxwill lin
#ver 0 done 2020/2/9 14:00, debug [space$#]

#!/bin/bash

function run()
{
    ./out < $1 $2 $3 $4
}

for board_size in $(seq 0 1 4);
do
    for algo_id in $(seq 1 1 10);
    do
        for test_id in $(seq 1 1 100);
        do
            x1 = $RANDOM % board_size
            x2 = $RANDOM % board_size
            y1 = $RANDOM % board_size
            y2 = $RANDOM % board_size
            echo $
            run ./out < board_size algo_id $
        done 
    done
done

if [ $# -eq 1 ]; then
  sub $1
elif [ $# -eq 0 ]; then
  read -p "input git commit message:" COMMITMESSAGE
  sub ${COMMITMESSAGE}
else
  echo "Usage : qgit COMMITMESSAGE or qgit"
fi

sleep 1
