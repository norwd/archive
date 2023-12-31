    -> encoding: UTF-8

Falderal Test: UTF-8
--------------------

This is an example Falderal document which contains Unicode
characters, encoded in UTF-8 (this is the assumed encoding
of all Falderal documents which go beyond mere ASCII.)

    -> Functionality "Cat" is implemented by
    -> shell command "python3 cat.py"

    -> Tests for functionality "Cat"

Cat cats.

    | n ← ★
    = n ← ★

Cat dogs, too. (Intentional fail.)

    | n ← ★
    = m ← ★

    -> Functionality "Cat (file)" is implemented by
    -> shell command "python3 cat.py -f %(test-body-file) -o %(output-file)"

    -> Tests for functionality "Cat (file)"

Cat (file) cats.

    | n ← ★
    = n ← ★

Cat (file) dogs, too. (Intentional fail.)

    | n ← ★
    = m ← ★

    -> Functionality "Cat (input)" is implemented by
    -> shell command "python3 cat.py -f %(test-input-file) -o %(output-file)"

    -> Tests for functionality "Cat (input)"

Cat (input) cats with its input.

    | ignored ← ♡
    + n ← ♡
    = n ← ♡

Cat (input) dogs with its input, too. (Intentional fail.)

    | m ← ★
    + n ← ♡
    = m ← ★
