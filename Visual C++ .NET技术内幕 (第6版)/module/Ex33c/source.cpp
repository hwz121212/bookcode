#include "stdafx.h"
#include "math.h"

#using <mscorlib.dll>
using namespace System;

// required dlls for WinForms
#using "System.dll"
#using "System.Windows.Forms.dll"
#using "System.Drawing.dll"

// required namespaces for WinForms
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;

using namespace System::Diagnostics;

__value enum DrawingTypes 
{
    None, Line, Circle, Rect
};

__gc class Shape 
{
public:
    Point m_topLeft;
    Point m_bottomRight;

    Color m_PenColor;

    Shape() 
    {
        m_topLeft.X = 0;
        m_topLeft.Y = 0;
        m_bottomRight.X = 0;
        m_bottomRight.Y = 0;

        m_PenColor = Color::Black;
    }
    Shape(Point topLeft, Point bottomRight) 
    {
        m_topLeft = topLeft;
        m_bottomRight = bottomRight;
        m_PenColor = Color::Black;
    }
    virtual void Draw(System::Drawing::Graphics* g)
    {
    }
    virtual void Erase(System::Drawing::Graphics* g) 
    {
    }

    int SetROP(HDC hdc) 
    {
        int nOldRop = ::SetROP2(hdc, R2_NOTXORPEN); 
        return nOldRop;
    }

    void ResetROP(HDC hdc, int nOldRop)
    {
        ::SetROP2(hdc, nOldRop);
    }
};

__gc class Line : public Shape 
{
public:
    Line(Point topLeft, Point bottomRight) :
        Shape(topLeft, bottomRight)
    {
    }
    Line():
        Shape()
    {
    }
    void Draw(System::Drawing::Graphics* g)
    {
        System:IntPtr hdc;
        hdc = g->GetHdc();

        ::MoveToEx((HDC)hdc.ToInt32(), m_topLeft.X,
            m_topLeft.Y, NULL);
        LineTo((HDC)hdc.ToInt32(), m_bottomRight.X,
            m_bottomRight.Y);
        g->ReleaseHdc(hdc);
    }

    void Erase(System::Drawing::Graphics* g) 
    {
        System:IntPtr hdc;
        hdc = g->GetHdc();

        int nOldROP = SetROP((HDC)hdc.ToInt32());
        ::MoveToEx((HDC)hdc.ToInt32(), m_topLeft.X,
            m_topLeft.Y, NULL);
        LineTo((HDC)hdc.ToInt32(), m_bottomRight.X,
            m_bottomRight.Y);
        ResetROP((HDC)hdc.ToInt32(), nOldROP);
        g->ReleaseHdc(hdc);
    }
};

__gc class Circle : public Shape 
{
public:
    Circle(Point topLeft, Point bottomRight) :
      Shape(topLeft, bottomRight)
    {

    }
    Circle():
        Shape()
    {
    }
    void Draw(System::Drawing::Graphics* g) 
    {
        // These are absolute coordiantes, so fixup

        System:IntPtr hdc;
        hdc = g->GetHdc();

        ::Ellipse((HDC)hdc.ToInt32(), 
            m_topLeft.X, 
            m_topLeft.Y, 
            m_bottomRight.X, 
            m_bottomRight.Y);
        g->ReleaseHdc(hdc);

    }
    void Erase(System::Drawing::Graphics* g) 
    {
        System:IntPtr hdc;
        hdc = g->GetHdc();

        int nOldROP = SetROP((HDC)hdc.ToInt32());
        ::Ellipse((HDC)hdc.ToInt32(), 
            m_topLeft.X, m_topLeft.Y, 
            m_bottomRight.X, 
            m_bottomRight.Y);
        ResetROP((HDC)hdc.ToInt32(), nOldROP);
        g->ReleaseHdc(hdc);
    }
};
__gc class Rect : public Shape 
{
public:
    Rect(Point topLeft, Point bottomRight) :
      Shape(topLeft, bottomRight)
    {

    }
    Rect():
        Shape()
    {
    }
    void Draw(System::Drawing::Graphics* g) 
    {
        System:IntPtr hdc;
        hdc = g->GetHdc();

        ::Rectangle((HDC)hdc.ToInt32(), m_topLeft.X,
            m_topLeft.Y, m_bottomRight.X, m_bottomRight.Y);
        g->ReleaseHdc(hdc);
    }
    void Erase(System::Drawing::Graphics* g) 
    {
        System:IntPtr hdc;
        hdc = g->GetHdc();

        int nOldROP = SetROP((HDC)hdc.ToInt32());
        ::Rectangle((HDC)hdc.ToInt32(), m_topLeft.X, m_topLeft.Y,
            m_bottomRight.X, m_bottomRight.Y);
        ResetROP((HDC)hdc.ToInt32(), nOldROP);
        g->ReleaseHdc(hdc);
    }
};

__gc class WinForm: public Form 
{
private:
    StatusBar  *statusBar;
    MainMenu  *mainMenu;
    MenuItem  *fileMenu;
    MenuItem  *drawingMenu;
    MenuItem  *circleMenu;
    MenuItem  *lineMenu;
    MenuItem  *rectMenu;
    MenuItem  *helpMenu;

    DrawingTypes drawingtype;

    ArrayList   *shapes;

    String      *caption;  // Caption of the WinForm
    int         width;     // width of the WinForm
    int         height;    // height of the WinForm

    Shape       *currentShape;

public:
    WinForm() 
    {
        // Set caption and size of the WinForm
        caption = "Default WinForm Example";
        width = 600;
        height = 500;

        InitForm();
    }

    void Dispose(bool disposing)
    {
        // Form is being destroyed.  Do any
        // necessary clean-up here.
        Form::Dispose(disposing);
    }

    void InitForm()
    {
        // Setup controls here

        // Basic WinForm Settings
        this->set_BackColor(Color::White);

        Text = caption;
        Size = Drawing::Size(width, height);

        drawingtype = DrawingTypes::Line;

        // Setup Menu
        mainMenu = new MainMenu();
        fileMenu = new MenuItem("&File");
        mainMenu->MenuItems->Add(fileMenu);
        fileMenu->MenuItems->Add(
         new MenuItem("E&xit",
             new EventHandler(this, &WinForm::OnFileExit)));
        Menu = mainMenu;

        drawingMenu = new MenuItem("&Drawing");
        circleMenu = 
            new MenuItem("&Circle",
                new EventHandler(this, OnDrawCircle));
        lineMenu = new MenuItem("&Line",
            new EventHandler(this, OnDrawLine));
        rectMenu = 
            new MenuItem("&Rectangle",
                new EventHandler(this, OnDrawRect));
        drawingMenu->MenuItems->Add(lineMenu);
        drawingMenu->MenuItems->Add(circleMenu);
        drawingMenu->MenuItems->Add(rectMenu);
        mainMenu->MenuItems->Add(drawingMenu);

        helpMenu = new MenuItem("&Help");
        mainMenu->MenuItems->Add(helpMenu);
        helpMenu->MenuItems->Add(
            new MenuItem("&About",
                new EventHandler(this, OnHelpAbout)));

        // Set status bar
        statusBar = new StatusBar();
        statusBar->Text = "Status Bar is Here";
        Controls->Add(statusBar);

        MouseDown += new MouseEventHandler(this,
            MouseDownHandler);  
        MouseMove += new MouseEventHandler(this,
            MouseMoveHandler);
        MouseUp += new MouseEventHandler(this,
            MouseUpHandler);

        Paint += new PaintEventHandler(this, OnPaint);

        shapes = new ArrayList();
        UIUpdate();
    }

    void UIUpdate() 
    {
        // uncheck all items
        lineMenu->Checked = false;
        rectMenu->Checked = false;
        circleMenu->Checked = false;

        switch(drawingtype) 
        {
        case DrawingTypes::Line:
            lineMenu->Checked = true;
            break;
        case DrawingTypes::Rect:
            rectMenu->Checked = true;
            break;
        case DrawingTypes::Circle:
            circleMenu->Checked = true;
            break;
        }
    }

    void OnDrawLine(Object* sender, EventArgs* e)
    {
        drawingtype = DrawingTypes::Line;
        UIUpdate();
    }

    void OnDrawCircle(Object* sender, EventArgs* e)
    {
        drawingtype = DrawingTypes::Circle;
        UIUpdate();
    }

    void OnDrawRect(Object* sender, EventArgs* e)
    {
        drawingtype = DrawingTypes::Rect;
        UIUpdate();
    }

    void OnFileExit(Object *sender, EventArgs *e) 
    {
        Close();
    }

    void OnHelpAbout(Object* sender, EventArgs* e)
    {
        ::MessageBox(NULL, 
           "WinForms Drawing Example", 
           "About WinForms Drawing Example", MB_OK);
    }

    void MouseDownHandler(Object* sender, MouseEventArgs* e)
    {
        if(!this->Capture)
            return;

        switch(drawingtype) 
        {
        case DrawingTypes::Line :
            currentShape = new Line();
            break;
        case DrawingTypes::Circle:
            currentShape = new Circle();
            break;
        case DrawingTypes::Rect:
            currentShape = new Rect();
            break;
        default:
            return;
        };

        try{
            currentShape->m_topLeft.X = e->X;
            currentShape->m_topLeft.Y = e->Y;
            currentShape->m_bottomRight.X = e->X;
            currentShape->m_bottomRight.Y = e->Y;

            this->Capture = true; // Capture the mouse
                                  //  until button up
        }
        catch(Exception* ex) {
            Debug::WriteLine(ex->ToString());
        }

    }


    void MouseMoveHandler(Object* sender, MouseEventArgs* e)
    {
        if(!this->Capture)
            return;

        try{
            Graphics* g = CreateGraphics();

            Pen *p = new Pen(this->BackColor);
            currentShape->Erase(g);

            currentShape->m_bottomRight.X = e->X;
            currentShape->m_bottomRight.Y = e->Y;

            currentShape->Draw(g);
        }
        catch (Exception* ex) { 
            Debug::WriteLine(ex->ToString());
        }
    }


    void MouseUpHandler(Object* sender, MouseEventArgs* e)
    {
        if(!currentShape)
                return;
        try{
            shapes->Add(currentShape);
            currentShape = 0;
            this->Invalidate();
            Capture = false;
            }
        catch (Exception* ex) { 
            Debug::WriteLine(ex->ToString());
        }

    }

    void DrawShapes(System::Drawing::Graphics* g) 
    {
        for(int i = 0; i < shapes->Count; i++) 
        {
            Shape* s = dynamic_cast<Shape*>(shapes->get_Item(i));
            s->Draw(g);
        }
    }

    void OnPaint(Object* sender, PaintEventArgs* e)
    {
        Graphics* g = e->Graphics;
        DrawShapes(g);
    }


};

void main()
{
    TextWriterTraceListener * myWriter = new
        TextWriterTraceListener(System::Console::Out);
    Debug::Listeners->Add(myWriter);

    // This line creates an instance of WinForm, and 
    // uses it as the main window of the application. 
    Application::Run(new WinForm());
}
