object Options: TOptions
  Left = 424
  Top = 335
  Width = 362
  Height = 182
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'Options'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Fixedsys'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 15
  object radOrgasm: TRadioGroup
    Left = 8
    Top = 8
    Width = 169
    Height = 105
    Caption = 'Update Output'
    TabOrder = 0
  end
  object radDot: TRadioButton
    Left = 24
    Top = 32
    Width = 137
    Height = 17
    Caption = 'After Every Dot'
    TabOrder = 1
  end
  object radEOL: TRadioButton
    Left = 24
    Top = 56
    Width = 145
    Height = 17
    Caption = 'On EOL'
    TabOrder = 2
  end
  object RadioButton3: TRadioButton
    Left = 24
    Top = 80
    Width = 137
    Height = 17
    Caption = 'At Interval'
    Checked = True
    TabOrder = 3
    TabStop = True
  end
  object butCloseOptions: TButton
    Left = 80
    Top = 120
    Width = 185
    Height = 25
    Caption = 'Okelidokeli'
    TabOrder = 4
    OnClick = butCloseOptionsClick
  end
  object groupCellSize: TGroupBox
    Left = 184
    Top = 8
    Width = 161
    Height = 105
    Caption = 'Cell Size'
    TabOrder = 5
    object radCellSizeByte: TRadioButton
      Left = 16
      Top = 24
      Width = 113
      Height = 17
      Caption = 'Byte'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object radCEllSizeWord: TRadioButton
      Left = 16
      Top = 48
      Width = 113
      Height = 17
      Caption = 'Word'
      TabOrder = 1
    end
    object radCellSizeDWord: TRadioButton
      Left = 16
      Top = 72
      Width = 113
      Height = 17
      Caption = 'DWord'
      TabOrder = 2
    end
  end
end
