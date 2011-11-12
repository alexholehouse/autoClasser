# autoClasser

Automatically create .h and .cpp files for C++ project, very basic, cli system. 

## Installation
Installation instructions to come

## Usage

    ./autoClasser className

Will create the following header file

    // --- Custom header for this file built by autoClasser --- //
    // File copywrite alex holehouse 2011
    // Part of the DEMO project
    // Contact me at alex.holehouse@gmail.com for more details


    #ifndef CLASSNAME_H
    #define CLASSNAME_H
    
    // include any relevant header files here...
    
    /*! \brief <One sentence class summary>
    
    <Longer class description>
    */ 
    
    //------------------------------------
    class className : public <PARENT CLASS> {
    
    public:
    // Public class methods go here      

    private:
    // Private class methods and class variables go here

    };

    #endif

And the following class file (className.cpp)

    // --- Custom header for this file built by autoClasser --- //
    // File copywrite alex holehouse 2011
    // Part of the DEMO project
    // Contact me at alex.holehouse@gmail.com for more details
    
    
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <cstdlib>
    
    
    
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // default constructor    
    className::className() {
    
    }



    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // another function would go here
    // <return_value> className::<Function Name>(<parameters>){
    
    }
    
    // END OF FILE    

This is an early release... 
