Falderal Test: Bad indentation
------------------------------

Since these blocks are not indented correctly, `falderal` should not
load tests from them.  (Ideally it should produce warnings though.)

  -> Functionality "Cat" is implemented by
  -> shell command "python cat.py"

Cat cats.

| meow
= meow

        | purr
        | prrr
        | prreow
        = purr
        = prrr
        = prreow
