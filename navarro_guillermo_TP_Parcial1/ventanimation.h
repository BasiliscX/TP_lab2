#pragma once

/*
  File: ventanimation.h
  Author: Guillermo Navarro
  Date: 30/07/2023
  Description:

    This software provides a collection of console manipulation and animation functions in C++
    that allows users to perform various tasks, such as changing the cursor position, modifying the console size,
    displaying text with animation, drawing boxes with animation, and more.
    The functions facilitate interactive and visually appealing console-based applications.

    The software is distributed under the MIT Zero-Clause License,
    granting users the freedom to use, modify, and distribute the code freely.
*/

#include<iostream>
#include<ctime>
#include<windows.h>

/// Position (X - Y):
void PosXY(int,int); // Change the cursor's position.
int  PosX();         // Return position X.
int  PosY();         // Return position Y.
void Pos_X_Y_INFO(); // Prints the current X - Y position on the screen.
/// Console tools:
int  ConsoleColumns();            // Return the amount of columns.
int  ConsoleRows();               // Return the amount of rows.
void ConsoleSize(SHORT, SHORT);        // Change the console size.
void ConsoleTitle(const char*);   // Change the console title.
void ConsoleCursorSHOW_HIDE(bool);// Show/hide cursor.
void ConsoleClsX_Y(int,int,int);  // Clear console(specific row/position).
void ConsoleDLT();                // Clear all.
/// Animation functions:
void TextAnimation(const char*,int);   // Text with animation.
void BoxAnimation(int,int,int,int);    // Draw a box with animation.
void Pause(int);                       // Slow down the screen printing.
void BackgroundAndTextColor(const int);// Set another color to the text with an underline.

/**
 * Description:
 * Set a new cursor position based on the X-Y coordinates.
 * @param x = Receive the new column position.
 * @param y = Receive the new row position.
 */void PosXY(int x, int y){
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD newPosition;
    newPosition.X=x;
    newPosition.Y=y;
    SetConsoleCursorPosition(hConsole, newPosition);
}
/**
 * Description:
 * Return the current position X.
 */int PosX(){
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    if (GetConsoleScreenBufferInfo(hConsole, &consoleInfo)){
        int x=consoleInfo.dwCursorPosition.X;
        return x;
    }
    else return 0;
}
/**
 * Description:
 * Return the current position Y.
 */int PosY(){
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    if (GetConsoleScreenBufferInfo(hConsole, &consoleInfo)){
        int y=consoleInfo.dwCursorPosition.Y;
        return y;
    }
    else return 0;
}
/**
 * Description:
 * Prints the current X - Y position on the screen.
 */void Pos_X_Y_INFO(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

    COORD posicionCursor = consoleInfo.dwCursorPosition;
    std::cout << "X: " << posicionCursor.X << " - Y: " << posicionCursor.Y << std::endl;
}
/**
 * Description:
 * Return the amount of columns.
 */int ConsoleColumns(){
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    if(GetConsoleScreenBufferInfo(hConsole, &consoleInfo)){
        int columns=consoleInfo.srWindow.Right-consoleInfo.srWindow.Left+1;
        return columns;
        }
        else return 0;
}
/**
 * Description:
 * Return the amount of rows.
 */int ConsoleRows(){
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    if(GetConsoleScreenBufferInfo(hConsole, &consoleInfo)){
        int rows=consoleInfo.srWindow.Bottom-consoleInfo.srWindow.Top+1;
        return rows;
        }
        else return 0;
}
/**
 * Description:
 * Change the console size.
 * @param X = Receives the new number of columns.
 * @param Y = Receives the new number of rows.
 */void ConsoleSize(SHORT X,SHORT Y){
    HWND consoleWindow = GetConsoleWindow();
    DWORD style = GetWindowLong(consoleWindow, GWL_STYLE);
    style &= ~WS_THICKFRAME;
    SetWindowLong(consoleWindow, GWL_STYLE, style);

    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT window ={0,0,X,Y};
    SetConsoleWindowInfo(hConsole,TRUE,&window);
}
/**
 * Description:
 * Change the console title.
 * @param TITLE = Receives the new title ("New Title." by default).
 */void ConsoleTitle(const char*TITLE="New Title."){
    SetConsoleTitle(TEXT(TITLE));
}
/**
 * Description:
 * Show/hide cursor.
 * @param CURSOR = Receives 0/FALSE or 1/TRUE (TRUE by default).
 */void ConsoleCursorSHOW_HIDE(bool CURSOR=true){

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = CURSOR;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
/**
 * Description:
 * You can clear the console output by specifying from a single position (X/Y) to a whole line.
 * @param X = Receives the column position.
 * @param Y = Receives the row position.
 * @param amount = Receives the number of columns to delete from X, Y (The entire row by default).
 */void ConsoleClsX_Y(int X, int Y, int amount=ConsoleColumns()){
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord={static_cast<SHORT>(X),static_cast<SHORT>(Y)};
    DWORD cells=amount;
    DWORD CHARACTER_W;

    FillConsoleOutputCharacter(hConsole,TEXT(' '),cells,coord,&CHARACTER_W);
}
/**
* Delete all of the console.
*/void ConsoleDLT(){for(int i=0;i<ConsoleRows();i++)ConsoleClsX_Y(0,i);}

/**
 * Description:
 * You can create a typing animation by entering a text as the first parameter and the typing speed as the second parameter.
 * @param text = Receives the text ("Here is your text." by default).
 * @param velocity = Receives the typing speed (10 by default).
 */void TextAnimation(const char*text="Here is your text.", int velocity=10){
    int i=0;
    while(text[i]!='\0'){std::cout<<text[i++];Pause(velocity);}
}
/**
 * Description:
 * Allows creating a box animation (3 different types).
 * @param tipe = Receives the box type (1 by default).
 * @param width = Receives the width of the box (20 by default).
 * @param width = Receives the height of the box (10 by default).
 * @param velocity = Receives the print speed (10 by default).
 */void BoxAnimation(int tipe=1, int width=20, int height=10, int velocity=10){
    int i, x, y;
    x=PosX();
    y=PosY();

    switch(tipe){
    case 1:
        enum Line1{
                    topLeftCorner1   =218, topRightCorner1   =191,
                    horizontalLine1  =196, verticalLine1     =179,
                    bottomLeftCorner1=192, bottomRightCorner1=217,};

        std::cout<<(char)topLeftCorner1;
        for(i=1;i<width;i++){std::cout<<(char)horizontalLine1;Pause(velocity);}
        std::cout<<(char)topRightCorner1;

        for(i=0;i<height;i++){PosXY(x,++y);std::cout<<(char)verticalLine1;
        PosXY((width+x),y);std::cout<<(char)verticalLine1;Pause(velocity);}

        PosXY(x,y);
        std::cout<<(char)bottomLeftCorner1;
        for(i=1;i<width;i++){std::cout<<(char)horizontalLine1;Pause(velocity);}
        std::cout<<(char)bottomRightCorner1;
    break;
    case 2:
        enum Line2{
                    topLeftCorner2   =201, topRightCorner2   =187,
                    horizontalLine2  =205, verticalLine2     =186,
                    bottomLeftCorner2=200, bottomRightCorner2=188,};

        std::cout<<(char)topLeftCorner2;
        for(i=1;i<width;i++){std::cout<<(char)horizontalLine2;Pause(velocity);}
        std::cout<<(char)topRightCorner2;

        for(i=0;i<height;i++){PosXY(x,++y);std::cout<<(char)verticalLine2;
        PosXY((width+x),y);std::cout<<(char)verticalLine2;Pause(velocity);}

        PosXY(x,y);
        std::cout<<(char)bottomLeftCorner2;
        for(i=1;i<width;i++){std::cout<<(char)horizontalLine2;Pause(velocity);}
        std::cout<<(char)bottomRightCorner2;
    break;
    case 3:
        enum Line3{
                    topHorizontalLine3   =220,
                    bottomHorizontalLine3=223,
                    verticalLine3        =219,};

        for(i=0;i<=width;i++){std::cout<<(char)topHorizontalLine3;Pause(velocity);}

        for(i=0;i<height;i++){PosXY(x,++y);std::cout<<(char)verticalLine3;
        PosXY((width+x),y);std::cout<<(char)verticalLine3;Pause(velocity);}

        PosXY(x,y);
        for(i=0;i<=width;i++){std::cout<<(char)bottomHorizontalLine3;Pause(velocity);}
    break;
    }
}
/**
 * Description:
 * You can create a delay in milliseconds during execution.
 * @param millisecond = Receives the number of milliseconds for the delay.
 */void Pause(int millisecond){
    clock_t endPause=clock()+millisecond*CLOCKS_PER_SEC/1000;
    while(clock()<endPause){}
}
/**
 * Description:
 * Set another color to the text with an underline.
 * @param CUSTOM_COLOR = Receives the number of the color (15 by default).
 */void BackgroundAndTextColor(const int CUSTOM_COLOR=15){
        /*
        <0 = DEFAULT
         0 = Black      1 = Blue    2 = Green   3 = Cyan    4 = Red
         5 = Purple     6 = Yellow  7 = White   8 = Gray    9 = Light Blue
        10 = Light Green    11 = Light Cyan     12 = Light Red
        13 = Light Purple   14 = Light Yellow   15 = Bright White
        */
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, CUSTOM_COLOR | FOREGROUND_INTENSITY);
}
