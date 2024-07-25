#!/bin/sed -f

# Ĉi tiu skripto tradukas la literojn de la norma Esperanto el la
# unikoda utf8-ĉefenigujo <sdtin> en HTML-koditajn literojn de la Ŝava
# alfabeto, kiujn ĝi sendas en la ĉefeligujon <stdout>.  La Ŝava
# alfabeto estas tiu de
#   http://eo.wikipedia.org/wiki/%C5%9Cava_alfabeto aŭ
#   http://esperanto.us/sxava_alfabeto/ aŭ
#   http://kovro.heliohost.org/eo/tools/Sxava/sxava.html
# Neesperantaj signoj restas senŝanĝaj.  Ligaĵojn la skripto ne
# kreas (esperantaj ligaĵoj ja mankas en la tiparoj).  La uskleco
# estas ignorata (la centra punkto ne estas aplikata).
#
# Ekzempla uzo:
# $ echo 'Eĥo-ŝanĝo!' | sxava.sed
# &#66663;&#66649;&#66665;-&#66646;&#66664;&#66677;&#66657;&#66665;!
#
# Sergio Pokrovskij, 2017-02-04, Novosibirsko

s/aŭ/\&#66674;/ig
s/eŭ/\&#66673;/ig
#
s/p/\&#66640;/ig
s/t/\&#66641;/ig
s/k/\&#66642;/ig
s/f/\&#66643;/ig
s/c/\&#66644;/ig
s/s/\&#66645;/ig
s/ŝ/\&#66646;/ig
s/ĉ/\&#66647;/ig
s/ŭ/\&#66648;/ig
s/ĥ/\&#66649;/ig
s/b/\&#66650;/ig
s/d/\&#66651;/ig
s/g/\&#66652;/ig
s/v/\&#66653;/ig
s/z/\&#66655;/ig
s/ĵ/\&#66656;/ig
s/ĝ/\&#66657;/ig
s/j/\&#66672;/ig
s/h/\&#66659;/ig
s/l/\&#66660;/ig
s/i/\&#66662;/ig
s/e/\&#66663;/ig
s/a/\&#66664;/ig
s/o/\&#66665;/ig
s/u/\&#66666;/ig
s/m/\&#66667;/ig
s/r/\&#66670;/ig
s/n/\&#66677;/ig

# Local Variables:
# coding: utf-8
# mode: shell-script
# End:
