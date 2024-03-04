
    Twelf code for Proposal        -      Tom Murphy  31 Jan 2006

These comprise the sources for the formalization of the content of my
proposal.

 el.elf - The external language 
 il.elf - Internal language with dynamic semantics
 elab.elf - Translation from external language to internal
 cps.elf - CPS language and dynamic semantics

Not yet complete:
 - type polymorphism
 - sums
 - recursive types
 - CPS conversion
  (coming soon; I have done this for a related 
   modal language without the circle type)

Won't do:
 - closure conversion
  (must resort to first-order encoding, which
   is too painful)


(Note: as of  1 Feb 2007, I've done most of the
 stuff above, including closure conversion, since
 Karl figured out a nice technique for that.)