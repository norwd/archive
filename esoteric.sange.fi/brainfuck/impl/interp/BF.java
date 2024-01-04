import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
/**
 *  Interpreter for the BrainFuck programming language
 *
 *@author     david moss
 *@created    02 January 2002
 */

public class BF {

    private char[] code;
    private byte[] memory = new byte[30000];
    private int pointer = 0;
    private int[] ins, outs;


    /**
     *  Default constructor for the BF class. This constructor takes a string
     *  that represents the code and uses it to execute as a BrainFuck program
     *
     *@param  codex          a bf code string
     *@exception  Exception  Description of Exception
     */
    public BF(String codex) throws Exception {
        code = codex.toCharArray();
        cleanCode();

        if (test()) {
            execute();
        } else {
            throw new Exception("Unbalanced BF code.");
        }
    }


    /**
     *  Default constructor for the BF class. This constructor takes a file with
     *  the code and uses it to execute as a BrainFuck program.
     *
     *@param  codex          a bf code file
     *@exception  Exception  Description of Exception
     */
    public BF(File codex) throws Exception {
        new BF(open(codex));
    }


    /**
     *  Just for testing.
     *
     *@param  args  nothing
     */
    public static void main(String[] args) {
        if (args.length > 0) {
            try {
                new BF(new File(args[0]));
            } catch (Exception e) {
                e.printStackTrace();
                System.exit(1);
            }
        } else {
            System.out.println("You must enter a file name in the commandline to "
                     + "execute it.\nThe syntax is: runBF.bat <path to/>BFfile.b");
            System.exit(1);
        }
    }


    /**
     *  Gets the end of a loop according to the index of the code passed to the
     *  function
     *
     *@param  i  The index at which the loop starts
     *@return    The endLoop value or -1 if there iss an error
     */
    private int getEndLoop(int i) {
        for (int o = 0; o < ins.length; o++) {
            if (ins[o] == i) {
                return outs[o];
            }
        }

        return -1;
    }


    /**
     *  Gets the stert of a loop according to the index of the code passed to
     *  the function
     *
     *@param  i  The index at which the loop ends
     *@return    The endLoop value or -1 if there iss an error
     */
    private int getStartLoop(int i) {
        for (int o = 0; o < outs.length; o++) {
            if (outs[o] == i) {
                return ins[o];
            }
        }

        return -1;
    }


    /**
     *  openss the file. Includes are file names between '{' and '}' ands work
     *  in the same way as c++'s #include "some.h" preprocessor statements with
     *  the difference that the code is included in the place where the
     *  statement appears.
     *
     *@param  f  the file
     *@return    the contents off the file + includes
     */
    private String open(File f) {
        String s = "";

        try {
            String line = "";
            BufferedReader bin = new BufferedReader(new FileReader(f));

            while ((line = bin.readLine()) != null) {
                if (line.length() > 0) {
                    line = line.trim();
                }

                if (line.startsWith("{") && line.endsWith("}")) {
                    line = open(new File(line.substring(1, line.length() - 1)));
                }

                s += line;
            }

            bin.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return s;
    }


    /**
     *  Probably an unnecessary method that strips the code from non BrainFuck
     *  chars
     */
    private void cleanCode() {
        String newCode = "";

        for (int i = 0; i < code.length; i++) {
            if (code[i] == '.'
                     || code[i] == ','
                     || code[i] == '+'
                     || code[i] == '-'
                     || code[i] == '<'
                     || code[i] == '>'
                     || code[i] == ']'
                     || code[i] == '[') {
                newCode += code[i];
            }
        }

        code = newCode.toCharArray();
    }


    /**
     *  Function tat tests the code for balance and allocates the correct loop
     *  index to an array
     *
     *@return    true if the code is balanced
     */
    private boolean test() {
        int x = 0;
        int inb = 0;
        int outb = 0;

        for (int i = 0; i < code.length; i++) {
            switch (code[i]) {

                case '[':
                {
                    x++;
                    inb++;
                    break;
                }

                case ']':
                {
                    outb++;
                    break;
                }
            }

            if (outb > inb) {
                return false;
            }
        }

        if (inb != outb) {
            return false;
        }

        ins = new int[x];
        outs = new int[x];
        int inAt = 0;
        int outAt = 0;

        for (int i = 0; i < code.length; i++) {
            switch (code[i]) {

                case '[':
                {
                    ins[inAt++] = i;
                    outAt = inAt;
                    break;
                }

                case ']':
                {
                    for (int o = outAt; o >= 0; o--) {
                        if (outs[o - 1] == 0) {
                            outs[o - 1] = i;
                            break;
                        }
                    }

                    break;
                }
            }
        }

        return true;
    }


    /**
     *  Executes the code in a command prompt
     *
     *@exception  Exception  when shit happpens
     */
    private void execute() throws Exception {
        for (int i = 0; i < code.length; i++) {
            switch (code[i]) {

                case '+':
                {
                    memory[pointer]++;
                    break;
                }

                case '-':
                {
                    memory[pointer]--;
                    break;
                }

                case '>':
                {
                    pointer = pointer == 29999 ? 0 : pointer + 1;
                    break;
                }

                case '<':
                {
                    pointer = pointer == 0 ? 29999 : pointer - 1;
                    break;
                }

                case '[':
                {
                    if (memory[pointer] == 0) {
                        i = getEndLoop(i);

                        if (i == -1) {
                            throw new Exception("Unable to find the end for the current loop");
                        }
                    }

                    break;
                }

                case ']':
                {
                    i = getStartLoop(i) - 1;

                    if (i == -1) {
                        throw new Exception("Unable to find the beginning for the current loop");
                    }

                    break;
                }

                case '.':
                {
                    System.out.print((char) memory[pointer]);
                    break;
                }

                case ',':
                {
                    try {
                        memory[pointer] = (byte) System.in.read();

                        while (memory[pointer] == (byte) '\r'
                                 || memory[pointer] == (byte) '\n') {
                            memory[pointer] = (byte) System.in.read();
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    }

                    break;
                }
            }
        }
    }
}

