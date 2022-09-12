#include <iostream>
#include <fstream>
#define CODIGO_PRODUCTO 5
#define CODIGO_CLIENTE 8

using namespace std;

void listarPorPeso(
    string nombreProducto[],
    string nombreCliente[],
    float peso[][CODIGO_PRODUCTO],
    int cantidad[])
{
    cout << "Listado por clientes, de los tipos de productos que superen los 13000 Kg acumulados:" << endl;

    for (int i = 0; i < CODIGO_CLIENTE; i++)
    {
        cout << nombreCliente[i] << ":\t";

        for (int j = 0; j < CODIGO_PRODUCTO; j++)
        {
            if (peso[i][j] > 13000)
            {
                cout << nombreProducto[j] << ", \t";
                cantidad[i] += 1;
            }
        }

        cout << endl;
    }
}

int obtenerPosicionMayor(
    int conteoCliente[])
{
    int mayor = conteoCliente[0];
    int posicion = 0;

    for (int i = 0; i < CODIGO_CLIENTE; i++)
    {
        if (conteoCliente[i] > mayor)
        {
            mayor = conteoCliente[i];
            posicion = i;
        }
    }

    return posicion;
}

void listarKmRecorridoPorTipoDeProducto(
    string nombreProducto[],
    int conteoCliente[],
    int seg[],
    float km[][CODIGO_PRODUCTO])
{
    int pos = obtenerPosicionMayor(conteoCliente);

    cout << endl
         << "Listado de Km recorridos por tipo de producto:" << endl;

    int n;
    float temp = 0;

    do
    {
        n = 0;

        for (int i{1}; i < CODIGO_PRODUCTO; i++)
        {
            if (km[pos][i - 1] < km[pos][i])
            {
                temp = km[pos][i - 1];
                km[pos][i - 1] = km[pos][i];
                km[pos][i] = temp;
                n++;

                temp = seg[i - 1];
                seg[i - 1] = seg[i];
                seg[i] = temp;
            }
        }
    } while (n != 0);

    for (int i = CODIGO_PRODUCTO - 1; i >= 0; i--)
    {
        cout << nombreProducto[seg[i]] << '\t' << km[pos][i] << " km" << endl;
    }
}

void informarEntregasProducto(
    string nombreProducto[],
    int cantidadDeEntregas[][CODIGO_PRODUCTO],
    int seguimiento[],
    int conteoCliente[])
{
    int cantidadEntregas = 0;

    cout << endl
         << "Cantidad de entregas para el tipo de producto de " << nombreProducto[seguimiento[0]] << ": ";

    for (int i = 0; i < CODIGO_CLIENTE; i++)
    {

        if (i == obtenerPosicionMayor(conteoCliente))
        {
            cantidadEntregas += cantidadDeEntregas[i][0];
        }
        else
        {
            cantidadEntregas += cantidadDeEntregas[i][seguimiento[0]];
        }
    }

    cout << cantidadEntregas;
}

int main()
{
    string nombreCliente[CODIGO_CLIENTE];
    string nombreProducto[CODIGO_PRODUCTO];
    float cantidadKm[CODIGO_CLIENTE][CODIGO_PRODUCTO]{0};
    float cantidadPeso[CODIGO_CLIENTE][CODIGO_PRODUCTO]{0};
    int conteoCliente[CODIGO_CLIENTE]{0};
    int seguimiento[CODIGO_PRODUCTO] = {0, 1, 2, 3, 4};
    int cantidadEntregas[CODIGO_CLIENTE][CODIGO_PRODUCTO]{0};

    ifstream archivoNombres;

    archivoNombres.open("Nombres.txt");

    if (!archivoNombres)
    {
        cout << " Ha ocurrido un error al intentar abrir el archivo de nombres.";
        return 0;
    }

    for (int i = 0; i < CODIGO_CLIENTE; i++)
    {
        archivoNombres >> nombreCliente[i];
    }

    for (int i = 0; i < CODIGO_PRODUCTO; i++)
    {
        archivoNombres >> nombreProducto[i];
    }

    archivoNombres.close();

    ifstream archivoDatos;
    archivoDatos.open("Datos.txt");

    if (!archivoDatos)
    {
        cout << "Ha ocurrido un error al intentar abrir el archivo de datos.";
        return 0;
    }

    float tipoKg, tipoKm = 0;
    int tipocliente, tipoProducto = 0;

    while (archivoDatos >> tipocliente >> tipoProducto >> tipoKg >> tipoKm)
    {
        cantidadEntregas[tipocliente][tipoProducto] += 1;
        cantidadPeso[tipocliente][tipoProducto] += tipoKg;
        cantidadKm[tipocliente][tipoProducto] += tipoKm;
    }

    archivoDatos.close();

    listarPorPeso(nombreProducto, nombreCliente, cantidadPeso, conteoCliente);
    listarKmRecorridoPorTipoDeProducto(nombreProducto, conteoCliente, seguimiento, cantidadKm);
    informarEntregasProducto(nombreProducto, cantidadEntregas, seguimiento, conteoCliente);

    return 0;
}
