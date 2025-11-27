//luke fadel
// nov 24, 2025
//physics simulation 

//header files for libraries

//for timer stuff

#include <wx/wxprec.h>

#define GLM_ENABLE_EXPERIMENTAL

//defining macro and importing more libs 
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "include/MyApp.h"
#include "include/MyFrame.h"


//stupid macro
wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit(){
    //making a new frame
    MyFrame * frame = new MyFrame();
    frame->Show(true);
    return true;
};
