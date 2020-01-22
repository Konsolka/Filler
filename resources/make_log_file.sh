#!/bin/bash
echo "Path to map"
read file_path
echo "Default player 1 is mburl y/n?"
read ans
case "$ans" in
	"y"|"Y"|"yes"|"Yes") player_1="../mburl.filler"
		;;
	"n"|"N"|"no"|"No")
		echo "Path to player 1"
		read player_1
		;;
esac
echo "Default player 2 is abanlin.filler y/n?"
read ans
case "$ans" in
	"y"|"Y"|"yes"|"Yes") player_2="players/abanlin.filler"
		;;
	"n"|"N"|"no"|"No")
		echo "Path to player 2"
		read player_2
		;;
esac
./filler_vm -f $file_path -p1 $player_1 -p2 $player_2 > game.log
echo "File game.log has been created"
read -p "Exec file with vis? (y/n): " item
	case "$item" in
		"y"|"Y"|"yes"|"Yes") ../vis -f game.log
			;;
		"n"|"N"|"no"|"No") echo "Not executing visualization"
			exit 1
			;;
	esac