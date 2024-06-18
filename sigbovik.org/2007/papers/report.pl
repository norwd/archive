#!/usr/bin/perl

$n = length "name.................................type.........";
for (<*.pdf>) {
 print "$_\n";
 @x = `pdffonts $_`;
 for $line (@x) {
  print $line unless "yes" eq substr($line, $n, 3);
 }
}
