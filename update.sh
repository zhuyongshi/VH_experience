#!/bin/sh
echo "udpate start!"

keyword_path=/home/zws/Desktop/111/2_14/key.txt
MM_st_path=/home/zws/Desktop/VH_experience/client/MM_st2_14.txt
stash_path=/home/zws/Desktop/VH_experience/client/stash2_14.txt
EMM_path=/home/zws/Desktop/VH_experience/server/EMM.txt
up_num=16444
m=8895
l=60
order_MM_path=/home/zws/Desktop/111/2_14/ans.txt
time_record_path=/home/zws/Desktop/VH_experience/client/time_record2_14.txt

./update $MM_st_path $m $keyword_path $EMM_path $stash_path $up_num $order_MM_path $l $time_record_path