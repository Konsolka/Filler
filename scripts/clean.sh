files="$(find . -name "*.log")"
files_trace="$(find . -name "filler.trace")"
if [ "$files" = "" ]; then
	echo " - Nothing to clean :)"
else
	echo " - Deliting"
	find . -name "*.log"
	echo " - Confirm delete [y/n]"
	read ans
	case "$ans" in
		"y"|"Y"|"Yes"|"yes")
			find . -name "*.log" -delete
			echo " - Files has been deleted"
			;;
		"n"|"N"|"no"|"No")
			;;
	esac
fi

if [ "$files_trace" = "" ]; then
	echo " - Exiting"
	exit 1
fi
echo " - Delete filler trace? [y/n]"
read ans
case "$ans" in
	"y"|"Y"|"Yes"|"yes")
		find . -name "filler.trace" -delete
		echo " - filler.trace has been deleted"
		;;
	"n"|"N"|"no"|"No")
		echo " - Exiting"
		;;
esac