files="$(find . -name "*.log")"
if [ "$files" = "" ]; then
	echo "Nothing to delete"
	exit 1
else
	echo " - Deliting"
	find . -name "*.log"
	echo " - Confirm delete [y/n]"
	read ans
	case "$ans" in
		"y"|"Y"|"Yes"|"yes")
			find . -name "*.log" -delete
			echo " - Files deleted"
			;;
		"n"|"N"|"no"|"No")
			echo " - Exiting"
			exit 1
			;;
	esac
fi