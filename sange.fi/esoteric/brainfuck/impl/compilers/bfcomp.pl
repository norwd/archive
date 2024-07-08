#!/usr/bin/perl
# received from Daryl Anderman <corwin.at.webhart.dot.net>

$infile=$ARGV[0];
if($#ARGV !=0) {
     print "Usage:\n./brainfuck.pl inputfile.bf\n";
     exit;
}
open INFILE, $infile or die "Cannot open $infile for read :$!";
open OUTFILE, ">$infile.c" or die "Cannot open $infile.c for write :$!";
%transhash = (">","++p;\n",
               "<","--p;\n",
               "+","++mem[p];\n",
               "-","--mem[p];\n",
               ".","putchar(mem[p]);\n",
               ",","mem[p]=getchar();\n",
               "[","while(mem[p]){\n",
               "]","}\n");
$/=\1;
print "writing $infile.c\n";
print OUTFILE "unsigned int p=0,z=65534;\nchar mem[65535];\n";
print OUTFILE "int main(){\nwhile(z--)mem[z]=0;";
while (<INFILE>) {
     print OUTFILE $transhash{$_};
}
print OUTFILE "}";
print "compiling...\n";
system("cc $infile.c -o $infile.exe");
print "done.\nNow execute ./$infile.exe\n";
