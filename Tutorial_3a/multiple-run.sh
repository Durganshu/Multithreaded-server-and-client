# Script to run multiple instances of the pokingclient
# Source: https://askubuntu.com/questions/712776/run-multiple-instance-of-a-program-in-parallel

#! /bin/bash
trap "pkill -P $$; kill -INT $$" INT

while read n
do
    "$@" 
done < <(seq 40)
wait
