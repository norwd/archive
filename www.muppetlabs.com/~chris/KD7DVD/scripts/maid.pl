#!/usr/bin/perl

#
# maid.pl : convert Maidenhead locator to latitude and longitude
#           Chris Osburn KD7DVD 020604
#
#           Input:  a list of 6-digit locators on the command line
#           example:  maid cn87un jl14fd jj00aa
# 
#           Output:  Grids and coordinates, one per line
#           example:
#                    Grid: CN87UN : 122 17 30 W / 47 33 45 N
#                    Grid: JL14FD : 002 27 30 E / 24 08 44 N
#                    Grid: JJ00AA : 000 02 30 E / 00 01 15 N
#
#           bugs:  no syntax checking on aruments.
#                  returns the coords for the center of the square
#

  # do this for each argument on commmand line
while (@ARGV)
{
    # grab the next argument
  $loc = shift @ARGV;

    # make it uppercase
  $loc =~ tr/[a-z]/[A-Z]/;

    # convert each character to its ASCII value; create a list of
    # these values in @parts
  @parts = map { ord $_ } split('',$loc);

    # compute longitude from parts
  $long = -180
        + ($parts[0] - 65) * 20 
        + ($parts[2] - 48) * 2 
        + ($parts[4] - 64.5) / 12;

    # compute latitude from parts
  $lat = -90 
       + ($parts[1] - 65) * 10 
       + ($parts[3] - 48) 
       + ($parts[5] - 64.5) / 24;

    # convert longitude to sexagesimal format
  $lx = $long;
  $ld = ($lx < 0.0) ? 'W' : 'E';
  $lx = abs($lx);
  $lh = int $lx;
  $lx -= $lh; $lx *= 60.0;
  $lm = int $lx;
  $lx -= $lm; $lx *= 60.0;
  $ls = int $lx;

    # convert latitude to sexagesimal format
  $bx = $lat;
  $bd = ($bx < 0.0) ? 'S' : 'N';
  $bx = abs($bx);
  $bh = int $bx;
  $bx -= $bh; $bx *= 60.0;
  $bm = int $bx;
  $bx -= $bm; $bx *= 60.0;
  $bs = int $bx;

    # print the result
  printf ("Grid: %s : %3.3d %2.2d %2.2d %s / %2.2d %2.2d %2.2d %s\n", 
          $loc, $lh, $lm, $ls, $ld, $bh, $bm, $bs, $bd);
}
