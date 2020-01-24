#!/bin/bash

player_num=2
game_log="5_game.log"
player_1="./$USER.filler"
filler_vm="$(find . -name "filler_vm")"
echo "Player 1 is $player_1? [y/n]"
read player_ans
case "$player_ans" in
	"y"|"Y"|"yes"|"Yes")
		;;
	"n"|"N"|"no"|"No")
		find . -name "*.filler"
		echo " -Path to player_1"
		read player_1
		;;
esac
clear
echo "==== Be patient ===="
echo "Player 1 is $player_1\n" > $game_log
for player_2 in "$(find . -name "players" -type d)"/*
do
	echo "Player $player_num = $player_2"
	echo "Player $player_num = $player_2" >> $game_log
	for map in "$(find . -name "maps" -type d)"/*
	do
		win_time_p1=0
		win_time_p2=0
		i=1
		echo "\tmap = $map"
		echo "\tmap = $map" >> $game_log
		while [ $i -le 5 ]; do
			$filler_vm -f $map -p1 $player_1 -p2 $player_2 > /dev/null
			won="$(cat ./filler.trace | grep "won")"
			echo "\t\t${won##*/}" >> $game_log
			score="$(cat ./filler.trace | grep "AGAINST")"
			if [ "$won" = "$player_1 won" ]; then
				win_time_p1=$(( $win_time_p1 + 1 ))
			else
				win_time_p2=$(( $win_time_p2 + 1 ))
			fi
			string="$(cat filler.trace | grep "AGAINST")"
			score_player_1=${string%"AGAINST"*}
			score_player_2=${string#*"AGAINST"}
			echo "\t\t\tScore [$score_player_1 | $score_player_2]" >> $game_log
			i=$(( $i + 1 ))
		done
		if [ $win_time_p1 -le $win_time_p2 ]; then
			echo "==== (${player_2##*/}) wins score [$win_time_p1] vs [$win_time_p2] ===="
			echo "=======================================================================" >> $game_log
			echo "Map {$map}" >> $game_log
			echo "Player 1 ($player_1)" >> $game_log
			echo "Player 2 ($player_2)" >> $game_log
			echo "Score player 1 = [$win_time_p1]" >> $game_log
			echo "Score player 2 = [$win_time_p2]" >> $game_log
			echo "Player 2 WON" >> $game_log
			echo "=======================================================================" >> $game_log
		else
			echo "==== (${player_1##*/}) wins score [$win_time_p1] vs [$win_time_p2] ===="
			echo "=======================================================================" >> $game_log
			echo "Map {$map}" >> $game_log
			echo "Player 1 ($player_1)" >> $game_log
			echo "Player 2 ($player_2)" >> $game_log
			echo "Score player 1 = [$win_time_p1]" >> $game_log
			echo "Score player 2 = [$win_time_p2]" >> $game_log
			echo "Player 1 WON" >> $game_log
			echo "=======================================================================" >> $game_log
		fi
		echo
		echo >> $game_log
	done
	echo
	echo >> $game_log
	player_num=$(( $player_num + 1 ))
done
echo "~~~~ Done! Check $game_log for additional info ~~~~"