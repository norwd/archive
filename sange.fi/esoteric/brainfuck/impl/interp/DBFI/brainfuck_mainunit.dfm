object MainForm: TMainForm
  Left = 234
  Top = 131
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Delphi Brainfuck Interpreter v1.00, brainfucker@binxoft.com'
  ClientHeight = 509
  ClientWidth = 603
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Fixedsys'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  DesignSize = (
    603
    509)
  PixelsPerInch = 96
  TextHeight = 15
  object butOpenBFScript: TSpeedButton
    Left = 480
    Top = 192
    Width = 33
    Height = 25
    Glyph.Data = {
      B6040000424DB604000000000000360000002800000015000000120000000100
      18000000000080040000130B0000130B00000000000000000000CED3D6CED3D6
      CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
      D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
      CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
      D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
      CED3D60000000000000000000000000000000000000000000000000000000000
      00000000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
      CED3D60000000000000086840086840086840086840086840086840086840086
      84008684000000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
      CED3D600000000FFFF0000000086840086840086840086840086840086840086
      84008684008684000000CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
      CED3D6000000FFFFFF00FFFF0000000086840086840086840086840086840086
      84008684008684008684000000CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
      CED3D600000000FFFFFFFFFF00FFFF0000000086840086840086840086840086
      84008684008684008684008684000000CED3D6CED3D6CED3D600CED3D6CED3D6
      CED3D6000000FFFFFF00FFFFFFFFFF00FFFF0000000000000000000000000000
      00000000000000000000000000000000000000CED3D6CED3D600CED3D6CED3D6
      CED3D600000000FFFFFFFFFF00FFFFFFFFFF00FFFFFFFFFF00FFFFFFFFFF00FF
      FF000000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
      CED3D6000000FFFFFF00FFFFFFFFFF00FFFFFFFFFF00FFFFFFFFFF00FFFFFFFF
      FF000000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
      CED3D600000000FFFFFFFFFF00FFFF0000000000000000000000000000000000
      00000000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
      CED3D6CED3D6000000000000000000CED3D6CED3D6CED3D6CED3D6CED3D6CED3
      D6CED3D6CED3D6000000000000000000CED3D6CED3D6CED3D600CED3D6CED3D6
      CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
      D6CED3D6CED3D6CED3D6000000000000CED3D6CED3D6CED3D600CED3D6CED3D6
      CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6000000CED3
      D6CED3D6CED3D6000000CED3D6000000CED3D6CED3D6CED3D600CED3D6CED3D6
      CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D60000
      00000000000000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
      CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
      D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
      CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
      D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600CED3D6CED3D6
      CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
      D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600}
    PopupMenu = BFScripts
    OnClick = butOpenBFScriptClick
  end
  object Label1: TLabel
    Left = 8
    Top = 195
    Width = 96
    Height = 15
    Caption = 'Input String'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Fixedsys'
    Font.Style = []
    ParentFont = False
  end
  object Code: TMemo
    Left = 0
    Top = 0
    Width = 601
    Height = 185
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Fixedsys'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object butDebug: TButton
    Left = 8
    Top = 224
    Width = 121
    Height = 25
    Caption = 'Debug'
    TabOrder = 1
    OnClick = butDebugClick
  end
  object RunCode: TButton
    Left = 136
    Top = 224
    Width = 329
    Height = 25
    Caption = 'Run, Brainfucker, Run'
    TabOrder = 2
    OnClick = RunCodeClick
  end
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 280
    Width = 601
    Height = 227
    Anchors = [akLeft, akTop, akRight, akBottom]
    Color = clBackground
    ParentColor = False
    TabOrder = 3
    object Output: TLabel
      Left = 0
      Top = 0
      Width = 8
      Height = 12
      Color = clBackground
      Font.Charset = OEM_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = 'Terminal'
      Font.Style = []
      ParentColor = False
      ParentFont = False
    end
  end
  object butOptions: TButton
    Left = 520
    Top = 192
    Width = 81
    Height = 25
    Caption = 'Options'
    TabOrder = 4
    OnClick = butOptionsClick
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 256
    Width = 601
    Height = 19
    Align = alNone
    Panels = <>
    SimplePanel = True
  end
  object edInput: TEdit
    Left = 112
    Top = 192
    Width = 225
    Height = 23
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Fixedsys'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
    OnKeyPress = edInputKeyPress
  end
  object Button1: TButton
    Left = 344
    Top = 192
    Width = 129
    Height = 25
    Caption = '<- Insert Byte'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Fixedsys'
    Font.Style = []
    ParentFont = False
    TabOrder = 7
    OnClick = Button1Click
  end
  object butHaltExec: TButton
    Left = 472
    Top = 224
    Width = 129
    Height = 25
    Caption = 'Halt Execution'
    TabOrder = 8
    OnClick = butHaltExecClick
  end
  object BFScripts: TPopupMenu
    AutoHotkeys = maManual
    MenuAnimation = [maTopToBottom]
    OwnerDraw = True
    Left = 8
    Top = 8
    object SelectBFScript1: TMenuItem
      Caption = 'Select BF Script'
    end
    object N1: TMenuItem
      Caption = '-'
    end
  end
end
