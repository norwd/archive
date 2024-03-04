#!/usr/local/bin/perl -w

# this is a simple command-line program that will add, remove and
# list phone numbers as associated with names.  it uses standard
# Berkeley DB files to store the information (and is therefore rather 
# slow).
#
# basic usage instructions: to add an entry, it's best to enclose the
# arguments in quotes, since most names will be multiple (space-
# separated) words, like "Ian Johnston", and many phone numbers will
# have spaces if an area code is included.  for removing and listing
# entries, the program expects a case-insensitive substring of the 
# name, like "ian" to match "Ian Johnston".  for example:
#
# to add my name: ./phone -add "Ian Johnston" "(206) 555-1212"
# to list entries with my name: ./phone -list ian
# to list all entries: ./phone -list ".*" (any valid perl regex is good)
# to remove entries with my name: ./phone -remove ian
#
# note that this last will ask you before deleting things.
# 
# this program is intended to be a sample of my perl coding ability,
# rather than a truly useful program.  it came from the following URL: 
# http://www.muppetlabs.com/~reaper/
#
# more information about me is available there as well, including my 
# resume, a generic cover letter, and a sample of my C code.
# 
# -- Ian Johnston <reaper@speakeasy.org>

use strict;
use DB_File;
use vars qw($opt_help $opt_add $opt_list $opt_remove);
use Getopt::Long;

#=================================================================
# function prototypes
#=================================================================
sub add_entry($$);
sub list_entries($);
sub remove_entry($);
sub get_matching_entries($);
sub usage();
sub error($$$);

#=================================================================
# "global" variables
#=================================================================
my %phone;			# the hash containing phone info
my $db_file = "phone-db";	# name of the database file
my $db_flags = O_CREAT|O_RDWR;	# flags to pass to dbopen()
my $db_mode = 0644;		# mode with which to create the dbfile
my $write_name;			# the "name" to use in the write() call
my $write_number;		# the "number" to use in the write() call

#=================================================================
# pre-main initialization
#=================================================================
print "The Phone Database, v. 0.0, written by Ian Johnston\n";

GetOptions("add=s", "list:s", "remove=s", "help");

tie (%phone, 'DB_File', $db_file, $db_flags, $db_mode, $DB_HASH) or
			error("tie", "fatal", "couldn't open $db_file");

#=================================================================
# main function
#=================================================================
if ($opt_help)
{
	usage();
}
elsif ($opt_add)    # add a number
{
	add_entry($opt_add, $ARGV[0]);
}
elsif ($opt_list)    # list entries
{
	list_entries($opt_list);
}
elsif ($opt_remove)    # remove entries
{
	remove_entry($opt_remove);
}
else 		   # bogus cmd line args
{
	usage();
}

# clean up
untie %phone;
exit 0;

#=================================================================
# subs
#=================================================================
sub add_entry ($$)
{
	my ($name, $number) = @_;
	my ($var, $i);

	# error condition if we don't get at least 2 args
	unless ($number)
	{
		error("add_entry", "fatal", "missing name and/or number");
	}

	# if there's more than one instance of a name (ie, two "john
	# doe"'s) append a ":1" to it (or 2, if there's already 1, and
	# so on), since the names are used as keys and must be unique.
	if ($phone{$name}) 
	{
		for ($i=1; $phone{"$name:$i"}; $i++)
		{
			$var = $i;
		}

		$var++;
		$name .= ":$var";
	}

	$phone{$name} = $number;

	# don't print the ":1" extensions -- they're for internal use only
	$name =~ s/:\d+$//;

	print "Adding the following entry:\n";
	print "Name: $name\n";
	print "Number: $number\n";
}

sub list_entries ($)
{
	my ($name) = @_;
	my @tmp_entries = get_matching_entries ($name);
	my (@entries, $key);

	if (@tmp_entries)
	{
		@entries = sort (@tmp_entries);
	}
	else
	{
		print "No entries matching '$name'\n";
		return;
	}

	foreach $key (@entries)
	{
		$key =~ s/:\d+$//;
		$write_name = $key;
		$write_number = $phone{$key};
		write;
	}
}

sub remove_entry ($)
{
	my ($name) = @_;
	my @entries = get_matching_entries ($name);
	my $answer;

	error ("remove_entry", "fatal", "must specify a pattern to remove") 
			unless ($name);
	unless (@entries)
	{
		print "No entries matching '$name'\n";
	}

	foreach $name (@entries)
	{
		print "*** $name - $phone{$name}\n";
		print "Do you want to delete this entry? (y/N)\n";
		$answer = getc;

		if ($answer =~ /y/i)
		{
			delete $phone{$name};
		}
	}
}

sub get_matching_entries ($)
{
	my ($name) = @_;
	my (@entries, $key);

	foreach $key (keys %phone)
	{
		if ($key =~ /$name/i)
		{
			push (@entries, $key);
		}
	}

	return @entries;
}

sub usage ()
{
	print STDERR "usage: $0 -[a|l|r] arguments\n";
	print STDERR "-add name number\tadd an entry with 'name' and 'number'\n";
	print STDERR "-list name\t\tlist entries matching 'name' (\".*\" to list all)\n";
	print STDERR "-remove name\t\tinteractively remove the listing[s] matching 'name'\n";
	print STDERR "-help\t\t\tthis message\n";
	untie %phone;
	exit 0;
}

sub error($$$)
{
	my ($func, $severity, $mesg) = @_;
	
	print STDERR "$severity error: $func: $mesg\n";

	if ($severity eq "fatal")
	{
		untie %phone;
		exit 1;
	}
}

#=================================================================
# formats
#=================================================================

format STDOUT_TOP =
Name				Number
------------------------------------------------------------------------
.

format STDOUT =
@<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< @<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
$write_name,			$write_number
.
