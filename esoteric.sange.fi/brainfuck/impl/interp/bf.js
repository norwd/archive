/* Created by David S. Moss
 * Version:  1.0
 * Revision: --
 * Date created:  10/01/02 10:08pm
 * Last modified: --
 */

//MAIN
/* Starts the application
 */
function main() {
    for(var i =0; i < 30000; i++) {
        memory[i] = 0;
    }
    
    var code = getCode(WScript.Arguments(0));

    if(test(code)) {
        execute(code);
    } else {
        d("Something went wrong with the test()");
    }
}

//OBJECTS

//FUNCTIONS
/* Generates debug info to a file
 */
function d(txt) {
    if(DEBUG) {
        if(create) {
            fout = fso.createTextFile(WScript.Arguments(0)+".out", true);
            create = false;
        }
        fout.write(txt);
    }
}

/* Gets the code from a file specified in the command line.
 * If mmore than one file was given as argument it will attempt
 * to open and execute them all one by one.
 */
function getCode(file) {
    var f = fso.openTextFile(file, forReading, false, tristateDefault);
    var s = "", c = '';
    
    while(!f.atEndOfStream) {
        c = f.read(1)
        switch(c) {
            case '+' : {
            }
            
            case '-' : {
            }
            
            case '>' : {
            }
            
            case '<' : {
            }
            
            case '[' : {
            }
            
            case ']' : {
            }
            
            case ',' : {
            }
            
            case '.' : {
                s += c;
                break;
            }
            
            default : {
                //Disscard character
            }
        }
    }
    
    return s;
}

/* Checks the code for correctness and validity
 */
function test(str) {
    var balance = 0;
    var x = 0;
    str = str + "";
    
    for(var i = 0; i < str.length; i++) {
        switch(str.charAt(i)) {
            case '[' : {
                x++;
            }
        }
    }
    
    for(var i = 0; i < x; i++) {
        ins[i] = 0;
        outs[i] = 0;
    }
    
    for (var i = 0; i < str.length; i++) {
        switch(str.charAt(i)) {
            case '[' : {
                balance++;
                d("inAt " + (inAt) + "::" + i + "\n");
                ins[inAt++] = i;
                outAt = inAt - 1;
                break;
            }
            
            case ']' : {
                balance--;
                
                for(var o = outAt; o >= 0; o--) {
                    if(outs[o] == 0) {
                        d("outAt " + o + "::" + i + "\n");
                        outs[o] = i;
                        break;
                    }
                }
                
                break;
            }
        }
        
        if(balance < 0) {
            return false;
        }
    }
    
    return true;
}

/* Executes the BF code in the cmd prompt
 */
function execute(str) {
    str = str + "";
    
    for(var i = 0; i < str.length; i++) {
        switch(str.charAt(i)) {
            case '+' : {
                d('+');
                memory[pointer] = memory[pointer] == 254 ? 0 : memory[pointer] + 1;
                d("mem@" + pointer + " = " + memory[pointer] + ";\n");
                break;
            }
            
            case '-' : {
                d('-');
                memory[pointer] = memory[pointer] == 0 ? 254 : memory[pointer] - 1;
                d("mem@" + pointer + " = " + memory[pointer] + ";\n");
                break;
            }
            
            case '>' : {
                d('>');
                pointer = pointer == 29999 ? 0 : pointer + 1;
                d("pointer = " + pointer + ";\n");
                break;
            }
            
            case '<' : {
                d('<');
                pointer = pointer == 0 ? 29999 : pointer - 1;
                d("pointer = " + pointer + ";\n");
                break;
            }
            
            case '[' : {
                d('[');
                d("i = " + i + "; ");
                
                if(memory[pointer] == 0) {
                    i = getEndLoop(i);
                }
                
                d("i = " + i + ";\n");
                break;
            }
            
            case ']' : {
                d(']');
                d("i = " + i + "; ");
                i = getStartLoop(i) - 1;
                d("i = " + i + ";\n");
                break;
            }
            
            case '.' : {
                d('.');
                d("write(" + memory[pointer] + ");\n");
                putChar(memory[pointer]);
                break;
            }
            
            case ',' : {
                d(',');
                memory[pointer] = getChar();
                d("read(" + memory[pointer] + ");\n");
                break;
            }
            
            default : {
                d('other char');
                //Do nothing
            }
        }
    }
}

/* Gets the end of a loop according to the index
 * of the code passed to the function
 */
function getEndLoop(starts) {
    for(var o = 0; o < ins.length; o++) {
        if(ins[o] == starts) {
            return outs[o];
        }
    }
}

/* Gets the stert of a loop according to the index
 * of the code passed to the function
 */
function getStartLoop(ends) {
    for(var o = 0; o < outs.length; o++) {
        if(outs[o] == ends) {
            return ins[o];
        }
    }
}

/* Gets the next character from the cmd line
 * ignoring return and newline characters
 */
function getChar() {
    var s = cin.read(1);

    while(s == '\r' || s == '\n') {
        s = cin.read(1);
    }

    return s.charCodeAt(0);
}

/* Writes a character to stdIo based on an ascii number
 */
function putChar(i) {
    cout.Write(String.fromCharCode(i));
}

//CONSTANTS
//DEBUG mode = true/false
var DEBUG = !true;

//STD IO control. easy to redirect to/from a file
var cin = WScript.StdIn, 
    cout = WScript.StdOut;

//File System Object
var fso = new ActiveXObject("Scripting.FileSystemObject");

//BF program
var memory = new Array(30000);
var pointer = 0;

//Loop control
var ins = new Array(), 
    outs = new Array();
//Loop indexing
var inAt = 0, 
    outAt = 0;

//DEBUG vars
var create = DEBUG, fout;

//File Open Constants
var forReading   = 1, //Open a file for reading only. You can't write to this file. 
    forWriting   = 2, //Open a file for writing. If a file with the same name exists, 
                      //its previous contents are overwritten. 
    forAppending = 8; //Open a file and write to the end of the file.
//File Mode Constants
var tristateDefault = -2, //Opens the file using the system default. 
    tristateTrue    = -1, //Opens the file as Unicode. 
    tristateFalse   = 0;  //Opens the file as ASCII. 


//GO!!!
main();
