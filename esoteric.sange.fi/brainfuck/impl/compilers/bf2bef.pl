#! /usr/local/bin/perl
# This program is from http://212.16.6.108/~mtve/code/bef/prog/bf2bef/.
# It compiles brainfuck into befunge.

use strict;
use warnings 'all';

my ($BefW, $BefH) = (80, 25);

my ($x, $y, @page, $s, $nl, $maxy, @input, $i);

($x, $y, $maxy, $nl) = (0) x 4;
push @page, [(' ') x $BefW]	for 1 .. $BefH;

sub	pyx
{
	my ($y, $x, $c) = @_;

	$x >= 0 && $x < $BefW && $y >= 0 && $y < $BefH
		or die "internal error #18";
	$page[$y][$x] eq $c or $page[$y][$x] eq ' '
		or die "internal error #19";
	$page[$y][$x] = $c;
}

sub	put
{
	my (@arr) = @_;
	my ($yy, $xx, $str);
	
	($yy, $xx) = ($y, $x);
	for $str (@arr) {
		pyx $y, $x++, $_	for split //, $str;
		$x = $xx;
		++$y < $BefH	or die "sorry, doesn't feet in $BefW*$BefH";
	}
	$maxy = $y	if $y > $maxy;
	$y = $yy;
}

$i = $BefW;
$_ = '';
while ($i) {
	$_ .= "+" . ($i % 9) . "*9";
	$i = int ($i / 9);
}
s/\*9$//;
s/\+0//;
s/\+(\d)$/$1/;
s/\*91$/9/;
put	"          " . (" " x length $_) . "v",
	">        v$_<",
	"|:p0\\0:-1<",
	">";
$y += 3;
$x++;

local $/;
$_ = <>;
s/[^+\-<>\[\].,]//sg;
@input = /(\+{1,9}|\-{1,9}|<{1,9}|>{1,9}|\[|\]|\.|,)/g;

for $i (0 .. $#input)
{
	$_ = $input[$i];
	if      (/\+/) {
		put	"v>",		# ::0g N+\0p
			"vp",
			":0",
			":\\",
			"0+",
			"g" . length $_,	# gosh, hate superfluous $_
			">^";
	} elsif (/\-/) {
		put	"v>",		# ::0g N-\0p
			"vp",
			":0",
			":\\",
			"0-",
			"g" . length $_,
			">^";
	} elsif (/>/) {
		put	"v>",		# N+
			"v ",
			(length $_) . "+",
			">^";
	} elsif (/</) {
		put	"v>",		# N-
			"v ",
			(length $_) . "-",
			">^";
	} elsif (/\[/) {
		$nl++;
		put	"v>#",		# :0g!|
			"v|",
			":>v",
			"0#",
			"g!",
			">^";
		$y += 1;
	} elsif (/\]/) {
		warn "are you sure? []"
			if $i > 0 && $input[$i - 1] eq '[';
		$nl-- > 0	or die "unbalanced square brackets";
		$y -= 1;
		$x -= 2		if $i > 0 && $input[$i - 1] ne ']';
		put	"#<";
		$page[$y + 1][$x + 1] = ' '	if $page[$y + 1][$x + 1] eq '>';
		pyx $y + 1, $x + 1, '^';
	} elsif (/\./) {
		put	"v>",		# :0 g,
			"v ",
			":,",
			"0g",
			">^";
	} elsif (/,/) {
		put	"v>",		# :~ \0p
			"vp",
			":0",
			"~\\",
			">^";
	} else {
		die "internal error #42";
	}
	$x += 2;
	if ($x >= $BefW - $nl * 2 -
	 ($i < $#input ?
		$input[$i + 1] eq '[' ? 4 :
		$input[$i + 1] eq ']' && !/\]/ ? 0 :
		2
	 : 0)) {
		pyx $y   , $x, 'v';
		pyx $maxy, $x, '<';
		pyx $maxy,  0, 'v';
		pyx $maxy + $nl * 3 + 1, 0, '>';
		for (1 .. $nl) {
			pyx $y - $nl + $_ - 1, $BefW - $_ * 2 - 1, '#';
			pyx $y - $nl + $_ - 1, $BefW - $_ * 2    , '<';
			pyx $y - $nl + $_ - 1, $BefW - $_ * 2 + 1, 'v';
			pyx $maxy + $_ * 2 - 1, $BefW - $_ * 2    , '^';
			pyx $maxy + $_ * 2    , $BefW - $_ * 2 + 1, '<';
			pyx $maxy + $_ * 2 - 1, $_ * 2 - 1, '>';
			pyx $maxy + $_ * 2    , $_ * 2    , 'v';
			pyx $maxy + $nl * 2 + $_, $_ * 2 - 1, '^';
			pyx $maxy + $nl * 2 + $_, $_ * 2    , '>';
			pyx $maxy + $nl * 2 + $_, $_ * 2 + 1, '#';
		}
		$y = $maxy + $nl * 3 + 1;
		$x = $nl * 2 + 1;
	}
}
$nl == 0	or die "unclosed square brackets";
pyx $y, $x, '@';

$s = '';
$s .= (join '', @{ $_ }) . "\n"	for @page;
$s =~ s/ +\n/\n/sg;
$s =~ s/\n+$/\n/s;
print $s;
