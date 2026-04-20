#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include <vector>
#include <algorithm>

#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    srand(time(NULL));
}

bool isOperator(String s)
{
    return s == "+" || s == "-" || s == "*" || s == "/";
}

void LayoutBlocks(TPanel* panel)
{
    const int margin = 10;
    const int spacing = 8;

    int x = margin;
    int y = margin;
    int rowHeight = 0;

    for(int i=0; i<panel->ControlCount; i++)
    {
        TLabel* lbl = dynamic_cast<TLabel*>(panel->Controls[i]);
        if(!lbl) continue;

        if(x + lbl->Width > panel->Width)
        {
            x = margin;
            y += rowHeight + spacing;
            rowHeight = 0;
        }

        lbl->Left = x;
        lbl->Top = y;

        x += lbl->Width + spacing;

        if(lbl->Height > rowHeight)
            rowHeight = lbl->Height;
    }
}

TLabel* CreateBlock(TComponent* owner, String text, TPanel* parent)
{
    TLabel* lbl = new TLabel(owner);
    lbl->Parent = parent;
    lbl->Caption = text;

    lbl->Width = 65;
    lbl->Height = 65;

    lbl->Alignment = taCenter;
    lbl->Layout = tlCenter;

    lbl->Color = clSkyBlue;
    lbl->Transparent = false;

    lbl->Font->Size = 18;
    lbl->Font->Style = TFontStyles() << fsBold;

    lbl->DragMode = dmAutomatic;

    lbl->Left = rand() % (parent->Width - lbl->Width);
    lbl->Top  = rand() % (parent->Height - lbl->Height);

    return lbl;
}

void __fastcall TForm1::BtnOperatorClick(TObject *Sender)
{
    TButton* btn = dynamic_cast<TButton*>(Sender);
    if(!btn) return;

    CreateBlock(this, btn->Caption, PanelOperators);
    LayoutBlocks(PanelOperators);
}

void __fastcall TForm1::BtnAddNumberClick(TObject *Sender)
{
    if(EditNumber->Text.IsEmpty()) return;

    CreateBlock(this, EditNumber->Text, PanelNumbers);
    LayoutBlocks(PanelNumbers);
}

void __fastcall TForm1::PanelDragOver(TObject *Sender, TObject *Source,
      int X, int Y, TDragState State, bool &Accept)
{
    TLabel* lbl = dynamic_cast<TLabel*>(Source);
    TPanel* targetPanel = dynamic_cast<TPanel*>(Sender);

    if (!lbl || !targetPanel) {
        Accept = false;
        return;
    }

    String content = lbl->Caption;

    if (targetPanel == PanelNumbers) {
        Accept = !isOperator(content);
    }
    else if (targetPanel == PanelOperators) {
        Accept = isOperator(content);
    }
    else if (targetPanel == PanelExpression || targetPanel == PanelTrash) {
        Accept = true;
    }
    else {
        Accept = false;
    }
}

bool IsOverlapping(TPanel* panel, TLabel* moving, int x, int y)
{
    for(int i=0; i<panel->ControlCount; i++)
    {
        TLabel* lbl = dynamic_cast<TLabel*>(panel->Controls[i]);
        if(!lbl || lbl == moving) continue;

        if(x < lbl->Left + lbl->Width &&
           x + moving->Width > lbl->Left &&
           y < lbl->Top + lbl->Height &&
           y + moving->Height > lbl->Top)
        {
            return true;
        }
    }
    return false;
}

void __fastcall TForm1::PanelExpressionDragDrop(TObject *Sender, TObject *Source,
      int X, int Y)
{
    TLabel* src = dynamic_cast<TLabel*>(Source);
    if(!src) return;

    int newX = X - src->Width / 2;
    int newY = Y - src->Height / 2;

    if(IsOverlapping(PanelExpression, src, newX, newY))
        return;

    src->Parent = PanelExpression;
    src->Left = newX;
    src->Top  = newY;
}

void __fastcall TForm1::PanelTrashDrop(TObject *Sender, TObject *Source,
      int X, int Y)
{
    TLabel* lbl = dynamic_cast<TLabel*>(Source);
    if(lbl) delete lbl;
}

bool IsInOneRow(TPanel* panel)
{
    std::vector<TLabel*> items;

    for(int i=0; i<panel->ControlCount; i++)
    {
        TLabel* lbl = dynamic_cast<TLabel*>(panel->Controls[i]);
        if(lbl) items.push_back(lbl);
    }

    if(items.size() <= 1) return true;

    double sum = 0;
    for(auto lbl : items)
        sum += lbl->Top;

    double avgY = sum / items.size();
    const int tolerance = 80;

    for(auto lbl : items)
    {
        if(abs(lbl->Top - avgY) > tolerance)
            return false;
    }

    return true;
}

void __fastcall TForm1::PanelBackDrop(TObject *Sender, TObject *Source, int X, int Y)
{
    TLabel* src = dynamic_cast<TLabel*>(Source);
    TPanel* targetPanel = dynamic_cast<TPanel*>(Sender);

    if (src && targetPanel)
    {
        bool isOp = isOperator(src->Caption);
        if ((targetPanel == PanelNumbers && isOp) || (targetPanel == PanelOperators && !isOp))
        {
            return;
        }

        src->Parent = targetPanel;
        src->Color = clSkyBlue;
        LayoutBlocks(targetPanel);
        targetPanel->Invalidate();
    }
}

bool HasInvalidXStructure(std::vector<TLabel*>& items)
{
    std::sort(items.begin(), items.end(),
        [](TLabel* a, TLabel* b)
        {
            return a->Left < b->Left;
        });

    for(size_t i=1; i<items.size(); i++)
    {
        TLabel* prev = items[i-1];
        TLabel* curr = items[i];

        if(curr->Left < prev->Left + prev->Width - 5)
            return true;
    }

    return false;
}

void __fastcall TForm1::BtnEvaluateClick(TObject *Sender)
{
    if(!IsInOneRow(PanelExpression))
    {
        LabelResult->Caption = "Blad: niepoprawny uklad poziomy";
        return;
    }

    std::vector<TLabel*> blocks;

    for(int i=0; i<PanelExpression->ControlCount; i++)
    {
        TLabel* lbl = dynamic_cast<TLabel*>(PanelExpression->Controls[i]);
        if(lbl) blocks.push_back(lbl);
    }

    if(blocks.empty())
    {
        LabelResult->Caption = "Brak danych";
        return;
    }

    std::sort(blocks.begin(), blocks.end(),
        [](TLabel* a, TLabel* b)
        {
            return a->Left < b->Left;
        });

    if(HasInvalidXStructure(blocks))
    {
        LabelResult->Caption = "Blad: nakladanie lub zla kolejnosc";
        return;
    }

    std::vector<String> tokens;
    for(auto b : blocks)
        tokens.push_back(b->Caption);

    for(size_t i=1; i<tokens.size(); i++)
    {
        if(isOperator(tokens[i]) && isOperator(tokens[i-1]))
        {
            LabelResult->Caption = "Blad wyrazenia";
            return;
        }
    }

  try
{
    std::vector<String> tokens;
    for(auto b : blocks)
        tokens.push_back(b->Caption);

    for(size_t i = 0; i < tokens.size(); )
    {
        if(tokens[i] == "*" || tokens[i] == "/")
        {
            double left = StrToFloat(tokens[i-1]);
            double right = StrToFloat(tokens[i+1]);
            double res;

            if(tokens[i] == "*") res = left * right;
            else
            {
                if(right == 0)
                {
                    LabelResult->Caption = "Dzielenie przez 0";
                    return;
                }
                res = left / right;
            }

            tokens[i-1] = FloatToStr(res);
            tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);
            i = 0;
        }
        else
        {
            i++;
        }
    }

    double result = StrToFloat(tokens[0]);

    for(size_t i = 1; i < tokens.size(); i += 2)
    {
        double val = StrToFloat(tokens[i+1]);

        if(tokens[i] == "+") result += val;
        else if(tokens[i] == "-") result -= val;
    }

    LabelResult->Caption = FloatToStr(result);
}
catch(...)
{
    LabelResult->Caption = "Blad wyrazenia";
}
}
