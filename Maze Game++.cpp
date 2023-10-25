
    #include<conio.h>
    #include<iostream>
    #include<stdlib.h>
    #include<time.h>
    #include<windows.h>
    using namespace std;


    char  array[39][39] = {};

    int sizeX = 7;
    int sizeY = 7;

    void gotoxy( int x, int y )
    {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void gotozero()
    {
        COORD coord;
        coord.X = 0;
        coord.Y = 0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void hideCursor()
    {
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

        CONSOLE_CURSOR_INFO cursorInfo;

        GetConsoleCursorInfo( out, &cursorInfo );
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo( out, &cursorInfo );
    }

    void printArray()
    {
        int a, i;
        gotoxy(0,0);
            for ( a = 0 ; a < sizeY ; a++ )
            {
                for ( i = 0 ; i < sizeX ; i++ )
                {
                    cout << array[a][i] << " ";
                }
                cout << endl;
            }
    }

    void clearScreen()
    {
        hideCursor();
        int a, i;
        gotoxy(0,0);
            for ( a = 0 ; a < 80 ; a++ )
            {
                for ( i = 0 ; i < 80 ; i++ )
                {
                    cout << " ";
                }
                cout << endl;
            }
    }

    void setSize()
    {
        hideCursor();
        cout << "Odd numbers only, Min= 5; Max= 35" << endl;
        cout << "Please enter X size: ";

        cin >> sizeX;
        sizeX += 4;

        cout << "Please enter Y size: ";
        cin >> sizeY;
        sizeY += 4;

        Sleep(100);

        if ( sizeX % 2 != 1 ){
            sizeX++;
        }
        if ( sizeX < 9 ){
            sizeX = 9;
        }
        if ( sizeX > 39 ){
            sizeX = 39;
        }


        if ( sizeY % 2 != 1 ){
            sizeY++;
        }
        if ( sizeY < 9 ){
            sizeY = 9;
        }
        if ( sizeY > 39 ){
            sizeY = 39;
        }
        cout << endl;
        cout << "Size: " << sizeX-4 << " and " << sizeY-4 <<endl;
        Sleep(1000);

    }

    void setMaze()
    {
        hideCursor();
        int i, j;

        for( i = 2 ; i < sizeY - 2 ; i++ ) /// adding inner walls
        {
            for ( j = 2 ; j < sizeX - 2 ; j+=2 )
            {
                if ( i % 2 == 0 )
                {
                    array[i][j] = ' ';
                    array[i][j+1] = 'o';
                }
                if ( i % 2 == 1 )
                {
                    array[i][j] = 'o';
                    array[i][j+1] = 'o';
                }
            } /// end for j
        } /// end for i

        for ( i = 0 ; i < sizeX ; i++ ) /// Adding walls (#) to edges of X side
        {
            array[0][i] = '#';
            array[1][i] = '#';

            array[sizeY - 1][i] = '#';
            array[sizeY - 2][i] = '#';
        }

        for ( i = 0 ; i < sizeY ; i++ ) /// Adding walls (#) to edges of Y side
        {
            array[i][0] = '#';
            array[i][1] = '#';

            array[i][sizeX - 1] = '#';
            array[i][sizeX - 2] = '#';
        }
    }


    int main()
    {
        srand(time(NULL));
        hideCursor();

        int i, a; /// index variables

        char move;  /// movement side
        int pr = 0; /// to fix a bug
        bool ifCompleted = false;   /// to control if random maze making completed
        bool end = 0;   /// to provide end point location

        char rand1, rand2;  /// random variables

        int dm1=2, dm2=2;   /// array player coordinates
        array[dm1][dm2] = '@';

        setSize();

        clearScreen();

        setMaze();

        //printArray();

        //Sleep(200);

        /// Computer random creating phase---------------------------------------------------------------------------------------------------------

        while ( true )
        {
            //printArray();
            ifCompleted = true;

            cout << endl;
            rand1 = 1 + rand() % 4;
            switch ( rand1 )
            {
                case 1: move = 'w'; break;
                case 2: move = 's'; break;
                case 3: move = 'a'; break;
                case 4: move = 'd'; break;
            }

                switch ( move )
                {
                    case 'w':
                        if ( array[dm1 - 2 ][dm2] == '#' || array[dm1 - 1 ][dm2] == '#' || array[dm1 - 2 ][dm2] == '*' || array[dm1 - 1 ][dm2] == '*' )
                        {
                            break;
                        }

                        array[dm1][dm2] = '*';
                        array[dm1 - 1][dm2] = '*';
                        dm1-=2;

                        array[dm1][dm2] = '@';

                        break;

                    case 's':
                        if ( array[dm1 + 2][dm2] == '#' || array[dm1 + 1][dm2] == '#' || array[dm1 + 2][dm2] == '*' || array[dm1 + 1][dm2] == '*' )
                        {
                            break;
                        }

                        array[dm1][dm2] = '*';
                        array[dm1 + 1][dm2] = '*';
                        dm1+=2;

                        array[dm1][dm2] = '@';

                        break;

                    case 'a':
                        if ( array[dm1][dm2 - 2] == '#' || array[dm1][dm2 - 1] == '#' || array[dm1][dm2 - 2] == '*' || array[dm1][dm2 - 1] == '*' )
                        {
                            break;
                        }

                        array[dm1][dm2] = '*';
                        array[dm1][dm2 - 1] = '*';
                        dm2-=2;

                        array[dm1][dm2] = '@';

                        break;

                    case 'd':
                        if ( array[dm1][dm2 + 2] == '#' ||array[dm1][dm2 + 1] == '#' || array[dm1][dm2 + 2] == '*' ||array[dm1][dm2 + 1] == '*')
                        {
                            break;
                        }

                        array[dm1][dm2] = '*';
                        array[dm1][dm2+1] = '*';
                        dm2+=2;

                        array[dm1][dm2] = '@';

                        break;
                }

                   if ( array[dm1+2][dm2] != ' ' && array[dm1-2][dm2] != ' ' && array[dm1][dm2+2] != ' ' && array[dm1][dm2-2] != ' ' )
                   {

                    rand1 = 1 + rand() % 4;
                    switch ( rand1 )
                    {
                        case 1: move = 'w'; break;
                        case 2: move = 's'; break;
                        case 3: move = 'a'; break;
                        case 4: move = 'd'; break;
                    }


                       if ( move == 'w' && array[dm1 - 2][dm2] == '*' )
                       {
                            array[dm1][dm2] = '*';
                            dm1-=2;

                            array[dm1][dm2] = '@';
                       }

                        if ( move == 's' && array[dm1 + 2][dm2] == '*' )
                       {
                            array[dm1][dm2] = '*';
                            dm1+=2;

                            array[dm1][dm2] = '@';
                       }

                        if ( move == 'd' && array[dm1][dm2+2] == '*' )
                       {
                            array[dm1][dm2] = '*';
                            dm2+=2;

                            array[dm1][dm2] = '@';
                       }

                        if ( move == 'a' && array[dm1][dm2-2] == '*' )
                       {
                            array[dm1][dm2] = '*';
                            dm2-=2;

                            array[dm1][dm2] = '@';
                       }
                   }

                   for ( a = 0 ; a < sizeY ; a++ )
                   {
                       for ( i = 0 ; i < sizeX ; i++ )
                       {
                           if ( array[a][i] == ' ')
                           {
                               ifCompleted = false;
                           }
                       }
                   }

                gotoxy(0,0);
                if ( ifCompleted == true )
                {
                    break;
                }
        } /// end while


        /// Preparing map for player ---------------------------------------------------------------------------------------------------------

            for ( a = 0 ; a < sizeY ; a++ )
            {
                for ( i = 0 ; i < sizeX ; i++ )
                {
                    if ( array[a][i] == '*' )
                    {
                        array[a][i] = ' ';
                    }
                }
            }

            for ( a = 0 ; a < sizeY ; a++ )
            {
                for ( i = 0 ; i < sizeX ; i++ )
                {
                    if ( array[a][i] == 'o' )
                    {
                        array[a][i] = '#';
                    }
                }
            }

        clearScreen();
        gotoxy(0,0);
        cout << "Game created!" << endl;
        Sleep(200);
        cout << "\aNew Game Starting" << endl;
        Sleep(500);

        /// Player phase -----------------------------------------------------------------------------------------------------------

        array[dm1][dm2] = ' ';

        dm1=2;
        dm2=2;

        array[dm1][dm2] = '@';

        rand1 = ( 2 + rand() % ( sizeY - 4 ) );
        rand2 = ( 2 + rand() % ( sizeX - 4 ) );

        while( array[rand1][rand2] == '#' || array[rand1][rand2] == '@')
        {
            rand1 = ( 2 + rand() % ( sizeY - 4 ) );
            rand2 = ( 2 + rand() % ( sizeX - 4 ) );
        }

        array[rand1][rand2] = '*';

        while ( move != 'q' )
        {

            printArray();

            if ( dm1 == sizeY - 3 && dm2 == sizeX - 1 )
            {
                //clearScreen();
                //gotozero();
                cout << "\n\n\aYou done it!" << endl;

                Sleep(1500);
                break;
            }

            if ( rand1 == dm1 && rand2 == dm2 && pr == 0 )
            {
                array[sizeY - 3][sizeX - 2] = ' ';
                array[sizeY - 3][sizeX - 1] = 'F';
                pr++;
                end = true;

                printArray();
            }

            if ( end == true )
                cout << "\nYou have opened the end point!\Go there\n" << endl;

            cout << "Play with w,a,s,d.\nPress q to quit game.\n" << endl;
            cout << "Move: " << endl;

            move = getch();

            switch ( move )
            {
                case 'w':
                    if ( array[dm1 - 1 ][dm2] == '#' )
                        break;

                    array[dm1][dm2] = ' ';
                    dm1--;
                    array[dm1][dm2] = '@';
                    break;

                case 's':
                    if ( array[dm1 + 1][dm2] == '#' )
                        break;

                    array[dm1][dm2] = ' ';
                    dm1++;
                    array[dm1][dm2] = '@';
                    break;

                case 'a':
                    if ( array[dm1][dm2 - 1] == '#' )
                        break;

                    array[dm1][dm2] = ' ';
                    dm2--;
                    array[dm1][dm2] = '@';
                    break;

                case 'd':
                    if ( array[dm1][dm2 + 1] == '#' )
                        break;

                    array[dm1][dm2] = ' ';
                    dm2++;
                    array[dm1][dm2] = '@';
                    break;
            }
        }

        cout << endl;
        cout << "\nSee you later" << endl;

        return 0;
    }
