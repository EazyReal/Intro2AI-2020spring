#for fast git operations
#for further info., just go see function sub 
#maxwill lin
#ver 0 done 2020/2/9 14:00, debug [space$#]

#!/bin/bash

function sub()
{
  git pull origin master
  git add  .
  git commit -m  $1
  git push origin master
}


if [ $# -eq 1 ]; then
  sub $1
elif [ $# -eq 0 ]; then
  read -p "input git commit message:" COMMITMESSAGE
  sub ${COMMITMESSAGE}
else
  echo "Usage : qgit COMMITMESSAGE or qgit"
fi

sleep 1
