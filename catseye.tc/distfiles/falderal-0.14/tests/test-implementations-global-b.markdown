Falderal Test 7b
----------------

This is a two-file test (the other file is 7a) which shows
that all implementations of a functionality apply to all
tests for that functionality, even when they're not in
the same file.

    -> Functionality "Cat" is implemented by
    -> shell command "python3 cat.py -f %(test-body-file)"

    -> Tests for functionality "Cat"

Cat totally, like, cats.

    | purr
    | prrr
    | prreow
    = purr
    = prrr
    = prreow
