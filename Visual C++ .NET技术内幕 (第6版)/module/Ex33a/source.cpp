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

__gc class WinForm: public Form 
{
private:
    StatusBar   *statusBar;
    Button      *closeButton;
    MainMenu    *mainMenu;
    MenuItem    *fileMenu;
    Label       *todoLabel;

    String      *caption;   // Caption of the WinForm
    int         width;      // width of the WinForm
    int         height;     // height of the WinForm


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
        // Form is being destroyed.  Do any
        // necessary clean-up here.
        Form::Dispose(disposing);
    }

    void InitForm()
    {
        // Setup controls here

        // Basic WinForm Settings
        Text = caption;
        Size = Drawing::Size(width, height);

        // Setup Menu
        mainMenu = new MainMenu();
        fileMenu = new MenuItem("&File");
        mainMenu->MenuItems->Add(fileMenu);
        fileMenu->MenuItems->Add(new MenuItem("E&xit", new EventHandler(this, &WinForm::OnFileExit)));
        Menu = mainMenu;

        // Label
        todoLabel = new Label();
        todoLabel->Text = "TODO: Place your controls here.";
        todoLabel->Size = Drawing::Size(150, 100);
        todoLabel->Location = Point (50, 50);
        Controls->Add(todoLabel);

        // Set status bar
        statusBar = new StatusBar();
        statusBar->Text = "Status Bar is Here";
        Controls->Add(statusBar);

        // Setup Close Button
        closeButton = new Button();
        closeButton->Text = "&Close";
        closeButton->Size = Drawing::Size(75, 23);
        closeButton->TabIndex = 0;
        closeButton->Location = Drawing::Point(width/2 - (75/2), height - 23 - 75);
        closeButton->Click += (new EventHandler(this, &WinForm::OnCloseButtonClick));
        Controls->Add(closeButton);

        
    }


    void OnCloseButtonClick(Object *sender, EventArgs *e) 
    {
        Close();
    }

    void OnFileExit(Object *sender, EventArgs *e) 
    {
        Close();
    }

};

void main()
{
    // ds
    // This line creates an instance of WinForm, and 
    // uses it as the Main Window of the application. 
    Application::Run(new WinForm());
}

