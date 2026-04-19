#ifndef Unit1H
#define Unit1H

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

//-------------------------------------------------------------
class TForm1 : public TForm
{
__published:

    TLabel *Label1;
    TLabel *Label2;
    TLabel *LabelResult;

    TButton *BtnAdd;
    TButton *BtnSub;
    TButton *BtnMul;
    TButton *BtnDiv;
    TButton *BtnAddNumber;
    TButton *BtnEvaluate;

    TEdit *EditNumber;

    TPanel *PanelOperators;
    TPanel *PanelNumbers;
    TPanel *PanelExpression;
	TPanel *PanelTrash;

    void __fastcall PanelBackDrop(TObject *Sender, TObject *Source, int X, int Y);
    void __fastcall BtnOperatorClick(TObject *Sender);
    void __fastcall BtnAddNumberClick(TObject *Sender);
    void __fastcall PanelDragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
    void __fastcall PanelExpressionDragDrop(TObject *Sender, TObject *Source,
          int X, int Y);
    void __fastcall PanelTrashDrop(TObject *Sender, TObject *Source,
          int X, int Y);
    void __fastcall BtnEvaluateClick(TObject *Sender);

public:
    __fastcall TForm1(TComponent* Owner);
};

//-------------------------------------------------------------
extern PACKAGE TForm1 *Form1;

#endif
