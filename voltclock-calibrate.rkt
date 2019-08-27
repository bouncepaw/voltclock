#lang racket
[define [->int i] [round [exact->inexact i]]]
[define [step lo hi] [/ [- hi lo] 10]]

[define [list-of-points lo hi]
  [map [λ [i] [+ lo [->int [* [step lo hi] i]]]]
       [range 10]]]

[define [->string lst]
  [string-replace
   [string-join [map [λ [i] [number->string i]]
                     lst]
                ", "]
   ".0"
   ""]]

[define args
  [map string->number
       [vector->list [current-command-line-arguments]]]]

[display [->string [apply list-of-points args]]]
[display ",\n"]
