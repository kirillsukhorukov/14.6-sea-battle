#include <iostream>

using namespace std;

//Объявление глобальной переменной размерности поля игроков
int N=10;
//Объявление глобальных двумерных массивов полей двух игроков
bool field_1[10][10];
bool field_2[10][10];

//Процедура инициализации массива пупырки
void init_array()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            field_1[i][j] = false;
            field_2[i][j] = false;
        }
    }
}
//Процедура вывода двумерного массива
void print_array (const bool (&array) [10][10], const char &player)
{
    cout << "Player " << player << " view of your field:" << endl;
    cout << "  ";
    for (int x=0; x<N; x++) cout << x << ' ';
    cout << endl;
    for (int i=0; i<N; i++)
    {
        cout << i << ' ';
        for (int j=0; j<N; j++)
        {
            (array[i][j]) ? cout << 'X' << ' ' : cout << 'O' << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

//Функция проверки введенных координат
bool coordinate_check (int &x1, int &y1, int &x2, int &y2)
{
    //Проверка координат на возрастание и их перестановка в случае необходимости
    if (x2-x1<0 || y2-y1<0)
    {
        swap (x1,x2);
        swap (y1,y2);
    }
    //Проверка координат на выход за пределы игрового поля
    if (x1<0 || x1>N-1 || y1<0 || y1>N-1)
    {
        cout << "The first coordinate is outside the field. Enter the coordinates again."<< endl;
        return true;
    }
    if (x2<0 || x2>N-1 || y2<0 || y2>N-1)
    {
        cout << "The second coordinate is outside the field. Enter the coordinates again."<< endl;
        return true;
    }
    //Проверка на диаганальность
    if (x1!=x2 && y1!=y2)
    {
        cout << "Installing a ship diagonally is not allowed! Enter the coordinates again."<< endl;
        return true;
    }
    return false;
}

//Функция установки корабля
bool ship_installation (bool (&array)[10][10], const int &x1, const int &y1, const int &x2, const int &y2)
{

    for (int i=y1; i<=y2; i++)
    {
        for (int j=x1; j<=x2; j++)
        {
            if (!array[i][j]) array[i][j] = true;
            else
            {
                cout << "The place on the field is occupied! Enter the coordinates again." << endl;
                return true;
            }

        }
    }
    return false;
}

//Процедура расстановки кораблей
void arrangement_ships (const char &player, bool (&array)[10][10])
{
    //Инициализация переменных координат
    int x1, y1, x2, y2;

    //Расстановка однопалубных кораблей
    for (int i=1; i<5; i++)
    {
        //Выводим поле игрока
        print_array(array,player);
        //Инициализация флага ошибки ввода
        bool check;
        //Ввод координат
        do
        {
            cout << "Enter the coordinate of " << i << " single-deck ship: ";
            cin >> x1 >> y1;
            check = coordinate_check(x1, y1, x1, y1);
            if (!check) check = ship_installation(array,x1,y1,x1,y1);
        } while(check);
    }

    //Расстановка двухпалубных кораблей
    for (int i=1; i<4; i++)
    {
        //Выводим поле игрока
        print_array(array,player);
        //Инициализация флага ошибки ввода
        bool check;
        //Ввод координат
        do
        {
            cout << "Enter the coordinates of " << i << " double-deck ship:" << endl;
            cout << "Ship start coordinate: ";
            cin >> x1 >> y1;
            cout << "End of ship coordinate: ";
            cin >> x2 >> y2;
            check = coordinate_check(x1, y1, x2, y2);
            if (!check)
            {
                //Проверка корабля на палубность
                if (x2-x1==1 ^ y2-y1==1) check = ship_installation(array,x1,y1,x2,y2);
                else
                {
                    cout << "The ship is not double-deck! Enter the coordinates again."<< endl;
                    check = true;
                }
            }
        } while(check);
    }

    //Расстановка трехпалубных кораблей
    for (int i=1; i<3; i++)
    {
        //Выводим поле игрока
        print_array(array,player);
        //Инициализация флага ошибки ввода
        bool check;
        //Ввод координат
        do
        {
            cout << "Enter the coordinates of " << i << " three-deck ship:" << endl;
            cout << "Ship start coordinate: ";
            cin >> x1 >> y1;
            cout << "End of ship coordinate: ";
            cin >> x2 >> y2;
            check = coordinate_check(x1, y1, x2, y2);
            if (!check)
            {
                //Проверка корабля на палубность
                if (x2-x1==2 ^ y2-y1==2) check = ship_installation(array,x1,y1,x2,y2);
                else
                {
                    cout << "The ship is not three-deck! Enter the coordinates again."<< endl;
                    check = true;
                }
            }
        } while(check);
    }

    //Установка четырехпалубного корабля
    //Выводим поле игрока
    print_array(array,player);
    //Инициализация флага ошибки ввода
    bool check;
    //Ввод координат
    do
    {
        cout << "Enter the coordinates of four-deck ship:" << endl;
        cout << "Ship start coordinate: ";
        cin >> x1 >> y1;
        cout << "End of ship coordinate: ";
        cin >> x2 >> y2;
        check = coordinate_check(x1, y1, x2, y2);
        if (!check)
        {
            //Проверка корабля на палубность
            if (x2-x1==3 ^ y2-y1==3) check = ship_installation(array,x1,y1,x2,y2);
            else
            {
                cout << "The ship is not four-deck! Enter the coordinates again."<< endl;
                check = true;
            }
        }
    } while(check);
    print_array(array,player);
}

//Функция хода игрока
bool shot (bool (&array)[10][10], const int &x, const int &y)
{
    //Проверка на попадание
    if (array[y][x])
    {
        cout << "HIT!" << endl;
        array[y][x]= false;
    }
    else cout << "MISS!" << endl;

    //Проверка игрового поля на окончание игры
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            if (array[i][j]) return false;
        }
    }
    return true;
}

int main() {

    cout << "------------SEA BATTLE------------\n" << endl;

    //Инициализация массива пупырки с помощью процедуры
    init_array();

    arrangement_ships('1',field_1);
    arrangement_ships('2',field_2);

    cout << "------------The battle begins------------\n" << endl;

    //Инициализация переменной номера игрока
    char player='2';

    //Инициализация конца игры
    bool endGame=false;

    //Организация цикла игры
    while (!endGame)
    {
        //Определение и смена имени игрока
        if (player == '2')
        {
            player = '1';
            print_array(field_1,player);
        }
        else
        {
            player = '2';
            print_array(field_2,player);
        }

        //Инициализация координат игрового поля
        int x, y;

        //Ввод координат хода
        do
        {
            cout << "Player " << player << " enter move coordinates: ";
            cin >> x >> y;
        } while(x<0 || x>N-1 || y<0 || y>N-1);

        //Ход игрока
        if (player == '1') endGame=shot(field_2,x,y);
        else endGame=shot(field_1,x,y);
    }

    cout << "Player " << player << " WINS!" << endl;
    cout << "GAME OVER!";

    return 0;
}
