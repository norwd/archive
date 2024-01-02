::: {style="max-width:64em;margin:1em;"}
[Download
yahtzee-1.6.tar.gz](http://www.muppetlabs.com/~breadbox/pub/software/yahtzee-1.6.tar.gz)\
[Sourcehut page](https://git.sr.ht/~breadbox/yahtzee)

A Simple Game with Multiple UIs
===============================

Yahtzee itself is a very simple dice game, and needs no introduction. I
wrote this program as a way to experiment with different ways to
implement multiple user interfaces on top of game logic.

This program comes with three separate interfaces:

-   The graphical user interface is implemented using
    [SDL](http://www.libsdl.org/) (plus
    [SDL\_ttf](http://www.libsdl.org/projects/SDL_ttf/)). It should be
    portable to just about any platform that SDL supports.
-   There is also a text-based user interface that is implemented using
    [ncurses](http://www.gnu.org/software/ncurses/). This interface
    should work on just about any modern Unix system that provides a
    curses library.
-   Finally, there is a pure text interface that just uses the standard
    input and output, and should work anywhere, on any kind of
    text-capable terminal.

Which interface to use is partly determined at runtime, depending on the
current environment. You can also choose to leave out the SDL interface
and/or the curses-based interface at compile-time. (The dumb text
interface is always included, since it is very small and incurs no
external dependencies.)

The three interfaces have different behaviors, and each one is suited to
the particulars of its capabilities. The graphical user interface, for
example, reacts appropriately to mouse-over events, as well as mouse
clicks and dragging. The curses interface is a little more
coarse-grained, in that every input event (i.e. keystroke) corresponds
to a user action. The plain-text interface is even more coarse-grained,
since a single input event can correspond to multiple user actions (from
the point of view of the game logic). Other issues such as displaying
help at run-time are also handled in a distinct way for each interface.

My other goal in writing this program was to experiment with creating
the elements of a comfortable graphical interface. SDL does not provide
its users with access to any of a given platform\'s native GUI elements
(such as menus or pushbuttons), and indeed using such things typically
requires that a program be designed to accommodate the platform\'s
specific event-driven model --- all of which interferes with the goal of
keeping the user interface in its own separate black box.

The game logic code is aware of the various interface elements, since
its whole purpose is to update the game state in reaction to the various
user actions. But the user interface code is free to provide other
\"actions\" that don\'t alter the game state but are needed to make a
good user experience --- such as rendering the pushbutton as depressed
when the mouse button is down and not yet released, or having the score
sheet elements display helpful information on mouse-over.

Some people may also find interesting the code that creates the images
of the die faces at runtime, using some basic floating-point math.

The code in this distribution is made available under the MIT license.
Share and Enjoy. Questions and comments should be directed to me at
<breadbox@muppetlabs.com>.

------------------------------------------------------------------------

[[Software](http://www.muppetlabs.com/~breadbox/software/)]{.small}\
[[Brian Raiter](http://www.muppetlabs.com/~breadbox/)]{.small}
:::
