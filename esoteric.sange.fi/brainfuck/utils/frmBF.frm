VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.1#0"; "RICHTX32.OCX"
Object = "{0D452EE1-E08F-101A-852E-02608C4D0BB4}#2.0#0"; "FM20.DLL"
Begin VB.Form frmBF 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "BrainF--- Interpreter by Gavin O. - Freeware 2002 - Comments to gtolson@snet.net"
   ClientHeight    =   7425
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   11145
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7425
   ScaleWidth      =   11145
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.CheckBox chkUseInStream 
      Caption         =   "Use In Stream"
      Height          =   375
      Left            =   120
      TabIndex        =   25
      Top             =   3720
      Width           =   975
   End
   Begin VB.TextBox txtInStream 
      Height          =   285
      Left            =   1200
      TabIndex        =   24
      Top             =   3720
      Width           =   3135
   End
   Begin VB.CommandButton cmdStep 
      Caption         =   "Step Ahead"
      Enabled         =   0   'False
      Height          =   375
      Left            =   2280
      TabIndex        =   22
      Top             =   4080
      Width           =   975
   End
   Begin VB.CheckBox chkStep 
      Caption         =   "Step"
      Height          =   375
      Left            =   1200
      TabIndex        =   21
      Top             =   4080
      Width           =   975
   End
   Begin VB.CheckBox chkWatch 
      Caption         =   "Watch"
      Height          =   375
      Left            =   120
      TabIndex        =   20
      Top             =   4080
      Width           =   975
   End
   Begin RichTextLib.RichTextBox txtLoad 
      Height          =   7215
      Left            =   4440
      TabIndex        =   19
      Top             =   120
      Width           =   6615
      _ExtentX        =   11668
      _ExtentY        =   12726
      _Version        =   327680
      Enabled         =   -1  'True
      ScrollBars      =   3
      TextRTF         =   $"frmBF.frx":0000
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Terminal"
         Size            =   9
         Charset         =   255
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin ComctlLib.ProgressBar prgProgress 
      Height          =   255
      Left            =   120
      TabIndex        =   18
      Top             =   3360
      Width           =   4215
      _ExtentX        =   7435
      _ExtentY        =   450
      _Version        =   327682
      Appearance      =   1
   End
   Begin MSComDlg.CommonDialog Dialog 
      Left            =   3000
      Top             =   1440
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DialogTitle     =   "Find BrainF--- Files"
      Filter          =   "BF Files (*.bf;*.b)|*.bf;*.b|Optimized BF Files (*.bfo;*.obf)|*.bfo;*.obf|Compressed BF Files (*.bfc;*.cbf)|*.bfc;*.cbf"
   End
   Begin VB.ListBox lstStack 
      BeginProperty Font 
         Name            =   "Terminal"
         Size            =   9
         Charset         =   255
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2760
      Left            =   2280
      TabIndex        =   4
      Top             =   480
      Width           =   2055
   End
   Begin VB.ListBox lstOut 
      BeginProperty Font 
         Name            =   "Terminal"
         Size            =   9
         Charset         =   255
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2760
      Left            =   120
      TabIndex        =   3
      Top             =   480
      Width           =   2055
   End
   Begin VB.CommandButton cmdBrowse 
      Caption         =   "..."
      Height          =   255
      Left            =   4080
      TabIndex        =   2
      Top             =   120
      Width           =   255
   End
   Begin VB.TextBox txtFile 
      Height          =   285
      Left            =   480
      TabIndex        =   0
      Top             =   120
      Width           =   3495
   End
   Begin MSForms.ToggleButton cmdHelp 
      Height          =   375
      Left            =   3360
      TabIndex        =   23
      Top             =   4080
      Width           =   975
      BackColor       =   -2147483633
      ForeColor       =   -2147483630
      DisplayStyle    =   6
      Size            =   "1720;661"
      Value           =   "0"
      Caption         =   "Help"
      PicturePosition =   131072
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
      ParagraphAlign  =   3
   End
   Begin VB.Label lblHelp 
      Caption         =   "BrainF--- Commands:"
      Height          =   1815
      Left            =   1200
      TabIndex        =   11
      Top             =   4560
      Visible         =   0   'False
      Width           =   3135
   End
   Begin MSForms.CommandButton cmdUnCompress 
      Height          =   855
      Left            =   1200
      TabIndex        =   17
      Top             =   4560
      Width           =   975
      VariousPropertyBits=   25
      Caption         =   "UnCompress"
      Size            =   "1720;1508"
      Picture         =   "frmBF.frx":00F4
      FontEffects     =   1073750016
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
      ParagraphAlign  =   3
   End
   Begin MSForms.CommandButton cmdStop 
      Height          =   855
      Left            =   120
      TabIndex        =   16
      Top             =   5520
      Width           =   975
      PicturePosition =   262148
      Size            =   "1720;1508"
      Picture         =   "frmBF.frx":0546
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
      ParagraphAlign  =   3
   End
   Begin MSForms.CommandButton cmdRunComp 
      Height          =   855
      Left            =   3360
      TabIndex        =   15
      Top             =   4560
      Width           =   975
      VariousPropertyBits=   25
      Caption         =   "Run Comp"
      Size            =   "1720;1508"
      FontEffects     =   1073750016
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
      ParagraphAlign  =   3
   End
   Begin MSForms.CommandButton cmdCompress 
      Height          =   855
      Left            =   2280
      TabIndex        =   14
      Top             =   4560
      Width           =   975
      VariousPropertyBits=   25
      Caption         =   "Compress"
      Size            =   "1720;1508"
      Picture         =   "frmBF.frx":0998
      FontEffects     =   1073750016
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
      ParagraphAlign  =   3
   End
   Begin MSForms.CommandButton cmdUnOptimize 
      Height          =   855
      Left            =   2280
      TabIndex        =   13
      Top             =   5520
      Width           =   975
      Caption         =   "UnOptimize"
      Size            =   "1720;1508"
      Picture         =   "frmBF.frx":0DEA
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
      ParagraphAlign  =   3
   End
   Begin MSForms.CommandButton cmdRunOp 
      Height          =   855
      Left            =   3360
      TabIndex        =   12
      Top             =   5520
      Width           =   975
      Caption         =   "Run Op"
      Size            =   "1720;1508"
      Picture         =   "frmBF.frx":123C
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
      ParagraphAlign  =   3
   End
   Begin MSForms.CommandButton cmdClear 
      Height          =   855
      Left            =   120
      TabIndex        =   10
      Top             =   6480
      Width           =   975
      Caption         =   "Clear"
      Size            =   "1720;1508"
      Picture         =   "frmBF.frx":168E
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
      ParagraphAlign  =   3
   End
   Begin MSForms.CommandButton cmdOptimize 
      Height          =   855
      Left            =   1200
      TabIndex        =   9
      Top             =   5520
      Width           =   975
      Caption         =   "Optimize"
      Size            =   "1720;1508"
      Picture         =   "frmBF.frx":1AE0
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
      ParagraphAlign  =   3
   End
   Begin MSForms.CommandButton cmdQuit 
      Height          =   855
      Left            =   3360
      TabIndex        =   8
      Top             =   6480
      Width           =   975
      Caption         =   "Quit"
      Size            =   "1720;1508"
      Picture         =   "frmBF.frx":1F32
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
      ParagraphAlign  =   3
   End
   Begin MSForms.CommandButton cmdSave 
      Height          =   855
      Left            =   2280
      TabIndex        =   7
      Top             =   6480
      Width           =   975
      Caption         =   "Save"
      Size            =   "1720;1508"
      Picture         =   "frmBF.frx":2384
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
      ParagraphAlign  =   3
   End
   Begin MSForms.CommandButton cmdLoad 
      Height          =   855
      Left            =   1200
      TabIndex        =   6
      Top             =   6480
      Width           =   975
      Caption         =   "Load"
      Size            =   "1720;1508"
      Picture         =   "frmBF.frx":27D6
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
      ParagraphAlign  =   3
   End
   Begin MSForms.CommandButton cmdRun 
      Height          =   855
      Left            =   120
      TabIndex        =   5
      Top             =   4560
      Width           =   975
      Caption         =   "Run"
      Size            =   "1720;1508"
      Picture         =   "frmBF.frx":2C28
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
      ParagraphAlign  =   3
   End
   Begin VB.Label lblFile 
      Caption         =   "File:"
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   375
   End
End
Attribute VB_Name = "frmBF"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Quit As Boolean
Dim Step As Byte

Private Sub chkStep_Click()
    cmdStep.Enabled = chkStep.Value
End Sub

Private Sub cmdBrowse_Click()
    Dialog.ShowOpen
    If Dialog.filename <> "" Then txtFile.Text = Dialog.filename
End Sub

Private Sub cmdClear_Click()
    If MsgBox("Really clear?", vbYesNo, "Really?") = vbYes Then txtLoad.Text = ""
End Sub

Private Sub cmdCompress_Click()
    Dim Ch(17) As String * 1
    Dim MyByte As Byte
    Open txtFile.Text & ".bfc" For Binary As #1
    For i = 1 To Len(txtLoad.Text)
        prgProgress.Value = i / Len(txtLoad.Text) * 100
        rpt = 0
        For j = 0 To 16
            Ch(j) = Mid$(txtLoad.Text, i + j, 1)
        Next j
        num = CompInst(Ch(0))
        If num < 4 Then
            For j = 0 To 16
                If Ch(j) = Ch(0) Then
                    rpt = rpt + 1
                Else
                    Exit For
                End If
            Next j
            If rpt > 3 Then
                code = 3 * 64 + rpt * 4 + num
                i = i + rpt + 1
            Else
                code = 2 * 63 + CompInst(Ch(0)) * 16 + CompInst(Ch(1)) * 4 + CompInst(Ch(2))
                i = i + 4
            End If
        Else
            For j = 0 To 8
                If Ch(j) = Ch(0) Then
                    rpt = rpt + 1
                Else
                    Exit For
                End If
            Next j
            If rpt > 1 Then
                code = 1 * 64 + rpt * 8 + num
                i = i + rpt + 1
            Else
                code = CompInst(Ch(0)) * 16 + CompInst(Ch(1))
                i = i + rpt + 3
            End If
        End If
        MyByte = Asc(code)
        Put 1, , MyByte
    Next i
    Close 1
    txtFile.Text = txtFile.Text & ".bfc"
    cmdLoad_Click
End Sub

Function CompInst(Inst As String)
        Select Case Inst
            Case "+"
                CompInst = 0
            Case "-"
                CompInst = 1
            Case ">"
                CompInst = 2
            Case "<"
                CompInst = 3
            Case "["
                CompInst = 4
            Case "]"
                CompInst = 5
            Case "."
                CompInst = 6
            Case ","
                CompInst = 7
        End Select
End Function

Function UnConvComp(Comp) As String
    Select Case Comp
        Case 0
            UnConvComp = "+"
        Case 1
            UnConvComp = "-"
        Case 2
            UnConvComp = ">"
        Case 3
            UnConvComp = "<"
        Case 4
            UnConvComp = "["
        Case 5
            UnConvComp = "]"
        Case 6
            UnConvComp = "."
        Case 7
            UnConvComp = ","
    End Select
End Function

Private Sub cmdHelp_Click()
    If cmdHelp.Value Then
        lblHelp.Visible = True
    Else
        lblHelp.Visible = False
    End If
End Sub

Private Sub cmdLoad_Click()
    'On Error GoTo LoadErrs
    Dim Ch As Byte
    txtLoad.Text = ""
    Open txtFile.Text For Binary As 1
    If LOF(1) = 0 Then Close 1: Exit Sub
    Do
        DoEvents
        prgProgress.Value = (Seek(1) - 1) / LOF(1) * 100
        Get 1, , Ch
        txtLoad.Text = txtLoad.Text & Chr$(Ch)
    Loop Until EOF(1) Or Quit
    Close #1
    Exit Sub
LoadErrs:
    Close #1
    MsgBox "Error!  " & Err.Description
End Sub

Private Sub cmdOptimize_Click()
    Open txtFile.Text For Binary As 1
    Open txtFile.Text & ".bfo" For Binary As 2
    If LOF(2) > 1 Then
        Close 2
        Kill txtFile.Text & ".bfo"
        Open txtFile.Text & ".bfo" For Binary As 2
    End If
    Dim MyByte As Byte
    Dim MyOtherByte As Byte
    Dim NumByte As Byte
    Do
        Get 1, , MyByte
        If MyByte = Asc("+") Or MyByte = Asc("-") Or MyByte = Asc(">") Or MyByte = Asc("<") Or MyByte = Asc("[") Or MyByte = Asc("]") Or MyByte = Asc(".") Or MyByte = Asc(",") Then
            NumByte = 1
            Do
                Get 1, , MyOtherByte
                If MyByte = MyOtherByte Then
                    NumByte = NumByte + 1
                Else
                    Seek 1, Seek(1) - 1
                    Exit Do
                End If
                If EOF(1) Then Exit Do
            Loop
            Put 2, , MyByte
            Put 2, , NumByte
        End If
        prgProgress.Value = (Seek(1) - 2) / LOF(1) * 100
    Loop Until EOF(1)
    Close 1
    Close 2
    txtFile.Text = txtFile.Text & ".bfo"
    cmdLoad_Click
End Sub

Private Sub cmdQuit_Click()
    If MsgBox("Really quit?", vbYesNo, "Quit?") = vbYes Then End
End Sub



Private Sub cmdRunOp_Click()
    On Error GoTo runoperrs
    lstStack.Clear
    For i = 1 To 1000
        lstStack.AddItem 0
    Next i
    lstOut.Clear
    Dim Ch As Byte
    Dim nCh As Byte
    Dim P As Integer
    Dim LoD As Integer
    Dim Lo(100) As Integer
ContRun:
    Open txtFile.Text For Binary As 1
    With lstStack
    Do
        DoEvents
        Get 1, , Ch
        Get 1, , nCh
        Select Case Chr$(Ch)
            Case "+"
                .List(P) = Val(.List(P)) + nCh
                If Val(.List(P)) > 255 Then .List(P) = 255
            Case "-"
                .List(P) = Val(.List(P)) - nCh
                If Val(.List(P)) < 0 Then .List(P) = 0
            Case ">"
                P = P + nCh
            Case "<"
                P = P - nCh
            Case "["
                For i = 1 To nCh
                    LoD = LoD + 1
                    Lo(LoD) = Seek(1)
                Next i
            Case "]"
                For i = 1 To nCh
                    If Val(.List(P)) Then
                        Seek 1, Lo(LoD)
                    Else
                        LoD = LoD - 1
                    End If
                Next i
            Case "."
                For i = 1 To nCh
                    If .List(P) > 0 And .List(P) < 256 Then
                        lstOut.AddItem .List(P) & " - " & Chr$(Val(.List(P)))
                    Else
                        lstOut.AddItem .List(P)
                    End If
                Next i
            Case ","
                For i = 1 To nCh
                    .List(P) = InputBox("Enter value >=0:<=255: ")
                    If Val(.List(P)) = vbCancel Then
                        Close 1
                        Exit Sub
                    End If
                Next i
        End Select
    Loop Until EOF(1) Or Quit
    Quit = False
    End With
    Close #1
    Exit Sub
runoperrs:
    Close #1
    MsgBox "Error!" & Err.Description
End Sub

Private Sub cmdSave_Click()
On Error GoTo saverrs
    If txtFile.Text = "" Then txtFile.Text = "temp.bff"
    Kill txtFile.Text
    Open txtFile.Text For Binary As #1
    For i = 1 To Len(txtLoad.Text)
        Put #1, , Mid$(txtLoad.Text, i, 1)
    Next i
    Close #1
    Exit Sub
saverrs:
    Close #1
    MsgBox "Error!" & Err.Description
End Sub

Private Sub cmdRun_Click()
    'On Error GoTo openerrs
    lstStack.Clear
    For i = 1 To 1000
        lstStack.AddItem 0
    Next i
    lstOut.Clear
    Dim Ch As Byte
    Dim P As Integer
    Dim LoD As Integer
    Dim Lo(1000) As Integer
ContRun:
    Open txtFile.Text For Binary As 1
    With lstStack
    Do
        DoEvents
        Get 1, , Ch
        If chkWatch.Value Then
            txtLoad.SelStart = Seek(1) - 2
            txtLoad.SelLength = 1
            txtLoad.SelColor = vbRed
            txtLoad.SelStart = 0
        End If
        Select Case Chr$(Ch)
            Case "+"
                .List(P) = Val(.List(P)) + 1
            Case "-"
                .List(P) = Val(.List(P)) - 1
            Case ">"
                P = P + 1
            Case "<"
                P = P - 1
            Case "["
                LoD = LoD + 1
                Lo(LoD) = Seek(1) - 1
            Case "]"
                If Val(.List(P)) Then
                    Seek 1, Lo(LoD)
                Else
                    LoD = LoD - 1
                End If
            Case "."
                If .List(P) > 0 And .List(P) < 256 Then
                    lstOut.AddItem .List(P) & " - " & Chr$(Val(.List(P)))
                Else
                    lstOut.AddItem .List(P)
                End If
            Case ","
                If chkUseInStream.Value Then
                    Do: Loop Until Len(txtInStream.Text) > 0
                    .List(P) = Left$(txtInStream.Text, 1)
                    txtInStream.Text = Right$(txtInStream.Text, Len(txtInStream.Text) - 1)
                Else
                    .List(P) = InputBox("Enter value >=0:<=255: ")
                End If
                If Val(.List(P)) = vbCancel Then
                    Close 1
                    Exit Sub
                End If
        End Select
        If chkWatch.Value Then
            Do: Loop Until Timer - lt > 0.01: lt = Timer
            txtLoad.SelStart = Seek(1) - 2
            txtLoad.SelLength = 1
            txtLoad.SelColor = vbBlack
            txtLoad.SelStart = 0
        End If
        If chkStep.Value Then
            Do: DoEvents: Loop While Step = 0
        End If
        Step = 0
    Loop Until EOF(1) Or Quit
    Quit = False
    End With
    Close #1
    Exit Sub
openerrs:
    Close #1
    MsgBox "Error!" & Err.Description
End Sub




Private Sub cmdStep_Click()
    Step = 1
End Sub

Private Sub cmdStop_Click()
    Quit = True
End Sub

Private Sub cmdUnCompress_Click()
    Dim MyByte As Byte
    Dim Cmd1 As Byte
    Dim Cmd2 As Byte
    Dim nCmd As Byte
    Dim Clipped As Byte
    Dim Process As Byte
    Open txtFile.Text For Binary As 1
    Open Left$(txtFile.Text, Len(txtFile.Text) - 4) For Binary As 2
    For i = 1 To LOF(1)
        Get 1, , MyByte
        Process = Int(MyByte / 64)
        Clipped = MyByte - Process * 64
        Select Case Process
            Case 0
                Cmd1 = Int(Clipped / 8)
                Cmd2 = Clipped - Cmd1
                Put 2, , UnConvComp(Cmd1)
                Put 2, , UnConvComp(Cmd2)
            Case 1
                Cmd1 = Int(Clippd / 8)
                Cmd2 = Clipped - Int(Clipped / 8)
                For j = 1 To Cmd1
                    Put 2, , UnConvComp(Cmd2)
                Next j
            Case 2
                Cmd1 = Int(Clipped / 16)
                Cmd2 = Int((Clipped - Cmd1) / 4)
                cmd3 = Clipped - Cmd1 - Cmd2
                Put 2, , UnConvComp(Cmd1)
                Put 2, , UnConvComp(Cmd2)
                Put 2, , UnConvComp(cmd3)
            Case 3
                Cmd1 = Int(Clipped / 4)
                Cmd2 = Clipped - Cmd1
                For j = 1 To Cmd1
                    Put 2, , UnConvComp(Cmd2)
                Next j
        End Select
    Next i
    Close 1
    Close 2
    txtFile.Text = Left$(txtFile.Text, Len(txtFile.Text) - 4)
    cmdLoad_Click
End Sub

Private Sub cmdUnOptimize_Click()
    Kill Left$(txtFile.Text, Len(txtFile.Text) - 4)
    Open txtFile.Text For Binary As 1
    Open Left$(txtFile.Text, Len(txtFile.Text) - 4) For Binary As 2
    
    Dim MyByte As Byte
    Dim MyOtherByte As Byte
    
    Do
        prgProgress.Value = (Seek(1) - 1) / LOF(1) * 100
        Get 1, , MyByte
        Get 1, , MyOtherByte
        For i = 1 To MyOtherByte
            Put 2, , MyByte
        Next i
    Loop Until EOF(1)
    
    Close 1
    Close 2
    
    txtFile.Text = Left$(txtFile.Text, Len(txtFile.Text) - 4)
    cmdLoad_Click
End Sub

Private Sub CommandButton1_Click()

End Sub

Private Sub Form_Load()
    lblHelp.Caption = "BrainF--- Commands:" & Chr$(13) & "+: Increment byte at pointer" & Chr$(13) & "-: Decrement byte at pointer" & Chr$(13) & ">: Increment Pointer" & Chr$(13) & "<: Decrement Pointer" & Chr$(13) & "[: Begin loop" & Chr$(13) & "]: End loop (Terminates on 0 at pointer)" & Chr$(13) & ".: Display byte at pointer" & Chr$(13) & ",: Input to byte at pointer"
    Dialog.InitDir = App.Path
End Sub

Private Sub Label4_Click()

End Sub

Private Sub txtLoad_Change()
    'Col = 8
    'For i = 1 To Len(txtLoad.Text)
    '    If Mid$(txtLoad.Text, i, 1) = "[" Then
    '        Col = Col + 1
    '        If Col > 15 Then Col = 8
    '    End If
    '    If Mid$(txtLoad.Text, i, 1) = "]" Then
    '        Col = Col - 1
    '        If Col < 8 Then Col = 15
    '    End If
    '    txtLoad.SelStart = i - 1
    '    txtLoad.SelLength = 1
    '    txtLoad.SelColor = QBColor(Col)
    '    txtLoad.SelLength = 0
    '    txtLoad.SelStart = i
    'Next i
End Sub
