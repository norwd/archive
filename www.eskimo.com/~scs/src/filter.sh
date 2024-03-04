: run a filter command on a number of files, in-place:
#	filter [options] command files
# -b: backup original file to .bak
# -p: preserve modtime
# -s: don't replace if unchanged by filter
# -v: verbose
#
# See http://www.eskimo.com/~scs/src/#filter for full documentation
# and possible updates.
#
# This program is in the Public Domain.
#
# --scs 2001-04-26

usage="usage: $0 command files"

if test -e / 2> /dev/null
then	exists="test -e"
else	exists="test -f"
fi

iflag=no
pflag=
bakflag=no
checksame=no
verbose=no
printedhelp=no

mv="/bin/mv -f"
cp="/bin/cp -f"
rm="/bin/rm -f"
# or for older machines might need e.g. "/bin/mv </dev/null"

# a command to copy the mtime of one file to another
# for GNU/Linux systems can use "touch -r"
# if available, can use scs fildate utility
# if set to ".intuit" will try to figure out what can use
# if set to ".none", won't try/be able to preserve mtimes

#fildatecmd="touch -r"
#fildatecmd="fildate -f"
fildatecmd=".intuit"
#fildatecmd=".none"

# a strategy for copying the rwx mode of one file to another

#modecopy="chmod-r"	 # use GNU chmod --reference=
#modecopy="stat+chmod"	 # use scs stat(1) + stock chmod
modecopy=".intuit"	 # try to figure out
#modecopy=".none"

while expr "$1" : "[-]" > /dev/null
do	case $1 in
		-\?|-h|-help|--help)
			echo $usage
			echo "options:"
			echo "	-b	backup original file to .bak"
			echo "	-i	ignore errors returned by command"
			echo "	-p	preserve modtime"
			echo "	-s	don't replace if unchanged by filter"
			echo "	-v	verbose"
			echo "	-?,-h	print this help"
			printedhelp=yes;;
		-b)	bakflag=yes;;
		-i)	iflag=yes;;
		-p)
			if test "$fildatecmd" = ".intuit"
			then
				tf=/tmp/tf$$
				touch -r / $tf 2> /dev/null
				if test $? -eq 0
				then	fildatecmd="touch -r"
				else
					touch $tf
					fildate -f / $tf 2> /dev/null
					if test $? -eq 0
					then	fildatecmd="fildate -f"
					else	fildatecmd=".none"
					fi
				fi

				$rm $tf

#				echo "(intuited fildatecmd as \"$fildatecmd\")" >&2
			fi

			if test "$fildatecmd" != ".none"
			then	pflag="-p"
			else	echo "$0: don't know how to preserve mtime; $1 ignored" >&2
			fi;;
		-s)	checksame=yes;;
		-v)	verbose=yes;;
		*)	echo "$0: unrecognized option $1" 1>&2;;
	esac
	shift
done

if test $# -lt 2
then
	if test $printedhelp = yes; then exit 0; fi
	echo $usage 1>&2
	exit 1
fi

PROG=$1
shift

status=0

for I in "$@"
do
	if test -d "$I"
	then
		echo "$0: $I: is a directory" 1>&2
	elif test -w "$I"
	then
		tmpfile=`echo "$I" | sed "s/[^/]*$/tmp$$/"`

		if test $verbose = "yes"
			then echo "$0: filtering $I through $PROG" 1>&2
		fi

		# 2003-07-24: quotes so "sed '/^$x	/s/^/# /'" works

		eval "$PROG" < "$I" > "$tmpfile"
		stat=$?

		if test $stat -eq 0 -a $checksame = "yes" && cmp -s "$I" "$tmpfile"
		then
			echo "$0: $I unchanged by filter"
			stat=1
		fi

		if test $stat -eq 0 -o "$iflag" = "yes"
		then
			# gotta try to preserve file's rwx mode, and this,
			# too, is tricky; gotta intuit how to do it,
			# similar to the way we intuited fildatecmd

			if test "$modecopy" = ".intuit"
			then
				tf=/tmp/tf$$
				touch $tf
				chmod --reference=/ $tf 2> /dev/null
				if test $? -eq 0
				then	modecopy="chmod-r"
				else
					stat -vv -p $tf > /dev/null 2>&1
					if test $? -eq 0
					then	modecopy="stat+chmod"
					else	modecopy=".none"
					fi
				fi

				$rm $tf

#				echo "(intuited modecopy as \"$modecopy\")" >&2

				if test "$modecopy" = ".none"
				then	echo "$0: don't know how to preserve file modes" >&2
				fi
			fi

			case "$modecopy" in

				"chmod-r")	chmod --reference="$I" "$tmpfile";;
				"stat+chmod")	chmod `stat -vv -p "$I" | sed 's/.*\(....\)$/\1/'` "$tmpfile";;
			esac
			
			if test "$pflag" = "-p"
			then
				# could arguably try to handle .intuit here

				if expr "$fildatecmd" : '\.' > /dev/null
				then	echo "$0: can't preserve mtime of $I" >&2
				else	$fildatecmd "$I" "$tmpfile"
				fi
			fi

			# if file has links or other owner, gotta cp back
			# (theoretically also if different group ownership...)
			# (looks like could use new test -O and -G?)

			# (or maybe should just always cp back)

			eval `ls -l "$I" |
				awk '{print "nlink=" $2 "; owner=" $3;}'`

			if test $nlink -eq 1 -a \
				$owner = `whoami` -a \
				! -L "$I"
			then
				if test $bakflag = yes
				then
					if test $verbose = "yes"
					then	echo "$0: backing up original $I as $I.bak" 1>&2
					fi
					$mv "$I" "$I".bak
				fi

				if test $verbose = "yes"
				then	echo "$0: replacing $I" 1>&2
				fi
				$mv "$tmpfile" "$I"
				if test $? -ne 0
				then
					echo "error replacing $I" 1>&2
					$rm "$tmpfile"
					status=1
				fi
			else
				if test $bakflag = yes
				then
					if test $verbose = "yes"
					then	echo "$0: backing up original $I as $I.bak" 1>&2
					fi
					$cp -p "$I" "$I".bak
				fi
				if test $verbose = "yes"
				then	echo "$0: rewriting $I" 1>&2
				fi
				$cp $pflag "$tmpfile" "$I"
				if test $? -ne 0
				then	echo "error rewriting $I" 1>&2
					status=1
				fi
				$rm "$tmpfile"
			fi
		else
			$rm "$tmpfile"
			echo "$0: $I not replaced" 1>&2
			status=1
		fi
	elif $exists $I
	then
		echo "$0: $I: no write" 1>&2
		status=1
	else
		echo "$0: $I: nonexistent" 1>&2
		status=1
	fi
done

exit $status
