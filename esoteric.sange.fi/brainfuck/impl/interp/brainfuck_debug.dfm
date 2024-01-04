object DebugForm: TDebugForm
  Left = 463
  Top = 337
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Debug information'
  ClientHeight = 153
  ClientWidth = 288
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Fixedsys'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 15
  object labCodePos: TLabel
    Left = 192
    Top = 16
    Width = 24
    Height = 15
    Caption = '---'
  end
  object Label1: TLabel
    Left = 8
    Top = 16
    Width = 104
    Height = 15
    Caption = 'Code Position'
  end
  object Label2: TLabel
    Left = 8
    Top = 40
    Width = 160
    Height = 15
    Caption = 'Memory Cell Position'
  end
  object labCellPos: TLabel
    Left = 192
    Top = 40
    Width = 24
    Height = 15
    Caption = '---'
  end
  object Label3: TLabel
    Left = 8
    Top = 88
    Width = 168
    Height = 15
    Caption = 'Instructions Executed'
  end
  object labInstructionCount: TLabel
    Left = 192
    Top = 88
    Width = 24
    Height = 15
    Caption = '---'
  end
  object labCellValue: TLabel
    Left = 192
    Top = 64
    Width = 24
    Height = 15
    Caption = '---'
  end
  object Label4: TLabel
    Left = 8
    Top = 64
    Width = 136
    Height = 15
    Caption = 'Memory Cell Value'
  end
  object DebugHalt: TButton
    Left = 8
    Top = 120
    Width = 89
    Height = 25
    Caption = 'Halt'
    TabOrder = 0
    OnClick = DebugHaltClick
  end
  object Button2: TButton
    Left = 104
    Top = 120
    Width = 89
    Height = 25
    Caption = 'Continue'
    TabOrder = 1
    OnClick = Button2Click
  end
  object butDebugStep: TButton
    Left = 200
    Top = 120
    Width = 83
    Height = 25
    Caption = 'Step'
    TabOrder = 2
    OnClick = butDebugStepClick
  end
end
