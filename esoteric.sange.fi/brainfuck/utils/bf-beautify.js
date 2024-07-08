/* Insert here the nuumber of columns/character that wiill 
 * be allowed per line in the output file
 */
var lineLength = 65;

/* This will be appended to the name of the output file
 * as a default termination. for example 'some.b' wiill
 * generate a file called 'some.b.out' with the beautified
 * code in it.
 */
var ending = ".";

/* General purpose function assigned to the String object
 * which returns true or false based on the existence of a 
 * character at the beginning of a string
 */
function startsWith(ch)
{
    return this.indexOf(ch) == 0;
}
String.prototype.startsWith = startsWith;

/* General purpose function assigned to the String object
 * which returns true or false based on the existence of a 
 * character at the ending of a string
 */
function endsWith(ch)
{
    return this.lastIndexOf(ch) == this.length - ch.length;
}
String.prototype.endsWith = endsWith;

/* General purpose function assigned to the String object
 * which trims a string from leading and trailing whitespace
 * NEEDS THE startsWith AND endsWith FUNCTIONS!!!
 */
function trim()
{
    if(this.length < 1)
        return "";
    
    var s = this;
   
    while(s.startsWith(' ')||s.startsWith('\t')||s.startsWith('\n')
        ||s.startsWith('\r'))
        s = s.substr(1);
        
    while(s.endsWith(' ')||s.endsWith('\t')||s.endsWith('\n')
        ||s.endsWith('\r'))
        s = s.substring(0, s.length - 1);
    
    return s;
}
String.prototype.trim = trim;

var fso = new ActiveXObject("Scripting.FileSystemObject");
var forReading = 1, forWriting = 2, forAppending = 8;

var s = "", s2 = "", s3 = "";

var file = fso.openTextFile(WScript.Arguments(0), forReading);
var filx = fso.openTextFile(WScript.Arguments(0) + (ending == "" 
                            || ending == "." ? ".b" : ending), 
                            forWriting, true);

while(!file.atEndOfStream){
    var line = file.readLine().trim();

    if(line.startsWith('{') 
    && line.endsWith('}')){
        filx.writeLine(s);
        filx.writeLine(line);
        line = s = "";
    }
    
    s += line;
    
    for(var i = 0; i < s.length; i++){
        s2 = (s.charAt(i) == '['
            || s.charAt(i) == ']'
            || s.charAt(i) == '-'
            || s.charAt(i) == '+'
            || s.charAt(i) == '<'
            || s.charAt(i) == '>'
            || s.charAt(i) == '.'
            || s.charAt(i) == ','
            ? s.charAt(i) : '');
        s3 += s2;
    }

    s = s3;
    s3 = "";

    while (s.length > lineLength){
        filx.writeLine(s.substring(0, lineLength));
        s = s.substr(lineLength);
    }
}

filx.writeLine(s);
file.close();
filx.close();
WScript.Echo('All done!\n' + WScript.Arguments(0) 
          + (ending == "" || ending == "." ? ".b" : ending));
