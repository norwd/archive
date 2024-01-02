<!DOCTYPE html>
<head>
  <meta charset="utf-8">
  
    <title>Languages | Cat's Eye Technologies</title>
  
  
    <meta name="description" content="Languages at Chris Pressey's modest esolang concern; serves as a database and gallery of open-source projects, primarily esoteric programming languages." />
  
  <link rel="shortcut icon" type="image/x-icon" href="/favicon.ico" />
  
  
  
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
  
  
    <meta name="twitter:card" content="summary" />
    <meta name="twitter:site" content="@catseye_tc" />
    <meta name="twitter:creator" content="@catseye_tc" />
    <meta name="twitter:title" content="Languages" />
    <meta name="twitter:description" content="Languages at Cat's Eye Technologies" />
    
      <meta name="twitter:image" content="https://static.catseye.tc/images/illustrations/Abacus_(PSF).jpg" />
    
  
  
    <link rel="stylesheet" type="text/css" href="/stylesheet/chrysoberyl3.css" />
  
</head>
<body>
  <div class="pageboundary">
    
      <header>
        <nav id="breadcrumbs">
          <p><a href="/">catseye.tc</a> » <a href="/node/Chrysoberyl">Chrysoberyl</a> »</p>
        </nav>
        <hgroup id="heading">
          <h1>Languages</h1>
        </hgroup>
      </header>
    
    
  <article>
    
      <img class="illustration" src="https://static.catseye.tc/images/illustrations/Abacus_(PSF).jpg" alt="An illustration for this article" />
    
    <p>This is a list of languages, in chronological order, that have been designed under the
auspices of Cat's Eye Technologies.  For more information on these languages,
<a href="#about-these-languages">see below</a>.</p>
<p>The distinction between a Language, a <a href="Formats.md">Format</a>, and an
<a href="Automata.md">Automaton</a> is not always cut-and-dried, so if you can't find what
you're looking for here, try those lists as well.</p>
    
      <h3 id="full-moon-fever"><a href="#full-moon-fever">Full Moon Fever</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
        
      </div>

      
      <ul>
        
          
            <li>type: Animation Language</li>
          
        
          
            <li>inception-date: ca 1993</li>
          
        
          
            <li>genre: DSL</li>
          
        
          
            <li>development-stage: archived</li>
          
        
          
            <li>computational-class: known not Turing-complete</li>
          
        
          
            <li>paradigms: Imperative</li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>GO 1 2 CLREOL CENTRE "Enter... the Stupid Guard." 2
GO 1 3 CLREOL
PAUSE 70
GO 76 19
PRINT "0"
PAUSE 20
DO 20
    LF PRINT " " LF LF PRINT "0" PAUSE 5;
</code></pre>
<p>Full Moon Fever is a language for describing ASCII animations.
It was used to deliver animated screens on Chris Pressey's BBS
(when it was operational in the early 90's) via <a href="../article/Project%20Dependencies.md#ansi-terminal">ANSI Terminal</a> control codes.
This probably counts as his first proper language, even though
it wasn't a full programming language, because it had
the usual machinery (syntax, parser, interpreter...)
Lives on, in a somewhat distended form, as a sub-language of
<a href="../article/Languages.md#illgol">ILLGOL</a>.</p>
<p>The name "Full Moon Fever" has nothing at all to do with lycanthropy;
I believe it came from mis-remembering the title of the song
"Full Moon Boogie" by <a href="https://en.wikipedia.org/wiki/Jan_Hammer">Jan Hammer</a> and <a href="https://en.wikipedia.org/wiki/Jerry_Goodman">Jerry Goodman</a>.</p>
    
      <h3 id="maentwrog"><a href="#maentwrog">Maentwrog</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Maentwrog">Browse files</a>
        
        
          <a class="button" href="/distribution/Maentwrog_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: ca 1993</li>
          
        
          
            <li>genre: Pedagogical language</li>
          
        
          
            <li>development-stage: archival</li>
          
        
          
            <li>computational-class: known not Turing-complete</li>
          
        
          
            <li>paradigms: Stack-based</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Maentwrog_distribution">Maentwrog distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Maentwrog">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>*a *b *c
0 =a 1 =b
: fib a b + =c c . b =a c =b c 100000 &lt; @fib ;
1 . fib
</code></pre>
<p>Maentwrog is an RPN-calculator-turned-FORTH-interpreter which
probably counts as <a href="../article/General%20Information.md#chris-pressey">Chris Pressey</a>'s first <em>proper</em> programming language.
It was implemented on his Amiga 500 in 1993, then lost and unearthed
multiple times.  It is hardly remarkable, save that it spawned <a href="../article/Languages.md#befunge-93">Befunge-93</a>.</p>
<p>There are no extant example programs from the time the language was first
implemented — I tried writing the Sieve of Eratosthenes in it once,
but never got it to work, probably because <code>==</code> was not
implemented correctly.  Recently, example programs and a description of the
language (which has become the provisional spec) have been provided by
<a href="https://esolangs.org/wiki/User:Marinus">Marinus</a> — thanks Marinus!</p>
<p>Also included in the Maentwrog distribution, just for fun, are some other
contemporaneous C programs of mine: an RPN
calculator which was the predecessor of Maentwrog, a simple
recursive-descent expression parser, and a simple cellular automata
parser (a distant ancestor of <a href="../article/Languages.md#alpaca">ALPACA</a>, perhaps?)</p>
<p>Maentwrog is the name of a town in Wales, but the usage of its name
for this language came via Douglas Adams' "The Meaning of Liff",
wherein it is defined thusly:
"MAENTWROG (n. Welsh) Celtic word for a computer spelling mistake."</p>
<h4 id="reference-implementation-maentwc">Reference Implementation: maentw.c</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#ansi-c">ANSI C</a></li>
</ul>
    
      <h3 id="befunge-93"><a href="#befunge-93">Befunge-93</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="https://archive.org/details/bef-2.11-dos">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Befunge-93">Browse files</a>
        
        
          <a class="button" href="/distribution/Befunge-93_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Sep 1993</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: can simulate some push-down automata</li>
          
        
          
            <li>influences: <a href="../article/Languages.md#maentwrog">Maentwrog</a>, <a href="https://esolangs.org/wiki/brainfuck">brainfuck</a>, <a href="https://esolangs.org/wiki/FALSE">FALSE</a></li>
          
        
          
            <li>paradigms: Stack-based, 2-dimensional, Self-modifying</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Befunge-93_distribution">Befunge-93 distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Befunge-93">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://archive.org/details/bef-2.11-dos">archive.org</a></li>
          
        
          
            <li>jnlp @ <a href="https://archive.org/details/yoob-rel_0_3_2018_1128">archive.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code> v    &lt;
&gt;?"/",^
 &gt;"\",^
</code></pre>
<p>Befunge-93 is an esoteric programming language where the program exists
in a two-dimensional grid of cells, where each cell contains a single
instruction, and execution can proceed in any cardinal direction across this
grid — not just left-to-right, but also right-to-left, top-to-bottom, and
bottom-to-top.</p>
<p>One of the more popular languages I ever designed and implemented.
Eventually begat <a href="../article/Languages.md#befunge-97">Befunge-97</a>, <a href="../article/Languages.md#funge-98">Funge-98</a>, and <a href="../article/Languages.md#wierd">Wierd</a>, and doubtless influenced
many others.  Cited in the New Hacker's Dictionary.</p>
<h4 id="reference-implementation-bef">Reference Implementation: bef</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#ansi-c">ANSI C</a></li>
</ul>
<h4 id="implementation-tccatseyeyoobbefunge93">Implementation: tc.catseye.yoob.befunge93</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#java">Java</a></li>
<li>host-platform: <a href="../article/Archived.md#yoob">yoob</a></li>
</ul>
    
      <h3 id="wierd"><a href="#wierd">Wierd</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Wierd (John Colagioia)">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Wierd">Browse files</a>
        
        
          <a class="button" href="/distribution/Wierd_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>authors: Chris Pressey, John Colagioia, and Ben Olmstead</li>
          
        
          
            <li>inception-date: 1997</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>influences: <a href="https://esolangs.org/wiki/brainfuck">brainfuck</a>, <a href="../article/Languages.md#befunge-93">Befunge-93</a></li>
          
        
          
            <li>paradigms: Stack-based, 2-dimensional, Angular</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Wierd_distribution">Wierd distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Wierd">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Wierd (John Colagioia)">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program (written by Milo van Handel):</p>
<pre><code>*
 *
  *
   *
  * *  **
 *   ** *
  **     **
    *      *
    *     *
    *     *
    *      *
    *     **
    *    *
    * ** *
    **  *
</code></pre>
<p>Wierd is a programming language, inspired somewhat by <a href="../article/Languages.md#befunge-93">Befunge-93</a> and
<a href="https://esolangs.org/wiki/brainfuck">brainfuck</a>, where instructions are not determined by the symbols in a
sequence of symbols, but by the <em>bends</em> in a sequence of symbols.</p>
<p>The original Wierd, designed during a three-way email conversation
between Chris Pressey, John Colagioia, and Ben Olmstead, is
probably lost and gone forever, but two dialects have been specified
(sorta) and implemented: <a href="../article/Languages.md#wierd">Wierd (John Colagioia)</a> and
<a href="../article/Languages.md#wierd">Wierd (Milo van Handel)</a>.</p>
<h4 id="implementation-wierdc-john-colagioia">Implementation: wierd.c (John Colagioia)</h4>
<ul>
<li>authors: John Colagioia</li>
<li>license: Unknown license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#ansi-c">ANSI C</a></li>
</ul>
<h4 id="implementation-wierdc-milo-van-handel">Implementation: wierd.c (Milo van Handel)</h4>
<ul>
<li>authors: Milo van Handel</li>
<li>license: Unknown license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#ansi-c">ANSI C</a></li>
</ul>
<h4 id="implementation-wierd-jncjs">Implementation: wierd-jnc.js</h4>
<ul>
<li>authors: Chris Pressey</li>
<li>license: Unknown license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#javascript">Javascript</a></li>
<li>host-platform: <a href="https://www.w3.org/TR/html5/">HTML5</a></li>
</ul>
    
      <h3 id="befunge-97"><a href="#befunge-97">Befunge-97</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Dec 25, 1997</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: lost</li>
          
        
          
            <li>computational-class: ???</li>
          
        
          
            <li>influences: <a href="../article/Languages.md#befunge-93">Befunge-93</a></li>
          
        
          
            <li>paradigms: Stack-based, 2-dimensional, Self-modifying</li>
          
        
      </ul>
      <p>Product of the <a href="https://esolangs.org/wiki/Befunge">Befunge Mailing List Working Group</a>.</p>
<p>Befunge-97 was an unimplemented attempt to design a successor to <a href="../article/Languages.md#befunge-93">Befunge-93</a>.
The design, however, was not successful — it has been described as
"brain-damaged" — primarily due to the fact that separate processes were specified
as sharing a single stack.</p>
    
      <h3 id="alpaca"><a href="#alpaca">ALPACA</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/ALPACA">Browse files</a>
        
        
          <a class="button" href="/distribution/ALPACA_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: 1998</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: ???</li>
          
        
          
            <li>paradigms: Metalanguage, Object-oriented</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/ALPACA_distribution">ALPACA distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>/* John Conway's Game of Life, expressed in ALPACA. */
state Dead  " " to Alive when 3 Alive and 5 Dead;
state Alive "*" to Dead when 4 Alive or 7 Dead.
</code></pre>
<p>ALPACA is a meta-language for describing cellular automata.</p>
<p>It stands for "A Language for the Pithy Articulation of Cellular Automata".
The acronym used to be "A Language for Programming Arbitrary Cellular Automata".
This was not quite accurate, as the automata are not in fact arbitrary, so I changed
it.</p>
<p>ALPACA is one of the few of my languages in which I've actually implemented
other languages (or, well, cellular automata — close enough).</p>
<h4 id="reference-implementation-alpacapl">Reference Implementation: alpaca.pl</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: compiler</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#perl">Perl</a></li>
<li>target-language: <a href="../article/Project%20Dependencies.md#perl">Perl</a></li>
</ul>
<h4 id="reference-implementation-alpaca-python">Reference Implementation: alpaca (Python)</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: compiler</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
<li>target-language: <a href="../article/Project%20Dependencies.md#javascript">Javascript</a></li>
</ul>
    
      <h3 id="funge-98"><a href="#funge-98">Funge-98</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Funge-98">Browse files</a>
        
        
          <a class="button" href="/distribution/Funge-98_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language Family</li>
          
        
          
            <li>inception-date: Sep 11, 1998</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: Turing-complete</li>
          
        
          
            <li>influences: <a href="../article/Languages.md#befunge-93">Befunge-93</a>, <a href="../article/Languages.md#befunge-97">Befunge-97</a></li>
          
        
          
            <li>paradigms: Stack-based, Self-modifying</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Funge-98_distribution">Funge-98 distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>&gt;&gt;#v?v
^,A' &lt;
 ^ C'
    T
 ^ &lt;&lt;
    G
    '
</code></pre>
<p>Product of the <a href="https://esolangs.org/wiki/Befunge">Befunge Mailing List Working Group</a>.</p>
<p>Funge-98 is a family of programming languages designed as the successor
to <a href="../article/Languages.md#befunge-93">Befunge-93</a>.  It generalizes Befunge-93's two-dimensional nature
somewhat, defining languages in one dimension (<a href="../article/Languages.md#unefunge-98">Unefunge-98</a>),
two dimensions (<a href="../article/Languages.md#befunge-98">Befunge-98</a>), and three dimensions (<a href="../article/Languages.md#trefunge-98">Trefunge-98</a>),
and suggests possibilities for other dimensions and topologies (but does
not specify exactly how they look or would behave.)
It also makes the playfield unbounded, allowing the language to be
<a href="https://esolangs.org/wiki/Turing-complete">Turing-complete</a>, and tries to define mechanisms for interacting with the
operating system and engaging extensions to the language.</p>
    
      <h3 id="befunge-98"><a href="#befunge-98">Befunge-98</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>genre: Esolang</li>
          
        
      </ul>
      <p>Befunge-98 is the realization of <a href="../article/Languages.md#funge-98">Funge-98</a> in two dimensions.</p>
    
      <h3 id="trefunge-98"><a href="#trefunge-98">Trefunge-98</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>genre: Esolang</li>
          
        
      </ul>
      <p>Trefunge-98 is the realization of <a href="../article/Languages.md#funge-98">Funge-98</a> in three dimensions.</p>
    
      <h3 id="unefunge-98"><a href="#unefunge-98">Unefunge-98</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>genre: Esolang</li>
          
        
      </ul>
      <p>Unefunge-98 is the realization of <a href="../article/Languages.md#funge-98">Funge-98</a> in one dimension.</p>
    
      <h3 id="mdpn"><a href="#mdpn">MDPN</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Specs-on-Spec">Browse files</a>
        
        
          <a class="button" href="/distribution/Specs_on_Spec_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Meta-language</li>
          
        
          
            <li>inception-date: 1999</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: ???</li>
          
        
          
            <li>paradigms: Metalanguage</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Specs_on_Spec_distribution">Specs on Spec distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>Box ::= "+" {"-"}^(w) r(-90) "+" "||" {"|"}^(h) r(-90)
        "+" {"-"}^(w) r(-90) "+" "||" {"|"}^(h) r(-90)
</code></pre>
<p>MDPN is a meta-language for describing multi-directional and
multi-dimensional languages.</p>
    
      <h3 id="shelta"><a href="#shelta">Shelta</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Shelta">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Shelta">Browse files</a>
        
        
          <a class="button" href="/distribution/Shelta_distribution">Download</a>
        
      </div>

      
        <div>
          
            
              <img alt="An example session with Shelta" src="https://static.catseye.tc/images/screenshots/Shelta.png" />
            
          
        </div>
      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: ca Jul 1999</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: ???</li>
          
        
          
            <li>paradigms: Stack-based</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Shelta_distribution">Shelta distribution</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Shelta">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>[ `Hello, _32 `world! _13 _10 ] \15 outs \0 halt
</code></pre>
<p>Shelta is an extremely minimal Forth-like language with barely
any semantics; it relies on inline machine code to write anything resembling
an actual program in it. In the spirit of compilers for languages such as <a href="https://esolangs.org/wiki/FALSE">FALSE</a>
and <a href="https://esolangs.org/wiki/brainfuck">brainfuck</a>, a Shelta-to-8086 compiler was implemented (with help from
<a href="https://esolangs.org/wiki/Ben_Olmstead">Ben Olmstead</a>) in less than 512 bytes of <a href="../article/Project%20Dependencies.md#ibm-pc-compatible">80286 machine code</a>. What's more,
it's also been bootstrapped — that is to say, a Shelta compiler was
written in Shelta, which was compiled with the original compiler, and then
compiled again with the resulting compiler, producing a wholly self-hosted
executable!</p>
<h4 id="reference-implementation-shelta">Reference Implementation: shelta</h4>
<ul>
<li>license: Freely Redistributable</li>
<li>implementation-type: compiler</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#nasm">NASM Assembler</a></li>
<li>target-language: <a href="../article/Project%20Dependencies.md#ibm-pc-compatible">x86 machine code</a></li>
</ul>
<h4 id="implementation-sheltas">Implementation: sheltas</h4>
<ul>
<li>license: Freely Redistributable</li>
<li>implementation-type: compiler</li>
<li>host-language: <a href="../article/Languages.md#shelta">Shelta</a></li>
<li>target-language: <a href="../article/Project%20Dependencies.md#ibm-pc-compatible">x86 machine code</a></li>
</ul>
    
      <h3 id="bear-food"><a href="#bear-food">Bear Food</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: ca Dec 1999</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: lost</li>
          
        
          
            <li>computational-class: ???</li>
          
        
          
            <li>paradigms: Stack-based</li>
          
        
      </ul>
      <p>Bear Food was a horrible language defined by an interpreter that
evolved (no... let's be honest, it <em>devolved</em>) from a small piece of example
code showing how to parse and intepret a simple reverse-polish notation language.
This same example code also took a very divergent line of evolution, eventually
becoming the programming language <a href="https://esolangs.org/wiki/Var'aq">Var'aq</a>.</p>
<h4 id="reference-implementation-bearfoodpl">Reference Implementation: bearfood.pl</h4>
<ul>
<li>license: Unknown license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#perl">Perl</a></li>
</ul>
    
      <h3 id="sally"><a href="#sally">Sally</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Sally">Browse files</a>
        
        
          <a class="button" href="/distribution/Sally_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: 2000</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: ???</li>
          
        
          
            <li>paradigms: Functional</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Sally_distribution">Sally distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>stdlib
int factorial int if $1 mul $1 factorial sub $1 1 1
int main int factorial $1
</code></pre>
<p>Sally is a cute but naive little functional language with a minimal syntax,
a strict type system, and some unusual rules for parameters and return values.</p>
<h4 id="reference-implementation-sally2c">Reference Implementation: sally2c</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: compiler</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#ansi-c">ANSI C</a></li>
<li>target-language: <a href="../article/Project%20Dependencies.md#ansi-c">ANSI C</a></li>
</ul>
    
      <h3 id="illgol"><a href="#illgol">ILLGOL</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/ILLGOL">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Illgol-Grand-Mal">Browse files</a>
        
        
          <a class="button" href="/distribution/Illgol:_Grand_Mal">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: ca Apr 2000</li>
          
        
          
            <li>genre: Joke language</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: ???</li>
          
        
          
            <li>paradigms: Imperative</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Illgol:_Grand_Mal">Illgol: Grand Mal</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/ILLGOL">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/ILLGOL">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>NB eh.ill
10 *f = { print str(#0), EoL };
20 do f(1);
30 don't f;
40 do f(2);
50 reinstate f;
60 do f(3);
FIN
</code></pre>
<p>ILLGOL is a joke language which parodies the sort of language designed by the
sheer fact that a compiler for it has been hacked together.</p>
<h4 id="reference-implementation-illgolexe">Reference Implementation: illgol.exe</h4>
<ul>
<li>license: Unknown license</li>
<li>implementation-type: compiler</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#ansi-c">ANSI C</a></li>
<li>target-language: <a href="../article/Project%20Dependencies.md#ibm-pc-compatible">x86 machine code</a></li>
<li>in-distributions: <a href="https://catseye.tc/distribution/ILLGOL_distribution">ILLGOL distribution</a>, <a href="https://catseye.tc/distribution/Illgol:_Grand_Mal">Illgol: Grand Mal</a></li>
</ul>
    
      <h3 id="illgola-2"><a href="#illgola-2">Illgola-2</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>genre: Joke language</li>
          
        
          
            <li>in-distributions: <a href="https://catseye.tc/distribution/Illgola-2_distribution">Illgola-2 distribution</a>, <a href="https://catseye.tc/distribution/Illgol:_Grand_Mal">Illgol: Grand Mal</a></li>
          
        
      </ul>
      <p>Successor to <a href="../article/Languages.md#illgol">ILLGOL</a>.</p>
    
      <h3 id="illberon"><a href="#illberon">Illberon</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>genre: Joke language</li>
          
        
          
            <li>in-distributions: <a href="https://catseye.tc/distribution/Illberon_distribution">Illberon distribution</a>, <a href="https://catseye.tc/distribution/Illgol:_Grand_Mal">Illgol: Grand Mal</a></li>
          
        
      </ul>
      <p>Successor to <a href="../article/Languages.md#illgola-2">Illgola-2</a>.</p>
    
      <h3 id="open-sores-illgol"><a href="#open-sores-illgol">Open Sores Illgol##</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>genre: Joke language</li>
          
        
          
            <li>in-distributions: <a href="https://catseye.tc/distribution/Illgol:_Grand_Mal">Illgol: Grand Mal</a></li>
          
        
      </ul>
      <p>Successor to <a href="../article/Languages.md#illberon">Illberon</a>.</p>
    
      <h3 id="apple-befunge"><a href="#apple-befunge">Apple Befunge</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="https://archive.org/details/apple-befunge-1.1-2014.0819">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Apple-Befunge">Browse files</a>
        
        
          <a class="button" href="/distribution/Apple_Befunge_distribution">Download</a>
        
      </div>

      
        <div>
          
            
              <img alt="Apple Befunge" src="https://static.catseye.tc/images/screenshots/Apple%20Befunge.png" />
            
          
        </div>
      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Jul 3, 2000</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>variant-of: <a href="../article/Languages.md#befunge-93">Befunge-93</a></li>
          
        
          
            <li>development-stage: archival</li>
          
        
          
            <li>paradigms: Stack-based, 2-dimensional, Self-modifying</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Apple_Befunge_distribution">Apple Befunge distribution</a></li>
          
        
          
            <li>online @ <a href="https://archive.org/details/apple-befunge-1.1-2014.0819">archive.org</a></li>
          
        
      </ul>
      <p>Apple Befunge is a variant of Befunge for the Apple ][+ which resembles
Befunge-93, with some extra Befunge-96-esque instructions and some
Apple ][+-specific instructions.</p>
<h4 id="reference-implementation-apple-befunge-editor">Reference Implementation: APPLE BEFUNGE EDITOR</h4>
<ul>
<li>development-stage: archival</li>
<li>license: Public Domain</li>
<li>implementation-type: interpreter, editor</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#applesoft-basic">Applesoft BASIC</a></li>
<li>host-platform: Apple II</li>
</ul>
    
      <h3 id="smith"><a href="#smith">SMITH</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="https://archive.org/details/smith-2.0l-dos">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/SMITH">Browse files</a>
        
        
          <a class="button" href="/distribution/SMITH_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: ca Jul 2000</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: Turing-complete</li>
          
        
          
            <li>influences: <a href="../article/Automata.md#smetana">SMETANA</a></li>
          
        
          
            <li>paradigms: Imperative, Self-modifying</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/SMITH_distribution">SMITH distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/SMITH">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://archive.org/details/smith-2.0l-dos">archive.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>MOV R0, 10
MOV R2, 0
SUB R2, 1
MOV R[R0], "Hello, world!"
MOV TTY, R[R0]
SUB R0, R2
MOV R1, R0
SUB R1, 23
NOT R1
NOT R1
MUL R1, 8
COR +1, -7, R1
</code></pre>
<p>SMITH is a self-modifying assembly-like language which completely lacks
any kind of jump instructions <em>whatsoever</em>.  Despite this handicap, it
has been shown to be <a href="https://esolangs.org/wiki/Turing-complete">Turing-complete</a>.</p>
<h4 id="reference-implementation-smithpl">Reference Implementation: smith.pl</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#perl">Perl</a></li>
</ul>
    
      <h3 id="tamerlane"><a href="#tamerlane">Tamerlane</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Specs-on-Spec">Browse files</a>
        
        
          <a class="button" href="/distribution/Specs_on_Spec_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Aug 2000</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: ???</li>
          
        
          
            <li>paradigms: Graph-rewriting, Imperative</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Specs_on_Spec_distribution">Specs on Spec distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>Point-A: 1 Point-B,
Point-B: 1 Point-C,
Point-C: 1 Point-A.
?- 1 Point-A -&gt; 0 Point-A @ Point-A
</code></pre>
<p>Tamerlane is a multi-paradigmatic programming language, unimplemented
and possibly unimplementable. One of its core execution mechanisms is the
traversing of a graph (representing the program) while rewriting that same
graph.</p>
    
      <h3 id="squishy2k"><a href="#squishy2k">Squishy2K</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Squishy2K">Browse files</a>
        
        
          <a class="button" href="/distribution/Squishy2K_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Sep 2000</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: String-rewriting, State machine</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Squishy2K_distribution">Squishy2K distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Squishy2K">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>* main { start many finish? "Hello, world!"! }
</code></pre>
<p>Squishy2K is a language which is a hybrid of string rewriting
and finite state automata; as an added twist, it also lets program states serve
as functions.  It was based largely on an earlier grammar-based language
called SQUISHY, taking also some ideas from the language <a href="https://esolangs.org/wiki/Thue">Thue</a>.  The
original SQUISHY was conceived sometime around 1998, but is now lost.  Because
it was based largely on EBNF, the author wanted to name it Wirth, but the
name SQUISHY was proposed and (somewhat unfortunately) stuck.</p>
<h4 id="reference-implementation-squishy2kpl">Reference Implementation: squishy2k.pl</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#perl">Perl</a></li>
</ul>
    
      <h3 id="hunter"><a href="#hunter">HUNTER</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="https://archive.org/details/hunter-rel_1_0_2002_0126-dos">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/HUNTER">Browse files</a>
        
        
          <a class="button" href="/distribution/HUNTER_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: ca Sep 20, 2000</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: ???</li>
          
        
          
            <li>paradigms: 2-dimensional, Maze-space-rewriting</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/HUNTER_distribution">HUNTER distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/HUNTER">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://archive.org/details/hunter-rel_1_0_2002_0126-dos">archive.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>##################
#   1#2#         #
# #### #         #
#      #         #
# ######    M    #
#     M#         #
#+######         #
#     !#         #
##################
*12+&gt;3
*21+&gt;3
</code></pre>
<p>HUNTER is a language I designed for the Esoteric Awards ("Essies")
Its abstract starts out like this:</p>
<blockquote>
<p>It is perceived that one of the biggest problems in maintaining
interest in programming is the above linear growth of boredom
compared to the usefulness of the program, resulting in an
acute loss of enthusiasm on the part of the programmers and
ultimately the abandonment of the software...</p>
</blockquote>
<h4 id="reference-implementation-hunterpl">Reference Implementation: hunter.pl</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#perl">Perl</a></li>
</ul>
    
      <h3 id="n-dcnc"><a href="#n-dcnc">&#x27;N-DCNC</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/N-DCNC">Browse files</a>
        
        
          <a class="button" href="/distribution/&#x27;N-DCNC_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Oct 2000</li>
          
        
          
            <li>genre: Joke language</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: ???</li>
          
        
          
            <li>paradigms: Functional</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/'N-DCNC_distribution">'N-DCNC distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/'N-DCNC">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>4*5+2/2,(9*`c)+1
</code></pre>
<p>'N-DCNC was <a href="../article/General%20Information.md#chris-pressey">Chris Pressey</a>'s entry for the 2000 Esoteric Awards
(which might have actually been <a href="../article/Events.md#esoteric-awards-2001">Esoteric Awards 2001</a>).
It is based on a conspiracy theory involving UFOs and a 5-member
boy band, or something.</p>
<p>A copy of PortableFalse is included in the 'N-DCNC distribution, to
make it easier for you to run the code generated by the 'N-DCNC compilers.
However, you still need a C compiler to build the PortableFalse interpreter.</p>
<h4 id="reference-implementation-ndcncpl">Reference Implementation: ndcnc.pl</h4>
<ul>
<li>license: Unknown license</li>
<li>implementation-type: compiler</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#perl">Perl</a></li>
<li>target-language: FALSE</li>
</ul>
<h4 id="implementation-ndcncbf">Implementation: ndcnc.bf</h4>
<ul>
<li>license: Unknown license</li>
<li>implementation-type: compiler</li>
<li>host-language: <a href="../article/Languages.md#befunge-93">Befunge-93</a></li>
<li>target-language: FALSE</li>
</ul>
<p>Broken.</p>
    
      <h3 id="strelnokoff"><a href="#strelnokoff">Strelnokoff</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="https://archive.org/details/strelnokoff-1.0-2001.0324-dos">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Strelnokoff">Browse files</a>
        
        
          <a class="button" href="/distribution/Strelnokoff_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Apr 2001</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Imperative, Non-deterministic</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Strelnokoff_distribution">Strelnokoff distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Strelnokoff">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://archive.org/details/strelnokoff-1.0-2001.0324-dos">archive.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>REM HELLO WORLD IN STRELNOKOFF
REM CHRIS PRESSEY MARCH 24 2001
X = (X / X) * X + (X = 0) * (T =  0) * (PRINT CHAR 'H' - 'H' +  1)
X = (X / X) * X + (X = 0) * (T =  1) * (PRINT CHAR 'e' - 'e' +  2)
X = (X / X) * X + (X = 0) * (T =  2) * (PRINT CHAR 'l' - 'l' +  3)
X = (X / X) * X + (X = 0) * (T =  3) * (PRINT CHAR 'l' - 'l' +  4)
X = (X / X) * X + (X = 0) * (T =  4) * (PRINT CHAR 'o' - 'o' +  5)
X = (X / X) * X + (X = 0) * (T =  5) * (PRINT CHAR ',' - ',' +  6)
X = (X / X) * X + (X = 0) * (T =  6) * (PRINT CHAR ' ' - ' ' +  7)
X = (X / X) * X + (X = 0) * (T =  7) * (PRINT CHAR 'w' - 'w' +  8)
X = (X / X) * X + (X = 0) * (T =  8) * (PRINT CHAR 'o' - 'o' +  9)
X = (X / X) * X + (X = 0) * (T =  9) * (PRINT CHAR 'r' - 'r' + 10)
X = (X / X) * X + (X = 0) * (T = 10) * (PRINT CHAR 'l' - 'l' + 11)
X = (X / X) * X + (X = 0) * (T = 11) * (PRINT CHAR 'd' - 'd' + 12)
X = (X / X) * X + (X = 0) * (T = 12) * (PRINT CHAR '!' - '!' + 13)
X = (T = X) * 0 + (X &gt; T) * X REM RESET FLAG
T = (X / X) * X + (X = 0) * T REM INCREMENT TICK
</code></pre>
<p>Strelnokoff is a non-deterministic imperative programming language.
Despite this apparent handicap, it appears to be <a href="https://esolangs.org/wiki/Turing-complete">Turing-complete</a> —
thanks to a short-circuiting multiplication operator — but a critical
feature, namely arrays, has yet to be implemented.</p>
<p>The name "Strelnokoff" was taken from a fictional brand of vodka
featured in a parody advertisement on the television show SCTV.</p>
<h4 id="reference-implementation-strelnokoffpl">Reference Implementation: strelnokoff.pl</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#perl">Perl</a></li>
</ul>
    
      <h3 id="opus-2"><a href="#opus-2">Opus-2</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Specs-on-Spec">Browse files</a>
        
        
          <a class="button" href="/distribution/Specs_on_Spec_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Conlang</li>
          
        
          
            <li>inception-date: Jul 2001</li>
          
        
          
            <li>genre: Abstract Artlang</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: ???</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Specs_on_Spec_distribution">Specs on Spec distribution</a></li>
          
        
      </ul>
      <p>Sample utterance:</p>
<pre><code>+ pale green
+ Eb, trombone, forte
+ leaning 40 degrees left (sudden)
+ C, tubular bells, piano
+ mothballs (gentle whiff)
</code></pre>
<p>Opus-2 is not a programming language, but rather, an abstract artlang
(i.e., a conlang designed independently from any conception of society.)
The sole design principle was to entirely eliminate word order.</p>
    
      <h3 id="ypsilax"><a href="#ypsilax">Ypsilax</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="https://archive.org/details/ypsilax-0.9-dos">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Ypsilax">Browse files</a>
        
        
          <a class="button" href="/distribution/Ypsilax_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Aug 2001</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Grid-rewriting, Reflective</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Ypsilax_distribution">Ypsilax distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Ypsilax">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://archive.org/details/ypsilax-0.9-dos">archive.org</a></li>
          
        
          
            <li>jnlp @ <a href="https://archive.org/details/yoob-rel_0_3_2018_1128">archive.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>(      )  (      )
  #            #
  # ###    ### #
  #            #

    ###   ###

    #      #
    #      #
    #    ###
</code></pre>
<p>Ypsilax is a non-deterministic, reflective, two-dimensional grid-rewriting
language.  Rewriting rules look for patterns in the grid and replace them
with other patterns.  These rules are themselves represented by patterns
in the grid, and therefore rules can match and rewrite other rules.</p>
<h4 id="reference-implementation-ypsilaxpl">Reference Implementation: ypsilax.pl</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#perl">Perl</a></li>
</ul>
<h4 id="implementation-tccatseyeyoobypsilax">Implementation: tc.catseye.yoob.ypsilax</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#java">Java</a></li>
<li>host-platform: <a href="../article/Archived.md#yoob">yoob</a></li>
</ul>
    
      <h3 id="version"><a href="#version">Version</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="https://archive.org/details/version-1.0-2001.1211-dos">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Version">Browse files</a>
        
        
          <a class="button" href="/distribution/Version_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Sep 2001</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: unknown computational class</li>
          
        
          
            <li>paradigms: Imperative, Regular-expression-based</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Version_distribution">Version distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Version">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://archive.org/details/version-1.0-2001.1211-dos">archive.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>START: ROOM = "VALLEY|BROOK|GLADE"
CONT: IGNORE = ROOM
VALLEY: OUTPUT = "You are standing in a valley."
HILL: OUTPUT = "You are on top of a hill."
BROOK: OUTPUT = "You are by a brook."
GLADE: OUTPUT = "You are standing in a sun-dappled glade."
ROOM: OUTPUT = EOL
ROOM: DIR = CHOP INPUT
ROOM: IGNORE = DIR
ROOM: MASK = "VAPOURS"
N: CAT = "|N"
S: CAT = "|S"
E: CAT = "|E"
W: CAT = "|W"
ROOM: IGNORE = MASK
N: ROOM = "VALLEY|BROOK|GLADE"
S: ROOM = "HILL|BROOK|GLADE"
E: ROOM = "VALLEY|HILL|BROOK"
W: ROOM = "VALLEY|HILL|GLADE"
LASTLY: IGNORE = "START"
</code></pre>
<p>Version is an imperative programming language that uses <em>ignorance-spaces</em>
for flow control; all  instructions which match the current ignorance pattern
are ignored during execution.</p>
<h4 id="reference-implementation-versionpl">Reference Implementation: version.pl</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#perl">Perl</a></li>
</ul>
    
      <h3 id="beta-juliet"><a href="#beta-juliet">beta-Juliet</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/beta-Juliet">Browse files</a>
        
        
          <a class="button" href="/distribution/beta-Juliet_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: ca 2002</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Event-oriented</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/beta-Juliet_distribution">beta-Juliet distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/beta-Juliet">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>event WindowSwitchBroken;
event MotionDetectorTriggered;

event SystemArmed;
event SystemDisarmed;

event Alarm,
 caused after WindowSwitchBroken      when SystemArmed &gt; SystemDisarmed,
 caused after MotionDetectorTriggered when SystemArmed &gt; SystemDisarmed,
 causes Alarm.

alphabet Domino,
        One, Two, Three, Four, Five, Six, Seven;
event Begin,
        causes Domino One Falls;
event Domino (N = Domino+) Falls,
        causes Domino (succ N) Falls.
</code></pre>
<p>beta-Juliet is a minimal event-based language.  Each event is caused by some other event.
Event causation is conditional based on which of two given events occurred more recently.</p>
<p>Portia is a preprocessor for beta-Juliet which allows large, regular, finite sets of events
to be described succinctly.</p>
<p>Version 2.0 of beta-Juliet (formerly known as "2iota") allows infinite sets of events to be
specified, allowing the language to be <a href="https://esolangs.org/wiki/Turing-complete">Turing-complete</a>.</p>
<h4 id="reference-implementation-2iota">Reference Implementation: 2iota</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#c99">C99</a></li>
</ul>
<h4 id="implementation-b_julietpl">Implementation: b_juliet.pl</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#perl">Perl</a></li>
</ul>
    
      <h3 id="sbeezg"><a href="#sbeezg">Sbeezg</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Sbeezg">Browse files</a>
        
        
          <a class="button" href="/distribution/Sbeezg_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: 2002</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: archival</li>
          
        
          
            <li>computational-class: ???</li>
          
        
          
            <li>paradigms: Functional</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Sbeezg_distribution">Sbeezg distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Sbeezg">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>f={a,b|i=*is;s=*pred;p=*print;g=p(*beer);h=s(a);
   ln={x,m|z=x|x};lg={y,n|q=n(y,n)|y};j=i(h,0,ln,lg);
   k=j(h,b)|a};l=f(99,f)
</code></pre>
<p>Sbeezg is a syntactically very simple language that attempts to
take the single-assignment concept to a logical extreme.</p>
<p>I really don't remember exactly what I was trying to accomplish
with this; the basic idea is fairly absurd (either your variables are
single-assignment or they're not...)</p>
<h4 id="reference-implementation-sbeezgerl">Reference Implementation: sbeezg.erl</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#erlang">Erlang</a></li>
</ul>
    
      <h3 id="granolam"><a href="#granolam">GraNoLa/M</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/GraNoLa-M">Browse files</a>
        
        
          <a class="button" href="/distribution/GraNoLa/M_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Jul 2002</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: ???</li>
          
        
          
            <li>influences: <a href="../article/Languages.md#tamerlane">Tamerlane</a></li>
          
        
          
            <li>paradigms: Graph-rewriting, Imperative</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/GraNoLa/M_distribution">GraNoLa/M distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>a=^sajalom(b=^#d(c=^bimodang(^a))d(e=^#cthulhu(f=^uwaming(g=^ubewic()))))
</code></pre>
<p>GraNoLa/M is a Graph-Node-based Language (possibly for Machines.) 
It was one of my submissions for the Esoteric Awards. Not unlike <a href="../article/Languages.md#tamerlane">Tamerlane</a>,
its execution model involves both traversing and rewriting a graph at the
same time.</p>
<h4 id="reference-implementation-granolamerl">Reference Implementation: granolam.erl</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#erlang">Erlang</a></li>
</ul>
    
      <h3 id="kangaroo-iceberg"><a href="#kangaroo-iceberg">Kangaroo Iceberg</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Kangaroo-Iceberg">Browse files</a>
        
        
          <a class="button" href="/distribution/Kangaroo_Iceberg_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Jul 2004</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: unfinished</li>
          
        
          
            <li>computational-class: ???</li>
          
        
          
            <li>influences: <a href="../article/Languages.md#tamerlane">Tamerlane</a></li>
          
        
          
            <li>paradigms: Graph-rewriting</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Kangaroo_Iceberg_distribution">Kangaroo Iceberg distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>A { ^A:0 / ^A:0 -&gt; ^A:1 }
B { / ^B:0 -&gt; ^B:1, ^B:1 -&gt; ^B:2 }
C { {}:0 / ^K:0 -&gt; ^K:1, ^K:1 -&gt; ^K:2; ^A:1 -&gt; ^A:0 }
</code></pre>
<p>Kangaroo Iceberg was a short-lived attempt to pare down <a href="../article/Languages.md#tamerlane">Tamerlane</a>
to something implementable, and implement it.  Although it got a fair ways
along (e.g. the parser for graphs seems to be complete, I lost interest
in it at the time, and put off finishing it indefinitely.</p>
<p>Now, the challenge will be reconstructing the language from the partial
implementation and notes that I left behind...</p>
<h4 id="reference-implementation-kiceberg">Reference Implementation: kiceberg</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#ansi-c">ANSI C</a></li>
</ul>
    
      <h3 id="beturing"><a href="#beturing">Beturing</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Beturing">Browse files</a>
        
        
          <a class="button" href="/distribution/Beturing_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Oct 20, 2005</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: Turing-complete</li>
          
        
          
            <li>influences: <a href="../article/Languages.md#befunge-93">Befunge-93</a></li>
          
        
          
            <li>paradigms: Imperative, State machine</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Beturing_distribution">Beturing distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Beturing">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code># D(40, 4)
# @(40, 4)
$bbab$
# C(0, 0)
# @(0, 0)
 . . . . . .
*v*&lt;*&lt;*&lt;*&gt;*v
aa .ab . .aa .
&gt;/*&gt;./*^*^&lt;/*v
bb .ba . .bb .
&gt;/*^./*^*^&lt;/*v
$$ .$$ . .$$ .
&gt;/*^&lt;/*&gt;*^.@*v
         . . .
*@      *^*&lt;*&lt;
</code></pre>
<p>Beturing is a "<a href="../article/Languages.md#befunge-93">Befunge</a>-flavoured" language for describing Turing
machines; both the tape and the finite control are laid out two-dimensionally.
In addition, the finite control must be expressed as a planar graph (no
edge representing a transition may cross any other edge.) It was devised
this way as a test of the so-called "wire-crossing problem". It turns out
that there are universal Turing machines with finite controls that are planar
graphs, so Beturing is <a href="https://esolangs.org/wiki/Turing-complete">Turing-complete</a>.</p>
<h4 id="reference-implementation-beturinglua">Reference Implementation: beturing.lua</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#lua">Lua</a></li>
</ul>
    
      <h3 id="bhuna"><a href="#bhuna">Bhuna</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Bhuna">Browse files</a>
        
        
          <a class="button" href="/distribution/Bhuna_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Oct 21, 2005</li>
          
        
          
            <li>genre: Production language</li>
          
        
          
            <li>development-stage: archival</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>influences: <a href="../article/Project%20Dependencies.md#lua">Lua</a></li>
          
        
          
            <li>paradigms: Imperative, Functional</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Bhuna_distribution">Bhuna distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>Fib = ^ X {
  if X &lt; 2 return 1 else
  return Fib(X - 1) + Fib(X - 2)
}
Print Fib(32), EoL
</code></pre>
<p>Bhuna is a small, garbage-collected language with a simple syntax,
closures, inferred types, lightweight processes, and support for UTF-8 source
code.  It was implemented partly to see how closely I could match the performance
of <a href="../article/Project%20Dependencies.md#lua">Lua</a>'s interpreter.  It was meant more more as an experimental starting
point for branching new languages, than as a useful language in and of itself.</p>
<h4 id="reference-implementation-bhuna">Reference Implementation: bhuna</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#c99">C99</a></li>
</ul>
    
      <h3 id="kosheri"><a href="#kosheri">Kosheri</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/">Browse files</a>
        
        
          <a class="button" href="/distribution/Kosheri_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: ca 2007</li>
          
        
          
            <li>genre: Production Language</li>
          
        
          
            <li>development-stage: unfinished</li>
          
        
          
            <li>etymology: Egyptian street food</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Kosheri_distribution">Kosheri distribution</a></li>
          
        
      </ul>
      <p>Kosheri is a virtual machine design that rose from the ashes of <a href="../article/Languages.md#bhuna">Bhuna</a>.</p>
<h4 id="reference-implementation-kosheri-c">Reference Implementation: kosheri (C)</h4>
<ul>
<li>license: Unknown license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#c99">C99</a></li>
</ul>
    
      <h3 id="burro"><a href="#burro">Burro</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Burro">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Burro">Browse files</a>
        
        
          <a class="button" href="/distribution/Burro_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: 2007</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: Turing-complete</li>
          
        
          
            <li>influences: <a href="https://esolangs.org/wiki/brainfuck">brainfuck</a></li>
          
        
          
            <li>paradigms: Imperative, Algebraic</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Burro_distribution">Burro distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Burro">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Burro">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>!--(--(--(!&gt;/
  &gt;&gt;--(+&lt;&lt;+++++++&gt;/+++&gt;+++++&gt;)&lt;
&gt;)/
  &gt;&gt;--(+++&gt;+++++&gt;/+++&lt;&lt;&lt;&lt;&lt;+++&gt;)&lt;
&gt;)/
  &gt;&gt;--(+++&gt;+&gt;/+&lt;&lt;+++&gt;)&lt;
&gt;)&lt;
</code></pre>
<p>Burro is a <a href="https://esolangs.org/wiki/brainfuck">brainfuck</a>-like programming language whose programs
form an algebraical <em>group</em> (modulo the equivalence relation of "computes the
same function") under the operation of concatenation. The upshot of this
is that, for every Burro program, we can find an <em>antiprogram</em> which, when
appended to the program, forms a "no-op" program which has no effect.
 This is a form of reversible computing, but unlike most reversible languages
where it is the execution of the program that is "undone", in Burro, it is
the program itself which is annihiliated by its antiprogram.  Burro 1.0
was released in fall of 2007, but proved not to form a proper group. This
shortcoming was rectified in summer of 2010.</p>
<h4 id="reference-implementation-burrolhs">Reference Implementation: Burro.lhs</h4>
<ul>
<li>license: Unknown license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
</ul>
    
      <h3 id="hev"><a href="#hev">Hev</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Hev">Browse files</a>
        
        
          <a class="button" href="/distribution/Hev_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: May 23, 2007</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Term-rewriting</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Hev_distribution">Hev distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Hev">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>71+8*27,19,29*99,6,37,7,61,47
</code></pre>
<p>Hev is a programming language that attempts to solve the "central
problem of infix notation": how do you allow it without requiring the programmer
to either memorize precedence tables or litter parentheses everywhere?  Hev
has a way! In Hev, <em>all</em> operators are infix, yet no tiresome memorization
of any dreadful precedence table is required!</p>
<h4 id="reference-implementation-hevhs">Reference Implementation: Hev.hs</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
</ul>
    
      <h3 id="cabra"><a href="#cabra">Cabra</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Cabra">Browse files</a>
        
        
          <a class="button" href="/distribution/Cabra_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Oct 30, 2007</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: known not Turing-complete</li>
          
        
          
            <li>influences: <a href="../article/Languages.md#burro">Burro</a></li>
          
        
          
            <li>paradigms: Imperative, Algebraic</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Cabra_distribution">Cabra distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>(SET 1 + SET 2) * IFSET 1 THEN (IFSET 2 THEN SET 3 ELSE SKIP) ELSE SKIP
</code></pre>
<p>Cabra is a (somewhat) formal programming language whose programs
form an algebraical <em>dioid</em> (an idempotent semiring), modulo the equivalence
relation of "computes the same function", under the operations of parallel
execution (as the additive operator) and sequential composition (as the multiplicative
operator).</p>
<h4 id="reference-implementation-cabrahs">Reference Implementation: cabra.hs</h4>
<ul>
<li>license: Unknown license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
</ul>
    
      <h3 id="you-are-reading-the-name-of-this-esolang"><a href="#you-are-reading-the-name-of-this-esolang">You are Reading the Name of this Esolang</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Specs-on-Spec">Browse files</a>
        
        
          <a class="button" href="/distribution/Specs_on_Spec_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Nov 2007</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: Turing-complete</li>
          
        
          
            <li>influences: <a href="https://esolangs.org/wiki/Spoon">Spoon</a></li>
          
        
          
            <li>paradigms: Imperative</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Specs_on_Spec_distribution">Specs on Spec distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/You%20are%20Reading%20the%20Name%20of%20this%20Esolang">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>001000000[0010000000111001000011]11100100001[0]
</code></pre>
<p>You are Reading the Name of this Esolang is an exploration in
the design space of programming languages with undecidable elements. Its syntax
is only recursively enumerable: the problem of determining whether or not
a given string of symbols is a well-formed You are Reading the Name of this
Esolang program is undecidable.</p>
<p>The description makes it sound a bit more mind-blowing than it actually is.
In fact <a href="http://www.open-std.org/jtc1/sc22/wg21/">C++</a> has essentially the same property: it's template system is
<a href="https://esolangs.org/wiki/Turing-complete">Turing-complete</a>.  In practice, this means you can hang the compiler with
templates that expand unboundedly (and the compiler has no means by
which to detect all possible compiler-hanging-templates.)</p>
    
      <h3 id="emmental"><a href="#emmental">Emmental</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Emmental">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Emmental">Browse files</a>
        
        
          <a class="button" href="/distribution/Emmental_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Nov 11, 2007</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Meta-circular, Reflective</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Emmental_distribution">Emmental distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Emmental">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Emmental">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>;#58#126#63#36!;#46#36#!;#0#1!;#0#2!;#0#3!;#0#4!;#0#5!;#0#6!;#0#7!#0#33#111#108#108#101#72$
</code></pre>
<p>Emmental is a self-modifying programming language.  It is defined
in terms of a meta-circular interpreter, and this meta-circular interpreter
provides an operation that redefines operations of the meta-circular interpreter.
In fact, this mechanism is required for Emmental to be <a href="https://esolangs.org/wiki/Turing-complete">Turing-complete</a>.</p>
<p>Emmental was followed up by <a href="../article/Languages.md#mascarpone">Mascarpone</a>, which tried to make this
self-modifying mechanism cleaner.</p>
<h4 id="reference-implementation-languageemmental">Reference Implementation: Language.Emmental</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
</ul>
    
      <h3 id="iphigeneia"><a href="#iphigeneia">Iphigeneia</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Iphigeneia">Browse files</a>
        
        
          <a class="button" href="/distribution/Iphigeneia_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Nov 25, 2007</li>
          
        
          
            <li>genre: Pedagogical language</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: ???</li>
          
        
          
            <li>paradigms: Imperative, Functional</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Iphigeneia_distribution">Iphigeneia distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>var a in a :=
    let c = 5 in let d = 1 in
        loop
            if c = 0 then
                d
            else
                let d = d * c in
                    let c = c - 1 in
                        repeat
</code></pre>
<p>Iphigeneia is a toy programming language which contains features
from both imperative programming (assignments to mutable variables, <code>while</code>
loops,) and functional programming (immutable name bindings, Scheme-style
"named <code>let</code>" loops.) It was originally intended as a testbed for algorithms
that convert programs between the two forms.</p>
<h4 id="reference-implementation-iphi">Reference Implementation: iphi</h4>
<ul>
<li>license: Unknown license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
</ul>
    
      <h3 id="mascarpone"><a href="#mascarpone">Mascarpone</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Mascarpone">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Mascarpone">Browse files</a>
        
        
          <a class="button" href="/distribution/Mascarpone_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Dec 10, 2007</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>influences: <a href="../article/Languages.md#emmental">Emmental</a></li>
          
        
          
            <li>paradigms: Meta-circular, Reflective</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Mascarpone_distribution">Mascarpone distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Mascarpone">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Mascarpone">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>v['[/''/']v*]v*'?&lt;^v[/?/&lt;]v*'S&lt;[&gt;!]v*'F&lt;^[]v*1'p'kS'kF.
</code></pre>
<p>Mascarpone is a self-modifying language able to alter the meta-circular
interpreter which defines it, like its predecessor <a href="../article/Languages.md#emmental">Emmental</a>.  Unlike Emmental
however, in Mascarpone interpreters are first-class objects, making the
job of reflective interpreter-modification quite a bit cleaner and richer.</p>
<h4 id="reference-implementation-languagemascarpone">Reference Implementation: Language.Mascarpone</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
</ul>
    
      <h3 id="larabee"><a href="#larabee">Larabee</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Larabee">Browse files</a>
        
        
          <a class="button" href="/distribution/Larabee_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Jan 10, 2008</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: known not Turing-complete</li>
          
        
          
            <li>paradigms: Imperative</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Larabee_distribution">Larabee distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Larabee">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>(store (input) (input)
  (store (input) (input)
    (label loop
      (store (input) (op * (fetch (input)) (fetch (input)))
        (store (input) (op - (fetch (input)) (input))
          (test (op &gt; (fetch (input)) (input))
            (goto loop) (print (fetch (input)))))))))
</code></pre>
<p>Larabee is an assembly-like programming language, with <a href="../article/Project%20Dependencies.md#scheme">Scheme</a>-like
syntax, that borrows the notion of branch prediction from computer architecture
and abuses it, creating a path that leads only to existential angst and self-destruction.</p>
<h4 id="reference-implementation-larabeescm">Reference Implementation: larabee.scm</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#scheme">Scheme</a></li>
</ul>
    
      <h3 id="arboretuum"><a href="#arboretuum">Arboretuum</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Arboretuum">Browse files</a>
        
        
          <a class="button" href="/distribution/Arboretuum_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Mar 2008</li>
          
        
          
            <li>genre: Experimental language</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Forest-rewriting</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Arboretuum_distribution">Arboretuum distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>(
  (
    (ast:   (let a 4 (+ 3 (* a 3))) )
    (stab:  eot)
    (out:   halt)
  )
  (
    ((ast:  (let #(n sym) #(v) #(expr)) =&gt; #(expr)            )
     (stab: eot                         =&gt; (#(n) #(v) EOT)    ))
    ((ast:  #(n sym)                    =&gt; #(v)               )
     (stab: (#(n) #(v) #(tab))          =&gt; (#(n) #(v) #(tab)) ))
    ((ast: #(a num)                     =&gt; _                  )
     (out: halt                         =&gt; (push #(a) halt)   ))
    ((ast: (+ _ _)                      =&gt; _                  )
     (out: halt                         =&gt; (add halt)         ))
    ((ast: (* _ _)                      =&gt; _                  )
     (out: halt                         =&gt; (mul halt)         ))
  )
)
</code></pre>
<p>Arboretuum is an experimental language based on <em>forest-rewriting</em>,
a variant of tree-rewriting in which multiple trees are rewritten simultaneously.
The language was intended for specifying compilers, with each tree representing
a major compiler data structure (AST, symbol table, output buffer, etc.,)
however, this idea was not entirely successful.  Regardless, Arboretuum is
<a href="https://esolangs.org/wiki/Turing-complete">Turing-complete</a>, as tree-rewriting is simply a special case of forest-rewriting.</p>
<h4 id="reference-implementation-forest-rewriterscm">Reference Implementation: forest-rewriter.scm</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#scheme">Scheme</a></li>
</ul>
    
      <h3 id="treacle"><a href="#treacle">Treacle</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Treacle">Browse files</a>
        
        
          <a class="button" href="/distribution/Treacle_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Apr 12, 2008</li>
          
        
          
            <li>genre: Experimental language</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>influences: <a href="../article/Languages.md#arboretuum">Arboretuum</a></li>
          
        
          
            <li>paradigms: Term-rewriting</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Treacle_distribution">Treacle distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>(
  (:i (? t (x (? i *) (? j *)))) -&gt; (t : (xx (? j *) (? i *)))))
  (:i (? p right))               -&gt; (p : left)
)
</code></pre>
<p>Treacle is an experimental compiler-definition language based on
<em>context rewriting</em>, an expressive variant of term rewriting that generalizes
the forest-rewriting used by its predecessor <a href="../article/Languages.md#arboretuum">Arboretuum</a>.  In context rewriting,
a separation is made between <em>names</em> and <em>variables</em>, and patterns may contain
<em>holes</em> inside which subpatterns may match at any depth.</p>
<h4 id="reference-implementation-treaclescm">Reference Implementation: treacle.scm</h4>
<ul>
<li>license: Unknown license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#scheme">Scheme</a></li>
</ul>
    
      <h3 id="quylthulg"><a href="#quylthulg">Quylthulg</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Quylthulg">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Quylthulg">Browse files</a>
        
        
          <a class="button" href="/distribution/Quylthulg_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Dec 6, 2008</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Functional</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Quylthulg_distribution">Quylthulg distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Quylthulg">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Quylthulg">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>foreach $n$=:L:[1,2,3|goto$L$] with $a$=1 be +$a$+$n$+ else be abort
</code></pre>
<p>Quylthulg is a programming language with but a single control-flow
construct: <code>foreach</code>.  In fact, it does also have a <code>goto</code>, but that can
only appear inside data structures.</p>
<h4 id="reference-implementation-qlzqqlzuup-the-lord-of-flesh">Reference Implementation: Qlzqqlzuup, the Lord of Flesh</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
</ul>
    
      <h3 id="zame"><a href="#zame">Zame</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Jan 2009</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>variant-of: <a href="../article/Languages.md#etcha">Etcha</a></li>
          
        
          
            <li>paradigms: Maze-space-rewriting (kind of)</li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>#########
# #     #
# # # ###
#   #   #
### # # #
#   # # #
#########
</code></pre>
<p>Zame is an automaton which uses the solution of a maze to
generate an <a href="../article/Languages.md#etcha">Etcha</a> program which draws a new maze, then
the process repeats.  An open question is to find a maze for which
this process repeats indefinitely.</p>
<p>Where it stands relative to other models of computation is, therefore,
not well understood.</p>
<p>Information on this language is only available on the Esowiki for now:
<a href="http://esolangs.org/wiki/Zame">Zame</a>.</p>
<p>This is actually a language family.</p>
    
      <h3 id="unlikely"><a href="#unlikely">Unlikely</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Unlikely">Browse files</a>
        
        
          <a class="button" href="/distribution/Unlikely_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Mar 15, 2009</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Continuation-passing, Object-oriented, Dependency injection</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Unlikely_distribution">Unlikely distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Unlikely">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>class Count(Count,Chain,Print,Add) extends Continuation

class CountForever(Count,Chain,Print,Add) extends Program {
  Count c;
  method continue(Passive accumulator) {
    c = new Count(Passive,Count,Chain,Print,Add);
    goto c.continue(new 1(Passive));
  }
}

class Count() extends Continuation {
  Count c;
  Print p;
  Add a;
  method continue(Passive accumulator) {
    c = new Count(Passive,Count,Chain,Print,Add);
    a = new Add(Passive,Chain);
    a.value = new 1(Passive);
    a.next = c;
    p = new Print(Passive,Chain);
    p.next = a;
    goto p.continue(accumulator);
  }
}
</code></pre>
<p>Unlikely is a programming language that conflates objects with
continuations, and methods with labels.  It exposes program structures as
objects with commensurate inheritance relationships.  It also takes dependency
injection to the logical extreme: if some class is used by an object, that
class <em>must</em> be specified when the object is instantiated.</p>
<h4 id="reference-implementation-coldwater">Reference Implementation: Coldwater</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: static analyzer</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
</ul>
    
      <h3 id="pixley"><a href="#pixley">Pixley</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Pixley">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Pixley">Browse files</a>
        
        
          <a class="button" href="/distribution/Pixley_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: May 2009</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Functional</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Pixley_distribution">Pixley distribution</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Pixley">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>(let* ((a (lambda (x y) (cons x y)))) (a (quote foo) (quote ())))
</code></pre>
<p>Pixley is a very small subset of R5RS <a href="../article/Project%20Dependencies.md#scheme">Scheme</a> (or, if you prefer, R4RS
Scheme), supporting only four datatypes (boolean, cons cell, function, and
symbol) and only a dozen built-in symbols.  The reference implementation of
Pixley is written in 124 lines of Pixley (or, if you prefer, 124 lines of
Scheme; and if you prefer more Scheme-ly metrics, it consists of 413
instances of 54 unique symbols in 684 cons cells.)</p>
<h4 id="reference-implementation-pixleypix">Reference Implementation: pixley.pix</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Languages.md#pixley">Pixley</a></li>
</ul>
<h4 id="implementation-mignon">Implementation: mignon</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#ansi-c">ANSI C</a></li>
</ul>
<h4 id="reference-implementation-haney">Reference Implementation: haney</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
</ul>
<h4 id="reference-implementation-pixleyjs">Reference Implementation: pixley.js</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#javascript">Javascript</a></li>
<li>host-platform: <a href="https://www.w3.org/TR/html5/">HTML5</a></li>
</ul>
<h4 id="implementation-pixleypifx">Implementation: pixley.pifx</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Languages.md#pifxley">Pifxley</a></li>
</ul>
<h4 id="reference-implementation-p-normalpix">Reference Implementation: p-normal.pix</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: compiler</li>
<li>host-language: <a href="../article/Languages.md#pixley">Pixley</a></li>
<li>target-language: <a href="../article/Languages.md#p-normal-pixley">P-Normal Pixley</a></li>
</ul>
    
      <h3 id="crabwell"><a href="#crabwell">Crabwell</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>genre: Esolang</li>
          
        
      </ul>
      <p>Crabwell is a dialect of <a href="../article/Languages.md#pixley">Pixley</a> which allows values to be bound to, not just symbols, but
arbitrary S-expressions.</p>
    
      <h3 id="p-normal-pixley"><a href="#p-normal-pixley">P-Normal Pixley</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>genre: Esolang</li>
          
        
      </ul>
      <p>P-Normal Pixley is a simplified version of <a href="../article/Languages.md#pixley">Pixley</a> where <code>let*</code> can only bind one identifer
to one value and <code>cond</code> can only make one test, like Scheme's <code>if</code>.</p>
    
      <h3 id="pifxley"><a href="#pifxley">Pifxley</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>genre: Esolang</li>
          
        
      </ul>
      <p>Pifxley is a dialect of <a href="../article/Languages.md#pixley">Pixley</a> which supports an <code>if</code> construct instead of <code>cond</code>.</p>
    
      <h3 id="dieter"><a href="#dieter">Dieter</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Dieter">Browse files</a>
        
        
          <a class="button" href="/distribution/Dieter_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: ca Oct 3, 2009</li>
          
        
          
            <li>genre: Experimental language</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Object-oriented</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Dieter_distribution">Dieter distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>module beefy
  procedure beef_up(x: ♥t): beefy ♥t
  begin
    return (bestow beefy x)
  end
end.
</code></pre>
<p>Dieter (as in the German masculine given name Dieter, not dieter as in
"one who diets") is a little experimental programming language that
conflates <em>type qualifiers</em> with <em>modules</em> to produce something
reminiscent of object-orientation.  It demonstrates another way of
thinking about objects, or rather, classes: not so much as
<em>aggregates of data</em> as <em>associations of predicates</em>.</p>
<p>Dieter was intended as a way to make Hungarian notation part of the type
system, and thus automatically checkable.  However, it also suggests
possible ways of dealing with the problems of aliasing — that is,
determining if two pointers cannot possibly point to the same data, for
safety and optimization considerations.</p>
<h4 id="reference-implementation-dieterpy">Reference Implementation: dieter.py</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: typechecker</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
</ul>
    
      <h3 id="etcha"><a href="#etcha">Etcha</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Etcha">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Etcha">Browse files</a>
        
        
          <a class="button" href="/distribution/Etcha_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Oct 4, 2009</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>influences: <a href="https://esolangs.org/wiki/BitChanger">BitChanger</a></li>
          
        
          
            <li>paradigms: Imperative</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Etcha_distribution">Etcha distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Etcha">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Etcha">catseye.tc</a></li>
          
        
          
            <li>jnlp @ <a href="https://archive.org/details/yoob-rel_0_3_2018_1128">archive.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>&gt;+++&gt;+++&gt;+++&gt;+++&gt;[+]&gt;&gt;&gt;&gt;+
</code></pre>
<p>Etcha is a two-dimensional descendant of <a href="https://esolangs.org/wiki/Jeffry%20Johnston">Jeffry Johnston</a>'s <a href="https://esolangs.org/wiki/BitChanger">BitChanger</a>.
Like BitChanger, it has four instructions; unlike BitChanger, its storage
model is based on turtle graphics, which permits it to be immediately used
for an alternative purpose: graphical composition. Unlike the turtle in LOGO
however, the turtle in Etcha is an integral part of the computation, playing
a role similar to the tape head of a Turing machine.</p>
<h4 id="reference-implementation-tccatseyeetcha">Reference Implementation: tc.catseye.etcha</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#java">Java</a></li>
</ul>
<h4 id="implementation-tccatseyeyoobetcha">Implementation: tc.catseye.yoob.etcha</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#java">Java</a></li>
<li>host-platform: <a href="../article/Archived.md#yoob">yoob</a></li>
</ul>
<h4 id="implementation-etchajs">Implementation: etcha.js</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#javascript">Javascript</a></li>
<li>host-platform: <a href="https://www.w3.org/TR/html5/">HTML5</a></li>
</ul>
    
      <h3 id="zowie"><a href="#zowie">ZOWIE</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/ZOWIE">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/ZOWIE">Browse files</a>
        
        
          <a class="button" href="/distribution/ZOWIE_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Dec 29, 2009</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: Turing-complete</li>
          
        
          
            <li>influences: <a href="https://esolangs.org/wiki/BitChanger">BitChanger</a>, <a href="../article/Languages.md#smith">SMITH</a></li>
          
        
          
            <li>paradigms: Imperative, Memory-mapped</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/ZOWIE_distribution">ZOWIE distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/ZOWIE">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/ZOWIE">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>MOV R10, 90
MOV R1, R1
MOV R0, R10
MOV R8, R10
MOV R5, 1
MOV R10, R8
MOV R8, R10
MOV R5, 64
MOV R3, R8
</code></pre>
<p>ZOWIE is a machine-like language in which all operations <em>including
structured control flow</em> are memory-mapped.  Control flow is structured in
the sense of structured programming — the programmer never deals with
<code>goto</code>s, or offsets or labels of any kind.  Instead, the program writes to
a memory location to mark the beginning or end of a loop or conditional.</p>
<h4 id="reference-implementation-zowiepy">Reference Implementation: zowie.py</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
</ul>
    
      <h3 id="whothm"><a href="#whothm">Whothm</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Whothm">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Whothm">Browse files</a>
        
        
          <a class="button" href="/distribution/Whothm_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Drawing Language</li>
          
        
          
            <li>inception-date: Jun 28, 2010</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: known not Turing-complete</li>
          
        
          
            <li>paradigms: Imperative</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Whothm_distribution">Whothm distribution</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Whothm">catseye.tc</a></li>
          
        
          
            <li>jnlp @ <a href="https://archive.org/details/jwhothm-rel_1_0_2018_1009">archive.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>r := (0, 0, 1, 2);
s := (0, 0, 1, 2);
XOR := TF/FT;

begin
r.x += r.w;
r.x += -1;
r.w += 1;
r.h += 1;
draw r, XOR;
s.x += s.w;
s.x += -1;
s.w += 1;
s.h += 2;
draw s, XOR;
end
</code></pre>
<p>Whothm is a simple language for describing infinite two-colour
bitmapped drawings.</p>
<h4 id="reference-implementation-jwhothm">Reference Implementation: JWhothm</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#java">Java</a></li>
</ul>
<h4 id="implementation-whothmlua">Implementation: whothm.lua</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#lua">Lua</a></li>
</ul>
    
      <h3 id="eightebed"><a href="#eightebed">Eightebed</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Eightebed">Browse files</a>
        
        
          <a class="button" href="/distribution/Eightebed_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: ca Sep 1, 2010</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Imperative</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Eightebed_distribution">Eightebed distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Eightebed">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>type node struct {
    int value;
    ptr to node next;
};
var ptr to node jim;
var ptr to node george;
{    
    jim = malloc node;
    if valid jim {
        [@jim].value = (1 + 4);
        george = jim;
    }
    if valid george {
        print [@george].value;
    }
    free george;
    free jim;
}
</code></pre>
<p>Eightebed is a small language with explicit <code>malloc</code> and <code>free</code>.
Through a modicum of static analysis
and runtime support, Eightebed is "safe": it is not possible to dereference a dangling
pointer or otherwise incorrectly-populated memory.</p>
<p>Eightebed was designed as a counter-example to <a href="https://esolangs.org/wiki/Gregor_Richards">Gregor Richards</a>' claim that such
a language would either need a garbage collector, or not actually implement <code>free</code>.
Eightebed has a real <code>free</code> and has no garbage collector.</p>
<p>The name "Eightebed" came from a typo by <a href="https://codeberg.org/catseye/Eightebed#legal-issues">Alise</a> for the word "enlightened".</p>
<h4 id="reference-implementation-8ebed2cpy">Reference Implementation: 8ebed2c.py</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: compiler</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
<li>target-language: <a href="../article/Project%20Dependencies.md#ansi-c">ANSI C</a></li>
</ul>
    
      <h3 id="oozlybub-and-murphy"><a href="#oozlybub-and-murphy">Oozlybub and Murphy</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Specs-on-Spec">Browse files</a>
        
        
          <a class="button" href="/distribution/Specs_on_Spec_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Dec 2010</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: ???</li>
          
        
          
            <li>paradigms: Imperative</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Specs_on_Spec_distribution">Specs on Spec distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Oozlybub and Murphy">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>VARIABLES ARE p /p*/, p /q*/.
dynast(3) &lt;-&gt;
  (. do (. if? not? exists/dynast 5 ,then
       create/countably/many/dynasts #myself#, 5 .) .) ,then
  (. for each prime /p*|p/ below #myself#+2 do
       for each prime /q*|q/ below /p*|pp/+1 do
         if? not? exists/dynast /p*|p|p/+/q*|q|q/ ,then
           copy/dynast #myself#, /p*|ppp/, /q*|qqq/ .)
</code></pre>
<p>The name of this language is Oozlybub and Murphy. Despite appearances,
this name refers to a single language. The majority of the language is named
Oozlybub. The fact that the language is not entirely named Oozlybub is named
Murphy. Deal with it.  For the sake of providing an "olde tyme esoterickal
de-sign", the language combines several unusual features, including multiple
interleaved parse streams, infinitely long variable names, gratuitously strong
typing, and only-conjectural Turing completeness.</p>
    
      <h3 id="gemooy"><a href="#gemooy">Gemooy</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Gemooy">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Gemooy">Browse files</a>
        
        
          <a class="button" href="/distribution/Gemooy_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Dec 2, 2010</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: Turing-complete</li>
          
        
          
            <li>influences: <a href="https://esolangs.org/wiki/2-ill">2-ill</a>, <a href="../article/Languages.md#etcha">Etcha</a></li>
          
        
          
            <li>paradigms: Imperative</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Gemooy_distribution">Gemooy distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Gemooy">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Gemooy">catseye.tc</a></li>
          
        
          
            <li>jnlp @ <a href="https://archive.org/details/yoob-rel_0_3_2018_1128">archive.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>%### # ###   # #   ### # ###   # #   ### # ###@

   @    @#         @
  @      @          @
 @@
@                   @
    $         @# # @
             #      @
            #
       @   @
                    @

       @
      #
     #
    @
    @    @
     @# @
@        @
         @
  @     @#@
</code></pre>
<p>Gemooy is a 2-dimensional esolang with 3 instructions (5 initial symbols)
which combines features from <a href="https://esolangs.org/wiki/2-ill">2-ill</a> and <a href="../article/Languages.md#etcha">Etcha</a>, and adds
self-modification.  It came about when the author noticed the tape-related
semantics of 2-ill were essentially the same as those of <a href="https://esolangs.org/wiki/BitChanger">BitChanger</a>.</p>
<h4 id="reference-implementation-gemooyjs">Reference Implementation: gemooy.js</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#javascript">Javascript</a></li>
<li>host-platform: <a href="https://www.w3.org/TR/html5/">HTML5</a></li>
</ul>
<h4 id="implementation-tccatseyeyoobgemooy">Implementation: tc.catseye.yoob.gemooy</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#java">Java</a></li>
<li>host-platform: <a href="../article/Archived.md#yoob">yoob</a></li>
</ul>
    
      <h3 id="nhohnhehr"><a href="#nhohnhehr">Nhohnhehr</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Nhohnhehr">Browse files</a>
        
        
          <a class="button" href="/distribution/Nhohnhehr_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Dec 8, 2010</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: can simulate some push-down automata</li>
          
        
          
            <li>paradigms: 2-dimensional</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Nhohnhehr_distribution">Nhohnhehr distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Nhohnhehr">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>+------+
|    /}|
|&amp;#/$?@|
|  / \&amp;|
|      |
| {    |
|\\    |
+------+
</code></pre>
<p>Nhohnhehr is a remotely fungeoid language which explores the design
space between having a fixed playfield versus an expandable one.  When the
instruction pointer reaches the edge of the playfield (the "room"), whether
it wraps around or creates a new room and adjoins it to that edge, depends
on the current <em>edge mode</em> of the program.  New copies of rooms may be rotated
before being adjoined to existing rooms, but rooms are otherwise immutable.</p>
<h4 id="reference-implementation-nhohnhehrpy">Reference Implementation: nhohnhehr.py</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
</ul>
    
      <h3 id="kelxquoia"><a href="#kelxquoia">Kelxquoia</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Kelxquoia">Browse files</a>
        
        
          <a class="button" href="/distribution/Kelxquoia_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Dec 23, 2010</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: 2-dimensional, Grid-rewriting, Self-modifying</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Kelxquoia_distribution">Kelxquoia distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code> &gt;+-0 0*+-1*/+-?*-R*- *+-?*-R*-?*/v
 RRRRRRRRRRRRRRRRRRRR RRRRRRRRRRRRR
$&gt;+-0 0*+-1*/+-?*-R*- *+-?*-R*-?*/v
    ' '   '       '  '      '   
             '         '  '     
 ^      /*?-*P-*?-+*?-*P-* -+     &lt;
 P      PPPPPPPPPPPPPPPPPP PP     P
 ^      /*?-*P-*?-+*?-*P-* -+     &lt;

 00 00 00 00
</code></pre>
<p>Kelxquoia is another remotely fungeoid language, this one self-modifying
— in fact, self-destroying.  As instructions are executed, they are
erased.  In order to execute indefinitely, new instructions of some sort
must be created. Luckily the language provides as its main data-manipulation
facility, grid-rewriting, which can be used to restore instructions that
were previously erased after execution.</p>
    
      <h3 id="wunnel"><a href="#wunnel">Wunnel</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Wunnel">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Wunnel">Browse files</a>
        
        
          <a class="button" href="/distribution/Wunnel_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Feb 13, 2011</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>influences: <a href="https://esolangs.org/wiki/1L">1L</a>, <a href="https://esolangs.org/wiki/reMorse">reMorse</a></li>
          
        
          
            <li>paradigms: Turning tarpit</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Wunnel_distribution">Wunnel distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Wunnel">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Wunnel">catseye.tc</a></li>
          
        
          
            <li>jnlp @ <a href="https://archive.org/details/yoob-rel_0_3_2018_1128">archive.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>          o   ooo  o


o
o
o
o         o
o         o
o         o
o         o
o
o        o     o
o         o
o
o        o
o              o
o        o     o
o              o

         o
o oooooooo     o
         o
         o
         o

         o    oooo o
</code></pre>
<p>Wunnel is a two-dimensional language which draws from the <a href="https://esolangs.org/wiki/1L">1L</a>
family of languages and incorporates features from <a href="https://esolangs.org/wiki/reMorse">reMorse</a>. The name
is both a play on the pronunciation of "1L", and a recursive portmanteau
of the words <em>Wunnel</em> and <em>tunnel</em> which is used to describe the long sequences
of identical instructions (often nops) used in Wunnel programs to sync up
remote parts of the program.</p>
<h4 id="reference-implementation-tccatseyeyoobwunnel">Reference Implementation: tc.catseye.yoob.wunnel</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#java">Java</a></li>
<li>host-platform: <a href="../article/Archived.md#yoob">yoob</a></li>
</ul>
<h4 id="implementation-wunneljs">Implementation: wunnel.js</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#javascript">Javascript</a></li>
<li>host-platform: <a href="https://www.w3.org/TR/html5/">HTML5</a></li>
</ul>
    
      <h3 id="pail"><a href="#pail">Pail</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Pail">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Pail">Browse files</a>
        
        
          <a class="button" href="/distribution/Pail_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: May 25, 2011</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>influences: <a href="../article/Languages.md#pixley">Pixley</a></li>
          
        
          
            <li>paradigms: Functional</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Pail_distribution">Pail distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Pail">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Pail">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>**[*let [
     [cadrg *[#fst ##*[#snd #g]]]
     **[*let [
          [g [x [y z]]]
          ***cadrg
       ]]
  ]]
</code></pre>
<p>Pail is a programming language based on pairs; just as Lisp stands
for LISt Processing, Pail stands for PAIr Language. Its original working
title was "Bizaaro[sic]-Pixley", as it attempts to resemble <a href="../article/Languages.md#pixley">Pixley</a>
while turning several concepts on their heads: use pairs instead of lists,
quote by default instead of eval by default, and allow not just values but also
names of bindings to be expressed.</p>
<p>"Pail is an acceptable Bizaaro[sic]-Pixley" is a reference to an article
called "Ruby is an acceptable Lisp".</p>
<h4 id="reference-implementation-paillhs">Reference Implementation: Pail.lhs</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a> (Literate Haskell)</li>
</ul>
    
      <h3 id="xoomonk"><a href="#xoomonk">Xoomonk</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Xoomonk">Browse files</a>
        
        
          <a class="button" href="/distribution/Xoomonk_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Aug 7, 2011</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Imperative, Lazy</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Xoomonk_distribution">Xoomonk distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Xoomonk">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>l := $loop*
counter := 5
l.do := {
  y := x
  print ^.counter
  o := $sub*
  o.x := ^.counter
  o.y := 1
  ^.counter := o.result
  continue := o.result
}
</code></pre>
<p>Xoomonk is a programming language in which <em>malingering updatable
stores</em> are first-class objects.  Malingering updatable stores unify several
language constructs, including procedure activations, named parameters, and
object-like data structures.</p>
<p>The Xoomonk project was also an experiment in <em>test-driven language design</em>.
The specification is largely composed of a number of example programs in
the format of <a href="../article/Formats.md#falderal">Falderal</a> tests, which were written while the language was
being designed.  These were used to compare the reference implementation,
while it was being developed, against the spec.</p>
<h4 id="reference-implementation-xoomonkpy">Reference Implementation: xoomonk.py</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
</ul>
    
      <h3 id="flobnar"><a href="#flobnar">Flobnar</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Flobnar">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Flobnar">Browse files</a>
        
        
          <a class="button" href="/distribution/Flobnar_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Oct 28, 2011</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>influences: <a href="../article/Languages.md#befunge-93">Befunge-93</a></li>
          
        
          
            <li>paradigms: Functional, 2-dimensional</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Flobnar_distribution">Flobnar distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Flobnar">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Flobnar">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>&gt;     v
^\ &lt;

:v    v   \&lt;@
-&lt;      : 6
1 :   &gt; *
  -|    &lt;
  11
</code></pre>
<p>One day in September of 2011 — though I'm not sure precisely
which one — marked <a href="../article/Languages.md#befunge-93">Befunge-93</a>'s 18th birthday.  That means that
Befunge is now old enough to drink in its native land of Canada.  To celebrate
this, I thought I'd get Befunge-93 drunk to see what would happen.  What
happened was Flobnar, an esolang which is in many respects a functional dual
of Befunge-93; most of the symbols have analogous meanings, but execution
proceeds in a much more dataflow-like fashion.</p>
<h4 id="reference-implementation-flobnarhs">Reference Implementation: Flobnar.hs</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
</ul>
    
      <h3 id="madison"><a href="#madison">Madison</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Specs-on-Spec">Browse files</a>
        
        
          <a class="button" href="/distribution/Specs_on_Spec_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Proof Language</li>
          
        
          
            <li>inception-date: Dec 2, 2011</li>
          
        
          
            <li>genre: DSL</li>
          
        
          
            <li>development-stage: unfinished</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Proof checking, Term-rewriting</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Specs_on_Spec_distribution">Specs on Spec distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>type tree is
  tree(leaf)        -&gt; true
  tree(branch(X,Y)) -&gt; and(tree(X),tree(Y))
in let
  reflect(leaf)        -&gt; leaf
  reflect(branch(A,B)) -&gt; branch(reflect(B),reflect(A))
in theorem
  forall X where tree(X)
    reflect(reflect(X)) ~&gt; X
proof
  case X = leaf
    reflect(reflect(leaf))
    -&gt; reflect(leaf)        [by reflect.1]
    -&gt; leaf                 [by reflect.1]
  case X = branch(S, T)
    reflect(reflect(branch(S, T)))
    -&gt; reflect(branch(reflect(T),reflect(S)))          [by reflect.2]
    -&gt; branch(reflect(reflect(S)),reflect(reflect(T))) [by reflect.2]
    -&gt; branch(S,reflect(reflect(T)))                   [by IH]
    -&gt; branch(S,T)                                     [by IH]
qed
</code></pre>
<p>Madison was an experiment in designing a language in which one can state
proofs of properties of term-rewriting systems.  Classical methods of
automated reasoning, such as resolution, are not used; indeed, term-rewriting itself is
used to check the proofs.  Both direct proof and proof by induction
are supported.  Induction in a proof must be across a structure which
has a well-founded inductive definition.  Such structures can be thought
of as types, although this is largely nominal; the traditional typelessness
of term-rewiting systems is largely retained.</p>
<p>This design never got to the point where I thought I could implement it,
but influenced <a href="../article/Languages.md#maxixe">Maxixe</a>.</p>
    
      <h3 id="robin"><a href="#robin">Robin</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Robin">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Robin">Browse files</a>
        
        
          <a class="button" href="/distribution/Robin_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: 2011</li>
          
        
          
            <li>genre: Production language</li>
          
        
          
            <li>development-stage: unfinished</li>
          
        
          
            <li>paradigms: Functional</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Robin_distribution">Robin distribution</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Robin">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>(require multiply)

(define fact (fun (self n)
  (multiply n
    (if (gt? n 1)
      (self self (subtract n 1))
      1))))
(display (fact fact 5))
</code></pre>
<p>Robin is a functional programming language with eager evaluation, latent typing,
and a homoiconic syntax (see <a href="../article/Project%20Dependencies.md#scheme">Scheme</a>), based on a radically simple core semantics
(see <a href="../article/Languages.md#pixley">Pixley</a>) in which both functions and macros are defined in terms of a more
basic abstraction, the <a href="https://en.wikipedia.org/wiki/Fexpr">fexpr</a>.</p>
<p>Expressions in Robin are referentially transparent; programs interact with the outside
world through an event-oriented framework.</p>
<p>Robin was originally a design for a <a href="../article/Languages.md#pixley">Pixley</a>-based operating system (or something
similar to an operating system) which was heavily resource-oriented; almost
everything, including every concurrent process, was a virtual device
which must be acquired from a central resource arbiter.  This arbiter could
satisfy the constraints specified when requesting a device any way it saw
fit; so the operating environment potentially had a lot of influence over
exactly what any given program does.</p>
<p>Not a lot of that idea remains, but it did influence the fact that Robin should
be a purely functional language which nevertheless interacts with the rest of the
world through some kind of framework.  After much consideration, the framework
arrived at is very similar to that used in The Elm Architecture.</p>
<h4 id="reference-implementation-languagerobin">Reference Implementation: Language.Robin</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
</ul>
    
      <h3 id="troupe"><a href="#troupe">Troupe</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Troupe">Browse files</a>
        
        
          <a class="button" href="/distribution/Troupe_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Jun 25, 2012</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Imperative, State machine</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Troupe_distribution">Troupe distribution</a></li>
          
        
      </ul>
      <p>Troupe is an esolang based on hedgehogs, faery rings, and hills.  It maps
fairly neatly to the definition of a Turing machine, so it is almost certainly
<a href="https://esolangs.org/wiki/Turing-complete">Turing-complete</a>.</p>
    
      <h3 id="velo"><a href="#velo">Velo</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Velo">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Velo">Browse files</a>
        
        
          <a class="button" href="/distribution/Velo_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Jul 2012</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>influences: Ruby</li>
          
        
          
            <li>paradigms: Object-oriented</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Velo_distribution">Velo distribution</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Velo">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>yes = {IO.print {Yes}}
no = {IO.print {No}}
if ({X}.equals {Y}), yes, no
</code></pre>
<p>Velo is a vaguely <a href="../article/Project%20Dependencies.md#ruby">Ruby</a>-inspired "scripting" language which unifies
strings with code blocks, and scripts with object classes.  Curly braces
delimit string literals, and there is no difference between a string literal
and a block of code given to, say, an <code>if</code> statement.  Any given script is
an object, which inherits from the root object in delegation-OO style.</p>
<h4 id="reference-implementation-velorb">Reference Implementation: velo.rb</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: Ruby</li>
</ul>
<h4 id="implementation-velolua">Implementation: velo.lua</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#lua">Lua</a></li>
</ul>
    
      <h3 id="exanoke"><a href="#exanoke">Exanoke</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Exanoke">Browse files</a>
        
        
          <a class="button" href="/distribution/Exanoke_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: ca Jul 2012</li>
          
        
          
            <li>genre: Experimental language</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: Primitive recursive</li>
          
        
          
            <li>paradigms: Functional</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Exanoke_distribution">Exanoke distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Exanoke">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>def inc(#)
  cons(:one, #)
def add(#, other)
  if eq?(#, :nil) then other else self(&lt;tail #, inc(other))
def mul(#, other)
  if eq?(#, :nil) then :nil else
    add(other, self(&lt;tail #, other))
def fact(#)
  if eq?(#, :nil) then cons(:one, :nil) else
    mul(#, self(&lt;tail #))
def four(#)
  cons(:one, cons(:one, cons(:one, cons(:one, #))))
fact(four(:nil))
</code></pre>
<p>Exanoke is a functional language which is syntactically restricted to
expressing the primitive recursive functions.</p>
<h4 id="reference-implementation-exanokepy">Reference Implementation: exanoke.py</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
</ul>
    
      <h3 id="cfluviurrh"><a href="#cfluviurrh">Cfluviurrh</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="https://archive.org/details/cfluviurrh-1.0-2014.0819">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Cfluviurrh">Browse files</a>
        
        
          <a class="button" href="/distribution/Cfluviurrh_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Aug 26, 2012</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Imperative</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Cfluviurrh_distribution">Cfluviurrh distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Cfluviurrh">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://archive.org/details/cfluviurrh-1.0-2014.0819">archive.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>(print ASCII table while experiencing a bewildering array of emotions)
a=8
a*=8
b=a
b+=a
b-=2
:X
a+=1
a&gt;
z@=X
z?a&lt;b
</code></pre>
<p>Cfluviurrh is, as far as I am aware, the first programming language designed
for writing programs that can <em>feel</em>. Cfluviurrh defines a mechanism by which a
program can be instructed to experience particular emotions.</p>
<p>You might, thus, on first blush, consider Cfluviurrh to be unimplementable,
as modern-day computers are not capable of experiencing emotions (you guess.)
However, this is demonstrably untrue.  The reference interpreter demonstrates it.</p>
<h4 id="reference-implementation-cfluviurrh">Reference Implementation: cfluviurrh</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#ansi-c">ANSI C</a></li>
</ul>
    
      <h3 id="jolverine"><a href="#jolverine">Jolverine</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Jolverine">Browse files</a>
        
        
          <a class="button" href="/distribution/Jolverine_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Sep 10, 2012</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: Turing-complete</li>
          
        
          
            <li>influences: Wunnel, Half-Broken Car in Heavy Traffic</li>
          
        
          
            <li>paradigms: Turning tarpit, 2-dimensional</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Jolverine_distribution">Jolverine distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Jolverine">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>--*-*
     \
      \
       \           *
        \         /
         \       /
          \     /
           *   /
            \ /
             *-*---*
</code></pre>
<p>The Jolverine language was devised as a conscious attempt to expand the
genre of turning tarpit by adding the feature of modifying the instruction
wheel during execution.</p>
<p>The name is a portmanteau of "jolly wolverine" (where "jolly" is a
euphemism for "drunk",) which is an attempt to capture, in a noun phrase,
the language's vicious, erratic nature.</p>
<h4 id="reference-implementation-jolverinepy">Reference Implementation: jolverine.py</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
</ul>
    
      <h3 id="sickbay"><a href="#sickbay">SICKBAY</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/SICKBAY">Browse files</a>
        
        
          <a class="button" href="/distribution/SICKBAY_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Sep 22, 2012</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: Turing-complete</li>
          
        
          
            <li>paradigms: Imperative</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/SICKBAY_distribution">SICKBAY distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/SICKBAY">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>10 LET B% = 99
(100+B%) END
100 GOTO 200:REM BEGIN LOOP
200 PRINT B%;:PRINT " BOTTLES OF BEER ON THE WALL,"
205 PRINT B%;:PRINT " BOTTLES OF BEER,"
210 PRINT "TAKE ONE DOWN, PASS IT AROUND,"
215 LET B% = (B% - 1)
220 PRINT B%;:PRINT " BOTTLES OF BEER ON THE WALL.":PRINT ""
230 GOTO 100
</code></pre>
<p>SICKBAY is an esoteric dialect of <a href="../article/Project%20Dependencies.md#basic">BASIC</a> with a call ring buffer instead of
a call stack, and computed line number definitions (and no <code>IF</code> because
of that.)</p>
<h4 id="reference-implementation-sawbones">Reference Implementation: SAWBONES</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
</ul>
    
      <h3 id="carriage"><a href="#carriage">Carriage</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Carriage">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Carriage">Browse files</a>
        
        
          <a class="button" href="/distribution/Carriage_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Nov 2012</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: unknown computational class</li>
          
        
          
            <li>paradigms: Concatenative</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Carriage_distribution">Carriage distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Carriage">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Carriage">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>111-@11-~!$11111++++11-~@11-~!
</code></pre>
<p>Carriage is the result of various, not-entirely-successful attempts to
design a "pure" concatenative language — one in which the program
texts are monoids and nothing but monoids (no quoting operators or
the like.)  The result was midly unusual — subroutines are specified
by indices into an area of the stack which contains program symbols,
thus may overlap — and was released as an esolang.</p>
<h4 id="reference-implementation-carriagehs">Reference Implementation: Carriage.hs</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
</ul>
    
      <h3 id="castile"><a href="#castile">Castile</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Castile">Browse files</a>
        
        
          <a class="button" href="/distribution/Castile_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Nov 21, 2012</li>
          
        
          
            <li>genre: Experimental language</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>influences: <a href="../article/Project%20Dependencies.md#ansi-c">ANSI C</a>, <a href="../article/Languages.md#eightebed">Eightebed</a>, <a href="http://www.rust-lang.org/">Rust</a></li>
          
        
          
            <li>paradigms: Imperative, Functional</li>
          
        
          
            <li>etymology: soap</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Castile_distribution">Castile distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>fun foo(a, b: integer|string) {
  r = a;
  typecase b is integer {
    r = r + b;
  };
  typecase b is string {
    r = r + len(b);
  };
  r
}
main = fun() {
  a = foo(a, 333 as integer|string);
  a = foo(a, "hiya" as integer|string);
  a /* should output 337 */
}
</code></pre>
<p>Castile is a simple imperative language with union types.  It exists mainly
because an interpreter-plus-compiler for it was written.  It is
a bit like <a href="../article/Project%20Dependencies.md#ansi-c">ANSI C</a> except with proper union types (and no typecasts.)  Null
pointer dereferencing is thus prevented because "null" is a separate type in
the union that must be selected explicitly with a <code>typecase</code> form.  Local
variables are mutable, but arguments and globals aren't.  The compiler
supports several backends, including <a href="../article/Project%20Dependencies.md#ansi-c">ANSI C</a>, <a href="../article/Project%20Dependencies.md#javascript">Javascript</a>, and <a href="../article/Project%20Dependencies.md#ruby">Ruby</a>.</p>
<h4 id="reference-implementation-castile-python">Reference Implementation: castile (Python)</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter-plus-compiler</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
<li>target-languages: <a href="../article/Project%20Dependencies.md#ansi-c">ANSI C</a>, <a href="../article/Project%20Dependencies.md#javascript">Javascript</a>, <a href="../article/Project%20Dependencies.md#ruby">Ruby</a>, stackmac</li>
</ul>
    
      <h3 id="sixtypical"><a href="#sixtypical">SixtyPical</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/SixtyPical">Browse files</a>
        
        
          <a class="button" href="/distribution/SixtyPical_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Mar 31, 2014</li>
          
        
          
            <li>genre: Machine language</li>
          
        
          
            <li>paradigms: Imperative</li>
          
        
          
            <li>etymology: portmanteau</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/SixtyPical_distribution">SixtyPical distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>byte table screen @ 1024
routine main
  trashes a, x, z, n, screen
{
    ld x, 0
    ld a, 83    // 83 = screen code for heart
    repeat {
        st a, screen + x
        inc x
    } until z
}
</code></pre>
<p>SixtyPical is a very low-level programming language, similar to 6502
assembly, which defines a set of static analyses via type-checking and
abstract interpretation (liveness analysis of variables, i.e. memory
locations.)</p>
<h4 id="reference-implementation-sixtypical-python">Reference Implementation: sixtypical (Python)</h4>
<ul>
<li>license: BSD license</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
<li>implementation-type: compiler</li>
<li>target-language: 6502 machine code</li>
</ul>
<h4 id="implementation-sixtypical-haskell">Implementation: sixtypical (Haskell)</h4>
<ul>
<li>license: BSD license</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
<li>implementation-type: compiler</li>
<li>target-language: Ophis Assembler</li>
</ul>
    
      <h3 id="tamsin"><a href="#tamsin">Tamsin</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Tamsin">Browse files</a>
        
        
          <a class="button" href="/distribution/Tamsin_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Apr 27, 2014</li>
          
        
          
            <li>genre: Experimental language</li>
          
        
          
            <li>development-stage: unfinished</li>
          
        
          
            <li>paradigms: Functional, Logic programming, Metalanguage</li>
          
        
          
            <li>etymology: feminine given name</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Tamsin_distribution">Tamsin distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>main = expr0 → E &amp; walk(E).
expr0 = expr1 → E1 &amp; {"+" &amp; expr1 → E2 &amp; E1 ← add(E1,E2)} &amp; E1.
expr1 = term → E1 &amp; {"*" &amp; term → E2 &amp; E1 ← mul(E1,E2)} &amp; E1.
term = "x" | "y" | "z" | "(" &amp; expr0 → E &amp; ")" &amp; E.
walk(add(L,R)) = walk(L) → LS &amp; walk(R) → RS &amp; return LS+RS+' +'.
walk(mul(L,R)) = walk(L) → LS &amp; walk(R) → RS &amp; return LS+RS+' *'.
walk(X) = return ' '+X.
</code></pre>
<p>Tamsin is an oddball little language that can't decide if it's a
meta-language, a programming language, or a <a href="https://catseye.tc/node/Perl">rubbish lister</a>.
Its primary goal is to allow the rapid development of parsers,
static analyzers, interpreters, and compilers, and to allow them
to be expressed <em>compactly</em>.</p>
<h4 id="reference-implementation-tamsinpy">Reference Implementation: tamsin.py</h4>
<ul>
<li>license: BSD license</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
<li>implementation-type: interpreter</li>
</ul>
<p>Kind of compiles, too.</p>
<h4 id="implementation-tamsintamsin">Implementation: tamsin.tamsin</h4>
<ul>
<li>license: BSD license</li>
<li>host-language: Tamsin</li>
<li>implementation-type: compiler</li>
<li>target-language: C99</li>
</ul>
    
      <h3 id="yolk"><a href="#yolk">Yolk</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Yolk">Browse files</a>
        
        
          <a class="button" href="/distribution/Yolk_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Aug 24, 2014</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Functional</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Yolk_distribution">Yolk distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Yolk">esolangs.org</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>(ifeq (head arg) (quote arg)
    (head (tail (tail arg)))
    (ifeq (head (head arg)) (quote head)
        (head (self (cons (head (tail (head arg))) (tail arg))))
        (ifeq (head (head arg)) (quote tail)
            (tail (self (cons (head (tail (head arg))) (tail arg))))
            (ifeq (head (head arg)) (quote cons)
                (cons (self (cons (head (tail (head arg))) (tail arg))) (self (cons (head (tail (tail (head arg)))) (tail arg))))
                (ifeq (head (head arg)) (quote quote)
                    (head (tail (head arg)))
                    (ifeq (head (head arg)) (quote ifeq)
                        (ifeq (self (cons (head (tail (head arg))) (tail arg)))
                              (self (cons (head (tail (tail (head arg)))) (tail arg)))
                              (self (cons (head (tail (tail (tail (head arg))))) (tail arg)))
                              (self (cons (head (tail (tail (tail (tail (head arg)))))) (tail arg))))
                        (ifeq (head (head arg)) (quote self)
                            (self (cons (head (tail arg))
                                    (cons (head (tail arg))
                                      (cons (self (cons (head (tail (head arg))) (tail arg))) (tail (quote (tail)))))))
                            (ifeq))))))))
</code></pre>
<p>Yolk is a tiny S-expression-based programming language (or computational
calculus) with a tiny meta-circular interpreter.</p>
<h4 id="reference-implementation-yolkpy">Reference Implementation: yolk.py</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
</ul>
<h4 id="reference-implementation-yolkyolk">Reference Implementation: yolk.yolk</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: Yolk</li>
</ul>
    
      <h3 id="matchbox"><a href="#matchbox">Matchbox</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Matchbox">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Matchbox">Browse files</a>
        
        
          <a class="button" href="/distribution/Matchbox_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Feb 2015</li>
          
        
          
            <li>genre: Pedagogical language</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: ???</li>
          
        
          
            <li>paradigms: Imperative</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Matchbox_distribution">Matchbox distribution</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Matchbox">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>MOV 1, M0
MOV 1, M2
WAIT M1, 0
WAIT M2, 0
; begin c.s.
MOV M3, R0
INC R0
MOV R0, M3
; end c.s.
MOV 0, M0
</code></pre>
<p>A toy language for a toy race-condition finder.</p>
<p>I wrote this because I feel race conditions are an underappreciated
problem in software development.  In programming education, they're often
not given the attention they deserve, given that they are a real problem
that comes up once you get into any kind of concurrent programming — and
one that can very difficult to pinpoint, much less fix.</p>
<p>The general "someone else's problem"-ness surrounding race conditions seems
to have fostered two misconceptions in particular that I wanted to highlight.</p>
<p>Even though Matchbox is an assembly-like language, race conditions are not
restricted to machine language.  Nearly every high-level programmer works
with either filesystems or databases, and those are both basically gigantic
tracts of shared memory.  Race conditions are just waiting to happen, if
you're not careful.</p>
<p>And there is sometimes the impression that the only way to protect oneself
against race conditions is if the system provides an
atomic-test-and-set-like operation.  If such an operation is avaiable, you
should probably use it, but it's not the only way.  There are several
different programming methods for guaranteeing mutually exclusive access to a
resource, even when such operations are not available.  These were developed
before such operations were widely available in hardware, and although they
are largely of historical interest, they also posess a certain conceptual
beauty.  One such method is
<a href="http://en.wikipedia.org/wiki/Peterson%27s_algorithm">Peterson's Algorithm</a>,
which Matchbox can run and show correct.</p>
<h4 id="implementation-matchboxjs">Implementation: matchbox.js</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: static analyzer</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#javascript">Javascript</a></li>
<li>host-platform: <a href="https://www.w3.org/TR/html5/">HTML5</a></li>
</ul>
    
      <h3 id="situ-sol"><a href="#situ-sol">SITU-SOL</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="https://archive.org/details/situ-sol-c64">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/SITU-SOL">Browse files</a>
        
        
          <a class="button" href="/distribution/SITU-SOL_distribution">Download</a>
        
      </div>

      
        <div>
          
            
              <img alt="SITU-SOL" src="https://git.catseye.tc/SITU-SOL/blob/master/doc/bootstrap-zero/images/tumblr_inline_nrw4gcaz1J1tvda25_540.png?raw=true" />
            
          
        </div>
      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Jul 2015</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: Turing-complete</li>
          
        
          
            <li>paradigms: Imperative, Stack-based</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/SITU-SOL_distribution">SITU-SOL distribution</a></li>
          
        
          
            <li>online @ <a href="https://archive.org/details/situ-sol-c64">archive.org</a></li>
          
        
      </ul>
      <p>SITU-SOL is a vaguely Forth-like language which was designed and
implemented (by hand!) during RetroChallenge 2015/07, and entered
into an emulated <a href="../article/Project%20Dependencies.md#commodore-64">Commodore 64</a> using <a href="../article/Tools.md#situ-mon">SITU-MON</a>.</p>
<h4 id="reference-implementation-situ-sol-commodore-64">Reference Implementation: SITU-SOL (Commodore 64)</h4>
<ul>
<li>license: Unknown license</li>
<li>implementation-type: compiler</li>
<li>host-language: 6502 machine code</li>
<li>target-language: 6502 machine code</li>
</ul>
    
      <h3 id="samovar"><a href="#samovar">Samovar</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Samovar">Browse files</a>
        
        
          <a class="button" href="/distribution/Samovar_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: 2016</li>
          
        
          
            <li>genre: DSL</li>
          
        
          
            <li>development-stage: basically complete</li>
          
        
          
            <li>computational-class: unknown computational class</li>
          
        
          
            <li>influences: <a href="../article/Languages.md#madison">Madison</a></li>
          
        
          
            <li>paradigms: Probabilistic, Logic programming, State machine</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Samovar_distribution">Samovar distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>rules
  [actor(α),item(β),¬holding(α,β)]  α picks up the β.   [holding(α,β)]
  [actor(α),item(β),holding(α,β)]   α puts down the β.  [¬holding(α,β)]
end
situations
  [actor(Ignatz),item(brick)]
end
</code></pre>
<p>Samovar is a DSL for world-modeling using propositions rather than explicit objects.
It could be thought of as an "assertion-retraction engine", which itself could be
thought of as a very stilted style of Prolog programming plus some syntactic
sugar.</p>
<h4 id="reference-implementation-samovar-python">Reference Implementation: samovar (Python)</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
</ul>
    
      <h3 id="maxixe"><a href="#maxixe">Maxixe</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Maxixe">Browse files</a>
        
        
          <a class="button" href="/distribution/Maxixe_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Proof Language</li>
          
        
          
            <li>inception-date: 2016</li>
          
        
          
            <li>genre: Experimental language</li>
          
        
          
            <li>development-stage: basically complete</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>influences: <a href="../article/Languages.md#madison">Madison</a></li>
          
        
          
            <li>paradigms: Proof checking, Natural deduction</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Maxixe_distribution">Maxixe distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>given
    Modus_Ponens                 = impl(P, Q) ; P |- Q
    Simplification               = and(P, Q)      |- Q
    Commutativity_of_Conjunction = and(P, Q)      |- and(Q, P)
    Premise                      =                |- and(p, impl(p, q))
show
    q
proof
    Step_1 = and(p, impl(p, q))    by Premise
    Step_2 = and(impl(p, q), p)    by Commutativity_of_Conjunction with Step_1
    Step_3 = impl(p, q)            by Simplification with Step_1
    Step_4 = p                     by Simplification with Step_2
    Step_5 = q                     by Modus_Ponens with Step_3, Step_4
qed
</code></pre>
<p>Maxixe is a simple, generalized proof-checking language.  Given a proof written out fully
and explicitly (including all rules of inference), a computer can check if it is valid
or not.  Since Maxixe has no built-in rules of inference, it is in this manner not
restricted to using a particular kind of logic — it ought to be possible to implement
propositional logic, predicate logic, equational logic in it (and fragments and
combinations thereof).</p>
<h4 id="reference-implementation-maxixe-python">Reference Implementation: maxixe (Python)</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
</ul>
    
      <h3 id="equipage"><a href="#equipage">Equipage</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Equipage">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Equipage">Browse files</a>
        
        
          <a class="button" href="/distribution/Equipage_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: May 14, 2018</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>influences: <a href="../article/Languages.md#carriage">Carriage</a></li>
          
        
          
            <li>paradigms: Functional, Concatenative</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Equipage_distribution">Equipage distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Equipage">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Equipage">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>1~%1-1-1-~;
.!.!.!.!.!.!.!.!.!.!
$11-1-~;
.!.!.!.!.!.!.!
1$
.!
11+11-11+1
.!.!.!.!.!.!.!.!.!
!
11-1-~;
.!.!.!.!.!.!
!
</code></pre>
<p>Equipage is a "pure" concatenative programming language — program
texts are monoids and nothing but monoids (no quoting operators or
the like.)  It is the language that <a href="../article/Languages.md#carriage">Carriage</a> might've been, if
I had not been so concerned about quoting at the time.</p>
<h4 id="reference-implementation-equipagehs">Reference Implementation: Equipage.hs</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
</ul>
<h4 id="implementation-equipagepy">Implementation: equipage.py</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
</ul>
    
      <h3 id="wanda"><a href="#wanda">Wanda</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Wanda">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Wanda">Browse files</a>
        
        
          <a class="button" href="/distribution/Wanda_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Feb 27, 2019</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Concatenative (nominally), String-rewriting</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Wanda_distribution">Wanda distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Wanda">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Wanda">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>$
: 0 $ fact -&gt; $ 1 ;
: $ fact -&gt; $ dup 1 - fact * ;
5 fact
</code></pre>
<p>Wanda is a Forth-like, "concatenative" programming language that's arguably not
concatenative at all, nor even "stack-based", because it's based on a
string-rewriting semantics.</p>
<h4 id="reference-implementation-wandalua">Reference Implementation: wanda.lua</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#lua">Lua</a></li>
</ul>
    
      <h3 id="wagon"><a href="#wagon">Wagon</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Wagon">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Wagon">Browse files</a>
        
        
          <a class="button" href="/distribution/Wagon_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Aug 13, 2019</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: Turing-complete</li>
          
        
          
            <li>paradigms: Functional, Concatenative</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Wagon_distribution">Wagon distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Wagon">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Wagon">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>p@ I I I SII SII
</code></pre>
<p>Wagon is a purely concatentive (in the sense of <a href="../article/Languages.md#equipage">Equipage</a>) language which
is "second-order concatenative": instead of functions which take states to states,
the symbols of the language represent functions which take functions from states
to states, to functions that take states to states.</p>
<p>The hope in designing it was that the second-order status would allow control
structures to be embedded in the program.  It does allow this, but it does not
allow arbitrary control structures.  Nevertheless, it has been shown to be
Turing-complete, as arbitrary Tag systems can be compiled to Wagon.</p>
<h4 id="reference-implementation-languagewagon">Reference Implementation: Language.Wagon</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
</ul>
    
      <h3 id="oxcart"><a href="#oxcart">Oxcart</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Oxcart">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Oxcart">Browse files</a>
        
        
          <a class="button" href="/distribution/Oxcart_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Oct 28, 2019</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Functional, Concatenative, Continuation-passing</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Oxcart_distribution">Oxcart distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Oxcart">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Oxcart">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>&lt;0^^^^^^^^^^&gt;S:&lt;:v:)%
</code></pre>
<p>Oxcart is another purely concatenative (in the sense of <a href="../article/Languages.md#equipage">Equipage</a>) language;
but this time it's a continuation-passing concatenative language.
Instead of functions which take states to states, the symbols of the language represent
functions which are written in continuation-passing style (CPS), i.e. they
take two arguments: a state and a continuation.  A special form of function
composition is used to compose two such functions, and it has an identity and
forms a monoid like conventional function composition.</p>
<h4 id="reference-implementation-languageoxcart">Reference Implementation: Language.Oxcart</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
</ul>
    
      <h3 id="tandem"><a href="#tandem">Tandem</a></h3>

      <div style="float: right; margin-top: 5px;">
        
          <a class="button" href="/installation/Tandem">
            Try it online
          </a>
        
        
          <a class="button" href="https://git.catseye.tc/Tandem">Browse files</a>
        
        
          <a class="button" href="/distribution/Tandem_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: June 2020</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: Turing-complete</li>
          
        
          
            <li>paradigms: String-rewriting</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Tandem_distribution">Tandem distribution</a></li>
          
        
          
            <li>entry @ <a href="https://esolangs.org/wiki/Tandem">esolangs.org</a></li>
          
        
          
            <li>online @ <a href="https://catseye.tc/installation/Tandem">catseye.tc</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>{B:I,O}
Q → 0 &amp;
O → N &amp;
(
  Q0 → 1 &amp; Ic… → … |
  Q1 → 2 &amp; Ia… → … |
  Q1 → 2 &amp; Io… → … |
  Q2 → 3 &amp; It → &amp; O… → Y
)*
</code></pre>
<p>Tandem is an experimental rewriting language where the rewrite rules form a Kleene algebra.
The object being rewritten by a Tandem program is a collection of labelled stacks — a finite mapping
from strings to strings. The strings are always rewritten at the left edge, so they are effectively stacks.</p>
<p>Writing finite automata, push-down automata, Turing machines, and other automata is quite natural in Tandem,
because transition rules such as "In state 4, if the next character in the input is <code>g</code>, consume it and
push <code>$</code> onto the stack and go to state 9" translate quite straightforwardly to rewrite rules such as</p>
<pre><code>Q4 → 9 &amp; Ig… → … &amp; K… → $…
</code></pre>
<h4 id="reference-implementation-languagetandem">Reference Implementation: Language.Tandem</h4>
<ul>
<li>license: Public Domain</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
</ul>
    
      <h3 id="lanthorn"><a href="#lanthorn">Lanthorn</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Lanthorn">Browse files</a>
        
        
          <a class="button" href="/distribution/Lanthorn_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Feb 2021</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: mature</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Functional</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Lanthorn_distribution">Lanthorn distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>letrec
    odd  = fun(x) -&gt; if eq(x, 0) then false else even(sub(x, 1))
    even = fun(x) -&gt; if eq(x, 0) then true else odd(sub(x, 1))
in
    even(6)
</code></pre>
<p>Lanthorn is a purely functional toy programming language in which
<code>letrec</code> is mere syntactic sugar.  In it is demonstrated a transformation
from <code>letrec</code> to <code>let</code> that is purely syntactic, and which turns the
sample program shown above, into this:</p>
<pre><code>let
  odd$0 = fun(x, odd$1, even$1) -&gt; let
      odd = fun(x$1) -&gt; odd$1(x$1, odd$1, even$1)
      even = fun(x$1) -&gt; even$1(x$1, odd$1, even$1)
    in
      if eq(x, 0) then false else even(sub(x, 1))
  even$0 = fun(x, odd$1, even$1) -&gt; let
      odd = fun(x$1) -&gt; odd$1(x$1, odd$1, even$1)
      even = fun(x$1) -&gt; even$1(x$1, odd$1, even$1)
    in
      if eq(x, 0) then true else odd(sub(x, 1))
  odd = fun(x) -&gt; odd$0(x, odd$0, even$0)
  even = fun(x) -&gt; even$0(x, odd$0, even$0)
in
  even(6)
</code></pre>
<h4 id="reference-implementation-languagelanthorn">Reference Implementation: Language.Lanthorn</h4>
<ul>
<li>license: MIT license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
</ul>
    
      <h3 id="vinegar"><a href="#vinegar">Vinegar</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Vinegar">Browse files</a>
        
        
          <a class="button" href="/distribution/Vinegar_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Programming Language</li>
          
        
          
            <li>inception-date: Nov 2021</li>
          
        
          
            <li>genre: Esolang</li>
          
        
          
            <li>development-stage: not fully complete</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Concatenative</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Vinegar_distribution">Vinegar distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>fact =&amp; fac1 fac2;
fac1 =&amp; dup int[0] gt!;
fac2 =| fac3 fac4;
fac3 =&amp; dup int[1] eq!;
fac4 =&amp; pop dup int[1] sub fact mul;
main =&amp; int[5] fact;
</code></pre>
<p>Vinegar is a "semi-concatenative" language where every operation can fail.</p>
<p>"Semi-concatenative" is supposed to mean that there isn't just the usual
implicit "concatenate" program-composing operator, there's also a second
program-composing operator, "alternate" (notated explicitly by <code>|</code>).</p>
<p>This second operator is intended to gracefully handle the case where a
program operation has failed -- which any of them can.</p>
<p>Although the second operator is notated explicitly, the language supports
a syntax variation (shown above) where both operators can be used
implicitly... as long as each definition is introduced appropriately.</p>
<h4 id="reference-implementation-vinegar-python">Reference Implementation: vinegar (Python)</h4>
<ul>
<li>license: BSD license</li>
<li>implementation-type: interpreter</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
</ul>
    
      <h3 id="eqthy"><a href="#eqthy">Eqthy</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Eqthy">Browse files</a>
        
        
          <a class="button" href="/distribution/Eqthy_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Proof Language</li>
          
        
          
            <li>inception-date: ca Jun 2022</li>
          
        
          
            <li>genre: Minimal language</li>
          
        
          
            <li>development-stage: work in progress</li>
          
        
          
            <li>computational-class: believed Turing-complete</li>
          
        
          
            <li>paradigms: Proof checking, Equational logic</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Eqthy_distribution">Eqthy distribution</a></li>
          
        
      </ul>
      <p>Sample proof:</p>
<pre><code>axiom (idright) mul(A, e) = A
axiom (idleft)  mul(e, A) = A
axiom (assoc)   mul(A, mul(B, C)) = mul(mul(A, B), C)
theorem (idcomm)
    mul(A, e) = mul(e, A)
proof
    A = A
    mul(A, e) = A           [by idright]
    mul(A, e) = mul(e, A)   [by idleft]
qed
</code></pre>
<p>Eqthy is a formalized language for proofs in equational logic.
Its design attempts to reconcile
<em>simplicity of implementation on a machine</em> with <em>human usability</em>.</p>
<p>On one hand, it is possible (and only somewhat tedious) for humans
to read Eqthy proofs, and to write them by hand.  On the other hand,
a checker for Eqthy proofs has been written in Python, in about 550
lines of code; the core verifier module is less than 200 lines of code.</p>
<h4 id="reference-implementation-eqthy-python">Reference Implementation: eqthy (Python)</h4>
<ul>
<li>reference: true</li>
<li>license: Unknown License</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#python">Python</a></li>
</ul>
    
      <h3 id="fountain"><a href="#fountain">Fountain</a></h3>

      <div style="float: right; margin-top: 5px;">
        
        
          <a class="button" href="https://git.catseye.tc/Fountain">Browse files</a>
        
        
          <a class="button" href="/distribution/Fountain_distribution">Download</a>
        
      </div>

      
      <ul>
        
          
            <li>type: Meta-language</li>
          
        
          
            <li>inception-date: 2023</li>
          
        
          
            <li>genre: Experimental language</li>
          
        
          
            <li>development-stage: unfinished</li>
          
        
          
            <li>paradigms: Metalanguage</li>
          
        
          
            <li>reference-distribution: <a href="https://catseye.tc/distribution/Fountain_distribution">Fountain distribution</a></li>
          
        
      </ul>
      <p>Sample program:</p>
<pre><code>Goal ::=
    &lt;. a = 0 .&gt; { "a" &lt;. a += 1 .&gt; } &lt;. a = n .&gt;
    &lt;. b = 0 .&gt; { "b" &lt;. b += 1 .&gt; } &lt;. b = n .&gt;
    &lt;. c = 0 .&gt; { "c" &lt;. c += 1 .&gt; } &lt;. c = n .&gt;
    ;
</code></pre>
<p>Fountain is a grammar formalism capable of expressing context-sensitive languages (CSLs),
and supporting both efficient parsing <em>and</em> efficient generation of strings
in to those languages.</p>
<p>The example grammar above both parses and generates strings of
the classic CSL <code>a</code>^<em>n</em> <code>b</code>^<em>n</em> <code>c</code>^<em>n</em>.  In both directions it
operates deterministically, and thus efficiently, guided by the
interspersed semantic constraints.</p>
<h4 id="reference-implementation-fountain">Reference Implementation: fountain</h4>
<ul>
<li>license: Unknown license</li>
<li>host-language: <a href="../article/Project%20Dependencies.md#haskell">Haskell</a></li>
<li>implementation-type: parser, generator</li>
</ul>
<hr />
<h2 id="about-these-languages">About these Languages</h2>
<p>Most of these languages are programming languages, or at least "computer languages" of
some kind, although some of them have not been implemented on a computer (or may even
be unimplementable on a computer), and at least one of them is a conlang.  Many of
them are <a href="../article/General%20Information.md#esolang">esolangs</a>.</p>
<p>If it was implemented by Cat's Eye Technologies, but was designed by someone else, it won't
be on this list, it'll be here instead: <a href="Language%20Implementations.md">Language Implementations</a>.</p>
<p>If it was implemented by Chris Pressey, but not under the auspices of Cat's Eye Technologies,
it won't be on this list.</p>
<p><strong>Some of these languages have interpreters that can run online, in your web browser.</strong>
(Look for the <strong>Try it Online</strong> button).
By selecting sample programs and watching them run, you can gain an appreciation of how the
language works; by composing your own programs, you can gain an even better appreciation.</p>
<p>You may also be interested in reading about
<a href="https://catseye.tc/view/The-Dossier/article/Retrospective%20on%20Language%20Design.md">what it was like to design these</a>
or <a href="List%20of%20Unfinished%20Interesting%20Esolangs.md">the ones that got away</a>.</p>
<hr />
    
  </article>

    
      <footer>
        <p>
          <small>Copyright ©2023, Chris Pressey, Cat's Eye Technologies.</small>
        </p>
      </footer>
    
  </div>
  
    <script src="/scripts/chrysoberyl2.js"></script>
  
</body>
