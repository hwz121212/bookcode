#using <mscorlib.dll>
using namespace System;

// required dlls for WinForms
#using "System.dll"
#using "System.Windows.Forms.dll"
#using "System.Drawing.dll"

// required namespaces for WinForms
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Drawing;

__gc class Shape 
{
public:
    Rectangle m_rect;
    Color m_PenColor;

    Shape() 
    {
        m_rect.set_X(0);
        m_rect.set_Y(0);
        m_rect.set_Height(0);
        m_rect.set_Width(0);

        m_PenColor = Color::Black;
    }
    Shape(Rectangle r) 
    {
        m_rect=r;
        m_PenColor = Color::Black;
    }
    virtual void Draw(System::Drawing::Graphics* g)
    {
    }
};

__gc class Line : public Shape 
{
public:
    Line(Rectangle r) :
        Shape(r)
    {
        m_rect=r;
    }
    Line():
        Shape()
    {
    }
    void Draw(System::Drawing::Graphics* g) 
    {
        g->DrawLine(new Pen(m_PenColor), m_rect.Left, 
            m_rect.Top, m_rect.Right, m_rect.Bottom);
    }
};

__gc class Circle : public Shape 
{
public:
    Circle(Rectangle r) :
        Shape(r)
    {
        m_rect=r;
    }
    Circle():
        Shape()
    {
    }
    void Draw(System::Drawing::Graphics* g) 
    {
        g->DrawEllipse(new Pen(m_PenColor), m_rect.Left, 
            m_rect.Top, m_rect.Right, m_rect.Bottom);
    }
};

__gc class Rect : public Shape 
{
public:
    Rect(Rectangle r) :
        Shape(r)
    {
        m_rect=r;
    }
    Rect():
        Shape()
    {
    }
    void Draw(System::Drawing::Graphics* g) 
    {
        g->DrawRectangle(new Pen(m_PenColor), 
            m_rect.Left, m_rect.Top, 
            m_rect.Right, m_rect.Bottom);
    }
};

__gc class WinForm: public Form 
{
private:
    MainMenu  *mainMenu;
    MenuItem  *fileMenu;

    String    *caption;  // Caption of the WinForm
    int       width;     // width of the WinForm
    int       height;    // height of the WinForm

    Shape*     l; // line
    Shape*     c; // circle
    Shape*     r; // rectangle

    Shape*     l2; // line
    Shape*     c2; // circle
    Shape*     r2; // rectangle

public:
    WinForm() 
    {
        // Set caption and size of the WinForm
        caption = "Default WinForm Example";
        width = 400;
        height = 500;

        InitForm();
    }

    void Dispose(bool disposing)
    {
        // Form is being destroyed.  Do any necessary clean-up here.
        Form::Dispose(disposing);
    }

    void CreateShapes() 
    {
        int x = 10;
        int y = 30;

        l = new Line(Rectangle(x, y, 30, 60));
        x = x + 50; 

        c = new Circle(Rectangle(x, y, 30, 60));
        x = x + 170;

        r = new Rect(Rectangle(x, y, 60, 60));

        y = 160;
        x = 10;
        l2 = new Line(Rectangle(x, y, 30, 60));
        l2->m_PenColor = Color::Red;
        x = x + 50; 

        c2 = new Circle(Rectangle(x, y, 30, 60));
        c2->m_PenColor = Color::Blue;
        x = x + 170;

        r2 = new Rect(Rectangle(x, y, 60, 60));
        r2->m_PenColor = Color::Green;
    }

    void DrawShapes(System::Drawing::Graphics* g) 
    {
        l->Draw(g);
        c->Draw(g);
        r->Draw(g);

        l2->Draw(g);
        c2->Draw(g);
        r2->Draw(g);
    }

    void InitForm()
    {
        CreateShapes();

        // Setup controls here

        // Basic WinForm Settings
        Text = caption;
        Size = Drawing::Size(width, height);

        // Setup Menu
        mainMenu = new MainMenu();
        fileMenu = new MenuItem("&File");   
        mainMenu->MenuItems->Add(fileMenu);
        fileMenu->MenuItems->Add(new MenuItem("E&xit", 
            new EventHandler(this, &WinForm::OnFileExit)));
        Menu = mainMenu;

        //Paint Handler
        Paint += new PaintEventHandler(this, OnPaint);  
        
    }

    void OnPaint(Object* sender, PaintEventArgs* e)
    {
        SolidBrush* b;
        b = new SolidBrush(Color::Black);

        e->Graphics->DrawString("Hello World", 
            this->Font, b, System::Drawing::PointF(10, 10));
        DrawShapes(e->Graphics);
    }

    void OnFileExit(Object *sender, EventArgs *e) 
    {
        Close();
    }

};

void main()
{
    // This line creates an instance of WinForm, and 
    // uses it as the Main Window of the application. 
    Application::Run(new WinForm());
}
