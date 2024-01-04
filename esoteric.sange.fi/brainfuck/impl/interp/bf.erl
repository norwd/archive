-module(bf).
-vsn('2001.02.07'). % Chris Pressey
-copyright('Copyright (c)2001 Cat`s Eye Technologies. All rights reserved.').

% Redistribution and use in source and binary forms, with or without
% modification, are permitted provided that the following conditions
% are met:
%
%   Redistributions of source code must retain the above copyright
%   notice, this list of conditions and the following disclaimer.
%
%   Redistributions in binary form must reproduce the above copyright
%   notice, this list of conditions and the following disclaimer in
%   the documentation and/or other materials provided with the
%   distribution.
%
%   Neither the name of Cat's Eye Technologies nor the names of its
%   contributors may be used to endorse or promote products derived
%   from this software without specific prior written permission.
%
% THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
% CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
% INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
% MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
% DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE
% LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
% OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
% PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
% OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
% ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
% OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
% OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
% POSSIBILITY OF SUCH DAMAGE. 

-export([interpret/1, interpret/2, parse/1, parse/2, test/1]).

%%% BEGIN bf.erl %%%

% Cat's Eye Technologies' Erlang Brainf*ck Interpreter.
% An implementation of the world's most beautifulest langugage
% in the world's second most beautifulest language.

% Demonstrates:
%  - sequential programming in Erlang
%  - simulating imperative programming techniques

% Variable names:
%  I = Instruction pointer
%  B = Brainf*ck program
%  D = Data pointer (tape head position)
%  M = Memory (Brainf*ck tape)

%%% MAIN %%%

% The main user interface to the interpreter is interpret/1.
% The user generally passes a list, which is parsed into a tuple.
% Each Brainf*ck instruction is an atom, except for [ and ],
% which are represented by a nested tuple to make things simpler.
% The return value is a tuple containing the data pointer and
% another tuple representing the state of the Brainf*ck tape
% after all is said and done.

interpret(B, N) when tuple(B) -> interpret(1, B, 1, erlang:make_tuple(N, 0));
interpret(B, N) when list(B)  -> interpret(parse(B), N).

interpret(B) -> interpret(B, 512).  % default memsize, use interpret/2 to specify

% The internal driver is interpret/4.
% When the I pointer is at the end of the program, processing is finished.
% But more usually, I will be travelling forward through B.

interpret(I, B, D, M) when I > size(B) -> {D, M};
interpret(I, B, D, M) ->
  {D2, M2} = execute(element(I, B), D, M),
  interpret(I + 1, B, D2, M2).

% Effects of individual instructions.  Erlang doesn't have an updatable
% store like Brainf*ck, so instead we approach the problem by continually
% deriving new stores from old stores, and passing them back.

execute($>, D, M) -> {D + 1, M};
execute($<, D, M) -> {D - 1, M};
execute($+, D, M) -> {D, setelement(D, M, element(D, M) + 1)};
execute($-, D, M) -> {D, setelement(D, M, element(D, M) - 1)};

% I/O is fairly crude, and could stand to be improved.

execute($., D, M) -> io:put_chars([element(D, M)]), {D, M};
execute($,, D, M) -> {D, setelement(D, M, hd(io:get_chars('bf> ', 1)))};

% The 'while' loop.  A tuple represents a [...] structure; if
% the data pointer points to a non-zero, the nested Brainf*ck
% subprogram is executed, and the check is repeated.

execute(B,  D, M) when tuple(B), element(D, M) == 0 -> {D, M};
execute(B,  D, M) when tuple(B) ->
  {D2, M2} = interpret(1, B, D, M),
  execute(B, D2, M2);

% Finally, ignore comments and other line noise.

execute(_, D, M) -> {D, M}.

% Brainf*ck parser - takes a string (list of ASCII values) and butchers
% it into a nested tuple data structure.  Writing this function elegantly
% was much trickier than writing the imperative processing engine above.

parse(L) -> parse({}, L).  % default is to add to fresh tuple

parse(U, []) -> U;
parse(U, [$]|T]) -> {U, T};
parse(U, [$[|T]) ->
  {V, L} = parse({}, T),
  parse(erlang:append_element(U, V), L);
parse(U, [H |T]) ->
  parse(erlang:append_element(U, H), T).

% test function - original helloworld program from brainf*ck.

test(1) -> test(hello);
test(hello) -> interpret("
>+++++++++[<++++++++>-]<.>+++++++[<++++>-]<+.+++++++..+++.[-]>++++++++[<++++>-]
<.>+++++++++++[<+++++>-]<.>++++++++[<+++>-]<.+++.------.--------.[-]>++++++++[
<++++>-]<+.[-]++++++++++."
);

test(2) -> test(atoi);
test(atoi) -> interpret("
==== ==== ====
cont digi num
==== ==== ====

+
[
 -                         cont=0
 >,
 ======SUB10======
 ----------
 
 [                         not 10
  <+>                      cont=1
  =====SUB38======
  ----------
  ----------
  ----------
  --------

  >
  =====MUL10=======
  [>+>+<<-]>>[<<+>>-]<     dup

  >>>+++++++++
  [
   <<<
   [>+>+<<-]>>[<<+>>-]<    dup
   [<<+>>-]
   >>-
  ]
  <<<[-]<
  ======RMOVE1======
  <
  [>+<-]
 ]
 <
]
>>[<<+>>-]<<
#"
).

%%% END of bf.erl %%%
