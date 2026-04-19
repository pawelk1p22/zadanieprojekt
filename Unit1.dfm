object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Edytor Wyrazen'
  ClientHeight = 561
  ClientWidth = 884
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Label1: TLabel
    Left = 20
    Top = 10
    Width = 90
    Height = 15
    Caption = 'Wybierz operator'
  end
  object Label2: TLabel
    Left = 20
    Top = 90
    Width = 64
    Height = 15
    Caption = 'Dodaj liczbe'
  end
  object LabelResult: TLabel
    Left = 120
    Top = 505
    Width = 3
    Height = 15
  end
  object BtnAdd: TButton
    Left = 20
    Top = 40
    Width = 75
    Height = 25
    Caption = '+'
    TabOrder = 0
    OnClick = BtnOperatorClick
  end
  object BtnSub: TButton
    Left = 101
    Top = 40
    Width = 75
    Height = 25
    Caption = '-'
    TabOrder = 1
    OnClick = BtnOperatorClick
  end
  object BtnMul: TButton
    Left = 182
    Top = 40
    Width = 75
    Height = 25
    Caption = '*'
    TabOrder = 2
    OnClick = BtnOperatorClick
  end
  object BtnDiv: TButton
    Left = 263
    Top = 40
    Width = 75
    Height = 25
    Caption = '/'
    TabOrder = 3
    OnClick = BtnOperatorClick
  end
  object EditNumber: TEdit
    Left = 20
    Top = 110
    Width = 100
    Height = 23
    TabOrder = 4
  end
  object BtnAddNumber: TButton
    Left = 130
    Top = 110
    Width = 75
    Height = 25
    Caption = 'Dodaj'
    TabOrder = 5
    OnClick = BtnAddNumberClick
  end
  object PanelOperators: TPanel
    Left = 20
    Top = 150
    Width = 250
    Height = 150
    Caption = 'Operatory'
    TabOrder = 6
    OnDragDrop = PanelBackDrop
    OnDragOver = PanelDragOver
  end
  object PanelNumbers: TPanel
    Left = 300
    Top = 150
    Width = 250
    Height = 150
    Caption = 'Liczby'
    TabOrder = 7
    OnDragDrop = PanelBackDrop
    OnDragOver = PanelDragOver
  end
  object PanelExpression: TPanel
    Left = 20
    Top = 320
    Width = 530
    Height = 150
    Caption = 'Wyrazenie'
    TabOrder = 8
    OnDragDrop = PanelExpressionDragDrop
    OnDragOver = PanelDragOver
  end
  object PanelTrash: TPanel
    Left = 600
    Top = 320
    Width = 150
    Height = 150
    Caption = 'Kosz'
    TabOrder = 9
    OnDragDrop = PanelTrashDrop
    OnDragOver = PanelDragOver
  end
  object BtnEvaluate: TButton
    Left = 20
    Top = 500
    Width = 75
    Height = 25
    Caption = 'Oblicz'
    TabOrder = 10
    OnClick = BtnEvaluateClick
  end
end
