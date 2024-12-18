#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std;

// Definici�n de constantes y variables //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int MaxCandidatos = 5;
const int MaxLongitud = 50;
const int MaxVotantes = 11;
char Candidatos[2][MaxLongitud][MaxCandidatos]; 
int Votos[MaxCandidatos] = {0};
int TotalVotosRegistrados = 0;
string CedulasRegistradas[MaxVotantes];

// Verificar si la c�dula ya ha votado ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CedulaYaVoto(const string& Cedula) {
    for (int i = 0; i < MaxVotantes; i++) {
        if (CedulasRegistradas[i] == Cedula) {
            return true;
        }
    }
    return false;
}

// Registrar candidatos ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RegistrarCandidatos(int &NumCandidatos) {
    char Continuar;
    while (NumCandidatos < MaxCandidatos) {
        cout << "\nIngrese el nombre del candidato " << (NumCandidatos + 1) << ": ";
        cin.ignore();
        cin.getline(Candidatos[0][NumCandidatos], MaxLongitud);

        cout << "Ingrese el partido del candidato " << (NumCandidatos + 1) << ": ";
        cin.getline(Candidatos[1][NumCandidatos], MaxLongitud);

        Votos[NumCandidatos] = 0;
        NumCandidatos++;

        cout << "�Desea registrar otro candidato? (s/n): ";
        cin >> Continuar;

        if (Continuar == 'n' || Continuar == 'N') {
            break;
        }
    }
    if (NumCandidatos == MaxCandidatos) {
        cout << "Se ha alcanzado el n�mero m�ximo de candidatos (" << MaxCandidatos << ").\n";
    }
}

// Registrar votos ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RegistrarVotos(int NumCandidatos) {
	
    if (TotalVotosRegistrados >= MaxVotantes) {
        cout << "Se ha alcanzado el m�ximo de votos permitidos (" << MaxVotantes << ").\n";
        return;
    }

    string Cedula;
    cout << "Ingrese su c�dula para votar: ";
    cin >> Cedula;

    if (CedulaYaVoto(Cedula)) {
        cout << "La c�dula ingresada ya ha votado.\n";
        return;
    }

    string Entrada;
    int Opcion;
    cout << "\nSeleccione el n�mero del candidato para votar:\n";
    for (int i = 0; i < NumCandidatos; i++) {
        cout << i + 1 << ". " << Candidatos[0][i] << " (" << Candidatos[1][i] << ")\n";
    }
    cout << "Opci�n: ";
    cin >> Entrada;


    if (Entrada.size() == 1 && isdigit(Entrada[0])) {
        Opcion = Entrada[0] - '0'; 
        if (Opcion > 0 && Opcion <= NumCandidatos) {
            Votos[Opcion - 1]++;
            CedulasRegistradas[TotalVotosRegistrados++] = Cedula;
            cout << "Voto registrado para " << Candidatos[0][Opcion - 1] << ".\n";
        } else {
            cout << "Opci�n inv�lida.\n";
        }
    } else {
        cout << "Digite una opci�n v�lida.\n";
    }
}

// Mostrar las estad�sticas y empates ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MostrarEstadisticas(int NumCandidatos) {
    int TotalVotos = 0;
    for (int i = 0; i < NumCandidatos; i++) {
        TotalVotos += Votos[i];
    }

    cout << "\nEstad�sticas de la elecci�n:\n";
    for (int i = 0; i < NumCandidatos; i++) {
        double Porcentaje = (TotalVotos > 0) ? (static_cast<double>(Votos[i]) / TotalVotos) * 100 : 0;
        cout << Candidatos[0][i] << " (" << Candidatos[1][i] << "): "
             << Votos[i] << " votos (" << fixed << setprecision(2) << Porcentaje << "%)\n";
    }

    int MaxVotos = 0;
    for (int i = 0; i < NumCandidatos; i++) {
        if (Votos[i] > MaxVotos) {
            MaxVotos = Votos[i];
        }
    }

    cout << "\nGanador(es): ";
    bool HayEmpate = false;
    for (int i = 0; i < NumCandidatos; i++) {
        if (Votos[i] == MaxVotos) {
            if (HayEmpate) {
                cout << " y ";
            }
            cout << Candidatos[0][i] << " del partido " << Candidatos[1][i];
            HayEmpate = true;
        }
    }
    cout << " con " << MaxVotos << " votos.\n";
}

// Funci�n principal /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    int NumCandidatos = 0;
    int Opcion;

    do {
        cout << "\nSistema de Votaciones\n";
        cout << "1. Registrar Candidato\n";
        cout << "2. Registrar Votos\n";
        cout << "3. Estad�sticas\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opci�n: ";
        cin >> Opcion;

        switch (Opcion) {
            case 1:
                RegistrarCandidatos(NumCandidatos);
                break;
            case 2:
                RegistrarVotos(NumCandidatos);
                break;
            case 3:
                MostrarEstadisticas(NumCandidatos);
                break;
            case 0:
                cout << "Saliendo del sistema.\n";
                break;
            default:
                cout << "Opci�n inv�lida. Intente de nuevo.\n";
                break;
        }
    } while (Opcion != 0);

    return 0;
}


