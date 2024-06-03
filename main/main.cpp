#include <iostream>

using namespace std;

void definindoValores(float matrix[][3], float* d) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << "Informe o valor do vetor na posicao (" << i+1 << ", " << j+1 << "): ";
            cin >> matrix[i][j];
            system("cls");
        }
        cout << "Informe o valor de d" << i+1 << ": ";
        cin >> d[i];
        system("cls");
    }
    for(int i = 0; i < 3; i++) {
        cout << "| ";
        for(int j = 0; j < 3; j++) {
            cout << matrix[i][j] << (j == 0 ? "x" : j == 1 ? "y" : "z") << (j < 2 ? " +" : "") << " ";
        }
        cout << "|= " << d[i] << "\n";
    }
    system("pause");
    system("cls");
}

bool convergencia(float matrix[][3]) {
    float b[3], maiorValor;
    b[0] = (matrix[0][1] + matrix[0][2])/matrix[0][0];
    b[1] = ((matrix[1][0] * b[0]) + matrix[1][2])/matrix[1][1];
    b[2] = ((matrix[2][0] * b[0]) + (matrix[2][1] * b[1]))/matrix[2][2];
    b[0] < 0 ? b[0] *= -1 : b[0];
    b[1] < 0 ? b[1] *= -1 : b[1];
    b[2] < 0 ? b[2] *= -1 : b[2];
    if(b[0] > b[1] && b[0] > b[2]) {
        maiorValor = b[0];
    } else if(b[1] > b[0] && b[1] > b[2]) {
        maiorValor = b[1];
    } else {
        maiorValor = b[2];
    }
    if(maiorValor < 1) {
        cout << maiorValor << " < 1 = " << "CONVERGE";
        return true;
    } else {
        cout << maiorValor << " >= 1 = " << "NAO CONVERGE";
        return false;
    }
}

void solucaoInicialFuncao(float matrix[][3], float* d, float solucaoInicial[][10]) {
    for(int i = 0; i < 3; i++) {
        solucaoInicial[i][0] = d[i]/matrix[i][i];
    }
    for(int i = 0; i < 3; i++) {
        cout << "| " << solucaoInicial[i][0] << " |\n";
    }
    system("pause");
    system("cls");
}

void condicaoParada(float matrix[][3], float* d, float solucaoInicial[][10], float e, int k) {
    cout << k+1 << " Iteracao\n";
    for(int i = 0; i < 3; i++) {
        cout << "| " << solucaoInicial[i][k] << " |\n";
    }
    system("cls");
    solucaoInicial[0][k+1] = (d[0] - matrix[0][1] * solucaoInicial[1][k] - matrix[0][2] * solucaoInicial[2][k])*(1/matrix[0][0]);
    solucaoInicial[1][k+1] = (d[1] - matrix[1][0] * solucaoInicial[0][k+1] - matrix[1][2] * solucaoInicial[2][k])*(1/matrix[1][1]);
    solucaoInicial[2][k+1] = (d[2] - matrix[2][0] * solucaoInicial[0][k+1] - matrix[2][1] * solucaoInicial[1][k+1])*(1/matrix[2][2]);
    float x = solucaoInicial[0][k+1], y = solucaoInicial[1][k+1], z = solucaoInicial[2][k+1], er, maiorValor;
    x < 0 ? x *= -1 : x;
    y < 0 ? y *= -1 : y;
    z < 0 ? z *= -1 : z;
    if(x > y && x > z) {
        maiorValor = x;
    } else if(y > x && y > z) {
        maiorValor = y;
    } else {
        maiorValor = z;
    }
    x = solucaoInicial[0][k+1] - solucaoInicial[0][k];
    y = solucaoInicial[1][k+1] - solucaoInicial[1][k];
    z = solucaoInicial[2][k+1] - solucaoInicial[2][k];
    x < 0 ? x *= -1 : x;
    y < 0 ? y *= -1 : y;
    z < 0 ? z *= -1 : z;
    if(x > y && x > z) {
        er = x/maiorValor;
    } else if(y > x && y > z) {
        er = y/maiorValor;
    } else {
        er = z/maiorValor;
    }
    if(er > e) {
        condicaoParada(matrix, d, solucaoInicial, e, k+1);
    } else {
        cout << er << " <= " << e << endl;
        for(int i = 0; i < 3; i++) {
            cout << "| " << solucaoInicial[i][k+1] << " |\n";
        }
        return;
    }
}

int main()
{
    float d[3];
    float matrix[3][3];
    float solucaoInicial[3][10];

    definindoValores(matrix,d);

    if(convergencia(matrix)) {
        system("pause");
        system("cls");
        solucaoInicialFuncao(matrix, d, solucaoInicial);
        condicaoParada(matrix, d, solucaoInicial, 0.05, 0);
    }

    return 0;
}
