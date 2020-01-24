#!/bin/bash
echo "\t==== Welcome to script made by mburl ===="
echo "===== Please be careful and pass only valid files :) ======"
echo
echo " - Map file located in resources/maps? [y/n]"
read map_ans
case "$map_ans" in
	"y"|"Y"|"yes"|"Yes")
		ls resources/maps/
		echo " - Write map file from given"
		read file_path
		file_path="./resources/maps/$file_path"
		;;
	"n"|"N"|"no"|"No")
		find . -type d | grep -v git
		echo " - Write path to map"
		read file_path
		;;
esac
echo " - Player 1 is $USER.filler? [y/n]"
read ans
case "$ans" in
	"y"|"Y"|"yes"|"Yes")
		player_1="./$USER.filler"
		;;
	"n"|"N"|"no"|"No")
		find . -name "*.filler"
		echo " - Path to player 1"
		read player_1
		;;
esac
echo " - Default player 2 is abanlin.filler y/n?"
read ans
case "$ans" in
	"y"|"Y"|"yes"|"Yes")
		player_2="$( find . -name "abanlin.filler" )"
		echo $player_2
		;;
	"n"|"N"|"no"|"No")
		echo " - Path to player 2"
		find . -name "*.filler"
		read player_2
		;;
esac
filler_vm="$(find . -name "filler_vm")"
echo
echo $filler_vm
echo $file_path
echo $player_1
echo $player_2
echo
$filler_vm -f $file_path -p1 $player_1 -p2 $player_2 > game.log
echo "\t==== File game.log has been created ===="
read -p " - Exec file with vis? (y/n): " item
case "$item" in
	"y"|"Y"|"yes"|"Yes")
		vis="$(find . -type f -name "vis")"
		$vis -f game.log
		;;
	"n"|"N"|"no"|"No")
		echo "Not executing visualization"
		exit 1
		;;
esac