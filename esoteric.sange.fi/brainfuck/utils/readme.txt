Gavin O.'s BF Interpreter

There are 12 command buttons on the main panel (lower left of window)

Clear, Load, Save Quit

The bottom row is your typical File menu of New, Open, Save, and Quit. I prefer this layout to pulldowns with so few commands, so it is this way. The Load and Save commands act on the file in the Filename box, but Clear does not. This means that if you accidentally hit Clear in a fit of rage, you simply have to press Load to get your file back.

Run, Stop

These commands will start the interpreter going on your program. You can hit Stop if the program crashes, or for any other reason requiring a Stop. Stop also works in alternate run modes (Optimized and Compressed) and in the Load command (As big files take forever to load). When you run a program, it does not have to be Loaded. This prevents a lengthy delay should you not need to edit the program.

Optimize, UnOptimize, Run Op

These buttons control the execution of Optimzed BF programs. This speeds up situations like this:

+++++>>>>>

Ordinarily, each increment is performed one at a time. Optimized mode does this:

+5>5

You will not see numbers, but the ASCII character with that value, as this is more compact. To Run Op, it is advisable that you Optimize first. Wierd things happen otherwise. The UnOptimize button does not resurrect spacing, line returns, or notation, so a clear backup is advisable.

Compress, Uncompress, Run Comp

These buttons will eventually control Compressed BF programs. These use the standard compression system, which I will not get into here. Needless to say, execuation time and file size are both improved. 

There are also buttons and checkboxes above the control panel (Middle left)

Use In Stream

This checkbox and corresponding textbox allow you to enter a series of ASCII characters to use as input, rather than typing numbers one at a time. This allows procedurally generaed input sets, as well as a `hands free' capability. Check the box to make the textbox work. If there is nothing in the box, it will wait until there is.

Watch

This slows the execution time to about 10 instructions per second, and highlights the position in the program. This mode is useful for debugging.

Step

This holds execution of each instruction until you press Step Ahead. This allows a controlled execution for debugging.

Above the checkbox controls are two lists. The left list is the output. The left column shows numberic value, the right shows ASCII characters. The right list is the stack. 

Above the lists is the Filename box and Browse button. The file in this box is the one upon which all operations will be performed. Before compressing and decompressing, and Optimzing and UnOptimizing, it is a good idea to change the file to a new one so that the clear commented one will not be overwritten.

If you have any comments, send them to gtolson@snet,net