VERSION 5.00
Begin VB.Form BFForm 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "BrainF*** Interpreter"
   ClientHeight    =   5550
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   7815
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   5550
   ScaleWidth      =   7815
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox BFChar 
      Alignment       =   1  'Right Justify
      Height          =   285
      Left            =   4200
      MaxLength       =   3
      TabIndex        =   8
      ToolTipText     =   "ASCII Char"
      Top             =   5160
      Width           =   495
   End
   Begin VB.TextBox BFInput 
      Height          =   285
      Left            =   120
      TabIndex        =   4
      ToolTipText     =   "Keyboard Input "
      Top             =   5160
      Width           =   3975
   End
   Begin VB.CommandButton BFStop 
      Caption         =   "Stop Program"
      Enabled         =   0   'False
      Height          =   375
      Left            =   6360
      TabIndex        =   3
      Top             =   5040
      Width           =   1215
   End
   Begin VB.CommandButton BFRun 
      Caption         =   "Run Program"
      Height          =   375
      Left            =   4920
      TabIndex        =   2
      Top             =   5040
      Width           =   1215
   End
   Begin VB.TextBox BFOutput 
      BackColor       =   &H8000000F&
      BeginProperty Font 
         Name            =   "Terminal"
         Size            =   6
         Charset         =   255
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3135
      Left            =   120
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   1
      ToolTipText     =   "Output Screen"
      Top             =   1800
      Width           =   7575
   End
   Begin VB.TextBox BFProgram 
      BeginProperty Font 
         Name            =   "Terminal"
         Size            =   6
         Charset         =   255
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1335
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      ToolTipText     =   "Program Entry"
      Top             =   240
      Width           =   7575
   End
   Begin VB.Label Label4 
      Caption         =   "Char"
      Height          =   255
      Left            =   4200
      TabIndex        =   9
      Top             =   4920
      Width           =   495
   End
   Begin VB.Label Label3 
      Caption         =   "Program"
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   0
      Width           =   735
   End
   Begin VB.Label Label2 
      Caption         =   "Input"
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   4920
      Width           =   495
   End
   Begin VB.Label Label1 
      Caption         =   "Output"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   1560
      Width           =   615
   End
End
Attribute VB_Name = "BFForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'BF interpreter
'Programmed by Jeffry Johnston, 2001
Dim Quit As Boolean
Private Sub BFChar_LostFocus()
  BFInput.Text = BFInput.Text + Chr$(Val(BFChar.Text))
End Sub
Private Sub BFStop_Click()
  Quit = True: BFRun.Enabled = True: BFStop.Enabled = False
End Sub
Private Sub Form_Load()
  Quit = False
End Sub
Private Sub BFRun_Click()
  Quit = False: BFRun.Enabled = False: BFStop.Enabled = True
  'Variable list
  '-------------
  'BFProgram.Text BF Program
  'Memory         Memory
  'Stack          Square bracket stack
  'IP             Instruction Pointer
  'IPValue        Value at Instruction Pointer, [IP]
  'MP             Memory Pointer
  'MPValue        Value at Memory Pointer, [MP]
  'SP             Stack Pointer
  'Level          (Temp) Depth of square brackets
  'Quit           Exit flag
  Dim Memory%(1 To 30000), Stack%(1 To 100)
  Dim Key$
  Dim IP&, Temp&, IPValue%, MP%, MPValue%, SP%, Level%
  BFOutput.Text = ""
  BFProgram.Text = BFProgram.Text + Chr$(255)
  IP = 0: MP = 1: SP = 1
  Do
    DoEvents
    IP = IP + 1
    IPValue = Asc(Mid$(BFProgram.Text, IP, 1))
    MPValue = Memory(MP)
    Select Case IPValue
    Case 255 '@
      Quit = True
    Case 60 '<
      MP = MP - 1
    Case 62 '>
      MP = MP + 1
    Case 43 '+
      Memory(MP) = (MPValue + 1) Mod 256
    Case 45 '-
      Memory(MP) = (MPValue + 255) Mod 256
    Case 46 '.
      If MPValue = 0 Then MPValue = 255
      BFOutput.Text = BFOutput.Text + Chr$(MPValue)
    Case 44 ',
      Do While Len(BFInput.Text) = 0 And Quit = False
        DoEvents
      Loop
      Memory(MP) = Asc(BFInput.Text)
      BFInput.Text = Mid$(BFInput.Text, 2)
    Case 93 ']
      SP = SP - 1: IP = Stack(SP)
    Case 91 '[
      If MPValue = 0 Then
        Level = 1
        Do
          IP = IP + 1: IPValue = Asc(Mid$(BFProgram.Text, IP, 1))
          If IPValue = 91 Then Level = Level + 1
          If IPValue = 93 Then Level = Level - 1
        Loop Until Level <= 0
      Else
        Stack(SP) = IP - 1: SP = SP + 1
      End If
    End Select
  Loop Until Quit
  BFRun.Enabled = True: BFStop.Enabled = False
  Temp = InStr(BFProgram.Text, Chr$(255))
  If Temp > 0 Then BFProgram.Text = Mid$(BFProgram.Text, 1, Temp - 1)
End Sub
