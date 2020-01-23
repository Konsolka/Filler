#!/bin/bash

player_1="../$USER.filler"
player_num=1
echo "main player $player_1\n" > 5_game.log
for player_2 in ./players/*
do
	echo "\t\tplayer $player_num = $player_2"
	echo "\t\tplayer $player_num = $player_2" >> 5_game.log
	for map in ./maps/*
	do
		win_time_p1=0
		win_time_p2=0
		i=1
		echo "\tmap = $map"
		echo "\tmap = $map" >> 5_game.log
		while [ $i -le 5 ]; do
			./filler_vm -f $map -p1 $player_1 -p2 $player_2 > /dev/null
			cat ./filler.trace | grep "won"
			cat ./filler.trace | grep "won" >> 5_game.log
			won="$(cat ./filler.trace | grep "won")"
			if [ "$won" = "$player_1 won" ]; then
				win_time_p1=$(( $win_time_p1 + 1 ))
			else
				win_time_p2=$(( $win_time_p2 + 1 ))
			fi
			i=$(( $i + 1 ))
		done
		echo "==== On map {$map} ($player_1) wins [$win_time_p1]\t($player_2) wins [$win_time_p2] ===="
		echo "==== On map {$map} ($player_1) wins [$win_time_p1]\t($player_2) wins [$win_time_p2] ====" >> 5_game.log
		echo
		echo >> 5_game.log
	done
	player_num=$(( $player_num + 1 ))
done
echo "Done check 5_game.log for log"