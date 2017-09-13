#include <iostream>
//
using namespace std;

int main()
{
    bool menu = true;
    int opcao = 3;
    double x, y;
    cout << "1 - X" << endl
         << "2 - Y" << endl
         << "3 - sair" << endl;
    cin >> opcao;
    while (true)
    {
        switch (opcao)
        {
        case 1:
            cout << "Digite o X" << endl;
            cin >> x;
            cout << (2 * x + 100) << endl;
            cin >> opcao;            
            break;
        case 2:
            cout << "Digite o Y" << endl;
            cin >> y;
            cout << (1.125 * y + 112.5 - 100) << endl;
            cin >> opcao;            
            break;
        case 3:
            menu = false;
            break;
        default:
            cout << "1 - X" << endl
                 << "2 - Y" << endl
                 << "3 - sair" << endl;
            cin >> opcao;
            break;
        }
    }
    return 0;
}
